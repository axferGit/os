	.file	"start.c"
	.option pic
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/home/axfer/Work/os" "start.c"
	.align	1
	.globl	w_mtvec
	.type	w_mtvec, @function
w_mtvec:
.LFB0:
	.file 1 "riscv.h"
	.loc 1 3 23
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	s0,24(sp)
	.cfi_offset 8, -8
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sd	a0,-24(s0)
	.loc 1 4 5
	ld	a5,-24(s0)
#APP
# 4 "riscv.h" 1
	csrw mtvec, a5
# 0 "" 2
	.loc 1 5 1
#NO_APP
	nop
	ld	s0,24(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE0:
	.size	w_mtvec, .-w_mtvec
	.align	1
	.globl	r_mstatus
	.type	r_mstatus, @function
r_mstatus:
.LFB1:
	.loc 1 7 19
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	s0,24(sp)
	.cfi_offset 8, -8
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	.loc 1 9 5
	ld	a5,-24(s0)
#APP
# 9 "riscv.h" 1
	csrr a5, mstatus
# 0 "" 2
#NO_APP
	sd	a5,-24(s0)
	.loc 1 10 12
	ld	a5,-24(s0)
	.loc 1 11 1
	mv	a0,a5
	ld	s0,24(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE1:
	.size	r_mstatus, .-r_mstatus
	.align	1
	.globl	w_mstatus
	.type	w_mstatus, @function
w_mstatus:
.LFB2:
	.loc 1 13 25
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	s0,24(sp)
	.cfi_offset 8, -8
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sd	a0,-24(s0)
	.loc 1 14 5
	ld	a5,-24(s0)
#APP
# 14 "riscv.h" 1
	csrw mstatus, a5
# 0 "" 2
	.loc 1 15 5
#NO_APP
	nop
	.loc 1 16 1
	ld	s0,24(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE2:
	.size	w_mstatus, .-w_mstatus
	.align	1
	.globl	s_mstatus
	.type	s_mstatus, @function
s_mstatus:
.LFB3:
	.loc 1 18 25
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	s0,24(sp)
	.cfi_offset 8, -8
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sd	a0,-24(s0)
	.loc 1 19 5
	ld	a5,-24(s0)
#APP
# 19 "riscv.h" 1
	csrs mstatus, a5
# 0 "" 2
	.loc 1 20 5
#NO_APP
	nop
	.loc 1 21 1
	ld	s0,24(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE3:
	.size	s_mstatus, .-s_mstatus
	.align	1
	.globl	r_mie
	.type	r_mie, @function
r_mie:
.LFB4:
	.loc 1 23 15
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	s0,24(sp)
	.cfi_offset 8, -8
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	.loc 1 25 5
	ld	a5,-24(s0)
#APP
# 25 "riscv.h" 1
	csrr a5, mie
# 0 "" 2
#NO_APP
	sd	a5,-24(s0)
	.loc 1 26 12
	ld	a5,-24(s0)
	.loc 1 27 1
	mv	a0,a5
	ld	s0,24(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE4:
	.size	r_mie, .-r_mie
	.align	1
	.globl	w_mie
	.type	w_mie, @function
w_mie:
.LFB5:
	.loc 1 29 21
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	s0,24(sp)
	.cfi_offset 8, -8
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sd	a0,-24(s0)
	.loc 1 30 5
	ld	a5,-24(s0)
#APP
# 30 "riscv.h" 1
	csrw mie, a5
# 0 "" 2
	.loc 1 31 5
#NO_APP
	nop
	.loc 1 32 1
	ld	s0,24(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE5:
	.size	w_mie, .-w_mie
	.align	1
	.globl	cpuid
	.type	cpuid, @function
cpuid:
.LFB6:
	.loc 1 34 15
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	s0,24(sp)
	.cfi_offset 8, -8
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	.loc 1 36 5
	ld	a5,-24(s0)
#APP
# 36 "riscv.h" 1
	csrr a5, mhartid
# 0 "" 2
#NO_APP
	sd	a5,-24(s0)
	.loc 1 37 12
	ld	a5,-24(s0)
	.loc 1 38 1
	mv	a0,a5
	ld	s0,24(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE6:
	.size	cpuid, .-cpuid
	.align	1
	.globl	uartinit
	.type	uartinit, @function
uartinit:
.LFB7:
	.file 2 "uart.c"
	.loc 2 6 16
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sd	s0,8(sp)
	.cfi_offset 8, -8
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 2 8 5
	li	a5,268435456
	addi	a5,a5,1
	sb	zero,0(a5)
	.loc 2 11 5
	li	a5,268435456
	addi	a5,a5,3
	li	a4,-128
	sb	a4,0(a5)
	.loc 2 14 5
	li	a5,268435456
	li	a4,3
	sb	a4,0(a5)
	.loc 2 15 5
	li	a5,268435456
	addi	a5,a5,1
	sb	zero,0(a5)
	.loc 2 19 5
	li	a5,268435456
	addi	a5,a5,3
	li	a4,3
	sb	a4,0(a5)
	.loc 2 22 5
	li	a5,268435456
	addi	a5,a5,2
	li	a4,7
	sb	a4,0(a5)
	.loc 2 25 5
	li	a5,268435456
	addi	a5,a5,1
	li	a4,1
	sb	a4,0(a5)
	.loc 2 27 5
	nop
	.loc 2 28 1
	ld	s0,8(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE7:
	.size	uartinit, .-uartinit
	.align	1
	.globl	uartputc
	.type	uartputc, @function
uartputc:
.LFB8:
	.loc 2 31 22
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	s0,24(sp)
	.cfi_offset 8, -8
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	mv	a5,a0
	sb	a5,-17(s0)
	.loc 2 32 10
	nop
.L17:
	.loc 2 32 13 discriminator 1
	li	a5,268435456
	addi	a5,a5,5
	lbu	a5,0(a5)
	andi	a5,a5,0xff
	.loc 2 32 26 discriminator 1
	sext.w	a5,a5
	andi	a5,a5,32
	sext.w	a5,a5
	.loc 2 32 11 discriminator 1
	beq	a5,zero,.L17
	.loc 2 35 5
	li	a5,268435456
	lbu	a4,-17(s0)
	sb	a4,0(a5)
	.loc 2 36 5
	nop
	.loc 2 37 1
	ld	s0,24(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE8:
	.size	uartputc, .-uartputc
	.align	1
	.globl	uartgetc
	.type	uartgetc, @function
uartgetc:
.LFB9:
	.loc 2 41 19
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sd	s0,8(sp)
	.cfi_offset 8, -8
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 2 42 9
	li	a5,268435456
	addi	a5,a5,5
	lbu	a5,0(a5)
	andi	a5,a5,0xff
	.loc 2 42 22
	sext.w	a5,a5
	andi	a5,a5,1
	sext.w	a5,a5
	.loc 2 42 8
	beq	a5,zero,.L20
	.loc 2 43 16
	li	a5,268435456
	lbu	a5,0(a5)
	andi	a5,a5,0xff
	sext.w	a5,a5
	j	.L21
.L20:
	.loc 2 46 16
	li	a5,-1
.L21:
	.loc 2 48 1
	mv	a0,a5
	ld	s0,8(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE9:
	.size	uartgetc, .-uartgetc
	.align	1
	.globl	_printf
	.type	_printf, @function
_printf:
.LFB10:
	.loc 2 50 27
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sd	ra,40(sp)
	sd	s0,32(sp)
	.cfi_offset 1, -8
	.cfi_offset 8, -16
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sd	a0,-40(s0)
.LBB2:
	.loc 2 51 5
	j	.L23
.L24:
	.loc 2 52 24 discriminator 2
	lw	a5,-20(s0)
	ld	a4,-40(s0)
	add	a5,a4,a5
	.loc 2 52 9 discriminator 2
	lbu	a5,0(a5)
	mv	a0,a5
	call	uartputc
	.loc 2 51 36 discriminator 2
	lw	a5,-20(s0)
	addiw	a5,a5,1
	sw	a5,-20(s0)
.L23:
	.loc 2 51 22 discriminator 1
	lw	a5,-20(s0)
	ld	a4,-40(s0)
	add	a5,a4,a5
	lbu	a5,0(a5)
	.loc 2 51 26 discriminator 1
	bne	a5,zero,.L24
.LBE2:
	.loc 2 54 5
	nop
	.loc 2 55 1
	ld	ra,40(sp)
	.cfi_restore 1
	ld	s0,32(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE10:
	.size	_printf, .-_printf
	.align	1
	.globl	plicinit
	.type	plicinit, @function
plicinit:
.LFB11:
	.file 3 "plic.c"
	.loc 3 6 16
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sd	s0,8(sp)
	.cfi_offset 8, -8
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 3 9 5
	li	a5,201326592
	addi	a5,a5,40
	.loc 3 9 45
	li	a4,1
	sw	a4,0(a5)
	.loc 3 10 5
	nop
	.loc 3 11 1
	ld	s0,8(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE11:
	.size	plicinit, .-plicinit
	.align	1
	.globl	plicinithart
	.type	plicinithart, @function
plicinithart:
.LFB12:
	.loc 3 12 20
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	ra,24(sp)
	sd	s0,16(sp)
	.cfi_offset 1, -8
	.cfi_offset 8, -16
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	.loc 3 13 16
	call	cpuid
	sd	a0,-24(s0)
	.loc 3 16 17
	ld	a4,-24(s0)
	li	a5,786432
	addi	a5,a5,32
	add	a5,a4,a5
	slli	a5,a5,8
	.loc 3 16 7
	mv	a4,a5
	.loc 3 16 46
	li	a5,1024
	sw	a5,0(a4)
	.loc 3 19 17
	ld	a4,-24(s0)
	li	a5,24576
	addi	a5,a5,256
	add	a5,a4,a5
	slli	a5,a5,13
	.loc 3 19 46
	sw	zero,0(a5)
	.loc 3 20 5
	nop
	.loc 3 22 1
	ld	ra,24(sp)
	.cfi_restore 1
	ld	s0,16(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE12:
	.size	plicinithart, .-plicinithart
	.globl	stack0
	.bss
	.align	4
	.type	stack0, @object
	.size	stack0, 4096
stack0:
	.zero	4096
	.text
	.align	1
	.globl	test
	.type	test, @function
test:
.LFB13:
	.file 4 "start.c"
	.loc 4 8 12
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sd	ra,8(sp)
	sd	s0,0(sp)
	.cfi_offset 1, -8
	.cfi_offset 8, -16
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 4 9 5
	li	a5,268435456
	.loc 4 9 39
	li	a4,97
	sb	a4,0(a5)
	.loc 4 10 12
	call	test
	.loc 4 11 1
	ld	ra,8(sp)
	.cfi_restore 1
	ld	s0,0(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE13:
	.size	test, .-test
	.align	1
	.globl	loop
	.type	loop, @function
loop:
.LFB14:
	.loc 4 13 12
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sd	ra,8(sp)
	sd	s0,0(sp)
	.cfi_offset 1, -8
	.cfi_offset 8, -16
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 4 14 12
	call	loop
	.loc 4 15 1
	ld	ra,8(sp)
	.cfi_restore 1
	ld	s0,0(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE14:
	.size	loop, .-loop
	.align	1
	.globl	mtrapvec
	.type	mtrapvec, @function
mtrapvec:
.LFB15:
	.loc 4 17 16
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	ra,24(sp)
	sd	s0,16(sp)
	.cfi_offset 1, -8
	.cfi_offset 8, -16
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	.loc 4 18 13
	call	uartgetc
	mv	a5,a0
	sw	a5,-20(s0)
	.loc 4 19 8
	lw	a5,-20(s0)
	sext.w	a4,a5
	li	a5,-1
	beq	a4,a5,.L35
	.loc 4 20 9
	lw	a5,-20(s0)
	andi	a5,a5,0xff
	mv	a0,a5
	call	uartputc
.L35:
	.loc 4 22 5
	li	a5,268435456
	.loc 4 22 39
	li	a4,98
	sb	a4,0(a5)
	.loc 4 23 5
	nop
	.loc 4 24 1
	ld	ra,24(sp)
	.cfi_restore 1
	ld	s0,16(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE15:
	.size	mtrapvec, .-mtrapvec
	.section	.rodata
	.align	3
.LC0:
	.string	"os is"
	.align	3
.LC1:
	.string	"o"
	.align	3
.LC2:
	.string	"uartinit ok\n"
	.text
	.align	1
	.globl	start
	.type	start, @function
start:
.LFB16:
	.loc 4 26 13
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sd	ra,8(sp)
	sd	s0,0(sp)
	.cfi_offset 1, -8
	.cfi_offset 8, -16
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 4 28 5
	call	uartinit
	.loc 4 29 5
	lla	a0,.LC0
	call	_printf
	.loc 4 30 5
	lla	a0,.LC1
	call	_printf
	.loc 4 32 5
	lla	a0,.LC2
	call	_printf
	.loc 4 34 5
	call	plicinit
	.loc 4 35 5
	call	plicinithart
	.loc 4 37 5
	lla	a5,mtrapvec
	mv	a0,a5
	call	w_mtvec
	.loc 4 39 11
	call	r_mie
	mv	a4,a0
	.loc 4 39 5
	li	a5,4096
	addi	a5,a5,-2048
	or	a5,a4,a5
	mv	a0,a5
	call	w_mie
	.loc 4 41 15
	call	r_mstatus
	mv	a5,a0
	.loc 4 41 5
	ori	a5,a5,8
	mv	a0,a5
	call	w_mstatus
	.loc 4 42 5
	call	loop
	.loc 4 43 1
	nop
	ld	ra,8(sp)
	.cfi_restore 1
	ld	s0,0(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE16:
	.size	start, .-start
	.align	1
	.globl	main
	.type	main, @function
main:
.LFB17:
	.loc 4 45 11
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sd	s0,8(sp)
	.cfi_offset 8, -8
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	li	a5,0
	.loc 4 47 1
	mv	a0,a5
	ld	s0,8(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE17:
	.size	main, .-main
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x342
	.2byte	0x5
	.byte	0x1
	.byte	0x8
	.4byte	.Ldebug_abbrev0
	.byte	0xa
	.4byte	.LASF24
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.8byte	.Ltext0
	.8byte	.Letext0-.Ltext0
	.4byte	.Ldebug_line0
	.byte	0x7
	.4byte	.LASF2
	.byte	0x1
	.byte	0x1
	.byte	0x17
	.4byte	0x3a
	.byte	0x4
	.byte	0x8
	.byte	0x7
	.4byte	.LASF4
	.byte	0x7
	.4byte	.LASF3
	.byte	0x3
	.byte	0x4
	.byte	0x16
	.4byte	0x4d
	.byte	0x4
	.byte	0x4
	.byte	0x7
	.4byte	.LASF5
	.byte	0xb
	.4byte	0x65
	.4byte	0x65
	.byte	0xc
	.4byte	0x3a
	.2byte	0xfff
	.byte	0
	.byte	0x4
	.byte	0x1
	.byte	0x8
	.4byte	.LASF6
	.byte	0xd
	.4byte	.LASF25
	.byte	0x4
	.byte	0x5
	.byte	0x25
	.4byte	0x54
	.byte	0x10
	.byte	0x9
	.byte	0x3
	.8byte	stack0
	.byte	0xe
	.4byte	.LASF26
	.byte	0x4
	.byte	0x2d
	.byte	0x5
	.4byte	0xa1
	.8byte	.LFB17
	.8byte	.LFE17-.LFB17
	.byte	0x1
	.byte	0x9c
	.byte	0xf
	.byte	0x4
	.byte	0x5
	.string	"int"
	.byte	0x5
	.4byte	.LASF7
	.byte	0x1a
	.8byte	.LFB16
	.8byte	.LFE16-.LFB16
	.byte	0x1
	.byte	0x9c
	.byte	0x8
	.4byte	.LASF10
	.byte	0x4
	.byte	0x11
	.8byte	.LFB15
	.8byte	.LFE15-.LFB15
	.byte	0x1
	.byte	0x9c
	.4byte	0xeb
	.byte	0x1
	.string	"c"
	.byte	0x4
	.byte	0x12
	.byte	0x9
	.4byte	0xa1
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x5
	.4byte	.LASF8
	.byte	0xd
	.8byte	.LFB14
	.8byte	.LFE14-.LFB14
	.byte	0x1
	.byte	0x9c
	.byte	0x5
	.4byte	.LASF9
	.byte	0x8
	.8byte	.LFB13
	.8byte	.LFE13-.LFB13
	.byte	0x1
	.byte	0x9c
	.byte	0x8
	.4byte	.LASF11
	.byte	0x3
	.byte	0xc
	.8byte	.LFB12
	.8byte	.LFE12-.LFB12
	.byte	0x1
	.byte	0x9c
	.4byte	0x146
	.byte	0x1
	.string	"x"
	.byte	0x3
	.byte	0xd
	.byte	0xc
	.4byte	0x2e
	.byte	0x2
	.byte	0x91
	.byte	0x68
	.byte	0
	.byte	0x9
	.4byte	.LASF12
	.byte	0x3
	.8byte	.LFB11
	.8byte	.LFE11-.LFB11
	.byte	0x1
	.byte	0x9c
	.byte	0x10
	.4byte	.LASF13
	.byte	0x2
	.byte	0x32
	.byte	0x6
	.8byte	.LFB10
	.8byte	.LFE10-.LFB10
	.byte	0x1
	.byte	0x9c
	.4byte	0x1ab
	.byte	0x11
	.4byte	.LASF15
	.byte	0x2
	.byte	0x32
	.byte	0x14
	.4byte	0x1ab
	.byte	0x2
	.byte	0x91
	.byte	0x58
	.byte	0x12
	.8byte	.LBB2
	.8byte	.LBE2-.LBB2
	.byte	0x1
	.string	"i"
	.byte	0x2
	.byte	0x33
	.byte	0xd
	.4byte	0xa1
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0
	.byte	0x13
	.byte	0x8
	.4byte	0x65
	.byte	0x14
	.4byte	.LASF27
	.byte	0x2
	.byte	0x29
	.byte	0x5
	.4byte	0xa1
	.8byte	.LFB9
	.8byte	.LFE9-.LFB9
	.byte	0x1
	.byte	0x9c
	.byte	0x3
	.4byte	.LASF14
	.byte	0x2
	.byte	0x1f
	.8byte	.LFB8
	.8byte	.LFE8-.LFB8
	.byte	0x1
	.byte	0x9c
	.4byte	0x1fa
	.byte	0x2
	.string	"c"
	.byte	0x2
	.byte	0x1f
	.byte	0x14
	.4byte	0x65
	.byte	0x2
	.byte	0x91
	.byte	0x6f
	.byte	0
	.byte	0x9
	.4byte	.LASF16
	.byte	0x2
	.8byte	.LFB7
	.8byte	.LFE7-.LFB7
	.byte	0x1
	.byte	0x9c
	.byte	0x6
	.4byte	.LASF17
	.byte	0x22
	.4byte	0x2e
	.8byte	.LFB6
	.8byte	.LFE6-.LFB6
	.byte	0x1
	.byte	0x9c
	.4byte	0x240
	.byte	0x1
	.string	"x"
	.byte	0x1
	.byte	0x23
	.byte	0xc
	.4byte	0x2e
	.byte	0x2
	.byte	0x91
	.byte	0x68
	.byte	0
	.byte	0x3
	.4byte	.LASF18
	.byte	0x1
	.byte	0x1d
	.8byte	.LFB5
	.8byte	.LFE5-.LFB5
	.byte	0x1
	.byte	0x9c
	.4byte	0x26b
	.byte	0x2
	.string	"x"
	.byte	0x1
	.byte	0x1d
	.byte	0x13
	.4byte	0x2e
	.byte	0x2
	.byte	0x91
	.byte	0x68
	.byte	0
	.byte	0x6
	.4byte	.LASF19
	.byte	0x17
	.4byte	0x2e
	.8byte	.LFB4
	.8byte	.LFE4-.LFB4
	.byte	0x1
	.byte	0x9c
	.4byte	0x299
	.byte	0x1
	.string	"x"
	.byte	0x1
	.byte	0x18
	.byte	0xc
	.4byte	0x2e
	.byte	0x2
	.byte	0x91
	.byte	0x68
	.byte	0
	.byte	0x3
	.4byte	.LASF20
	.byte	0x1
	.byte	0x12
	.8byte	.LFB3
	.8byte	.LFE3-.LFB3
	.byte	0x1
	.byte	0x9c
	.4byte	0x2c4
	.byte	0x2
	.string	"x"
	.byte	0x1
	.byte	0x12
	.byte	0x17
	.4byte	0x2e
	.byte	0x2
	.byte	0x91
	.byte	0x68
	.byte	0
	.byte	0x3
	.4byte	.LASF21
	.byte	0x1
	.byte	0xd
	.8byte	.LFB2
	.8byte	.LFE2-.LFB2
	.byte	0x1
	.byte	0x9c
	.4byte	0x2ef
	.byte	0x2
	.string	"x"
	.byte	0x1
	.byte	0xd
	.byte	0x17
	.4byte	0x2e
	.byte	0x2
	.byte	0x91
	.byte	0x68
	.byte	0
	.byte	0x6
	.4byte	.LASF22
	.byte	0x7
	.4byte	0x2e
	.8byte	.LFB1
	.8byte	.LFE1-.LFB1
	.byte	0x1
	.byte	0x9c
	.4byte	0x31d
	.byte	0x1
	.string	"x"
	.byte	0x1
	.byte	0x8
	.byte	0xc
	.4byte	0x2e
	.byte	0x2
	.byte	0x91
	.byte	0x68
	.byte	0
	.byte	0x15
	.4byte	.LASF23
	.byte	0x1
	.byte	0x3
	.byte	0x6
	.8byte	.LFB0
	.8byte	.LFE0-.LFB0
	.byte	0x1
	.byte	0x9c
	.byte	0x2
	.string	"f"
	.byte	0x1
	.byte	0x3
	.byte	0x15
	.4byte	0x2e
	.byte	0x2
	.byte	0x91
	.byte	0x68
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.byte	0x1
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0x2
	.byte	0x5
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0x3
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0x21
	.byte	0x6
	.byte	0x27
	.byte	0x19
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x7
	.byte	0x40
	.byte	0x18
	.byte	0x7a
	.byte	0x19
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x4
	.byte	0x24
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x3e
	.byte	0xb
	.byte	0x3
	.byte	0xe
	.byte	0
	.byte	0
	.byte	0x5
	.byte	0x2e
	.byte	0
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0x21
	.byte	0x4
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0x21
	.byte	0x6
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x7
	.byte	0x40
	.byte	0x18
	.byte	0x7c
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0x6
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0x21
	.byte	0x1
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0x21
	.byte	0x8
	.byte	0x49
	.byte	0x13
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x7
	.byte	0x40
	.byte	0x18
	.byte	0x7a
	.byte	0x19
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x7
	.byte	0x16
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x8
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0x21
	.byte	0x6
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x7
	.byte	0x40
	.byte	0x18
	.byte	0x7c
	.byte	0x19
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x9
	.byte	0x2e
	.byte	0
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x21
	.byte	0x6
	.byte	0x39
	.byte	0x21
	.byte	0x6
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x7
	.byte	0x40
	.byte	0x18
	.byte	0x7a
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0xa
	.byte	0x11
	.byte	0x1
	.byte	0x25
	.byte	0xe
	.byte	0x13
	.byte	0xb
	.byte	0x3
	.byte	0x1f
	.byte	0x1b
	.byte	0x1f
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x7
	.byte	0x10
	.byte	0x17
	.byte	0
	.byte	0
	.byte	0xb
	.byte	0x1
	.byte	0x1
	.byte	0x49
	.byte	0x13
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0xc
	.byte	0x21
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0x2f
	.byte	0x5
	.byte	0
	.byte	0
	.byte	0xd
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x3f
	.byte	0x19
	.byte	0x88,0x1
	.byte	0xb
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0xe
	.byte	0x2e
	.byte	0
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x7
	.byte	0x40
	.byte	0x18
	.byte	0x7a
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0xf
	.byte	0x24
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x3e
	.byte	0xb
	.byte	0x3
	.byte	0x8
	.byte	0
	.byte	0
	.byte	0x10
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x7
	.byte	0x40
	.byte	0x18
	.byte	0x7c
	.byte	0x19
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x11
	.byte	0x5
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0x12
	.byte	0xb
	.byte	0x1
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x7
	.byte	0
	.byte	0
	.byte	0x13
	.byte	0xf
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x14
	.byte	0x2e
	.byte	0
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x49
	.byte	0x13
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x7
	.byte	0x40
	.byte	0x18
	.byte	0x7a
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0x15
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x7
	.byte	0x40
	.byte	0x18
	.byte	0x7a
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x2c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x8
	.byte	0
	.2byte	0
	.2byte	0
	.8byte	.Ltext0
	.8byte	.Letext0-.Ltext0
	.8byte	0
	.8byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF15:
	.string	"string"
.LASF3:
	.string	"uint32"
.LASF22:
	.string	"r_mstatus"
.LASF5:
	.string	"unsigned int"
.LASF25:
	.string	"stack0"
.LASF27:
	.string	"uartgetc"
.LASF26:
	.string	"main"
.LASF19:
	.string	"r_mie"
.LASF16:
	.string	"uartinit"
.LASF4:
	.string	"long unsigned int"
.LASF17:
	.string	"cpuid"
.LASF2:
	.string	"uint64"
.LASF21:
	.string	"w_mstatus"
.LASF18:
	.string	"w_mie"
.LASF11:
	.string	"plicinithart"
.LASF20:
	.string	"s_mstatus"
.LASF12:
	.string	"plicinit"
.LASF6:
	.string	"char"
.LASF13:
	.string	"_printf"
.LASF10:
	.string	"mtrapvec"
.LASF23:
	.string	"w_mtvec"
.LASF9:
	.string	"test"
.LASF7:
	.string	"start"
.LASF24:
	.string	"GNU C17 11.3.0 -mabi=lp64d -misa-spec=2.2 -march=rv64imafdc -ggdb -fstack-protector-strong"
.LASF8:
	.string	"loop"
.LASF14:
	.string	"uartputc"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/home/axfer/Work/os"
.LASF0:
	.string	"start.c"
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
