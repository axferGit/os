K = kernel
U = user

OBJS = ${K}/entry.o \
	${K}/start.o \
	${K}/main.o \
	${K}/plic.o \
	${K}/uart.o \
	${K}/alloc.o \
	${K}/printf.o \
	${K}/kernelvec.o \
	${K}/vm.o \
	${K}/proc.o \
	${K}/trap.o \
	${K}/ssys.o \
	${K}/trampoline.o \
	${U}/userproc.o 
	

CONSTANT = ${K}/memlayout.h ${K}/riscv.h ${K}/types.h
CORES = 1

TOOLPREFIX = riscv64-linux-gnu-
LD = ${TOOLPREFIX}ld
CC = ${TOOLPREFIX}gcc
AS = ${TOOLPREFIX}as
OBJDUMP = $(TOOLPREFIX)objdump
QEMU = qemu-system-riscv64
GDB = gdb-multiarch

CFLAGS = ggdb -ffreestanding -fno-common -nostdlib -fno-stack-protector
QEMUOPTS = -machine virt -cpu rv64 -smp $(CORES) -m 128M -nographic -bios none -kernel ${K}/kernel 

.PHONY : gdb clear


${K}/kernel: $(OBJS) ${K}/t.ld ${K}/riscv.h
	$(LD) -T ${K}/t.ld -o ${K}/kernel $(OBJS) 
	$(OBJDUMP) -d -S ${K}/kernel > ${K}/kernel.asm
	$(OBJDUMP) -t ${K}/kernel | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > ${K}/kernel.sym

qemu : ${K}/kernel
	${QEMU} ${QEMUOPTS}

qemu-gdb : ${K}/kernel
	${QEMU} -machine virt -cpu rv64 -smp $(CORES) -s -S -nographic -bios none -kernel ${K}/kernel

gdb :
	${GDB} --command=./${K}/gdb

%.o : %.c ${CONSTANT}
	${CC} -${CFLAGS} -c $< -o $@

%.o : %.S
	${AS} $< -o $@

clear :
	rm ${OBJS}
	rm ${K}/kernel ${K}/kernel.asm ${K}/kernel.sym
