#ifndef TYPES_H
#define TYPES_H

#include "memlayout.h"

typedef unsigned long uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef uint64* t_pagetable;

struct trapframe {
    // saved process' registers
    /*   0 */ uint64 ra;
    /*   8 */ uint64 sp;
    /*  16 */ uint64 gp;
    /*  24 */ uint64 tp;
    /*  32 */ uint64 t0;
    /*  40 */ uint64 t1;
    /*  48 */ uint64 t2;
    /*  56 */ uint64 fp;
    /*  64 */ uint64 s1;
    /*  72 */ uint64 a0;
    /*  80 */ uint64 a1;
    /*  88 */ uint64 a2;
    /*  96 */ uint64 a3;
    /* 104 */ uint64 a4;
    /* 112 */ uint64 a5;
    /* 120 */ uint64 a6;
    /* 128 */ uint64 a7;
    /* 136 */ uint64 s2;
    /* 144 */ uint64 s3;
    /* 152 */ uint64 s4;
    /* 160 */ uint64 s5;
    /* 168 */ uint64 s6;
    /* 176 */ uint64 s7;
    /* 184 */ uint64 s8;
    /* 192 */ uint64 s9;
    /* 200 */ uint64 s10;
    /* 208 */ uint64 s11;
    /* 216 */ uint64 t3;
    /* 224 */ uint64 t4;
    /* 232 */ uint64 t5;
    /* 240 */ uint64 t6;

    // process' epc
    /* 248 */ uint64 pc;
    
    /* 256 */ uint64 k_sp;
    /* 264 */ uint64 k_pt;
    /* 272 */ uint64 k_trap;
};

struct context {
    /*   0 */ uint64 ra;
    /*   8 */ uint64 sp;

    /*  16 */ uint64 fp;
    /*  24 */ uint64 s1;
    /*  32 */ uint64 s2;
    /*  40 */ uint64 s3;
    /*  48 */ uint64 s4;
    /*  56 */ uint64 s5;
    /*  64 */ uint64 s6;
    /*  72 */ uint64 s7;
    /*  80 */ uint64 s8;
    /*  88 */ uint64 s9;
    /*  96 */ uint64 s10;
    /* 104 */ uint64 s11;

};

enum state {RUNNABLE, RUNNING};

struct proc {
    uint64 pid;
    enum state state;
    t_pagetable pt;
    char * stack;
    struct trapframe * trapframe;
    struct context context;
};

struct cpu {
    struct proc* proc;
    struct context context;

};

struct virtq_desc {
    uint64 addr;
    uint32 len;
    uint16 flags;
    uint16 next;
};

struct virtq_avail {
    uint16 flags;
    uint16 idx;
    uint16 ring [QUEUE_SIZE];
    uint16 used_event;
};

struct virtq_used_elem  {
    uint32 id;
    uint32 len;
};

struct virtq_used {
    uint16 flags;
    uint16 idx;
    struct virtq_used_elem ring [QUEUE_SIZE];
    uint16 avail_event;
};

struct disk {
    char data[2*QALIGN]; // 
    struct virtq_desc * DescriptorArea ;
    struct virtq_avail * DriverArea;
    struct virtq_used * DeviceArea;
    uint8 free[QUEUE_SIZE];
};

struct virtio_blk_req {
    uint32 type;
    uint32 reserved;
    uint64 sector;
    // uint8 data[1024];
    // uint8 status;
};

struct superblock {
    uint64 magic;
    uint32 nblock;
    uint32 slog;
    uint32 nlog;
    uint32 sinode;
    uint32 ninode;
    uint32 sdata;
    uint32 ndata;
};

typedef uint64 inodeent; // size for the address of a data block

struct dinode {
    uint16 type; // FILE / DIR / UNDEF
    uint32 size; // size in bytes
    inodeent data [NADDR]; // addresses of data blocks
};

struct dirent {
    uint16 inum;
    uint8 name[NCHAR];
};

struct buf {
    uint8 written;
    uint64 blk;
    uint8 data[BLOCK_SIZE];
    uint8 status;
};

struct inode {
    uint16 inum;
    struct dinode di;
};



#endif