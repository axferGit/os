#include "uart.c"

__attribute__ ((aligned (16))) char stack0[4096];

void loop(){
    return loop();
}

void start(){
    // initialize uart
    uartinit();;
    //plic init
    _printf("ok\n");
    _printf("a\n");
    loop();    
}
