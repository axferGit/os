#include "uart.c"

typedef unsigned long uint64;

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

void w_mtvec(uint64 f){
    asm volatile("csrw mtvec, %0" : : "r" (f));
}

uint64 r_mstatus(){
    uint64 x;
    asm volatile("csrr %0, mstatus" : "+r" (x):); /// a voir si bonnes operandes
    return x;
}

void w_mstatus(uint64 x){
    asm volatile("csrw mstatus, %0": : "r" (x));
    return;
}

void s_mstatus(uint64 x){
    asm volatile("csrs mstatus, %0": : "r"(x));
    return;
}

void start(){
    
    // initialize uart
    uartinit();
    // set trap vector
    w_mtvec((uint64)&mtrapvec);
    // enable interrupts
    w_mstatus(r_mstatus() | 0b1L << 3);

    
}

