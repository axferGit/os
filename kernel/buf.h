#ifndef BUF_H
#define BUH_H

#include "types.h"
#include "memlayout.h"

extern struct buf bcache [NBUF];
extern struct inode inode_list [NINODE * IPB];

extern struct buf * getfreeBuf();
extern void createbuf(struct buf *,uint8,uint32);
extern struct buf * rblock(uint64);
extern struct buf * riblock(struct inode*,uint32);
extern uint32 rinode(struct inode*,uint32,uint32,uint8*);
extern struct inode* getfreeInode();
extern struct inode * oinode(uint16);

#endif