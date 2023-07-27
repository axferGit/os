#include "types.h"
#include "memlayout.h"

// Initialize interrupt sources
// Must be done only once.
void plicinit(){
    // Interrupt priority
    *((uint32*) PLIC_PRIORITY(UART0_IRQ)) = 1;
    return;
}

// Initialize the targets for each hart, namely :
// - interrupt enable
// - priority threshold.
void plicinithart(){
    //uint64 target = cpuid() * 2;
    uint64 target = 0;
    // Interrupt enables
    ((uint32*) PLIC_ENABLE(target))[UART0_IRQ/32] |= (1<<(UART0_IRQ % 32));
    // Priority threshold
    *((uint32*) PLIC_THRESHOLD(target)) = 0;
    return;
}

// Claim the interrupt for the target.
// Return the interrupt identifier.
uint32 plicclaim(){
    //uint64 target = cpuid() * 2;
    uint64 target = 0;
    return *((uint32*) PLIC_CLAIM(target));
}

// Complete the interrupt for the target
void pliccomplete(uint32 id){
    //uint64 target = cpuid() * 2;
    uint64 target = 0;
    *((uint32 *) PLIC_COMPLETE(target)) = id;
    return;
}