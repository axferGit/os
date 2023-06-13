.section .text
.global mtrapvec
.global mtraphandler


# mtrapvec saves all the registers ans load a machine stack
mtrapvec:
    csrrw a0, mscratch, a0 #swap a0 and mscratch
    sd ra, 8(a0)
    sd sp, 16(a0)
    sd gp, 24(a0)
    sd tp, 32(a0)
    sd t0, 40(a0)
    sd t1, 48(a0)
    sd t2, 56(a0)
    sd fp, 64(a0)
    sd s1, 72(a0)
    # a0 will be saved later
    sd a1, 88(a0)
    sd a2, 96(a0)
    sd a3, 104(a0)
    sd a4, 112(a0)
    sd a5, 120(a0)
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

    # save a0
    csrrw a1, mscratch, a0 
    sd a1, 80(a0)

    # all registers jave been saved
    # mscratch points to mstrach(memory)

    # Set the stack pointer
    ld sp, 0(a0)

    #jump to mtrapvec
    call mtraphandler

mtrapvecret:
    csrr a0, mscratch
    ld a1, 80(a0)
    csrw mscratch, a1

    ld ra, 8(a0)
    ld sp, 16(a0)
    ld gp, 24(a0)
    ld tp, 32(a0)
    ld t0, 40(a0)
    ld t1, 48(a0)
    ld t2, 56(a0)
    ld fp, 64(a0)
    ld s1, 72(a0)
    # a0 will be loaded after
    ld a1, 88(a0)
    ld a2, 96(a0)
    ld a3, 104(a0)
    ld a4, 112(a0)
    ld a5, 120(a0)
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

    csrrw a0, mscratch, a0

    mret

