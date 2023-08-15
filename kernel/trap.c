#include "riscv.h"
#include "uart.h"
#include "plic.h"
#include "memlayout.h"
#include "printf.h"
#include "vm.h"
#include "proc.h"
#include "ssys.h"
#include "trap.h"
#include "uart.h"
#include "swtch.h"


extern void uservecret(uint64,uint64);
extern void uservec();
extern char* trampoline;
extern struct cpu cpu_list[NHART];

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

char* ssys[] = {
    [1] "S_SYSCALL_HARTID"
};

char* usys[] = {
    [1] "U_SYSCALL_TEST"
};

void mtraphandler(){
    printf("\n##### MACHINE TRAP HANDLER #####\n");

    uint64 mcause = r_mcause();
    uint64 cause = mcause & 0x7fffffffffffffffL;

    // Interrupt
    if (mcause >> 63){
        switch (cause){
            case MTI:
                printf("%s\n",cause_interrupt[cause]);
                s_mip(1 << SSI);
                *((uint64*) CLINT_MTIMECMP(r_mhartid())) = (TIME + TIMER_INTERVAL);
                break;
            case MEI:
                printf("%s\n",cause_interrupt[cause]);
                printf("Source: %i\n", plicclaim());
                break;
            default:
                printf("Interrupt \"%s\" not handled in machine mode !\n",cause_interrupt[cause]);
                panic("");
                break;
        }
    }

    // Exception
    else {
        switch (cause){
            case ENVIRONMENT_CALL_FROM_S_MODE:
                //printf("%s\n",cause_exception[cause]);
                switch (mscratch[r_mhartid()].a7) {
                    case S_SYSCALL_HARTID:
                        w_mepc(r_mepc() + 4);
                        mscratch[r_mhartid()].a0 = r_mhartid();
                        //printf("%s\n",ssys[S_SYSCALL_HARTID]);
                        break;
                    
                    default:
                        panic("bad S_SYSCALL value\n");
                        break;
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
    printf("##########\n");
    return; 
}

void usertrap(){
    //printf("\n##### USERTRAP #####\n");
    uint64 id = hartid();
    uint64 scause = r_scause();
    uint64 cause = scause & 0x7fffffffffffffffL;

    struct proc * proc = myproc();
    proc -> trapframe -> pc = r_sepc(); // save sepc because the context will change


    // Interrupts
    if(scause >> 63){
        switch (cause) {
            case (SSI):
                printf("SSI\n");
                c_sip(1 << SSI); // clear SIP
                
                proc ->state = RUNNABLE;

                // switch to scheduler (on main thread)
                swtch(&(proc->context), &(cpu_list[id].context));
                // resume from scheduler (on main thread)

                break;
            
            default:
                printf("Interruptions not handled in supervisor mode\n");
                printf("cause : %p\n",cause);
                panic("");
                break;
      }     
    }

    // Exceptions
    else{
        switch (cause)
        {
            case ENVIRONMENT_CALL_FROM_U_MODE:
                //printf("%s\n",cause_exception[cause]);
                //match nulber of syscall stored in a7
                switch(cpu_list[id].proc -> trapframe -> a7){
                    case(U_SYSCALL_TEST):
                        //printf("%s\n",usys[U_SYSCALL_TEST]);
                        proc -> trapframe -> pc += 4;
                        //printf(">>>>>>>>>>>>>>>> ");
                        uartputc((char) (myproc() -> trapframe -> a0));
                        //printf("%p",cpu_list[id].proc -> trapframe -> a0);
                        //printf(" <<<<<<<<<<<<<<<<\n");
                        break;
                    
                    default:
                        panic("Bad U_SYSCALL\n");
                        break;
                }
                break;
            
            default:
                printf("Interruption not handled in supervisor mode\n");
                panic("");
                break;
        }
    }
    //printf("##########\n");
    usertrapret();
    return;
}

// jump to uservecret (trampline.S) with right arguments
void usertrapret(){
    w_sepc(myproc()->trapframe->pc); //restore pc
    s_sstatus(((uint64) USER) << SPP);
    w_stvec((uint64)(TRAMPOLINE + ((uint64) &uservec - (uint64) &trampoline)));

    uint64 fn = (TRAMPOLINE + ((uint64) &uservecret - (uint64) &trampoline));
    ((void (*) (uint64,uint64)) fn) (TRAPFRAME, (uint64) MAKE_SATP(myproc()->pt));
    return;
}

