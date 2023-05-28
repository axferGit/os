.section .text
.global s

s: 
    li t1, 0x10000000 # t1 <- @UART
    li t2, 0x61 # t2 <- 'a'
    sb t2, 0(t1)
    jal loop

loop : 
    sb t2,0(t1)
    addi t2, t2, 1
    jal loop
