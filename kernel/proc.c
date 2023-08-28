#include "riscv.h"
#include "memlayout.h"
#include "alloc.h"
#include "printf.h"
#include "vm.h"
#include "proc.h"
#include "trap.h"
#include "ssys.h"
#include "trampoline.h"
#include "swtch.h"
#include "spinlock.h"
#include "fs.h"

extern char* edata;
extern char* trampoline;
extern uint64 euser_text;
extern uint64 euser_data;
extern uint64 euser_rodata;
extern uint64 euser_bss;

struct proc proc_list[NPROC];
struct cpu cpu_list[NHART];

void procfirstlaunch(){
    struct proc * p = myproc();
    release(&p->lk);
    usertrapret();
}

void procinit(){
    int i;
    for(i = 0 ; i < NPROC ; ++i){
        struct proc * proc;
        proc = &proc_list[i];

        proc -> pid = i;
        spinlockinit(&proc->lk,"spinlock process");
        
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
        mappages(kernel_pagetable,(void*) TRAPFRAME - (2*(i+1)) * PAGESIZE, PAGESIZE, 0x0, 0x0); // Guard page
        
        proc -> trapframe -> k_sp = (TRAPFRAME - (2*(i+1) -1)* PAGESIZE) + PAGESIZE;
        

        // stack
        if((proc -> stack = alloc()) == 0){
            panic("Proc stack alloc failed\n");
        }
        proc -> trapframe -> sp = ((uint64) STACK) + PAGESIZE;
        mappages(proc -> pt,(void*) STACK, PAGESIZE, proc -> stack, PTE_U | PTE_R | PTE_W);

        // UART
        mappages(proc -> pt, (void*) UART0, PAGESIZE, (void*) UART0, PTE_U | PTE_R | PTE_W);

        // text
        mappages(proc -> pt, (void*) 0x0, PAGESIZE, (void*) &edata, PTE_U | PTE_X | PTE_R | PTE_W);

        // rodata.str1.8
        mappages(proc->pt, (void*) PAGESIZE, PAGESIZE, (void*) &euser_data, PTE_U | PTE_R | PTE_W);

        // context (called to launch the process)
        proc -> context.sp = proc -> trapframe -> k_sp; // kernel sp
        proc -> context.ra = (uint64) &procfirstlaunch; // ra points to usertrapret
        proc -> trapframe -> pc = 0; // pc points to the first instruction
        
        ofinit(proc);

        proc -> state = RUNNABLE; 

    }
    return;      
};

// return a pointer to current hart's process
struct proc * myproc() {
    return cpu_list[hartid()].proc;
}

// Return the cpu of current hart
struct cpu * mycpu(){
    return &cpu_list[hartid()];
}

// Switch from user process to scheduler process
// p->lk must be locked before
// p->lk is locked after
void sched(){
    swtch(&(myproc()->context), &(mycpu() ->context));
    return;
}

// Sleep proc on channel [chan] with spinlock acquired [lk]
// [lk] is locked on return
void sleep(void* chan, struct spinlock* lk){
    printf("Went on sleep\n");
    struct proc* p = myproc();
    if(lk != &p->lk){
        acquire(&p->lk);
        release(lk);
    }
    
    p->chan = chan;
    p->state = SLEEPING;

    sched();

    if(lk != &p->lk){
        release(&p->lk);
        acquire(lk);   
    }

    return;   
}

// Wakeup all processes sleeping on chan [chan]
// must be called without any proc->lk locked !
void wakeup(void* chan){
    struct proc* p;
    for(p = &proc_list[0]; p < &proc_list[NPROC]; p++){
        acquire(&p->lk);
        if((p->state == SLEEPING) && (p->chan == chan)){
            p->state = RUNNABLE;
        }
        release(&p->lk);
    }
    return;
}

