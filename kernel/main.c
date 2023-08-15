#include "uart.h"
#include "plic.h"
#include "alloc.h"
#include "vm.h"
#include "proc.h"
#include "scheduler.h"
#include "printf.h"
#include "disk.h"

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
    diskinit();
    printf("[OK] diskinit\n");

    printf(">>> BOOT OK <<<\n");

    diskread();


    panic("Stop main\n");
    
    scheduler();
}

