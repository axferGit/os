#ifndef ALLOC_H
#define ALLOC_H

#include "types.h"


void allocinit();
void free(void*);
void* alloc();
void memset(void*,char,uint32);
void memcpy(void*,void*,uint32);

#endif