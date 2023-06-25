#include "riscv.h"
#include "memlayout.h"
#include "alloc.h"
#include "printf.h"

extern char* edata;

typedef struct proc {
    uint64 pid;
    t_pagetable pt;
    uint64 regs[32];
} t_proc;

t_proc proc_list[NPROC];
uint64 process_id = 0;

void initproc(){
    t_proc proc = proc_list[0] ;
    proc.pid = (process_id++);
    if ((proc.pt = alloc()) == 0){
        panic("Proc pt alloc failed\n");
    }
    t_pagetable ptext;
    if((ptext = alloc()) == 0){
        panic("Proc ptext alloc failed\n");
    }

    //alloc stack
    //alloc text
    // set sp, pc, pagetable
    //go back user mode
}