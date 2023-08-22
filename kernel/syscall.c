#include "memlayout.h"
#include "proc.h"
#include "vm.h"
#include "alloc.h"
#include "printf.h"
#include "fs.h"


void sys_print();
void sys_open();
void sys_print_hex();
void sys_read();

void (*(sys_call[NSYSCALL]))() = {
    [U_SYSCALL_PRINT_STR] sys_print,
    [U_SYSCALL_OPEN] sys_open,
    [U_SYSCALL_PRINT_HEX] sys_print_hex,
    [U_SYSCALL_READ] sys_read
};


// Return the [n]-th argument in a sys call
uint64 argn(uint32 n){
    struct proc* p = myproc();
    switch (n)
    {
    case 0:
        return (p->trapframe->a0);
        break;
    
    case 1:
        return (p->trapframe->a1);
        break;
    
    case 2:
        return (p->trapframe->a2);
        break;
    
    case 3:
        return (p->trapframe->a3);
        break;
    
    case 4:
        return (p->trapframe->a4);
        break;

    case 5:
        return (p->trapframe->a5);
        break;

    case 6:
        return (p->trapframe->a6);
        break;

    case 7:
        return (p->trapframe->a7);
        break;

    default:
        printf("Arg out of range : %i\n",n);
        panic("");
        break;
    }
}

// Copy max [max] characters string from [va_src] in user space to [dst] in kernel space
// until '\0' or [max]
// return 0 on success, -1 on failure
uint32 copyinstr(uint8* dst, uint8* va_src,uint32 max){
    if (max == 0){
        return 0;
    }

    uint8* pa_src = (uint8*)walkaddr(myproc()->pt,va_src);

    if (pa_src == 0){
        printf("kVirtual address in user land not mappes: %p\n",va_src);
        return -1;
    } 

    *dst = *pa_src;
    if (*pa_src == '\0'){
        return 0;
    } else {
        return copyinstr(++dst,++va_src,--max);
    }

}

uint32 copyoutstr(uint8* va_dst, uint8* src,uint32 max){
    if (max == 0){
        return 0;
    }

    uint8* pa_dst = (uint8*)walkaddr(myproc()->pt,va_dst);

    if (pa_dst == 0){
        printf("kVirtual address in user land not mappes: %p\n",va_dst);
        return -1;
    } 

    *pa_dst = *src;
    if (*src == '\0'){
        return 0;
    } else {
        return copyinstr(++va_dst,++src,--max);
    }

}



void sys_print(){
    uint8 buf [128];
    memset(buf,0,sizeof(buf));
    copyinstr(buf,(void*) argn(0),sizeof(buf)-1);
    printf(">>>>%s<<<<\n",buf);
    return;
}

void sys_print_hex(){
    printf("%p\n",argn(0));
    return;
}

void sys_open(){
    struct proc * p = myproc();
    uint8 name[NCHAR];
    memset(name,0,sizeof(name));
    if (copyinstr(name,(void*) argn(0),sizeof(name)-1) == -1){
        printf("cpstr failed\n");
        panic("");
    };
    int inum = find(name);
    if (inum !=-1){
        struct file* f = getfile();
        f->off = 0;
        f->in = openi(inum); 
        uint32 fd = getofile();
        p->ofile[fd] = f; //TODO : clean way to find available slot in open files
        p->trapframe->a0 = fd;
    }
    else {
        printf("error :can not find file");
        p->trapframe->a0 = -1;
    }
    return;
}

void sys_read(){
    uint32 fd = argn(0);
    uint8* va_buf = argn(1);
    uint32 sz = argn(2);
    uint8* buf[128];

    struct proc* p = myproc();

    uint8* pa_dst = (uint8*)walkaddr(p->pt,va_buf);

    if (pa_dst == 0){
        printf("kVirtual address in user land not mappes: %p\n",va_buf);
        return -1;
    } 


    uint32 nb = readi(p->ofile[fd]->in,p->ofile[fd]->off,sz,pa_dst);
    p->ofile[fd]->off += nb;
    p->trapframe->a0 = nb;

    return;
}

