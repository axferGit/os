#include "riscv.h"
#include "uart.h"
#include "plic.h"
#include "memlayout.h"
__attribute__ ((aligned (16))) char stack0[4096];


void test(){
    *((unsigned char *) 0x10000000UL) = 0x61;
    return test();
}

void loop(){
    return loop();
}

void mtrapvec(){
    _printf("trap !\n");

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
                _printf("UART0_IRQ\n");
                int c = uartgetc();
                if (c != -1){
                    uartputc(c);
                }
                else{
                    *((unsigned char *) 0x1000UL) = '.';
                }
            }

            // Complete the interrupt
            pliccomplete(id);
        }

        if (cause == MACHINE_TIMER_INTERRUPT){
            _printf("timer\n");
            int cpu_id = cpuid();
            *((uint64*) a_mtimecmp(cpu_id)) = TIME + 10000000UL;
        }
    }
    asm volatile("mret"); 
}

void start(){
    
    // initialize uart
    uartinit();
    _printf("[OK] uartinit\n");
    //plic init
    plicinit();
    _printf("[OK] plicinit\n");
    plicinithart();
    _printf("[OK] plichartinit\n");
    // set trap vector
    w_mtvec((uint64)&mtrapvec);
    // enable machine external interrupts
    w_mie(r_mie() | 1UL << 11); //0x7FF to enable every thing

    // enable Machine timer interrupts
    w_mie(r_mie() | 1UL << 7); //0x7FF to enable every thing
    int cpu_id = cpuid();
    *((uint64*) a_mtimecmp(cpu_id)) = 10000000UL;
    

    // enable machine interrupts
    w_mstatus(r_mstatus() | 1UL << 3);
    return;    
}
