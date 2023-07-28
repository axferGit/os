#include "types.h"
#include "memlayout.h"
#include "riscv.h"
#include "main.h"
#include "proc.h"

__attribute__ ((aligned (16))) char stack0[4096 * NHART]; // initial stack, one per hart
__attribute__ ((aligned (16))) struct trapframe mscratch[NHART]; // mscratch area for machine interrupt handler, one per hart
__attribute__ ((aligned (16))) uint64 Mstack0[4096 * NHART]; // Machine stack for machine interrupts, one per hart

extern void mtrapvec();

static inline void timerinit(){
    *((uint64*) CLINT_MTIMECMP(r_mhartid())) = TIME + TIMER_INTERVAL;
    return;
}
// Enable interrupts
static inline void ieinit(){
    s_mie(1 << MTI);
    return;
}
// Delegate traps (interrupts and exceptions) to corresponding modes
static inline void trapdelegateinit(){
    //s_mideleg(1 << SSI | 1 << STI | 1 << SEI);
    s_medeleg(1 << ENVIRONMENT_CALL_FROM_U_MODE);
    return;
}

static inline void mtvecinit(){
    uint64 hartid = r_mhartid();
    // set trap vector
    w_mtvec((uint64)&mtrapvec);
    // set mscratch[0] to the machine stack
    mscratch[hartid].k_sp = (uint64) &Mstack0[4096 * (hartid+1)];
    w_mscratch((uint64) &mscratch[hartid]);
}

static inline void mret(){
    s_mstatus(1UL << SPIE | SUPERVISOR << MPP);
    w_mepc((uint64)&main);
    w_satp((uint64) 0);
    asm volatile("mret");
}

static inline void pmpinit(){
    // w_pmpaddr0(1 << 2); // MAx address
    // w_pmpcfg0(0b01101111); // TOR (top of range)
    w_pmpaddr0(0x3fffffffffffffull);
    w_pmpcfg0(0xf);
    return;
}



void start(){
    timerinit();
    ieinit();
    trapdelegateinit();
    mtvecinit();
    pmpinit();
    mret();
}
