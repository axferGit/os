OBJS = entry.o \
	start.o \
	machine_trap.o \
	main.o \
	plic.o \
	uart.o \
	riscv.o \
	printf.o \
	kernelvec.o

CONSTANT = memlayout.h
CORES = 1

TOOLPREFIX = riscv64-linux-gnu-
LD = ${TOOLPREFIX}ld
CC = ${TOOLPREFIX}gcc
AS = ${TOOLPREFIX}as
OBJDUMP = $(TOOLPREFIX)objdump
QEMU = qemu-system-riscv64
GDB = gdb-multiarch

CFLAGS = ggdb -nostdlib -fno-stack-protector

.PHONY : gdb


kernel: $(OBJS) t.ld 
	$(LD) -T t.ld -o kernel $(OBJS) 
	$(OBJDUMP) -d -S kernel > kernel.asm
	$(OBJDUMP) -t kernel | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > kernel.sym

qemu : kernel
	${QEMU} -machine virt -cpu rv64 -smp $(CORES) -nographic -bios none -kernel kernel 

qemu-gdb : kernel
	${QEMU} -machine virt -cpu rv64 -smp $(CORES) -s -S -nographic -bios none -kernel kernel

gdb :
	${GDB} --command=./gdb

%.o : %.c ${CONSTANT}
	${CC} -${CFLAGS} -c $< -o $@

%.o : %.S
	${AS} $< -o $@

clean :
	rm ${OBJS}
	rm kernel kernel.asm
