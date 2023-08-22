#include "types.h"
#include "memlayout.h"
#include "alloc.h"
#include "disk.h"
#include "printf.h"
#include "proc.h"
#include "vm.h"

#define ADDR2FBLOCK(addr) ((addr) / (BLOCK_SIZE))
#define ADDR2OFF(addr) ((addr) % (BLOCK_SIZE))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))


struct buf bcache [NBUF];
struct inode inode_list [NINODE * IPB];
struct file file_list [NFILE];

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

// Read block number [blk] into a buffer
// return the buffer
struct buf * readb(uint64 blk){
    struct buf * b = getb();
    createb(b,VIRTIO_BLK_S_UNDEF,blk);
    diskrequest(VIRTIO_BLK_T_IN,b);
    return b;
}

// Read the data block with file block number [fbn] in inode [i]
struct buf * readfb(struct inode* i,uint64 fbn){
    uint64 blk;
    if (NADDR <= fbn){
        struct buf * b = readb(i->di.data[NADDR]);
        fbn -= NADDR;
        blk = ((inodeent*) b->data)[fbn];
    } else {
        blk = i->di.data[fbn];
    }
    return readb(blk);
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

    while(sz > 0){
        uint32 fbn = ADDR2FBLOCK(off);
        uint32 fbn_off = ADDR2OFF(off);
        uint32 nb = min(sz,(BLOCK_SIZE) - fbn_off);


        b = readfb(i,fbn);
        
        memcpy(buffer+tot,b->data + fbn_off,nb);

        sz -= nb;
        off += nb;
        tot += nb;
    };

    return tot;
}

// Retrurn a pointer to a free structure inside inode list
struct inode* geti(){
    return &(inode_list[0]);
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

uint32 strcmp(uint8* s1, uint8* s2){
    if (s1[0] == s2[0]){
        if(s1[0] == 0){
            return 0;
        } else {
            return strcmp(s1+1,s2+1);
        }
    } else {
        return -1;
    }
}


// Return the inode number of file [name]
// return -1 on failure
uint16 find(uint8* name){
    // TOSO : Make sure it is a directory
    struct inode * inroot = openi(0);
    uint32 sz = inroot->di.size;
    uint32 nb=0;
    struct dirent dent;

    while(readi(inroot,nb,sizeof(struct dirent),(uint8*) &dent) == sizeof(struct dirent)){
        nb+=sizeof(struct dirent);
        if(!strcmp(name,dent.name)){
            return dent.inum;
        }
    }
    return -1;   
}

// Return a pointer to an available file in the file list
struct file * getfile(){
    return &file_list[0];
}

// return an free file destriptor
uint32 getofile(){
    return 0;
}


/*
int fd = open("README.md",O_RO);

>>> SYS call
sys_open(){
    char* name [NCHAR];
    cpstruser(name,argn(0)) // copy string from user land to kernel land
    int inum = find(name)
    if (inum !=-1){
        sqtruct proc * p = myproc();
        struct file* f = getfile();
        f->off = 0;
        f->in  = openi(inum); 
        int f = getfile();
        uint32 fd = getofile();
        p->ofile[fd] = f; //TODO : clean way to find available slot in open files
        p->trapframe->a0 = fd;
    }
    else {
        printf("error :can not find file");
    }
    return;
}

sys_read(){
    uint32 fd = (uint32) argn(0);
    uint8* buf = (uint8*) argn(1);
    uint32 n = (uint32) argn(2);

    struct proc* p = myproc(){
        struct file f * = p->ofile[fd];
        if(f != 0){
            readi()
        }
    }
}

*/

