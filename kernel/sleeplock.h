#ifndef SLEEPLOCK_H
#define SLEEPLOCK_H

#include "types.h"

void acquiresleep(struct sleeplock*);
void releasesleep(struct sleeplock*);

#endif