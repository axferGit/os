#include "memlayout.h"
#include "proc.h"
#include "vm.h"
#include "alloc.h"
#include "printf.h"

void sys_test();
void (*(sys_call[NSYSCALL]))() = {
    [U_SYSCALL_TEST] sys_test
};


// Return the [n]-th argument in a sys call
uint64 argn(uint32 n){
    struct proc* p = myproc();
    switch (n)
    {
    case 0:
        return (p->trapframe->a0);
        break;
    
    default:
        printf("Arg out of range : %i\n",n);
        panic("");
        break;
    }
}

void cpstruser(uint8* dst, uint8* src){
    //printf("dst :%p - src: %p\n",dst,src);
    uint8* addr_src = (uint8*)kva(myproc()->pt,src); // src addr in user space (in user rodata)
    // uint8* addr_dst = (uint8*)kva(kernel_pagetable,dst); // dst address in kernel space (on the kernel stack)

    // printf("src %p - addr_src %p\n",src,addr_src);
    // printf("dst %p - addr_dst %p\n",dst,addr_dst);
    // print_page(p->pt,(uint64) src);
    // print_page(kernel_pagetable,(uint64) dst);
    // print_page(kernel_pagetable,(uint64) addr_src);

    if (addr_src == 0){
        printf("kva src to 0 : error\n");
        panic("");
    } 

    *dst = *addr_src;
    //printf("<<<%i>>>\n",*addr_src);
    if (*addr_src == '\0'){
        return;
    } else {
        return cpstruser(++dst,++src);
    }

}




void sys_test(){
    //printf("Beginning of sys_test\n");
    struct proc* p = myproc();
    uint8 buf [16];
    memset(buf,0,sizeof(buf));

    //printf("Beginning of cpstruser\n");
    //printf("argn(0): %p\n",argn(0));

    cpstruser(buf,(void*) argn(0));
    printf(">>>>%s<<<<\n",buf);
    return;


}


