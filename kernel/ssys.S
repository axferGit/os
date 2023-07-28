#include "memlayout.h"
# ne marche pas !

.section .text

.global hartid
hartid:
    li a7, 1 #S_SYSCALL_HARTID
    ecall
    ret
