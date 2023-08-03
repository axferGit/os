#ifndef PROC_H
#define PROC_H

#include "types.h"
#include "memlayout.h"

extern struct proc proc_list[NPROC];
extern struct cpu cpu_list[NHART];

extern void procinit();
extern void proclaunch();
extern struct proc * myproc();

#endif
