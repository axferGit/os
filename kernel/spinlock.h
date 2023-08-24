#ifndef SPINLOCK_H
#define SPINLOCK_H

#include "types.h"

void acquire(struct spinlock*);
void release(struct spinlock*);

#endif