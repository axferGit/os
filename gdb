target remote localhost:1234
layout split
layout regs
focus cmd
#Comments
#ecall
b* 0x10
b* 0x14
#uservecret
#b* 0x0000003ffffff08c
