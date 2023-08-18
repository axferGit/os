#ifndef DISK_H
#define DISK_H

#include "types.h"

void diskinit();
void diskrequest(uint32,struct buf *);

#endif