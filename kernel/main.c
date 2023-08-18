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

    struct buf b;
    b.blk = 0;
    for (uint32 i = 0 ; i < 32; i++){
        printf(">>>>%i\n",i);
        memset(b.data,i,sizeof(b.data));
        diskrequest(VIRTIO_BLK_T_OUT,&b);
    }
    

    panic("Stop main\n");
    
    // Launch process
    scheduler();
}

