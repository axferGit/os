	.file	"start.c"
	.option pic
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/home/axfer/Work/os" "start.c"
	.align	1
	.globl	uartinit
	.type	uartinit, @function
uartinit:
.LFB0:
	.file 1 "uart.c"
	.loc 1 15 16
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sd	s0,8(sp)
	.cfi_offset 8, -8
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 1 17 5
	li	a5,268435456
	addi	a5,a5,1
	sb	zero,0(a5)
	.loc 1 20 5
	li	a5,268435456
	addi	a5,a5,3
	li	a4,-128
	sb	a4,0(a5)
	.loc 1 23 5
	li	a5,268435456
	li	a4,3
	sb	a4,0(a5)
	.loc 1 24 5
	li	a5,268435456
	addi	a5,a5,1
	sb	zero,0(a5)
	.loc 1 28 5
	li	a5,268435456
	addi	a5,a5,3
	li	a4,3
	sb	a4,0(a5)
	.loc 1 31 5
	li	a5,268435456
	addi	a5,a5,2
	li	a4,7
	sb	a4,0(a5)
	.loc 1 34 5
	li	a5,268435456
	addi	a5,a5,1
	li	a4,1
	sb	a4,0(a5)
	.loc 1 36 5
	nop
	.loc 1 37 1
	ld	s0,8(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE0:
	.size	uartinit, .-uartinit
	.align	1
	.globl	uartputc
	.type	uartputc, @function
uartputc:
.LFB1:
	.loc 1 40 22
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	s0,24(sp)
	.cfi_offset 8, -8
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	mv	a5,a0
	sb	a5,-17(s0)
	.loc 1 41 10
	nop
.L4:
	.loc 1 41 13 discriminator 1
	li	a5,268435456
	addi	a5,a5,5
	lbu	a5,0(a5)
	andi	a5,a5,0xff
	.loc 1 41 26 discriminator 1
	sext.w	a5,a5
	andi	a5,a5,32
	sext.w	a5,a5
	.loc 1 41 11 discriminator 1
	beq	a5,zero,.L4
	.loc 1 44 5
	li	a5,268435456
	lbu	a4,-17(s0)
	sb	a4,0(a5)
	.loc 1 45 5
	nop
	.loc 1 46 1
	ld	s0,24(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE1:
	.size	uartputc, .-uartputc
	.align	1
	.globl	uartgetc
	.type	uartgetc, @function
uartgetc:
.LFB2:
	.loc 1 50 19
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sd	s0,8(sp)
	.cfi_offset 8, -8
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 1 51 9
	li	a5,268435456
	addi	a5,a5,5
	lbu	a5,0(a5)
	andi	a5,a5,0xff
	.loc 1 51 22
	sext.w	a5,a5
	andi	a5,a5,1
	sext.w	a5,a5
	.loc 1 51 8
	beq	a5,zero,.L7
	.loc 1 52 16
	li	a5,268435456
	lbu	a5,0(a5)
	andi	a5,a5,0xff
	sext.w	a5,a5
	j	.L8
.L7:
	.loc 1 55 16
	li	a5,-1
.L8:
	.loc 1 57 1
	mv	a0,a5
	ld	s0,8(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE2:
	.size	uartgetc, .-uartgetc
	.align	1
	.globl	_printf
	.type	_printf, @function
_printf:
.LFB3:
	.loc 1 59 27
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
	.loc 1 60 5
	j	.L10
.L11:
	.loc 1 61 24 discriminator 2
	lw	a5,-20(s0)
	ld	a4,-40(s0)
	add	a5,a4,a5
	.loc 1 61 9 discriminator 2
	lbu	a5,0(a5)
	mv	a0,a5
	call	uartputc
	.loc 1 60 36 discriminator 2
	lw	a5,-20(s0)
	addiw	a5,a5,1
	sw	a5,-20(s0)
.L10:
	.loc 1 60 22 discriminator 1
	lw	a5,-20(s0)
	ld	a4,-40(s0)
	add	a5,a4,a5
	lbu	a5,0(a5)
	.loc 1 60 26 discriminator 1
	bne	a5,zero,.L11
.LBE2:
	.loc 1 63 5
	nop
	.loc 1 64 1
	ld	ra,40(sp)
	.cfi_restore 1
	ld	s0,32(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE3:
	.size	_printf, .-_printf
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
.LFB4:
	.file 2 "start.c"
	.loc 2 8 12
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sd	ra,8(sp)
	sd	s0,0(sp)
	.cfi_offset 1, -8
	.cfi_offset 8, -16
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 2 9 5
	li	a5,268435456
	.loc 2 9 39
	li	a4,97
	sb	a4,0(a5)
	.loc 2 10 12
	call	test
	.loc 2 11 1
	ld	ra,8(sp)
	.cfi_restore 1
	ld	s0,0(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE4:
	.size	test, .-test
	.align	1
	.globl	loop
	.type	loop, @function
loop:
.LFB5:
	.loc 2 13 12
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sd	ra,8(sp)
	sd	s0,0(sp)
	.cfi_offset 1, -8
	.cfi_offset 8, -16
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 2 14 12
	call	loop
	.loc 2 15 1
	ld	ra,8(sp)
	.cfi_restore 1
	ld	s0,0(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE5:
	.size	loop, .-loop
	.align	1
	.globl	mtrapvec
	.type	mtrapvec, @function
mtrapvec:
.LFB6:
	.loc 2 17 16
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	ra,24(sp)
	sd	s0,16(sp)
	.cfi_offset 1, -8
	.cfi_offset 8, -16
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	.loc 2 18 13
	call	uartgetc
	mv	a5,a0
	sw	a5,-20(s0)
	.loc 2 19 8
	lw	a5,-20(s0)
	sext.w	a4,a5
	li	a5,-1
	beq	a4,a5,.L18
	.loc 2 20 9
	lw	a5,-20(s0)
	andi	a5,a5,0xff
	mv	a0,a5
	call	uartputc
.L18:
	.loc 2 22 5
	li	a5,268435456
	.loc 2 22 39
	li	a4,98
	sb	a4,0(a5)
	.loc 2 23 5
	nop
	.loc 2 24 1
	ld	ra,24(sp)
	.cfi_restore 1
	ld	s0,16(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE6:
	.size	mtrapvec, .-mtrapvec
	.align	1
	.globl	w_mtvec
	.type	w_mtvec, @function
w_mtvec:
.LFB7:
	.loc 2 26 23
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	s0,24(sp)
	.cfi_offset 8, -8
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sd	a0,-24(s0)
	.loc 2 27 5
	ld	a5,-24(s0)
#APP
# 27 "start.c" 1
	csrw mtvec, a5
# 0 "" 2
	.loc 2 28 1
#NO_APP
	nop
	ld	s0,24(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE7:
	.size	w_mtvec, .-w_mtvec
	.align	1
	.globl	r_mstatus
	.type	r_mstatus, @function
r_mstatus:
.LFB8:
	.loc 2 30 19
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	s0,24(sp)
	.cfi_offset 8, -8
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	.loc 2 32 5
	ld	a5,-24(s0)
#APP
# 32 "start.c" 1
	csrr a5, mstatus
# 0 "" 2
#NO_APP
	sd	a5,-24(s0)
	.loc 2 33 12
	ld	a5,-24(s0)
	.loc 2 34 1
	mv	a0,a5
	ld	s0,24(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE8:
	.size	r_mstatus, .-r_mstatus
	.align	1
	.globl	w_mstatus
	.type	w_mstatus, @function
w_mstatus:
.LFB9:
	.loc 2 36 25
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	s0,24(sp)
	.cfi_offset 8, -8
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sd	a0,-24(s0)
	.loc 2 37 5
	ld	a5,-24(s0)
#APP
# 37 "start.c" 1
	csrw mstatus, a5
# 0 "" 2
	.loc 2 38 5
#NO_APP
	nop
	.loc 2 39 1
	ld	s0,24(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE9:
	.size	w_mstatus, .-w_mstatus
	.align	1
	.globl	start
	.type	start, @function
start:
.LFB10:
	.loc 2 41 13
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sd	ra,8(sp)
	sd	s0,0(sp)
	.cfi_offset 1, -8
	.cfi_offset 8, -16
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 2 44 5
	call	uartinit
	.loc 2 46 5
	lla	a5,mtrapvec
	mv	a0,a5
	call	w_mtvec
	.loc 2 48 15
	call	r_mstatus
	mv	a5,a0
	.loc 2 48 5
	ori	a5,a5,8
	mv	a0,a5
	call	w_mstatus
	.loc 2 51 1
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
.LFE10:
	.size	start, .-start
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x224
	.2byte	0x5
	.byte	0x1
	.byte	0x8
	.4byte	.Ldebug_abbrev0
	.byte	0x6
	.4byte	.LASF14
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.8byte	.Ltext0
	.8byte	.Letext0-.Ltext0
	.4byte	.Ldebug_line0
	.byte	0x7
	.4byte	.LASF15
	.byte	0x2
	.byte	0x3
	.byte	0x17
	.4byte	0x3a
	.byte	0x5
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.byte	0x8
	.4byte	0x52
	.4byte	0x52
	.byte	0x9
	.4byte	0x3a
	.2byte	0xfff
	.byte	0
	.byte	0x5
	.byte	0x1
	.byte	0x8
	.4byte	.LASF3
	.byte	0xa
	.4byte	.LASF16
	.byte	0x2
	.byte	0x5
	.byte	0x25
	.4byte	0x41
	.byte	0x10
	.byte	0x9
	.byte	0x3
	.8byte	stack0
	.byte	0x1
	.4byte	.LASF7
	.byte	0x29
	.8byte	.LFB10
	.8byte	.LFE10-.LFB10
	.byte	0x1
	.byte	0x9c
	.byte	0x2
	.4byte	.LASF4
	.byte	0x2
	.byte	0x24
	.8byte	.LFB9
	.8byte	.LFE9-.LFB9
	.byte	0x1
	.byte	0x9c
	.4byte	0xb3
	.byte	0x3
	.string	"x"
	.byte	0x2
	.byte	0x24
	.byte	0x17
	.4byte	0x2e
	.byte	0x2
	.byte	0x91
	.byte	0x68
	.byte	0
	.byte	0xb
	.4byte	.LASF5
	.byte	0x2
	.byte	0x1e
	.byte	0x8
	.4byte	0x2e
	.8byte	.LFB8
	.8byte	.LFE8-.LFB8
	.byte	0x1
	.byte	0x9c
	.4byte	0xe3
	.byte	0x4
	.string	"x"
	.byte	0x2
	.byte	0x1f
	.byte	0xc
	.4byte	0x2e
	.byte	0x2
	.byte	0x91
	.byte	0x68
	.byte	0
	.byte	0x2
	.4byte	.LASF6
	.byte	0x2
	.byte	0x1a
	.8byte	.LFB7
	.8byte	.LFE7-.LFB7
	.byte	0x1
	.byte	0x9c
	.4byte	0x10e
	.byte	0x3
	.string	"f"
	.byte	0x2
	.byte	0x1a
	.byte	0x15
	.4byte	0x2e
	.byte	0x2
	.byte	0x91
	.byte	0x68
	.byte	0
	.byte	0xc
	.4byte	.LASF17
	.byte	0x2
	.byte	0x11
	.byte	0x6
	.8byte	.LFB6
	.8byte	.LFE6-.LFB6
	.byte	0x1
	.byte	0x9c
	.4byte	0x13a
	.byte	0x4
	.string	"c"
	.byte	0x2
	.byte	0x12
	.byte	0x9
	.4byte	0x13a
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0xd
	.byte	0x4
	.byte	0x5
	.string	"int"
	.byte	0x1
	.4byte	.LASF8
	.byte	0xd
	.8byte	.LFB5
	.8byte	.LFE5-.LFB5
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.4byte	.LASF9
	.byte	0x8
	.8byte	.LFB4
	.8byte	.LFE4-.LFB4
	.byte	0x1
	.byte	0x9c
	.byte	0xe
	.4byte	.LASF10
	.byte	0x1
	.byte	0x3b
	.byte	0x6
	.8byte	.LFB3
	.8byte	.LFE3-.LFB3
	.byte	0x1
	.byte	0x9c
	.4byte	0x1be
	.byte	0xf
	.4byte	.LASF11
	.byte	0x1
	.byte	0x3b
	.byte	0x14
	.4byte	0x1be
	.byte	0x2
	.byte	0x91
	.byte	0x58
	.byte	0x10
	.8byte	.LBB2
	.8byte	.LBE2-.LBB2
	.byte	0x4
	.string	"i"
	.byte	0x1
	.byte	0x3c
	.byte	0xd
	.4byte	0x13a
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0
	.byte	0x11
	.byte	0x8
	.4byte	0x52
	.byte	0x12
	.4byte	.LASF18
	.byte	0x1
	.byte	0x32
	.byte	0x5
	.4byte	0x13a
	.8byte	.LFB2
	.8byte	.LFE2-.LFB2
	.byte	0x1
	.byte	0x9c
	.byte	0x2
	.4byte	.LASF12
	.byte	0x1
	.byte	0x28
	.8byte	.LFB1
	.8byte	.LFE1-.LFB1
	.byte	0x1
	.byte	0x9c
	.4byte	0x20d
	.byte	0x3
	.string	"c"
	.byte	0x1
	.byte	0x28
	.byte	0x14
	.4byte	0x52
	.byte	0x2
	.byte	0x91
	.byte	0x6f
	.byte	0
	.byte	0x13
	.4byte	.LASF13
	.byte	0x1
	.byte	0xf
	.byte	0x6
	.8byte	.LFB0
	.8byte	.LFE0-.LFB0
	.byte	0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.byte	0x1
	.byte	0x2e
	.byte	0
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0x21
	.byte	0x2
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
	.byte	0x2
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
	.byte	0x3
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
	.byte	0x4
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
	.byte	0x5
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
	.byte	0x6
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
	.byte	0x1
	.byte	0x1
	.byte	0x49
	.byte	0x13
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x9
	.byte	0x21
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0x2f
	.byte	0x5
	.byte	0
	.byte	0
	.byte	0xa
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
	.byte	0xb
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
	.byte	0xc
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
	.byte	0xd
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
	.byte	0xe
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
	.byte	0xf
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
	.byte	0x10
	.byte	0xb
	.byte	0x1
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x7
	.byte	0
	.byte	0
	.byte	0x11
	.byte	0xf
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x12
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
	.byte	0x13
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
.LASF8:
	.string	"loop"
.LASF2:
	.string	"long unsigned int"
.LASF18:
	.string	"uartgetc"
.LASF14:
	.string	"GNU C17 11.3.0 -mabi=lp64d -misa-spec=2.2 -march=rv64imafdc -ggdb -fstack-protector-strong"
.LASF16:
	.string	"stack0"
.LASF10:
	.string	"_printf"
.LASF6:
	.string	"w_mtvec"
.LASF4:
	.string	"w_mstatus"
.LASF13:
	.string	"uartinit"
.LASF5:
	.string	"r_mstatus"
.LASF11:
	.string	"string"
.LASF17:
	.string	"mtrapvec"
.LASF15:
	.string	"uint64"
.LASF12:
	.string	"uartputc"
.LASF7:
	.string	"start"
.LASF9:
	.string	"test"
.LASF3:
	.string	"char"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/home/axfer/Work/os"
.LASF0:
	.string	"start.c"
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
