#include "types.h"
#include "memlayout.h"
#include "alloc.h"
#include "disk.h"
#include "printf.h"
#include "proc.h"
#include "vm.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "string.h"

#define ADDR2FBLOCK(addr) ((addr) / (BLOCK_SIZE))
#define ADDR2OFF(addr) ((addr) % (BLOCK_SIZE))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

struct bcache bcache_list;
struct icache icache_list;
struct fcache fcache_list;

// Init bcache, by setting all buffers as free
void binit(){
    spinlockinit(&bcache_list.lk,"bcahce list");
    struct buf* b;
    for (b = &bcache_list.array[0]; b < &bcache_list.array[NBUF]; b++){
        sleeplockinit(&b->slk,"buf sleeplock");
        b->refcnt = 0;
        b->valid = 0;
    }
    return;
}

// Acquire a buffer for block [blk]
// the buffer is locked (sleeplock of the buffer)
// panic on failure
struct buf * bacquire(uint64 blk){
    struct buf * b;
    acquire(&bcache_list.lk);

    // Case 1 : buf blk exists
    for (b = bcache_list.array; b <= &bcache_list.array[NBUF]; b++){
        if (b->blk == blk){
            b->refcnt++;
            release(&bcache_list.lk);
            acquiresleep(&b->slk);
            return b;
        }
    }
    // Case 2 : buf blk does not exist, need to allocate a new one
    for (b = bcache_list.array; b <= &bcache_list.array[NBUF]; b++){
        if (b->refcnt == 0){
            b->blk = blk;
            b->refcnt = 1;
            // No need to lock sleeplock as no one is supposed to used the data field
            b->valid = 0;
            release(&bcache_list.lk);
            acquiresleep(&b->slk);
            return b;
        }
    }
    panic("No buffer cache available\n");
}

// Release buffer [b]
// must be called with b->slk locked
void brelease(struct buf* b){
    releasesleep(&b->slk);
    acquire(&bcache_list.lk);
    if (b->refcnt == 0){
        panic("Buffer ref is 0! Impossible to free!\n");
    }
    b->refcnt--;
    release(&bcache_list.lk);
    return;
}

// Return a locked buffer with the content of block [blk]
// Lock must be release with call to **brelease()**
struct buf * bread(uint64 blk){
    struct buf * b = bacquire(blk); // we get the sleeplock
    if (b->valid == 1){
        return b;
    } else {
        diskrequest(VIRTIO_BLK_T_IN,b);
        b->valid = 1;
    }    
    return b;
}

// Return a locked buf with the content of file block number [fbn] of inode [i]
struct buf * fbread(struct inode* i,uint64 fbn){
    uint64 blk;
    if (NADDR <= fbn){
        struct buf * b = bread(i->di.data[NADDR]);
        fbn -= NADDR;
        blk = ((inodeent*) b->data)[fbn];
        brelease(b);
    } else {
        blk = i->di.data[fbn];
    }
    return bread(blk);
}

// Init inode_list
void iinit(){
    spinlockinit(&icache_list.lk,"icache list");
    struct inode* in;
    for (in = &icache_list.array[0]; in < &icache_list.array[NIN]; in++){
        sleeplockinit(&in->slk,"inode sleeplock");
        in->ref = 0;
        in->valid = 0;
    }
    return;
}

// Acquire an inode for inum [inum]
// the inode is locked
struct inode* iacquire(uint16 inum){
    acquire(&icache_list.lk);

    struct inode* in;

    for (in = icache_list.array; in <= &icache_list.array[NIN]; in++){
        if(in->inum == inum){
            in->ref ++;
            release(&icache_list.lk);
            acquiresleep(&in->slk);
            return in;
        }
    }
    for (in = icache_list.array; in <= &icache_list.array[NIN]; in++){
        if(in->ref == 0){
            in->inum = inum;
            in->ref++;
            in->valid = 0;
            release(&icache_list.lk);
            acquiresleep(&in->slk);
            return in;
        }
    }
    panic("No inode vailable\n");
}

// Release inode [in]
// must be called with in->slk locked
void irelease(struct inode* in){
    releasesleep(&in->slk);

    acquire(&icache_list.lk);
    if(in->ref == 0){
        panic("Cannot free inode, no ref\n");
    }
    in->ref--;
    release(&icache_list.lk);
    return;
}

// Fillup inode number [inum]
// the inode is locked!
struct inode * iopen(uint16 inum){
    struct inode * in = iacquire(inum); // sleeplock locked!
    if(in->valid == 1){
        return in;
    }
    else {
        uint64 blk = IBLOCK(inum);
        uint32 off = IBLOCKOFF(inum);

        struct buf * b = bread(blk); // locked
        memcpy(&in->di,&((struct dinode *) b->data)[off],sizeof(struct dinode));
        brelease(b);
        return in;
        
    }
}

// Read from inode [in], [sz] bytes maximum starting from [off] into data buffer [buffer]
// return the number of read bytes
// Must be called with sleeplock in->slk locked
// Lock must be release with call to **irelease()**
uint32 iread(struct inode* in,uint32 off, uint32 sz, uint8* buffer){
    
    uint32 tot = 0;

    // Resize sz to be in the file
    if (in->di.size < off){
        sz = 0;
    } else {
        sz = min(sz,(in->di.size - off));
    }

    while(sz > 0){
        uint32 fbn = ADDR2FBLOCK(off);
        uint32 fbn_off = ADDR2OFF(off);
        uint32 nb = min(sz,(BLOCK_SIZE) - fbn_off);
        struct buf * b = fbread(in,fbn);

        memcpy(buffer+tot,b->data + fbn_off,nb);
        brelease(b);

        sz -= nb;
        off += nb;
        tot += nb;
    };
    return tot;
}

// Return the inode number of file [name]
// return -1 on failure
uint16 find(uint8* name){
    // TODO : Make sure it is a directory
    struct inode * inroot = iopen(0); // locked!
    uint32 sz = inroot->di.size;
    uint32 off=0;
    struct dirent dent;

    while(iread(inroot,off,sizeof(struct dirent),(uint8*) &dent) == sizeof(struct dirent)){
        off += sizeof(struct dirent);
        if(!strcmp(name,dent.name)){
            irelease(inroot);
            return dent.inum;
        }
    }
    irelease(inroot);
    return -1;   
}

// Init file list
void finit(){
    spinlockinit(&fcache_list.lk,"fcache list");
    struct file* f;
    for(f = &fcache_list.array[0]; f < &fcache_list.array[NFILE]; f++){
        sleeplockinit(&f->slk,"file sleeplock");
        f->ref = 0;
    }
    return;
}

// Acquire an available file in the file list
// panic on failure
struct file * facquire(){
    acquire(&fcache_list.lk);
    for(struct file* f = fcache_list.array; f <= &fcache_list.array[NFILE]; f++){
        if(f->ref == 0){
            f->ref++;
            release(&fcache_list.lk);
            return f;
        }
    }
    panic("No file available\n");
}

// Free file [f]
void frelease(struct file* f){
    acquire(&fcache_list.lk);
    if (f->ref == 0){
        panic("Cannot free file, ref is 0\n");
    }
    f->ref --;
    release(&fcache_list.lk);
    return;
}

// Init array of open files of proc [p]
void ofinit(struct proc* p){
    for(uint32 i = 0; i < NOFILE; i++){
        p->ofile[i] = 0;
    }
    return;
}

// Acquire file descriptor [fd]
// panic on failure
uint32 ofalloc(){
    struct proc* p = myproc();
    struct file* f;
    for(uint32 i = 0; i < NOFILE; i++){
        if(p->ofile[i] == 0){
            return i;
        }
    }
    panic("No openfile available\n");
}

// Release file descriptor [fd]
void ofdalloc(uint32 fd){
    struct proc* p = myproc();
    p->ofile[fd] = 0;
    return;
}

// Init fs
void fsinit(){
    binit();
    iinit();
    finit();
}