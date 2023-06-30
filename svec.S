.section .trampoline
.global strapret

strapret:
    csrr a0,sscratch
    ld a1, 0(a0)
    csrw satp, a1
    sfence.vma zero, zero
    sret

