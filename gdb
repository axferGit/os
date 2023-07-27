target remote localhost:1234
layout split
layout regs
focus cmd
#Comments
#ecall
b * 0x80001840
#mtrapvec 
b * 0x80001730
#mtrapret
b * 0x800017b8 