#include "types.h"
#include "memlayout.h"

#define S_PLIC_ENABLE_INT(irq) (((uint32*) PLIC_ENABLE(target))[(irq)/32] |= (1<<((irq) % 32)))
#define S_PLIC_PRIORITY(irq,v) (*((uint32*) PLIC_PRIORITY(irq)) = v)

// Initialize interrupt sources
void plicinit(){
    // Interrupt priority
    S_PLIC_PRIORITY(UART0_IRQ,1);
    S_PLIC_PRIORITY(VIRTIO0_IRQ,0);
    return;
}

// Initialize the targets for each hart, namely :
// - interrupt enable
// - priority threshold.
void plicinithart(){
    //uint64 target = cpuid() * 2;
    uint64 target = 0;
    // Interrupts enable
    //S_PLIC_ENABLE_INT(UART0_IRQ);
    S_PLIC_ENABLE_INT(VIRTIO0_IRQ);
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