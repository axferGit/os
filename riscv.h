typedef unsigned long uint64;

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

uint64 r_mie(){
    uint64 x;
    asm volatile("csrr %0, mie" : "+r" (x));
    return x;
}

void w_mie(uint64 x){
    asm volatile("csrw mie, %0" : : "r" (x));
    return;
}

uint64 cpuid(){
    uint64 x;
    asm volatile("csrr %0, mhartid" : "+r" (x));
    return x;
}