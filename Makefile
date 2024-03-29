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
	${K}/swtch.o \
	${K}/scheduler.o \
	${K}/disk.o \
	${K}/fs.o \
	${K}/spinlock.o \
	${K}/sleeplock.o \
	${K}/syscall.o \
	${K}/string.o\
	${U}/userproc.o \
	${U}/userlib.o
	
USERPROGS = README.md

CONSTANT = ${K}/memlayout.h ${K}/riscv.h ${K}/types.h
CORES = 1

TOOLPREFIX = riscv64-linux-gnu-
LD = ${TOOLPREFIX}ld
CC = ${TOOLPREFIX}gcc
AS = ${TOOLPREFIX}as
OBJDUMP = $(TOOLPREFIX)objdump
QEMU = qemu-system-riscv64
GDB = gdb-multiarch

CFLAGS = ggdb -ffreestanding -fno-common -nostdlib -fno-stack-protector -O

QEMUOPTS = -machine virt -cpu rv64 -smp $(CORES) -m 128M -nographic -bios none -kernel ${K}/kernel 
QEMUOPTS += -drive file=fs.img,if=none,format=raw,id=x0 -device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0

.PHONY : gdb clear fs.img

fs.img : mkfs.c ${USERPROGS} ${CONSTANT}
	gcc mkfs.c -o mkfs
	./mkfs ${USERPROGS}
	xxd fs.img > fs.txt


${K}/kernel: $(OBJS) ${K}/t.ld ${K}/riscv.h
	$(LD) -T ${K}/t.ld -o ${K}/kernel $(OBJS) 
	$(OBJDUMP) -d -S ${K}/kernel > ${K}/kernel.asm

qemu : ${K}/kernel
	${QEMU} ${QEMUOPTS}

qemu-gdb : ${K}/kernel
	${QEMU} ${QEMUOPTS} -s -S

gdb :
	${GDB} --command=./gdb

%.o : %.c ${CONSTANT}
	${CC} -${CFLAGS} -c $< -o $@

%.o : %.S ${CONSTANT}
	${CC} -${CFLAGS} -c $< -o $@

clear :
	rm ${OBJS}
	rm ${K}/kernel ${K}/kernel.asm
