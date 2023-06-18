target remote localhost:1234
layout split
layout regs
focus cmd
#mtrapvec
b* 0x80000450
b* 0x800001ce