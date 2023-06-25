#include "memlayout.h"
#include "riscv.h"
#include "machine_trap.h"
#include "main.h"
#include "printf.h"
#include "uart.h"

__attribute__ ((aligned (16))) char stack0[4096 * NHART]; // initial stack, one per hart
__attribute__ ((aligned (16))) uint64 mscratch[32 * NHART]; // mscratch area for machine interreupt handler, one per hert
__attribute__ ((aligned (16))) uint64 Mstack0[4096 * NHART]; // Machine stack for machine interrupts, one per hart

extern void mtrapvec();

static inline void timerinit(){
    int cpu_id = cpuid();
    *((uint64*) a_mtimecmp(cpu_id)) = TIME + TIMER_INTERVAL;
    return;
}

static inline void enableInterrupts(){
    //Enable MACHINE_TIMER_INTERRUPT
    s_mie(1UL << MACHINE_TIMER_INTERRUPT);
    return;
}

static inline void delegateInterrupts(){
    s_mideleg(1UL << SUPERVISOR_EXTERNAL_INTERRUPT);
    return;
}

static inline void configMachineTrap(){
    uint64 id = cpuid();
    // set trap vector
    w_mtvec((uint64)&mtrapvec);
    // set mscratch[0] to the machine stack
    mscratch[32 * id] = (uint64) &Mstack0[4096 * (id+1)];
    w_mscratch((uint64) &mscratch[32 * id]);
}

static inline void Ret(){
    s_mstatus(1UL << SPIE | ((uint64) SUPERVISOR) << MPP);
    w_mepc((uint64)&main);
    w_satp((uint64) 0);
    asm volatile("mret");
}

static inline void physicalProtection(){
    w_pmpaddr0(0x3fffffffffffffull);
    w_pmpcfg0(0xf);
}

void start(){

    // DEBUG only
    uartinit();
    printf("[OK] uartinit\n");  


    // DEBUG commands


    // DEBUF END
    enableInterrupts();
    delegateInterrupts();
    configMachineTrap();
    timerinit();
    physicalProtection();
    Ret();
}
