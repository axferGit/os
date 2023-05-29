CORES = 1
qemu : kernel
	qemu-system-riscv64 -machine virt -cpu rv64 -smp $(CORES) -nographic -bios none -kernel kernel 

gdb : kernel
	qemu-system-riscv64 -machine virt -cpu rv64 -smp $(CORES) -s -S -nographic -bios none -kernel kernel

kernel : test.c t.ld
	riscv64-linux-gnu-gcc test.c -S -o test.S
	riscv64-linux-gnu-as test.S -o test.o
	riscv64-linux-gnu-as entry.S -o entry.o
	riscv64-linux-gnu-ld -T t.ld entry.o test.o -o kernel
