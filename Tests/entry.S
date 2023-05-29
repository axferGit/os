.section .text
.global stack0
.global start
.global _entry

_entry:
    la sp, stack0
    li a0, 1024*4
    csrr a1, mhartid
    addi a1, a1, 1
    mul a0, a1, a0
    add sp, sp, a0
    call start

junk:
    j junk # ra points to junk
