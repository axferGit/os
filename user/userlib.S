.section .text

.global print_user
print_user:
    li a7, 1
    ecall
    ret
