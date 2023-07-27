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
                printf("Reserved (%p)\n",cause);
                panic("");
                break;
        }
    }

    // Exception
    else {
        switch (cause){

        case ENVIRONMENT_CALL_FROM_S_MODE:
            printf("%s\n",cause_exception[cause]);
            printf("mepc  : %p\n",r_mepc());
            w_mepc(r_mepc() + 4);
            if (mscratch[r_mhartid()].a7 == 1){
                mscratch[r_mhartid()].a0 = r_mhartid();
            }
            else{
                panic("bad S_SYSCALL value\n");
            }
            break;

        default:
            if(cause < (sizeof(cause_exception)/8)){
                printf("%s\n",cause_exception[cause]);
            }
            else{
                printf("Reserved (%p)\n",cause);
            }

            printf("mepc : %p\nmtval : %p\n",r_mepc(),r_mtval());

            panic("");
            break;
        }
    }
    return mtrapvecret(); 
}

void traphandler(){
    panic("\ntrap S mode\n");
    return;
}

// {
//     printf("Machine trap!\n");

//     uint64 mcause = r_mcause();
//     uint64 cause = mcause & 0x7fffffffffffffffL;

//     // Interrupt
//     if (mcause >> 63){
//         switch (cause){

//             case MEI:
//                 // Claim the device which triggered the interrupt
//                 uint32 id = plicclaim();
                
//                 // UART interrupts
//                 if (id == UART0_IRQ){
//                     printf("UART0_IRQ\n");
//                     int c = uartgetc();
//                     if (c != -1){
//                         uartputc(c);
//                     }                
//                 }

//                 // Complete the interrupt
//                 pliccomplete(id);

//                 break;

//             case MTI:
//                 printf("%s\n",cause_interrupt[cause]);
//                 //int cpu_id = cpuid();
//                 uint64 cpu_id = 0;
//                 *((uint64*) CLINT_MTIMECMP(cpu_id)) = (TIME + TIMER_INTERVAL);
//                 break;
            
//             default:
//                 printf("Reserved (%p)\n",cause);
//                 panic("");
//                 break;
//         }
//     }

//     // Exception
//     else {
//         switch (cause){

//         case ENVIRONMENT_CALL_FROM_S_MODE:
//             printf("%s\n",cause_exception[cause]);
//             printf("mepc  : %p\n",r_mepc());
//             w_mepc(r_mepc() + 4);
//             if (mscratch[r_mhartid()].a7 == 1){
//                 mscratch[r_mhartid()].a0 = r_mhartid();
//             }
//             else{
//                 panic("bad S_SYSCALL value\n");
//             }
//             break;

//         case LOAD_PAGE_FAULT:
//             printf("%s\n",cause_exception[cause]);
//             printf("mepc  : %p\n",r_mepc());
//             printf("mtval : %p\n",r_mtval());
//             printf("satp  : %p\n",r_satp());
//             panic("");
//             break;

//         case INSTRUCTION_PAGE_FAULT:
//             printf("%s\n",cause_exception[cause]);
//             printf("mepc  : %p\n",r_mepc());
//             printf("mtval : %p\n",r_mtval());
//             printf("satp  : %p\n",r_satp());
//             panic("");
//             break;

//         default:
//             if(cause < (sizeof(cause_exception)/8)){
//                 printf("%s\n",cause_exception[cause]);
//             }
//             else{
//                 printf("Reserved (%p)\n",cause);
//             }

//             printf("mepc : %p\nmtval : %p\n",r_mepc(),r_mtval());

//             panic("");
//             break;
//         }
//     }
//     return mtrapvecret(); 
// }