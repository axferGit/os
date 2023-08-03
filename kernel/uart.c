#include "memlayout.h"
#include "uart.h"

#define addrReg(Reg) ((volatile unsigned char *) (UART0 + Reg))
#define readReg(Reg) (*(addrReg(Reg)))
#define writeReg(Reg,v) *(addrReg(Reg)) = (v)

void uartinit(){
    // Disable interrupts
    writeReg(IER,0x00);

    // Enter special mode for baud rate
    writeReg(LCR,0x80);

    // Set baud rate to 38.4K
    writeReg(0,0x03);
    writeReg(1,0x00);

    // Leave special mode
    // Set 8 bits word length, no parity
    writeReg(LCR,0x03);

    // enable FIFO and reset TX and RW buffers
    writeReg(FCR,0X07);

    // enable receive interrupts
    writeReg(IER,0x01);
    
    return;
}
// write 1 character tu UART.
// block until the character is written
void uartputc(char c){
    while(!(readReg(LSR) & 1 << 5)){
        ; // wait for THR empty
    }
    writeReg(THR,c);
    return;
}

// read 1 character from UART
// return the charecter or return -1 if no character is availible (error)
int uartgetc(){
    if (readReg(LSR) & 0x01){
        return readReg(RHR);
    }
    else{
        return -1;
    }
}