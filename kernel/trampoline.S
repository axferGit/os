.section .trampoline
.global uservec
.global uservecret
.align 4
uservec :
# Save user-proc registers
    # sscratch = TRAPFRAME
    csrrw a0, sscratch, a0 #swap a0 and ssracth
    #sscratch points to TRAPFRAME in user satp mode !

    sd ra, 0(a0)
    sd sp, 8(a0)
    sd gp, 16(a0)
    sd tp, 24(a0)
    sd t0, 32(a0)
    sd t1, 40(a0)
    sd t2, 48(a0)
    sd fp, 56(a0)
    sd s1, 64(a0)
    # a0 will be saved later
    sd a1, 80(a0)
    sd a2, 88(a0)
    sd a3, 96(a0)
    sd a4, 104(a0)
    sd a5, 112(a0)
    sd a6, 120(a0)
    sd a7, 128(a0)
    sd s2, 136(a0)
    sd s3, 144(a0)
    sd s4, 152(a0)
    sd s5, 160(a0)
    sd s6, 168(a0)
    sd s7, 176(a0)
    sd s8, 184(a0)
    sd s9, 192(a0)
    sd s10, 200(a0)
    sd s11, 208(a0)
    sd t3, 216(a0)
    sd t4, 224(a0)
    sd t5, 232(a0)
    sd t6, 240(a0)
    csrr t0, sscratch # save a0
    sd t0, 72(a0)

# Load kernel-proc registers 
    ld sp, 256(a0) # stack pointer
    ld ra, 272(a0) # function trap handler
    ld t1, 264(a0) # page table
    csrw satp, t1
    sfence.vma zero, zero
    jr ra


uservecret:
    # uservecret(TRAPFRAME,pagetable) in user-mode satp
    # a0 = TRAPFRAME
    # a1 = pagetable of user process
    
    # satp
    csrw satp, a1
    sfence.vma zero, zero

    # save a0 in sscratch
    ld t0, 72(a0)
    csrw sscratch, t0

    ld ra, 0(a0)
    ld sp, 8(a0)
    ld gp, 16(a0)
    ld tp, 24(a0)
    ld t0, 32(a0)
    ld t1, 40(a0)
    ld t2, 48(a0)
    ld fp, 56(a0)
    ld s1, 64(a0)
    ld a1, 80(a0)
    ld a2, 88(a0)
    ld a3, 96(a0)
    ld a4, 104(a0)
    ld a5, 112(a0)
    ld a6, 120(a0)
    ld a7, 128(a0)
    ld s2, 136(a0)
    ld s3, 144(a0)
    ld s4, 152(a0)
    ld s5, 160(a0)
    ld s6, 168(a0)
    ld s7, 176(a0)
    ld s8, 184(a0)
    ld s9, 192(a0)
    ld s10, 200(a0)
    ld s11, 208(a0)
    ld t3, 216(a0)
    ld t4, 224(a0)
    ld t5, 232(a0)
    ld t6, 240(a0)
    csrrw a0, sscratch, a0 # swap sscratch (=a0) and a0 (=TRAPFRAME)

    sret
