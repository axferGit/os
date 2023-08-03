#include "uart.h"
#include "plic.h"
#include "alloc.h"
#include "vm.h"
#include "proc.h"
#include "scheduler.h"
#include "printf.h"

void junk();

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
    
    printf(">>> BOOT OK <<<\n");

    scheduler();
}