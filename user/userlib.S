#include "../kernel/memlayout.h"

.section .text

.global print_user
print_user:
    li a7, U_SYSCALL_TEST
    ecall
    ret
