#include "memlayout.h"
#include "riscv.h"
void kvminit();
void kvminithart();
void mappages(t_pagetable, void*, uint64, void*, uint64);
void mappage(t_pagetable, void*, void*, uint64);
void* walk(t_pagetable, void* , int);
void printmemory();

