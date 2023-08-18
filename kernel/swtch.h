#ifndef SWTCH_H
#define SWTCH_H
#include "types.h"

// swtch(stuct context * old_context, struct context * new_context)
void swtch(struct context *, struct context *);

#endif