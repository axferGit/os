.section .text
.global f
.global p
.global s

p:
    jal s

f: 
    addi t1, t1, 1
    jal f


s: 
    li t1, 0x10000000
    li t2, 0x61
loop : sb t2,0(t1)
    addi t2, t2, 1
    jal loop
