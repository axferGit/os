#include "riscv.h"
#include "memlayout.h"
#include "alloc.h"
#include "printf.h"
#include "vm.h"
#include "proc.h"
#include "trap.h"
#include "ssys.h"
#include "trampoline.h"

extern char* edata;
extern char* trampoline;

struct proc proc_list[NPROC];
struct cpu cpu_list[NHART];

void procinit(){
    int i;
    for(i = 0 ; i < NPROC ; ++i){
        struct proc * proc;
        proc = &proc_list[i];

        proc -> pid = i;
        
        // pagetable
        if ((proc -> pt = alloc()) == 0){
            panic("Proc pt alloc failed\n");
        }
        
        // trampoline
        mappages(proc -> pt, (void*) TRAMPOLINE, PAGESIZE, (void*) &trampoline, PTE_X);
        
        // trapframe
        if ((proc -> trapframe = (struct trapframe *) alloc()) == 0){
            panic("Proc trapframe alloc failed\n");
        }
        mappages(proc -> pt, (void*) TRAPFRAME, PAGESIZE, (void*) proc -> trapframe, PTE_R | PTE_W);
        
        // kernel
        proc -> trapframe -> k_pt = (uint64) MAKE_SATP(kernel_pagetable);
        proc -> trapframe -> k_trap = (uint64) &usertrap;

        void* k_stack;
        if ((k_stack = alloc()) == 0){
            panic("Fail to alloc k_stack\n");
        }
        mappages(kernel_pagetable,(void*) TRAPFRAME - (2*(i+1) - 1) * PAGESIZE, PAGESIZE, k_stack, PTE_R | PTE_W);
        mappages(kernel_pagetable,(void*) TRAPFRAME - (2*(i+1)) * PAGESIZE, PAGESIZE, 0x0, 0x0);
        
        proc -> trapframe -> k_sp = TRAPFRAME - (2*(i+1) -1)* PAGESIZE + PAGESIZE -1;
        

        // stack
        if((proc -> stack = alloc()) == 0){
            panic("Proc stack alloc failed\n");
        }
        proc -> trapframe -> sp = ((uint64) STACK) + PAGESIZE - 1 ;
        mappages(proc -> pt,(void*) STACK, PAGESIZE, proc -> stack, PTE_U | PTE_R | PTE_W);

        // UART
        mappages(proc -> pt, (void*) UART0, PAGESIZE, (void*) UART0, PTE_U | PTE_R | PTE_W);

        // text
        mappages(proc -> pt, (void*) 0x0, PAGESIZE, (void*) &edata, PTE_U | PTE_X | PTE_R | PTE_W);

        // context (called to launch the process)
        proc -> context.sp = proc -> trapframe -> k_sp; // kernel sp
        proc -> context.ra = (uint64) &usertrapret; // ra points to usertrapret
        proc -> trapframe -> pc = 0;
        proc -> state = RUNNABLE; 

    }
    return;      
};

// return a pointer to current hart's process
struct proc * myproc() {
    return cpu_list[hartid()].proc;
}