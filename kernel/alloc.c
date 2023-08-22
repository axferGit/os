#include "memlayout.h"
#include "types.h"
#include "alloc.h"

uint64 * hd_pagelist = 0;
extern uint64 end;

// initialise unused DRAM in a list of pages of [PAGESIZE] bytes.
void allocinit(){
    hd_pagelist = &end;
    char* page ;
    for(page = (char*) hd_pagelist; page + PAGESIZE < (char*) PHYSTOP ; page += PAGESIZE){
        memset(page,(char)0,PAGESIZE);
        *((uint64*)page) = (uint64)(page + PAGESIZE); // set next page
    }
    memset(page,(char)0,PAGESIZE);
    *((uint64*) page) = 0x0UL; // next page of last page is 0, useless as already set to zero
    return;
}

// return the addres of the newly allocated page, filled with 0
// return 0 if no more page is available.
void* alloc(){
    if (hd_pagelist){
        uint64* page = hd_pagelist;
        hd_pagelist = (uint64*) (*hd_pagelist);
        memset(page,0,PAGESIZE);
        return page;
    }
    else{
        return (void*) 0;
    }
}

// append the page [pa] in the free page list and reset it
void free(void* pa){
    memset(pa,(char)0, PAGESIZE);
    *(uint64*) pa = (uint64) hd_pagelist;
    hd_pagelist = (uint64*) pa;
    return;
}

// set the addresses between [dst] and [dst + sz -1] to char [v] 
void memset(void* dst, char v, uint32 sz){
    char* p;
    for(p = (char*) dst; p < ((char*) dst) + sz ; p++){
        *p = v;
    }
    return;
}

// Copy [sz] bytes from [src] into [dst]
void memcpy(void* dst, void* src, uint32 sz){
    uint32 p;
    for(p = 0; p <  sz; p++){
        ((uint8*) dst)[p] = ((uint8*) src)[p];
    };
    return;
}