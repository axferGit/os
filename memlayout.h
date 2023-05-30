// UART
#define UART0 0x10000000UL
#define RHR 0b0
#define THR 0b0
#define IER 0b1
#define ISR 0b10
#define FCR 0b10
#define LCR 0b11
#define LSR 0b101

//PLIC
#define PLIC 0x0c000000UL
#define a_PLIC_PRIORITY(source) (PLIC + (source) * 4)
#define a_PLIC_MACHINE_INTERRUPT(hart) (PLIC + 0x2000 + (hart) * 0x100)
#define a_PLIC_MACHINE_THRESHOLD(hart) (PLIC + 0x200000 + (hart) * 0x2000)
#define UART0_IRQ 10