#include "riscv.h"
#include "uart.h"
#include "plic.h"
#include "memlayout.h"
#include "printf.h"
#include "vm.h"
#include "proc.h"

extern void mtrapvecret();
extern struct trapframe mscratch[NHART];

char* cause_interrupt[] = {
    [0] "User sofware interrupt",
    [1] "Supervisor software interrupt",
    [3] "Machine software interrupt",
    [4] "User timer interrupt",
    [5] "Supervisor timerinterrupt",
    [7] "Machine timer interrupt",
    [8] "User external interrupt",
    [9] "Supervisor external interrupt",
    [11] "Machine external interrupt"
};

char* cause_exception[] = {
    [0] "Instruction address misaligned",
    [1] "instruction access fault",
    [2] "Illegal instruction",
    [3] "Breakpoint",
    [4] "Load address misaligned",
    [5] "Load access fault",
    [6] "Store/AMO address misaligned",
    [7] "Store/AMO access fault",
    [8] "Environment call from U-mode",
    [9] "Environment call from S-mode",
    [11] "Environment call from M-mode",
    [12] "Instruction page fault",
    [13] "Load page fault",
    [15] "Store/Amo page fault"
};

void mtraphandler(){
    printf("Machine trap!\n");

    uint64 mcause = r_mcause();
    uint64 cause = mcause & 0x7fffffffffffffffL;

    // Interrupt
    if (mcause >> 63){
        switch (cause){
            case MTI:
                printf("%s\n",cause_interrupt[cause]);
                *((uint64*) CLINT_MTIMECMP(r_mhartid())) = (TIME + TIMER_INTERVAL);
                break;
            
            default:
                printf("Interrupt (%p) not handled in machine mode !\n",cause);
                panic("");
                break;
        }
    }

    // Exception
    else {
        switch (cause){
            case ENVIRONMENT_CALL_FROM_S_MODE:
                printf("%s\n",cause_exception[cause]);
                w_mepc(r_mepc() + 4);
                if (mscratch[r_mhartid()].a7 == 1){
                    mscratch[r_mhartid()].a0 = r_mhartid();
                }
                else{
                    panic("bad S_SYSCALL value\n");
                }
                break;

            default:
                printf("Exception (%p) not handled in machine mode !\n",cause);
                printf("mepc  : %p\n",r_mepc());
                printf("mtval : %p\n",r_mtval());
                printf("satp  : %p\n",r_satp());
                panic("");
                break;
        }
    }
    return; 
}

void straphandler(){
    printf("\ntrap S mode\n");
    printf("ok trap\n");
    return;
}