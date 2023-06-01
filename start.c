#include "riscv.h"
#include "uart.c"
#include "plic.c"

__attribute__ ((aligned (16))) char stack0[4096];


void test(){
    *((unsigned char *) 0x10000000UL) = 0x61;
    return test();
}

void loop(){
    return loop();
}

void mtrapvec(){
    int c = uartgetc();
    if (c != -1){
        uartputc(c);
    }
    *((unsigned char *) 0x10000000UL) = 0x62;
    return;
}

void start(){
    // initialize uart
    uartinit();;
    //plic init
    plicinit();
    plicinithart();
    // set trap vector
    w_mtvec((uint64)&mtrapvec);
    // enable machine external interrupts
    w_mie(r_mie() | 1UL << 11); //0x7FF to enable every thing
    // enable machine interrupts
    w_mstatus(r_mstatus() | 0b1L << 3);
    loop();    
}

int main(){
    
}