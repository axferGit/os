#include "riscv.h"
#include "memlayout.h"
#include "printf.h"
#include "alloc.h"


char * hd_pagelist = 0;
extern char end;

// initialise unused DRAM in a list of pages of [PAGESIZE] bytes.
void allocinit(){
    hd_pagelist = &end;
    char* i = hd_pagelist;
    for(; i + PAGESIZE < (char*) PHYSTOP ; i += PAGESIZE){
        memset(i,(char)0);
        *((uint64*)i) = (uint64)(i + PAGESIZE); // set next page
    }
    memset(i,(char)0);
    *((uint64*) i) = 0x0UL; // next page of last page is 0, useless as already set to zero
    return;
}

// Allocate a page, filled in with 0,
// return 0 if no more page is available.
void* alloc(){
    if (hd_pagelist){
        char * page = hd_pagelist;
        hd_pagelist = (char*)(*(uint64*)hd_pagelist);
        memset(page,0);
        return page;
    }
    else{
        return (void*) 0;
    }
}

// Free a page, by appending it in the free list;
void free(void* pa){
    memset(pa,(char)5);
    *(uint64*) pa = (uint64) hd_pagelist;
    hd_pagelist = (char*) pa;
    return;
}

void memset(void* pa, char v){
    for(char* p = (char*) pa; p < (char*) pa + PAGESIZE ; p++){
        *p = v;
    }
    return;
}