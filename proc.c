#include "riscv.h"
#include "memlayout.h"
#include "alloc.h"
#include "printf.h"
#include "vm.h"
#include "proc.h"

extern char* edata;
extern char* uservecret;
extern char* trampoline;

struct proc proc_list[NPROC];

void procinit(){
    int i;
    for(i = 0 ; i < NPROC ; ++i){
        struct proc * proc;
        proc = &proc_list[i];
        
        // pagetable
        if ((proc ->pt = alloc()) == 0){
            panic("Proc pt alloc failed\n");
        }
        
        // trampoline
        mappages(proc -> pt, (void*) TRAMPOLINE, PAGESIZE, (void*) &trampoline, PTE_X);
        
        // trapframe
        if ((proc -> trapframe = (struct trapframe *) alloc()) == 0){
            panic("Proc trapframe alloc failed\n");
        }
        mappages(proc -> pt, (void*) TRAPFRAME, PAGESIZE, (void*) proc -> trapframe, PTE_R | PTE_W);

        // stack
        if((proc -> stack = alloc()) == 0){
            panic("Proc pstack alloc failed\n");
        }
        proc -> trapframe -> sp = (uint64) STACK + PAGESIZE - 1 ;
        mappages(proc -> pt,(void*) STACK, PAGESIZE, proc -> stack, PTE_U | PTE_R | PTE_W | PTE_X);

        // UART
        mappages(proc -> pt, (void*) UART0, PAGESIZE, (void*) UART0, PTE_R | PTE_W | PTE_U);

        // text
        mappages(proc -> pt, (void*) 0x0, PAGESIZE, (void*) &edata, PTE_U | PTE_X | PTE_R | PTE_W);
        
    }
    return;      
}

void proclaunch(){
    struct proc proc = proc_list[0];
    
    printmemory();
    printvm();
    printf("proc0\n");
    printf("pt : %p\n",proc.pt);
    printf("trapframe : %p\n",proc.trapframe);

    printf("uservecret %p\n",(uint64) &uservecret);
    printf("trampoline %p\n",(uint64) &trampoline);
    printf("TRAMPOLINE %p\n",(uint64) TRAMPOLINE);
    printf("TRAMPOLINE + uservecret - trampoline %p\n",(uint64) (TRAMPOLINE + ((uint64) &uservecret - (uint64) &trampoline)));
    w_sepc((uint64) 0x0);
    s_sstatus(((uint64) USER) << SPP);

    ((void (*) (uint64,uint64)) (TRAMPOLINE + ((uint64) &uservecret - (uint64) &trampoline))) (TRAPFRAME, (uint64) MAKE_SATP(proc_list[0].pt));
}