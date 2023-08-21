#ifndef SYSCALL_H
#define SYSCALL_H

#include "memlayout.h"

extern void (*(sys_call[NSYSCALL]))(void);

#endif