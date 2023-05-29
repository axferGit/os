#define UART0 0x10000000UL

#define RHR 0b0
#define THR 0b0
#define IER 0b1
#define ISR 0b10
#define FCR 0b10
#define LCR 0b11
#define LSR 0b101

#define addrReg(Reg) ((volatile unsigned char *) (UART0 + Reg))
#define readReg(Reg) (*(addrReg(Reg)))
#define writeReg(Reg,v) (*(addrReg(Reg)) = (v))

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
    while(!(readReg(LSR) & 0b100000)){
        ; // wait for THR empty
    }
    writeReg(THR,c);
    return;
}

// read 1 character from UART
// return -1 if none is waiting (error)
int uartgetc(void){
    if (readReg(LSR) & 0x01){
        return readReg(RHR);
    }
    else{
        return -1;
    }
}

void _printf(char* string){
    for(int i; string[i] != 0x00; i=i+1){
        uartputc(string[i]);
    }
    return;
}