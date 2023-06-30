#include "riscv.h"
#include "memlayout.h"
#include "alloc.h"
#include "printf.h"
#include "vm.h"

extern char* edata;
extern void strapret();
extern char* trampoline;
typedef struct proc {
    uint64 pid;
    t_pagetable pt;
    uint64 regs[32];
} t_proc;

t_proc proc_list[NPROC];
uint64 process_id = 0;

void procinit(){
    t_proc proc ;
    proc.pid = (process_id++);
    
    if ((proc.pt = alloc()) == 0){
        panic("Proc pt alloc failed\n");
    }
    void* pstack;
    if((pstack = alloc()) == 0){
        panic("Proc pstack alloc failed\n");
    }

    // Stack [0x2000 - 0x2fff]
    mappages(proc.pt,(void*) 0x2000, PAGESIZE, pstack, PTE_READ | PTE_WRITE | PTE_EXECUTE);
    // User text [0x1000 - 0x1fff]
    mappages(proc.pt, (void*) 0x1000, PAGESIZE, (void*) &edata, PTE_READ | PTE_WRITE | PTE_U | PTE_EXECUTE);
    // UART
    mappages(proc.pt, (void*) UART0, PAGESIZE, (void*) UART0, PTE_READ | PTE_WRITE | PTE_U);
    // TRAMPOLINE
    mappages(proc.pt, (void*) &trampoline, PAGESIZE, (void*) &trampoline, PTE_READ | PTE_U | PTE_EXECUTE);

    


    // sscratch
    proc.regs[0] = (SV39 | ((uint64)proc.pt / PAGESIZE));


    printf("proc.pt : %p\n",proc.pt);
    printf("pt : %p\n",proc.regs[0]);
    print_pt(proc.pt);
    
    w_sscratch((uint64) proc.regs);
    // User mode on return
    s_sstatus(((uint64) USER) << SPP);
    w_sepc((uint64) 0x1000);

    strapret();

}
