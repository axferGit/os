#include "types.h"
#include "memlayout.h"
#include "alloc.h"
#include "disk.h"
#include "printf.h"

#define ADDR2BLOCK(addr) ((addr) / (BLOCK_SIZE))
#define ADDR2OFF(addr) ((addr) % (BLOCK_SIZE))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))


struct buf bcache [NBUF];
struct inode inode_list [NINODE * IPB];

// Return a free buf from cache buffers list
struct buf * getb(){
    return &bcache[0];
}

// Cretae a cache buffer with request type [t_rqt] and block number [blk]
// return nothing
void createb(struct buf * b, uint8 t_rqt, uint32 blk){
    b->blk = blk;
    b->status = t_rqt;
    return;
}

// Read block number [blk] inot a buffer
// return the buffer
struct buf * readb(uint64 blk){
    struct buf * b = getb();
    createb(b,VIRTIO_BLK_S_UNDEF,blk);
    diskrequest(VIRTIO_BLK_T_IN,b);
    return b;
}


// Read from inode [i] [sz] bytes maximum starting from [off] into data buffer [buffer]
// return the number of bytes read
uint32 readi(struct inode* i,uint32 off, uint32 sz, uint8* buffer){
    struct buf * b;
    uint32 tot = 0;

    // Resize sz to be in the file
    if (i->di.size < off){
        sz = 0;
    } else {
        sz = min(sz,(i->di.size - off));
    }
    printf("sz: %i\n",sz);
   
    while(sz > 0){
        uint32 fbn = ADDR2BLOCK(off);
        uint32 fbn_off = ADDR2OFF(off);
        uint32 nb = min(sz,(BLOCK_SIZE) - fbn_off);
        b = readb(i->di.data[fbn]);
        
        memcpy(buffer+tot,b->data + fbn_off,nb);

        sz -= nb;
        off += nb;
        tot += nb;
    };

    return tot;
}

// Retrurn a pointer to a free structure inside inode list
struct inode* geti(){
    return &inode_list[0];
}

// Open inode [inum] to an inode strcuture
// return a pointer to this strcuture
struct inode * openi(uint16 inum){
    struct inode * in = geti();
    uint64 blk = IBLOCK(inum);
    uint32 off = IBLOCKOFF(inum);
    struct buf * b = readb(blk);
    memcpy(&in->di,&((struct dinode *) b->data)[off],sizeof(((struct dinode *) b->data)[off]));
    return in;
}


