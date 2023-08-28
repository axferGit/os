#ifndef FS_H
#define FS_H

#include "types.h"
#include "memlayout.h"

extern struct bcache bcache_list;
extern struct icache icache_list;
extern struct fcache fcache_list;

extern void binit();
extern struct buf* bacquire(uint64);
extern void brelease();
extern struct buf* bread(uint64);
extern struct buf* fbread(struct inode*,uint64);

extern void iinit();
extern struct inode* iacquire(uint16);
extern void irelease(struct inode*);
extern struct inode* iopen(uint16);
extern uint32 iread(struct inode*,uint32,uint32,uint8*);
extern uint16 find(uint8*);

extern void finit();
extern struct file* facquire();
extern void frelease(struct file*);

extern void ofinit(struct proc*);
extern uint32 ofalloc();
extern void ofdealloc();

extern void fsinit();

#endif