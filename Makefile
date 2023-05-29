OBJECTS = entry.o start.o
CORES = 1


qemu : kernel
	qemu-system-riscv64 -machine virt -cpu rv64 -smp $(CORES) -nographic -bios none -kernel kernel 

gdb : kernel
	qemu-system-riscv64 -machine virt -cpu rv64 -smp $(CORES) -s -S -nographic -bios none -kernel kernel

kernel : entry.o start.o t.ld
	riscv64-linux-gnu-ld -T t.ld entry.o start.o -o kernel

entry.o : entry.S
	riscv64-linux-gnu-as $< -o $@

start.s : start.c
	riscv64-linux-gnu-gcc $< -S -ggdb $@

start.o : start.s
	riscv64-linux-gnu-as $< -o $@
clean :
	rm *.o
	rm kernel