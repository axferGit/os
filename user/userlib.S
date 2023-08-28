#include "../kernel/memlayout.h"

.section .text

.global uprint_str
.global open
.global uprint_hex
.global read
.global usys_test

usys_test:
    li a7, U_SYSCALL_TEST
    ecall
    ret

uprint_str:
    li a7, U_SYSCALL_PRINT_STR
    ecall
    ret

open :
    li a7, U_SYSCALL_OPEN
    ecall
    ret

uprint_hex:
    li a7, U_SYSCALL_PRINT_HEX
    ecall
    ret

read:
    li a7, U_SYSCALL_READ
    ecall
    ret