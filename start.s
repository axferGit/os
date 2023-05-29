	.file	"start.c"
	.option pic
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/home/axfer/Work/os" "start.c"
	.globl	stack0
	.bss
	.align	4
	.type	stack0, @object
	.size	stack0, 4096
stack0:
	.zero	4096
	.text
	.align	1
	.globl	uartinit
	.type	uartinit, @function
uartinit:
.LFB0:
	.file 1 "start.c"
	.loc 1 19 16
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sd	s0,8(sp)
	.cfi_offset 8, -8
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 1 21 5
	li	a5,16777216
	addi	a5,a5,1
	sb	zero,0(a5)
	.loc 1 24 5
	li	a5,16777216
	addi	a5,a5,3
	li	a4,-128
	sb	a4,0(a5)
	.loc 1 27 5
	li	a5,16777216
	li	a4,3
	sb	a4,0(a5)
	.loc 1 28 5
	li	a5,16777216
	addi	a5,a5,1
	sb	zero,0(a5)
	.loc 1 32 5
	li	a5,16777216
	addi	a5,a5,3
	li	a4,3
	sb	a4,0(a5)
	.loc 1 35 5
	li	a5,16777216
	addi	a5,a5,2
	li	a4,7
	sb	a4,0(a5)
	.loc 1 38 5
	li	a5,16777216
	addi	a5,a5,1
	li	a4,1
	sb	a4,0(a5)
	.loc 1 40 5
	nop
	.loc 1 41 1
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
	.loc 1 44 22
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	s0,24(sp)
	.cfi_offset 8, -8
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	mv	a5,a0
	sb	a5,-17(s0)
	.loc 1 45 10
	nop
.L4:
	.loc 1 45 13 discriminator 1
	li	a5,16777216
	addi	a5,a5,5
	lbu	a5,0(a5)
	andi	a5,a5,0xff
	.loc 1 45 26 discriminator 1
	sext.w	a5,a5
	andi	a5,a5,32
	sext.w	a5,a5
	.loc 1 45 11 discriminator 1
	beq	a5,zero,.L4
	.loc 1 48 5
	li	a5,16777216
	lbu	a4,-17(s0)
	sb	a4,0(a5)
	.loc 1 49 5
	nop
	.loc 1 50 1
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
	.loc 1 54 19
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sd	s0,8(sp)
	.cfi_offset 8, -8
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 1 55 9
	li	a5,16777216
	addi	a5,a5,5
	lbu	a5,0(a5)
	andi	a5,a5,0xff
	.loc 1 55 22
	sext.w	a5,a5
	andi	a5,a5,1
	sext.w	a5,a5
	.loc 1 55 8
	beq	a5,zero,.L7
	.loc 1 56 16
	li	a5,16777216
	lbu	a5,0(a5)
	andi	a5,a5,0xff
	sext.w	a5,a5
	j	.L8
.L7:
	.loc 1 59 16
	li	a5,-1
.L8:
	.loc 1 61 1
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
	.loc 1 63 27
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
	.loc 1 64 5
	j	.L10
.L11:
	.loc 1 65 24 discriminator 2
	lw	a5,-20(s0)
	ld	a4,-40(s0)
	add	a5,a4,a5
	.loc 1 65 9 discriminator 2
	lbu	a5,0(a5)
	mv	a0,a5
	call	uartputc
	.loc 1 64 36 discriminator 2
	lw	a5,-20(s0)
	addiw	a5,a5,1
	sw	a5,-20(s0)
.L10:
	.loc 1 64 22 discriminator 1
	lw	a5,-20(s0)
	ld	a4,-40(s0)
	add	a5,a4,a5
	lbu	a5,0(a5)
	.loc 1 64 26 discriminator 1
	bne	a5,zero,.L11
.LBE2:
	.loc 1 67 5
	nop
	.loc 1 68 1
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
	.align	1
	.globl	loop
	.type	loop, @function
loop:
.LFB4:
	.loc 1 69 12
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sd	ra,8(sp)
	sd	s0,0(sp)
	.cfi_offset 1, -8
	.cfi_offset 8, -16
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 1 70 5
	li	a5,16777216
	.loc 1 70 38
	li	a4,97
	sb	a4,0(a5)
	.loc 1 71 12
	call	loop
	.loc 1 72 1
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
	.size	loop, .-loop
	.align	1
	.globl	mtrapvec
	.type	mtrapvec, @function
mtrapvec:
.LFB5:
	.loc 1 74 16
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	ra,24(sp)
	sd	s0,16(sp)
	.cfi_offset 1, -8
	.cfi_offset 8, -16
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	.loc 1 75 13
	call	uartgetc
	mv	a5,a0
	sw	a5,-20(s0)
	.loc 1 76 8
	lw	a5,-20(s0)
	sext.w	a4,a5
	li	a5,-1
	beq	a4,a5,.L18
	.loc 1 77 9
	lw	a5,-20(s0)
	andi	a5,a5,0xff
	mv	a0,a5
	call	uartputc
	.loc 1 79 5
	nop
.L18:
	nop
	.loc 1 80 1
	ld	ra,24(sp)
	.cfi_restore 1
	ld	s0,16(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE5:
	.size	mtrapvec, .-mtrapvec
	.align	1
	.globl	w_mtvec
	.type	w_mtvec, @function
w_mtvec:
.LFB6:
	.loc 1 82 23
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	s0,24(sp)
	.cfi_offset 8, -8
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sd	a0,-24(s0)
	.loc 1 83 5
	ld	a5,-24(s0)
#APP
# 83 "start.c" 1
	csrw mtvec, a5
# 0 "" 2
	.loc 1 84 1
#NO_APP
	nop
	ld	s0,24(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE6:
	.size	w_mtvec, .-w_mtvec
	.align	1
	.globl	start
	.type	start, @function
start:
.LFB7:
	.loc 1 86 13
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	ra,24(sp)
	sd	s0,16(sp)
	.cfi_offset 1, -8
	.cfi_offset 8, -16
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	.loc 1 87 5
	call	loop
	.loc 1 89 5
	call	uartinit
	.loc 1 91 5
	lla	a5,mtrapvec
	mv	a0,a5
	call	w_mtvec
	.loc 1 93 12
	li	a5,1
	sd	a5,-24(s0)
	.loc 1 94 5
	ld	a5,-24(s0)
#APP
# 94 "start.c" 1
	csrrs zero, mstatus, a5
# 0 "" 2
	.loc 1 95 5
#NO_APP
	call	loop
	.loc 1 97 1
	nop
	ld	ra,24(sp)
	.cfi_restore 1
	ld	s0,16(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE7:
	.size	start, .-start
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x1bc
	.2byte	0x5
	.byte	0x1
	.byte	0x8
	.4byte	.Ldebug_abbrev0
	.byte	0x6
	.4byte	.LASF12
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.8byte	.Ltext0
	.8byte	.Letext0-.Ltext0
	.4byte	.Ldebug_line0
	.byte	0x7
	.4byte	.LASF13
	.byte	0x1
	.byte	0x1
	.byte	0x17
	.4byte	0x3a
	.byte	0x2
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
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF3
	.byte	0xa
	.4byte	.LASF14
	.byte	0x1
	.byte	0x3
	.byte	0x25
	.4byte	0x41
	.byte	0x10
	.byte	0x9
	.byte	0x3
	.8byte	stack0
	.byte	0x3
	.4byte	.LASF4
	.byte	0x56
	.8byte	.LFB7
	.8byte	.LFE7-.LFB7
	.byte	0x1
	.byte	0x9c
	.4byte	0x99
	.byte	0x1
	.string	"y"
	.byte	0x5d
	.byte	0xc
	.4byte	0x2e
	.byte	0x2
	.byte	0x91
	.byte	0x68
	.byte	0
	.byte	0x4
	.4byte	.LASF6
	.byte	0x52
	.8byte	.LFB6
	.8byte	.LFE6-.LFB6
	.byte	0x1
	.byte	0x9c
	.4byte	0xc2
	.byte	0x5
	.string	"f"
	.byte	0x52
	.byte	0x15
	.4byte	0x2e
	.byte	0x2
	.byte	0x91
	.byte	0x68
	.byte	0
	.byte	0x3
	.4byte	.LASF5
	.byte	0x4a
	.8byte	.LFB5
	.8byte	.LFE5-.LFB5
	.byte	0x1
	.byte	0x9c
	.4byte	0xeb
	.byte	0x1
	.string	"c"
	.byte	0x4b
	.byte	0x9
	.4byte	0xeb
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0xb
	.byte	0x4
	.byte	0x5
	.string	"int"
	.byte	0xc
	.4byte	.LASF10
	.byte	0x1
	.byte	0x45
	.byte	0x6
	.8byte	.LFB4
	.8byte	.LFE4-.LFB4
	.byte	0x1
	.byte	0x9c
	.byte	0xd
	.4byte	.LASF7
	.byte	0x1
	.byte	0x3f
	.byte	0x6
	.8byte	.LFB3
	.8byte	.LFE3-.LFB3
	.byte	0x1
	.byte	0x9c
	.4byte	0x158
	.byte	0xe
	.4byte	.LASF8
	.byte	0x1
	.byte	0x3f
	.byte	0x14
	.4byte	0x158
	.byte	0x2
	.byte	0x91
	.byte	0x58
	.byte	0xf
	.8byte	.LBB2
	.8byte	.LBE2-.LBB2
	.byte	0x1
	.string	"i"
	.byte	0x40
	.byte	0xd
	.4byte	0xeb
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0
	.byte	0x10
	.byte	0x8
	.4byte	0x52
	.byte	0x11
	.4byte	.LASF15
	.byte	0x1
	.byte	0x36
	.byte	0x5
	.4byte	0xeb
	.8byte	.LFB2
	.8byte	.LFE2-.LFB2
	.byte	0x1
	.byte	0x9c
	.byte	0x4
	.4byte	.LASF9
	.byte	0x2c
	.8byte	.LFB1
	.8byte	.LFE1-.LFB1
	.byte	0x1
	.byte	0x9c
	.4byte	0x1a5
	.byte	0x5
	.string	"c"
	.byte	0x2c
	.byte	0x14
	.4byte	0x52
	.byte	0x2
	.byte	0x91
	.byte	0x6f
	.byte	0
	.byte	0x12
	.4byte	.LASF11
	.byte	0x1
	.byte	0x13
	.byte	0x6
	.8byte	.LFB0
	.8byte	.LFE0-.LFB0
	.byte	0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.byte	0x1
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0x21
	.byte	0x1
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
	.byte	0x3
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
	.byte	0x4
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
	.byte	0x5
	.byte	0x5
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0x21
	.byte	0x1
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
	.byte	0xc
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
	.byte	0x7c
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0xd
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
	.byte	0xe
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
	.byte	0xf
	.byte	0xb
	.byte	0x1
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x7
	.byte	0
	.byte	0
	.byte	0x10
	.byte	0xf
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x11
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
.LASF10:
	.string	"loop"
.LASF2:
	.string	"long unsigned int"
.LASF15:
	.string	"uartgetc"
.LASF12:
	.string	"GNU C17 11.3.0 -mabi=lp64d -misa-spec=2.2 -march=rv64imafdc -ggdb -fstack-protector-strong"
.LASF14:
	.string	"stack0"
.LASF6:
	.string	"w_mtvec"
.LASF11:
	.string	"uartinit"
.LASF8:
	.string	"string"
.LASF5:
	.string	"mtrapvec"
.LASF13:
	.string	"uint64"
.LASF9:
	.string	"uartputc"
.LASF4:
	.string	"start"
.LASF3:
	.string	"char"
.LASF7:
	.string	"_printf"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/home/axfer/Work/os"
.LASF0:
	.string	"start.c"
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
