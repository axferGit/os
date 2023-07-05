OBJS = entry.o \
	start.o \
	main.o \
	machine_trap.o \
	plic.o \
	uart.o \
	alloc.o \
	riscv.o \
	printf.o \
	kernelvec.o \
	vm.o \
	proc.o \
	trap.o \
	trampoline.o \
	userproc.o
	

CONSTANT = memlayout.h
CORES = 1

TOOLPREFIX = riscv64-linux-gnu-
LD = ${TOOLPREFIX}ld
CC = ${TOOLPREFIX}gcc
AS = ${TOOLPREFIX}as
OBJDUMP = $(TOOLPREFIX)objdump
QEMU = qemu-system-riscv64
GDB = gdb-multiarch

CFLAGS = ggdb -ffreestanding -fno-common -nostdlib -fno-stack-protector
QEMUOPTS = -machine virt -cpu rv64 -smp $(CORES) -m 128M -nographic -bios none -kernel kernel 

.PHONY : gdb clear


kernel: $(OBJS) t.ld 
	$(LD) -T t.ld -o kernel $(OBJS) 
	$(OBJDUMP) -d -S kernel > kernel.asm
	$(OBJDUMP) -t kernel | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > kernel.sym

qemu : kernel
	${QEMU} ${QEMUOPTS}

qemu-gdb : kernel
	${QEMU} -machine virt -cpu rv64 -smp $(CORES) -s -S -nographic -bios none -kernel kernel

gdb :
	${GDB} --command=./gdb

%.o : %.c ${CONSTANT}
	${CC} -${CFLAGS} -c $< -o $@

%.o : %.S
	${AS} $< -o $@

clear :
	rm ${OBJS}
	rm kernel kernel.asm
