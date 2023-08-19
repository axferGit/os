#ifndef FS_H
#define FS_H

#include "types.h"
#include "memlayout.h"

extern struct buf bcache [NBUF];
extern struct inode inode_list [NINODE * IPB];

extern struct buf * getb();
extern void createb(struct buf *,uint8,uint32);
extern struct buf * readb(uint64);
extern uint32 readi(struct inode*,uint32,uint32,uint8*);
extern struct inode* geti();
extern struct inode * openi(uint16);

#endif