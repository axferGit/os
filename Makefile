OBJS = entry.o start.o plic.o uart.o riscv.o

CORES = 1
TOOLPREFIX = riscv64-linux-gnu-


CC = $(TOOLPREFIX)gcc
AS = $(TOOLPREFIX)gas
LD = $(TOOLPREFIX)ld
OBJCOPY = $(TOOLPREFIX)objcopy
OBJDUMP = $(TOOLPREFIX)objdump
QEMU = qemu-system-riscv64
GDB = gdb-multiarch


CFLAGS = -Wall -Werror -O -fno-omit-frame-pointer -ggdb
CFLAGS += -MD
CFLAGS += -mcmodel=medany
CFLAGS += -ffreestanding -fno-common -nostdlib -mno-relax
CFLAGS += -I.
CFLAGS += $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector)

# Disable PIE when possible (for Ubuntu 16.10 toolchain)
ifneq ($(shell $(CC) -dumpspecs 2>/dev/null | grep -e '[^f]no-pie'),)
CFLAGS += -fno-pie -no-pie
endif
ifneq ($(shell $(CC) -dumpspecs 2>/dev/null | grep -e '[^f]nopie'),)
CFLAGS += -fno-pie -nopie
endif

LDFLAGS = -z max-page-size=4096

.PHONY : gdb

kernel: $(OBJS) t.ld 
	$(LD) $(LDFLAGS) -T t.ld -o kernel $(OBJS) 
	$(OBJDUMP) -S kernel > kernel.asm
	$(OBJDUMP) -t kernel | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > kernel.sym

qemu : kernel
	${QEMU} -machine virt -cpu rv64 -smp $(CORES) -nographic -bios none -kernel kernel 

qemu-gdb : kernel
	${QEMU} -machine virt -cpu rv64 -smp $(CORES) -s -S -nographic -bios none -kernel kernel

gdb :
	${GDB} --command=./gdb

entry.o : entry.S
	riscv64-linux-gnu-as $< -o $@


${OBJ} : %.o : %.c
	riscv64-linux-gnu-gcc -c $< -g -o $@

clean :
	rm *.o
	rm kernel*
	rm *.d
