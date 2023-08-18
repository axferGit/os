#include "types.h"
#include "memlayout.h"
#include "alloc.h"
#include "disk.h"

#define ADDR2BLOCK(addr) ((addr) / (BLOCK_SIZE))
#define ADDR2OFF(addr) ((addr) % (BLOCK_SIZE))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))


struct buf bcache [NBUF];
struct inode inode_list [NINODE * IPB];

// Return a free buf from cache buffers list
struct buf * getfreeBuf(){
    return &bcache[0];
}

// Cretae a cache buffer with request type [t_rqt] and block number [blk]
// return nothing
void createbuf(struct buf * b, uint8 t_rqt, uint32 blk){
    b->blk = blk;
    b->status = t_rqt;
    return;
}

// Read file block number [fbn] from inode [i] into a cache buffer
// return the buffer filled up with data
struct buf * rblock(uint64 blk){
    struct buf * b = getfreeBuf();
    createbuf(b,VIRTIO_BLK_S_UNDEF,blk);
    diskrequest(VIRTIO_BLK_T_IN,b);
    return b;
}

// Read file block number [fbn] from inode [i] into a cache buffer
// return the buffer filled up with data
struct buf * riblock(struct inode* i, uint32 fbn){
    if (i->di.data[fbn]){
        return rblock(i->di.data[fbn]);
    }
    
}


// Read from inode [i] [sz] bytes maximum from [off] into data buffer [buffer]
// return the number of bytes read
uint32 rinode(struct inode* i,uint32 addr, uint32 sz, uint8* buffer){
    struct buf * b;
    uint32 tot = 0;

    //sz = min(sz,max(i->di.size - addr,0));
    

    while(sz > 0){
        uint32 fbn = ADDR2BLOCK(addr);
        uint32 off = ADDR2OFF(addr);
        uint32 nb = min(sz,(BLOCK_SIZE) - off);
        b = riblock(i,fbn);
        
        memcpy(buffer,b->data + off,nb);

        sz -= nb;
        addr += nb;
        tot += nb;
    };

    return tot;
}

struct inode* getfreeInode(){
    return &inode_list[0];
}

struct inode * oinode(uint16 inum){
    struct inode * in = getfreeInode();
    uint64 blk = IBLOCK(inum);
    uint32 off = IBLOCKOFF(inum);
    struct buf * b = rblock(blk);
    memcpy(&in->di,&((struct dinode *) b->data)[off],sizeof(((struct dinode *) b->data)[off]));
    return in;
}


