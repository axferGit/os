QEMU : quit 
* CTRL-A + X

## Qemu
* Start qemu : ```make qemu```

## Qemu and gdb
* Start qemu : ```make qemu-gdb```
* Start gdb : 
    * ```gdb-multiarch```
    * ```target remote localhost:260000```


# Assembler

Assmbler files are made of  ```directives``` and ```statements```

```directives``` are instructions for linking the file. It controls the assembly of asm file into an objectfile.

```statements``` combine a label and an instruction.

## Directive

## Statement

A statement follows the structure ```[label:] [instrcution]```
* ```label``` is a symbol name. It can be used to refer to this instruction
* ```instruction``` is a pseudo ISA instruction

### Sources
* RISC-V assembler language : https://michaeljclark.github.io/asm.html

# RISC-V

```assembly
call f :
        ra <- pc + 4
        j f
```

```assembly
ret <-> jalr zero, ra, 0
```


The callee saves ```ra``` and ```s0/fp``` and sets its ```fp```
```assembly
addi sp, sp, -16        #make place for storing ra and fp
sd ra, 8(sp)            #store its ra (in case it calls an other function)
sd s0, 0(sp)            #store previous fp
addi s0, sp, 16         #set the new fp (equal to previous sp)
```

For return, the callee resets ```ra``` , ```fp``` and ```sp``` and jumps to ```ra```
```assembly
addi sp, fp, 0          #reset sp to the previous sp
sd ra, -8(sp)           #reset its ra
sd fp, -16(sp)          #reset previous fp
jr ra                   #jump to next instruction of the previous function
```

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
This piece of code comes from QEMU itself. It aims at junmping at ```0x80000000```, which is the address of the DRAM, where the kernel is supposed to be loaded.

At the end of this stage: 
```gdb
$pc = 0x80000000 # starting address of the kernel (in DRAM)
$a0 = csr.mhartid # core
$a1 = 0x87000000 # ending address of the kernel (in DRAM)
$a2 = 0x1032 # end of the ROM code ?
```

## Entry

This piece of code must be loaded at ```0x80000000``` (start of the kernel for QEMU).The correct location is ensured by the loading script ```t.ld```, which sets the address and call ```_entry```.

```assembly
_entry:
	# set up a stack for C.
        # stack0 is declared in start.c,
        # with a 4096-byte stack per CPU.
        # sp = stack0 + (hartid * 4096)
        la sp, stack0
        li a0, 1024*4
	csrr a1, mhartid
        addi a1, a1, 1
        mul a0, a0, a1
        add sp, sp, a0
	# jump to start() in start.c
        call start
```
This piece of code aims at provinding each core with a stack. The stack is defined in code files and located in ```.bss``` section.
At the end, the fucntion ```start``` is called.

## PLIC (Platform level interrupt controller)

The PLIC makes the link between external components and the microprocessor. It is the source of ```external interrupts```.
External devices are connected to the PLIC through the ```irq``` wire. This wire is pulled up/down (in case of level trigger) to signal an interrupt has occured on the device, then the PLIC will warn the core.

Configuration
* for each source (device), set the priority. 
* for each target (core x mode) connect sources which can possiblly trigger this core
* for each target (core x mode) set the priority threshold

Rules
* a target will be warned only if the source is connected to the core and the source's priority is greater than the target's threshold
* when a source raises an interruption, a pending bit is set in the PLIC and MEIP too.
* if a target is triggered, it should claim the PLIC to know which source raised the interruption. Only one target will be given the id of the source, the other targets will be given zero (does not match any source). The claim clears the pending bit in PLIC and possibly in MEIP if there is no other pending interrupt for that target.
* once a target has finished dealing with an interrupt, it must warn the PLIC, so that it becomes available for dealing with other interrupts.

Qemu
* there are 16 targets (8 cores and 2 modes (M, S))

### Sources
* https://github.com/riscv/riscv-plic-spec/blob/master/riscv-plic.adoc

## Serial I/O
Uart 16550A is virtualized by Qemu. It is in charge of converting data from the CPU (parallel) to the serial port (serial) and each other.
It is located at address ```0x10000000```

Initially:
* RHR and THR : ```0x00```
* IER : ```0x00``` : No interrupt is enabled
* ISR : ```0x01``` : No interrupt is pending
* MCR : ```0x08``` : Gobal interrupts enabled
* LSR : ```0x60``` : Transmitter empty and THR empty

# Trap handling

## MTVEC

One gets into machine mode only for timer interrupts. as timer interrupts can occur from either user or supervisor mode, its behaviour should be independant of the previous privilege mode. So, ```mtvec``` points to ```mtrapvec``` which saves all the registers of the core to a scratch area pointed by ```mscratch```, load the stack of the core in machine mode, and call ```machinetraphandler()``` which handles the trap. On return, this function calls ```mtrapvecret``` which retores the stack.

The scratch registers has the form:
sp (machine) | ra (ppm) | ...(ppm)


# CLINT (Core Local Interrupt)

The CLINT is the hardware module responsible of timer and software interrupts.

Machine software interrupts are generated by writting 1 in the register ```msip``` of a hart. Only 1 out of 32 bits is writable, the others are hardwired to 0.

Machine timer interrupts are generated whenever the value of ```mtime``` (a single register for the processor) is greater or equal to the value in ```mtimecmp``` of a hart.

The raised interruption will automatically be reflected in the ```mip``` register.

Machine software interrupt is reset by writting zero to the ```msip``` register of the hart.
Machine timer interrupt is reset by setting the value of ```mtimecmp``` greater that that of ```mtime``` register.

```mtimecmp``` registers require to be modified under machine mode, so, timer interrupts can not be delegated to lower priviledge modes.

![CLINT memory map](Images/CLINT.png)

# PLIC (Platform Local Interrupt COntroller)

The PLIC is the hardware module responsible for external interrupts.

The PLIC allows various source of interrupts. Each source is given a priority by writting to a specefic register for each source.

The PLIC will generate an external interrupt to the mode of the target in the ```mip``` register. A target is a tuple hart, mode.

Each target allows the sources to be connected. This is called the matrix.
Each Target defines a threshold. An interrupt will be sent to the target, only if:
* the target is available
* the source is connected to the target
* the priority of the source is greater than the threshold of the target

In result, the extenal interrupt bit in ```mip``` for the target's mode will be set.

Then each target has to claim the interrupt (reading in their ```claim``` register the id of the source). Only one target we get the id of the source, the others will get zero. This clears the pending bit. 

Finally, the harted which claimed the interrupt, must complete the interrupt by writting the id of the source in the ```complete``` register. This makes the target evailable for handling new interrupts.

Each target sets :
* its matrix (source connected)
* its threshold
has:
* its claim/complete register

Each source is set with a priority.

# TODO:
* delegation
* exceptions
* sceduler
* 