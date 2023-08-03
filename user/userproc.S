.section .text
.global f
.global print_user
#.global user_foo

f:
    lui a0, 0x10000
    li a1, 0x61
    sb a1, 0(a0)
    li a1, 0x0a #new line
    sb a1, 0(a0)
    li a0, 0x61
    li a2, 0x1

# user_foo:
#     add a0, x0, x0
#     j user_foo

f2:
    call print_user
    add a0, a0, a2
    j f2

print_user:
    li a7, 1
    ecall
    ret

