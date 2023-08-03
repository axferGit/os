// QEMU
#define KERNBASE (0x80000000UL)

// CPU
#define NHART 1 //maximum number of cores

// DRAM
#define PHYSTOP (KERNBASE + 128 * 1024 * 1024)

// VIRTUAL MEMORY
#define MAXVA (1L << (9 + 9 + 9 + 12 - 1)) // first byte out of virtual memory, minus 1 to avoid complex addresses, see documentation
#define TRAMPOLINE (MAXVA - PAGESIZE) 
#define TRAPFRAME (TRAMPOLINE - PAGESIZE) // (MAXVA - 2 * PAGESIZE)
#define STACK (TRAPFRAME - PAGESIZE) // (MAXVA - 3 * PAGESIZE)

// PAGE
#define SV39 (0x8UL << 60)
#define PAGESIZE (4096)
#define MAKE_SATP(pt) ((SV39) | ((uint64)pt / (PAGESIZE)))
#define PTE_CFG_BITS 10
#define PTE_CFG_MASK 0x3ffUL
#define MASK_PAGE 0xfffffffffffUL
#define INDEXLEVEL(va,level) (((va) >> (9*(level) + 12)) & 0x1ff)
#define PTE_V (1UL << 0)
#define PTE_R (1UL << 1)
#define PTE_W (1UL << 2)
#define PTE_X (1UL << 3)
#define PTE_U (1UL << 4)
#define PAGE2PTE(page,perm) (((((page) / (PAGESIZE)) & MASK_PAGE) << PTE_CFG_BITS) | (perm) & PTE_CFG_MASK | PTE_V)
#define PTE2PAGE(pte) ((((pte) >> (PTE_CFG_BITS)) & MASK_PAGE) * PAGESIZE)

// PROCESS
#define NPROC 3

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
#define PLIC_BASE 0x0c000000UL
#define UART0_IRQ 10
#define NO_SOURCE 0
#define PLIC_PRIORITY(source) (PLIC_BASE + 4 * (source))
#define PLIC_ENABLE(target) (PLIC_BASE + 0x2000 + 0x80 * (target))
#define PLIC_THRESHOLD(target) (PLIC_BASE + 0x200000 + 0x1000 * (target))
#define PLIC_CLAIM(target) (PLIC_BASE + 0x200000 + 0x4 + 0x1000 * (target))
#define PLIC_COMPLETE(target) (PLIC_CLAIM(target))

//RISC-V
// Interrupt
#define MEI (11UL)
#define SEI (9UL)
#define UEI (8UL)
#define MTI (7UL)
#define STI (5UL)
#define UTI (4UL)
#define MSI (3UL)
#define SSI (1UL)
#define USI (0UL)

// Exception
#define INSTRUCTION_ADDRESS_MISALIGNED (0UL)
#define INSTRUCTION_ACCESS_FAULT (1UL)
#define ILLEGAL_INSTRUCTION (2UL)
#define BREAKPOINT (3UL)
#define LOAD_ADDRESS_MISALIGNED (4UL)
#define LOAD_ACCESS_FAULT (5UL)
#define STORE_AMO_ADDRESS_MISALIGNED (6UL)
#define STORE_AMO_ACCESS_FAULT (7UL)
#define ENVIRONMENT_CALL_FROM_U_MODE (8UL)
#define ENVIRONMENT_CALL_FROM_S_MODE (9UL)
#define ENVIRONMENT_CALL_FROM_M_MODE (11UL)
#define INSTRUCTION_PAGE_FAULT (12UL)
#define LOAD_PAGE_FAULT (13UL)
#define STORE_AMO_PAGE_FAULT (15UL)


#define SPIE 5
#define MPP 11
#define SPP 8
#define MACHINE (3UL)
#define SUPERVISOR (1UL)
#define USER (0UL)

//CLINT
#define CLINT_BASE (0x02000000UL)
#define CLINT_MTIME (CLINT_BASE + 0xbff8)
#define CLINT_MTIMECMP(hart) (CLINT_BASE + 0x4000 + 8 * (hart))
#define TIME (*((uint64*) (CLINT_MTIME)))
#define TIMER_INTERVAL 30000000UL

// SSYSCALL
#define S_SYSCALL_HARTID (1)

// USYSCALL
#define U_SYSCALL_TEST (1)

