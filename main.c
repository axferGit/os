#include "uart.h"
#include "plic.h"
#include "printf.h"


extern void junk();

void loop(){
    _printf("loop");
    loop();
}

void main(){

    junk();
}