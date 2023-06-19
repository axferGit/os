// QEMU
#define KERNBASE (0x80000000UL)

// CPU
#define NHART 1 //maximum number of cores

// DRAM
#define PHYSTOP (KERNBASE + 128 * 1024 * 1024)

// PAGE
#define SV39 (0x8UL << 60)
#define PAGESIZE 4096
#define PTE_CFG_BITS 10
#define PTE_CFG_MASK 0x1ff
#define INDEXLEVEL(va,level) (((va) >> (9*(level) + 12)) & 0x1ff)
#define PAGE_VALID 1
#define PAGE_READ (1 << 1)
#define PAGE_WRITE (1 << 2)
#define PAGE_EXECUTE (1 << 3)

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
#define a_PLIC_MACHINE_CLAIM(hart) (PLIC + 0x200004 + (hart) * 0x2000)
#define a_PLIC_MACHINE_COMPLETE(hart) (a_PLIC_MACHINE_CLAIM(hart))
#define UART0_IRQ 10
#define NO_SOURCE 0

//RISC-V
#define MACHINE_EXTERNAL_INTERRUPT 11UL
#define MACHINE_TIMER_INTERRUPT 7UL
#define SUPERVISOR_EXTERNAL_INTERRUPT 9UL
#define SPIE 5
#define MPP 11
#define SUPERVISOR 0b01

//CLINT
#define CLINT 0x02000000UL
#define a_mtime (CLINT + 0xbff8)
#define a_mtimecmp(hart) (CLINT + 0x4000 + (hart) * 8)
#define TIME (*((uint64*) (a_mtime)))
#define TIMER_INTERVAL 30000000UL