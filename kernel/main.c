#include "uart.h"
#include "plic.h"
#include "alloc.h"
#include "vm.h"
#include "proc.h"
#include "scheduler.h"
#include "printf.h"
#include "disk.h"
#include "fs.h"

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

    
    uint8 buf[2*BLOCK_SIZE];
    memset(buf,0,sizeof(buf));

    struct inode * in = openi(1);
    uint32 i = readi(in,0,2*BLOCK_SIZE,buf);
    printf("nb read: %i\n",i);
    printf("%s\n",buf);

    panic("Stop main\n");
    
    // Launch process
    scheduler();
}

