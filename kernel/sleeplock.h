#ifndef SLEEPLOCK_H
#define SLEEPLOCK_H

#include "types.h"
extern void sleeplockinit(struct sleeplock*,uint8*);
extern void acquiresleep(struct sleeplock*);
extern void releasesleep(struct sleeplock*);

#endif