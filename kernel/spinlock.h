#ifndef SPINLOCK_H
#define SPINLOCK_H

#include "types.h"

void spinlockinit(struct spinlock*,uint8*);
void acquire(struct spinlock*);
void release(struct spinlock*);

#endif