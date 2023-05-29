	.file	"test.c"
	.option pic
	.text
	.globl	stack0
	.bss
	.align	4
	.type	stack0, @object
	.size	stack0, 4096
stack0:
	.zero	4096
	.text
	.align	1
	.globl	start
	.type	start, @function
start:
	addi	sp,sp,-16
	sd	s0,8(sp)
	addi	s0,sp,16
	li	a5,268435456
	li	a4,97
	sb	a4,0(a5)
	nop
	ld	s0,8(sp)
	addi	sp,sp,16
	jr	ra
	.size	start, .-start
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
