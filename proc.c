#include "riscv.h"
#include "memlayout.h"
#include "alloc.h"
#include "printf.h"
#include "vm.h"
#include "proc.h"

extern char* edata;
extern void strapret();
extern char* trampoline;

struct proc proc_list[NPROC];

void procinit(){
    struct proc proc ;

    if ((proc.pt = alloc()) == 0){
        panic("Proc pt alloc failed\n");
    }
    void* pstack;
    if((pstack = alloc()) == 0){
        panic("Proc pstack alloc failed\n");
    }

    // Stack [0x2000 - 0x2fff]
    mappages(proc.pt,(void*) 0x2000, PAGESIZE, pstack, PTE_R | PTE_W | PTE_X);
    // User text [0x1000 - 0x1fff]
    mappages(proc.pt, (void*) 0x0, PAGESIZE, (void*) &edata, PTE_R | PTE_W | PTE_U | PTE_X);
    // UART
    mappages(proc.pt, (void*) UART0, PAGESIZE, (void*) UART0, PTE_R | PTE_W | PTE_U);
    // TRAMPOLINE
    mappages(proc.pt, (void*) TRAMPOLINE, PAGESIZE, (void*) &trampoline, PTE_R | PTE_U | PTE_X);

    


    // sscratch
    proc.regs[0] = MAKE_SATP((uint64)proc.pt);


    printf("proc.pt : %p\n",proc.pt);
    printf("pt : %p\n",proc.regs[0]);
    print_pt(proc.pt);
    
    w_sscratch((uint64) proc.regs);
    // User mode on return
    s_sstatus(((uint64) USER) << SPP);
    w_sepc((uint64) 0x0);

    strapret();

}
