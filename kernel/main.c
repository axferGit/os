#include "uart.h"
#include "plic.h"
#include "printf.h"
#include "alloc.h"
#include "memlayout.h"
#include "vm.h"
#include "proc.h"
#include "riscv.h"

extern void junk();

void loop(){
    printf("loop");
    loop();
}
extern char* hd_pagetable;
extern uint64 hartid();
void main(){
    uartinit();
    printf("[OK] uartinit\n");
    plicinit();
    printf("[OK] plicinit\n");
    plicinithart();
    printf("[OK] plicinithart\n");
    allocinit();
    printf("[OK] allocinit\n");
    kvminit();
    printf("[OK] kvminit\n");
    kvminithart();
    printf("[OK] kvminihart\n");
    procinit();
    printf("[OK] procinit\n");
    
    proclaunch();


    junk();
}