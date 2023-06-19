#include "riscv.h"

void w_mtvec(uint64 f){
    asm volatile("csrw mtvec, %0" : : "r" (f));
}

uint64 r_mstatus(){
    uint64 x = 0;
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
    uint64 x = 0;
    asm volatile("csrr %0, mie" : "+r" (x));
    return x;
}

void w_mie(uint64 x){
    asm volatile("csrw mie, %0" : : "r" (x));
    return;
}

void s_mie(uint64 x){
    asm volatile("csrs mie, %0" : : "r"(x));
    return;
}

uint64 cpuid(){
    uint64 x = 0;
    asm volatile("csrr %0, mhartid" : "+r" (x));
    return x;
}

uint64 r_mcause(){
    uint64 x = 0;
    asm volatile("csrr %0, mcause" : "+r" (x));
    return x;
}

void s_mideleg(uint64 x){
    asm volatile("csrs mideleg, %0" : : "r"(x));
    return;
}

void w_mepc(uint64 x){
    asm volatile("csrw mepc, %0": : "r" (x));
    return;
}

void w_pmpaddr0(uint64 x)
{
  asm volatile("csrw pmpaddr0, %0" : : "r" (x));
}

void w_pmpcfg0(uint64 x)
{
  asm volatile("csrw pmpcfg0, %0" : : "r" (x));
}

void w_mscratch(uint64 x){
    asm volatile("csrw mscratch, %0" : : "r" (x));
    return;
}

void w_satp(uint64 x){
    asm volatile("csrw satp, %0" : : "r" (x));
    return;
}

uint64 r_satp(){
    uint64 x = 0;
    asm volatile("csrr %0, satp" : "+r" (x));
    return x;
}