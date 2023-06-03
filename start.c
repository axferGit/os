#include "riscv.h"
#include "uart.h"
#include "plic.h"
#include "memlayout.h"
__attribute__ ((aligned (16))) char stack0[4096];

void loop(){
    _printf("loop");
    loop();
}

extern void junk();

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
                
            }

            // Complete the interrupt
            pliccomplete(id);
        }

        if (cause == MACHINE_TIMER_INTERRUPT){
            _printf("timer\n");
            int cpu_id = cpuid();
            *((uint64*) a_mtimecmp(cpu_id)) = TIME + 100000UL;
        }
    }
    asm volatile("mret"); 
}

void timerinit(){
    int cpu_id = cpuid();
    *((uint64*) a_mtimecmp(cpu_id)) = 100000UL;
}


void start(){

    //Enable MACHINE_TIMER_INTERRUPT
    s_mie(1UL << MACHINE_TIMER_INTERRUPT);
    
    // Delegate interrupt
    s_mideleg(1UL << SUPERVISOR_EXTERNAL_INTERRUPT);

    // set trap vector
    w_mtvec((uint64)&mtrapvec);

    timerinit();
    
    // Return
    s_mstatus(1UL << 5 | 01UL << 11);
    w_mepc((uint64)&junk);

    w_pmpaddr0(0x3fffffffffffffull);
    w_pmpcfg0(0xf);


    asm volatile("mret");    
}
