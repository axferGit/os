#include "uart.h"
#include "plic.h"
#include "printf.h"
#include "alloc.h"
#include "memlayout.h"
#include "vm.h"
#include "proc.h"

extern void junk();

void loop(){
    printf("loop");
    loop();
}
extern char* hd_pagetable;

void main(){
    uartinit();
    printf("[OK] uartinit\n");
    allocinit();
    printf("[OK] allocinit\n");
    kvminit();
    printf("[OK] kvminit\n");
    kvminithart();
    printf("[OK] kvminihart\n");

    procinit();

    junk();
}