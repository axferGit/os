#include "riscv.h"
#include "memlayout.h"
#include "printf.h"



char * hd_pagelist = 0;
extern char end;

// initialise unused DRAM in a list of pages of [PAGESIZE] bytes.
void allocinit(){
    hd_pagelist = &end;
    char* i = hd_pagelist;
    for(; i + PAGESIZE < (char*) PHYSTOP ; i += PAGESIZE){
        *((uint64*)i) = (uint64)(i + PAGESIZE); // set next page
    }
    *((uint64*) i) = 0x0UL; // next page of last page is 0
    return;
}

