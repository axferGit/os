#include "uart.h"
#include "plic.h"

extern void junk();

void loop(){
    _printf("loop");
    loop();
}

void main(){
    junk();
}