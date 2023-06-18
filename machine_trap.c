#include "riscv.h"
#include "uart.h"
#include "plic.h"
#include "memlayout.h"
#include "printf.h"


void mtraphandler(){
    printf("trap !\n");

    uint64 reg_cause = r_mcause();
    uint64 cause = reg_cause & 0x7fffffffffffffffL;

    // Interrupt
    if (reg_cause & (1L<<63)){ 

        // Machine extarnal interrupt
        if(cause == MACHINE_EXTERNAL_INTERRUPT){
            
            // Claim the device which triggered the interrupt
            uint32 id = plicclaim();
            
            // UART interrupts
            if (id == UART0_IRQ){
                printf("UART0_IRQ\n");
                int c = uartgetc();
                if (c != -1){
                    uartputc(c);
                }
                
            }

            // Complete the interrupt
            pliccomplete(id);
        }

        if (cause == MACHINE_TIMER_INTERRUPT){
            printf("timer\n");
            int cpu_id = cpuid();
            *((uint64*) a_mtimecmp(cpu_id)) = (TIME + TIMER_INTERVAL);
        }
    }
    return; 
}