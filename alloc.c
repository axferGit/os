#include "riscv.h"
#include "memlayout.h"
#include "printf.h"
#include "alloc.h"


char * hd_pagelist = 0;
extern char end;

// initialise unused DRAM in a list of pages of [PAGESIZE] bytes.
void allocinit(){
    hd_pagelist = &end;
    char* page ;
    for(page = hd_pagelist; page + PAGESIZE < (char*) PHYSTOP ; page += PAGESIZE){
        memset(page,(char)0);
        *((uint64*)page) = (uint64)(page + PAGESIZE); // set next page
    }
    memset(page,(char)0);
    *((uint64*) page) = 0x0UL; // next page of last page is 0, useless as already set to zero
    return;
}

// return the addres of the newly allocated page, filled with 0
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
// Set char [v] to all bytes of the page [pa]
void memset(void* pa, char v){
    for(char* p = (char*) pa; p < (char*) pa + PAGESIZE ; p++){
        *p = v;
    }
    return;
}