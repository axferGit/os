#include "riscv.h"
#include "memlayout.h"
#include "alloc.h"
#include "printf.h"
#include "vm.h"
#include "proc.h"
#include "trap.h"


extern char* edata;
extern void uservecret(uint64,uint64);
extern char* trampoline;
extern t_pagetable kernel_pagetable;
struct proc proc_list[NPROC];

void procinit(){
    int i;
    for(i = 0 ; i < NPROC ; ++i){
        struct proc * proc;
        proc = &proc_list[i];
        
        // pagetable
        if ((proc->pt = alloc()) == 0){
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
        proc -> trapframe -> k_pt = (uint64) kernel_pagetable;
        proc->trapframe->k_ra = (uint64) &traphandler;

        void* k_stack;
        if ((k_stack = alloc()) == 0){
            panic("Fail to alloc k_stack\n");
        }
        mappages(proc->pt,(void*) TRAMPOLINE - (2*i +1)* PAGESIZE,PAGESIZE,k_stack,PTE_R | PTE_W);
        mappages(proc->pt,(void*) TRAMPOLINE - (2*i +2)* PAGESIZE,PAGESIZE, 0x0, 0x0);
        
        proc->trapframe->k_sp = TRAMPOLINE - (2*i +1)* PAGESIZE + PAGESIZE -1;
        

        // stack
        if((proc -> stack = alloc()) == 0){
            panic("Proc pstack alloc failed\n");
        }
        proc -> trapframe -> sp = (uint64) STACK + PAGESIZE - 1 ;
        mappages(proc -> pt,(void*) STACK, PAGESIZE, proc -> stack, PTE_U | PTE_X | PTE_R | PTE_W);

        // UART
        mappages(proc -> pt, (void*) UART0, PAGESIZE, (void*) UART0, PTE_U | PTE_R | PTE_W);

        // text
        mappages(proc -> pt, (void*) 0x0, PAGESIZE, (void*) &edata, PTE_U | PTE_X | PTE_R | PTE_W);
        
    }
    return;      
}

void proclaunch(){
    struct proc proc = proc_list[0];
    
    w_sepc((uint64) 0x0);
    s_sstatus(((uint64) USER) << SPP);
    printf("[OK] proclaunch\n");

    (((void (*) (uint64,uint64)) (TRAMPOLINE + ((uint64) &uservecret - (uint64) &trampoline)))) (TRAPFRAME, (uint64) MAKE_SATP(proc_list[0].pt));
}