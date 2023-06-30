.section .text
.global f

f :
    lui a0, 0x10000
    li a1, 0x61
    sb a1, 0(a0)
    j f
