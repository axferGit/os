OBJECTS = a.o
CORES = 1


gdb : kernel
	qemu-system-riscv64 -machine virt -cpu rv64 -smp $(CORES) -s -S -nographic -bios none -kernel kernel

kernel : $(OBJECTS) t.ld
	riscv64-linux-gnu-ld -T t.ld $< -o $@

$(OBJECTS) : %.o : %.S
	riscv64-linux-gnu-as $< -o $@

clean :
	rm *.o
	rm kernel

