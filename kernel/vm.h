#ifndef VM_H
#define VM_H

#include "types.h"

extern t_pagetable kernel_pagetable;

extern void kvminit();
extern void kvminithart();
extern void mappages(t_pagetable, void*, uint64, void*, uint64);
extern void mappage(t_pagetable, void*, void*, uint64);
extern void* walk(t_pagetable, void* , int);
extern void printmemory();
extern void print_pt(t_pagetable);
extern void printvm();
extern void print_page(t_pagetable, uint64);

#endif