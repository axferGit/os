#include "riscv.h"

void w_mtvec(uint64 f){
    asm volatile("csrw mtvec, %0" : : "r" (f));
}

void w_stvec(uint64 x){
    asm volatile("csrw stvec, %0" : :"r" (x));
    return;
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

void s_medeleg(uint64 x){
    asm volatile("csrs medeleg, %0" : : "r" (x));
    return;
}

uint64 r_mepc(){
    uint64 x = 0;
    asm volatile("csrr %0, mepc" : "+r"(x));
    return x;
}

void w_mepc(uint64 x){
    asm volatile("csrw mepc, %0": : "r" (x));
    return;
}

uint64 r_mtval(){
    uint64 x = 0;
    asm volatile("csrr %0, mtval" : "+r"(x));
    return x;
}

void w_mtval(uint64 x){
    asm volatile("csrw mtval, %0": : "r" (x));
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

void sfence_vma(){
    asm volatile("sfence.vma zero, zero");
    return;
}

void w_sscratch(uint64 x){
    asm volatile("csrw sscratch, %0" : :"r" (x));
    return;
}

void s_sstatus(uint64 x){
    asm volatile("csrs sstatus, %0" : : "r"(x));
    return;
}

void w_sepc(uint64 x){
    asm volatile("csrw sepc, %0" : : "r" (x));
    return;
}