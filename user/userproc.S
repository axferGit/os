.section .text
.global f
.global print_user

f :
    lui a0, 0x10000
    li a1, 0x61
    sb a1, 0(a0)
    li a1, 0x0a #new line
    sb a1, 0(a0)
    li a7, 7
    li a0, 0x61
    ecall
    j f

# f:
#     li a0, 0x61
#     ecall print_user
#     addi a0, a0, 1
#     j f
    