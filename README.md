QEMU : quit 
* CTRL-A + X

# Start
## ROM
```assembly
0x1000 : auipc t0,0x0
0x1004 : addi a2, t0, 40
0x1008 : csrr a0, mhartid
0x100C : ld a1, 32(t0) # ld a1, 0x87000000
0x1010 : ld t0, 24(t0) # ld t0, 0x80000000
0x1014 : jr t0
```
This piece of code comes from QEMU itself. It aims at junmping at 0x80000000, which is the address of the DRAM, where the kernel is supposed to be loaded.

At the end of this stage: 
```gdb
$pc = 0x80000000 # starting address of the kernel (in DRAM)
$a0 = csr.mhartid # core
$a1 = 0x87000000 # ending address of the kernel (in DRAM)
$a2 = 0x1032 # end of the ROM code ?
```

The outcome of this code is independant of its locqtion : the location is discovered at 0x1000 and the offsets to get the values stored in a1 and a2 are calculated given this position.