#ifndef MEMLAYOUT_H
#define MEMLAYOUT_H

// QEMU
#define KERNBASE (0x80000000UL)

// CPU
#define NHART 1 //maximum number of cores

//PLIC
#define PLIC_BASE (0x0c000000UL)
#define UART0_IRQ (10)
#define VIRTIO0_IRQ (1) 
#define NO_SOURCE (0)
#define PLIC_PRIORITY(source) (PLIC_BASE + 4 * (source))
#define PLIC_ENABLE(target) (PLIC_BASE + 0x2000 + 0x80 * (target))
#define PLIC_THRESHOLD(target) (PLIC_BASE + 0x200000 + 0x1000 * (target))
#define PLIC_CLAIM(target) (PLIC_BASE + 0x200000 + 0x4 + 0x1000 * (target))
#define PLIC_COMPLETE(target) (PLIC_CLAIM(target))

//CLINT
#define CLINT_BASE (0x02000000UL)
#define CLINT_MTIME (CLINT_BASE + 0xbff8)
#define CLINT_MTIMECMP(hart) (CLINT_BASE + 0x4000 + 8 * (hart))
#define TIME (*((uint64*) (CLINT_MTIME)))
#define TIMER_INTERVAL 10000000UL

// UART
#define UART0 0x10000000UL
#define RHR 0b0
#define THR 0b0
#define IER 0b1
#define ISR 0b10
#define FCR 0b10
#define LCR 0b11
#define LSR 0b101

// VIRTIO BUS
#define VIRTIO_MMIO_BASE (0x10001000)
#define VIRTIO_MMIO_DEVICE_BASE(n) ((VIRTIO_MMIO_BASE) + n * 0x1000UL)

// VIRTIO DISK
#define NDISK 1
#define QUEUE_SIZE (8)
#define VIRTIO_BLK_T_IN 0 //read
#define VIRTIO_BLK_T_OUT 1 //write
#define SECTOR_SIZE (512) // constant
#define QALIGN (PAGESIZE) // need to be a power of 2
#define BLOCK2SEC(blk) ((blk) * ((BLOCK_SIZE)/(SECTOR_SIZE)))
#define IBLOCK(inum) (SINODE + ((inum) / (IPB)))
#define IBLOCKOFF(inum) ((inum) % (IPB))

// Status
#define ACKNOWLEDGE (0x1)
#define DRIVER (0x2)
#define FAILED (128)
#define FEATURES_OK (8)
#define DRIVER_OK (4)
#define DEVICE_NEEDS_RESET (64)

// Memory layout
#define VIRTIO_MMIO_DISK_MAGIC_NUMBER(n) ((VIRTIO_MMIO_DEVICE_BASE(n)) + 0x00)
#define VIRTIO_MMIO_DISK_MN (0x74726976)
#define VIRTIO_MMIO_DISK_VERSION(n) ((VIRTIO_MMIO_DEVICE_BASE(n)) + 0x004)
#define VIRTIO_MMIO_DISK_V (0x1)
#define VIRTIO_MMIO_DISK_DEVICE_ID(n) ((VIRTIO_MMIO_DEVICE_BASE(n)) + 0x008)
#define VIRTIO_MMIO_DISK_DID (0x02)
#define VIRTIO_MMIO_DISK_VENDOR_ID(n) ((VIRTIO_MMIO_DEVICE_BASE(n)) + 0x00c)
#define VIRTIO_MMIO_DISK_HOST_FEATURES(n) ((VIRTIO_MMIO_DEVICE_BASE(n)) + 0x010)
#define VIRTIO_MMIO_DISK_HOST_FEATURES_SEL(n) ((VIRTIO_MMIO_DEVICE_BASE(n)) + 0x014)
#define VIRTIO_MMIO_DISK_GUEST_FEATURES(n) ((VIRTIO_MMIO_DEVICE_BASE(n)) + 0x020)
#define VIRTIO_MMIO_DISK_GUEST_FEATURES_SEL(n) ((VIRTIO_MMIO_DEVICE_BASE(n)) + 0x024)
#define VIRTIO_MMIO_DISK_GUEST_PAGE_SIZE(n) ((VIRTIO_MMIO_DEVICE_BASE(n)) + 0x028)
#define VIRTIO_MMIO_DISK_QUEUE_SEL(n) ((VIRTIO_MMIO_DEVICE_BASE(n)) + 0x030)
#define VIRTIO_MMIO_DISK_QUEUE_NUM_MAX(n) ((VIRTIO_MMIO_DEVICE_BASE(n)) + 0x034)
#define VIRTIO_MMIO_DISK_QUEUE_NUM(n) ((VIRTIO_MMIO_DEVICE_BASE(n)) + 0x038)
#define VIRTIO_MMIO_DISK_QUEUE_ALIGN(n) ((VIRTIO_MMIO_DEVICE_BASE(n)) + 0x03c)
#define VIRTIO_MMIO_DISK_QUEUE_PFN(n) ((VIRTIO_MMIO_DEVICE_BASE(n)) + 0x040)
#define VIRTIO_MMIO_DISK_QUEUE_NOTIFY(n) ((VIRTIO_MMIO_DEVICE_BASE(n)) + 0x050)
#define VIRTIO_MMIO_DISK_INTERRUPT_STATUS(n) ((VIRTIO_MMIO_DEVICE_BASE(n)) + 0x060)
#define VIRTIO_MMIO_DISK_INTERRUPT_ACK(n) ((VIRTIO_MMIO_DEVICE_BASE(n)) + 0x064)
#define VIRTIO_MMIO_DISK_DEVICE_STATUS(n) ((VIRTIO_MMIO_DEVICE_BASE(n)) + 0x070)
#define VIRTIO_MMIO_DISK_CONFIGURATION_SPACE(n) ((VIRTIO_MMIO_DEVICE_BASE(n)) + 0x100)

// Features
#define VIRTIO_BLK_F_SIZE_MAX (1)
#define VIRTIO_BLK_F_SEG_MAX (2)
#define VIRTIO_BLK_F_GEOMETRY (4)
#define VIRTIO_BLK_F_RO (5)
#define VIRTIO_BLK_F_BLK_SIZE (6)
#define VIRTIO_BLK_F_SCSI (7)
#define VIRTIO_BLK_F_FLUSH (9)
#define VIRTIO_BLK_F_TOPOLOGY (10)
#define VIRTIO_BLK_F_CONFIG_WCE (11)
#define VIRTIO_BLK_F_MQ (12)
#define VIRTIO_BLK_F_DISCARD (13)
#define VIRTIO_BLK_F_WRITE_ZEROES (14)
#define VIRTIO_F_ANY_LAYOUT (27)
#define VIRTIO_RING_F_INDIRECT_DESC (28)
#define VIRTIO_RING_F_EVENT_IDX (29)

//Flags
#define VIRTQ_DESC_F_READ 0
#define VIRTQ_DESC_F_NEXT 1
#define VIRTQ_DESC_F_WRITE 2

// STATUS BIT
#define VIRTIO_BLK_S_OK 0
#define VIRTIO_BLK_S_IOERR 1
#define VIRTIO_BLK_S_UNSUPP 2
#define VIRTIO_BLK_S_UNDEF 3

// FILE SYSTEM
#define BLOCK_SIZE (2*SECTOR_SIZE)
#define NBLOCK (2000)
#define SSB (1)
#define NSB (1)
#define SLOG ((SSB) + (NSB))
#define NLOG (30)
#define SINODE ((SLOG) + (NLOG))
#define NINODE (200)
#define SBITMAP ((SINODE) + (NINODE))
#define NBITMAP (1)
#define SDATA ((SBITMAP) + (NBITMAP))
#define NDATA ((NBLOCK) -1 - (SDATA))

#define IPB (BLOCK_SIZE / (sizeof(struct dinode))) // Inode per block
#define MAXINODE ((IPB)*(NINODE))
#define T_DIR (1)
#define T_FILE (2)

#define FS_MAGIC (0x0807060504030201UL)
#define NADDR (14)
#define NINDADDR (BLOCK_SIZE / (sizeof(inodeent)))
#define NCHAR (14)
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
#define ADR2PAGE(addr) (((uint64) addr) / PAGESIZE)

// PROCESS
#define NPROC 1

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

// SSYSCALL
#define S_SYSCALL_HARTID (1)

// USYSCALL
#define NSYSCALL 1 // number of sys calls
#define U_SYSCALL_TEST (0)

// BUFFER CACHE
#define NBUF 16
#define NFILE 16
#define NOFILE 16

#endif