#include "riscv.h"
#include "memlayout.h"
#include "plic.h"


void plicinit(){
    // Priority devices
    // Set priority to 1 for devices
    *((uint32*) a_PLIC_PRIORITY(UART0_IRQ)) = 1;
    return;
}

void plicinithart(){
    uint64 x = cpuid();
    // Matrix devices x targets
    // Enable machine interrupts for the core
    *((uint32*) a_PLIC_MACHINE_INTERRUPT(x)) = (1 << UART0_IRQ);

    // Threshold targets
    *((uint32*) a_PLIC_MACHINE_THRESHOLD(x)) = 0;
    return;
}