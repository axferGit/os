#include "uart.h"
#include "plic.h"
#include "printf.h"
#include "alloc.h"

extern void junk();

void loop(){
    printf("loop");
    loop();
}

void main(){
    uartinit();
    printf("[OK] uartinit\n");
    allocinit();
    printf("[OK] pageinit\n");
    junk();
}