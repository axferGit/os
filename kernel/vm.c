#include "alloc.h"
#include "riscv.h"
#include "memlayout.h"
#include "printf.h"
#include "vm.h"
#include "types.h"

t_pagetable kernel_pagetable;

extern uint64 etext;
extern uint64 trampoline;
extern uint64 erodata;
extern uint64 edata;
extern uint64 end;


// iitialize kernel page table
// panic on error
void kvminit(){
    //allocate page table
    if ((kernel_pagetable = alloc()) == 0){
        panic("Fail to allocate kernel page table\n");
    }

    // UART
    mappages(kernel_pagetable, (void*) UART0, PAGESIZE, (void*) UART0, PTE_R | PTE_W);

    // VIRTIO BUS
    mappages(kernel_pagetable, (void*) VIRTIO_MMIO_DEVICE_BASE(0), PAGESIZE, (void*) VIRTIO_MMIO_DEVICE_BASE(0), PTE_R | PTE_W);

    // .text section
    mappages(kernel_pagetable, (void*) KERNBASE, (uint64) &etext - KERNBASE, (void*) KERNBASE, PTE_R | PTE_X);

    // .rodata section
    mappages(kernel_pagetable, (void*) &etext, (uint64) &erodata - (uint64) &etext, (void*) &etext, PTE_R);

    // .data .bss sections
    mappages(kernel_pagetable, (void*) &erodata, (uint64) &edata - (uint64) &erodata, (void*) &erodata, PTE_R | PTE_W);
    
    // Unused DRAM (including userprocs)
    mappages(kernel_pagetable,(void*) &edata, PHYSTOP - (uint64) &edata, (void*) &edata, PTE_R | PTE_W);

    // TRAMPOLINE
    mappages(kernel_pagetable,(void*) TRAMPOLINE, PAGESIZE, (void*) &trampoline, PTE_X);

    return;
}

//Initialize SATP on hart
void kvminithart(){
    w_satp(MAKE_SATP(kernel_pagetable));
    sfence_vma();
    return;
}

// Map the virtual pages starting from [va] with size [sz] (in bytes) to physical pages starting from [pa], with permissions [perm]
// panic on error.
void mappages(t_pagetable pagetable, void* va, uint64 sz, void* pa, uint64 perm){

    if ((uint64)va & 0xfff){
        panic("va not aligned on page boundary\n");
    }
    if ((uint64)pa & 0xfff){
        panic("pa not aligned on page boundary\n");
    }

    while(1){
        if(PAGESIZE < sz){
            mappage(pagetable, va, pa, perm);
            sz -= PAGESIZE;
            pa = (char*) pa + PAGESIZE;
            va = (char*) va + PAGESIZE;
        }
        else{
            mappage(pagetable, va, pa, perm);
            break;
        }
    }
    return;
}

// Map virtual page at address [va] to physical page at address [pa] with permissions [perm]
// panic on error
void mappage(t_pagetable pagetable, void* va, void* pa, uint64 perm){
    uint64* pte;
    if ((pte = walk(pagetable,va,1)) == 0){
        panic("Fail mappage\n");
    };
    *pte = PAGE2PTE((uint64) pa, perm);
    return;
}

// Return the address of the PTE that corresponds to virtual address [va] in pagetable [pagetable]
// [b_allocate] tells if allocation of intermediary pages is allowed
// return 0 on failure.
void* walk(t_pagetable pagetable, void* va, int bool_alloc){

    uint32 level;
    uint32 index;
    uint64* p ;
    
    for (level = 2, index = INDEXLEVEL((uint64)va,level), p = pagetable;
        0 < level;
        level--, index = INDEXLEVEL((uint64)va,level)){

        uint64 pte = p[index];

        if ((pte & PTE_V) == 0){
            if(bool_alloc){
                
                void* newpage;
                
                if((newpage = alloc()) == 0){
                    printf("Alloc failed\n");
                    return 0;
                }
                p[index] = PAGE2PTE((uint64)newpage,0);
                p = (uint64*) newpage;
            }
            else {
                return 0;
            }
        }
        else{
            p = (uint64*) PTE2PAGE(pte);
        }
    }
    return &p[index];
}

// Translate a user land address [addr] into its address in the RAM (~ in kernel land)
// return 0 on failure
uint64 walkaddr(t_pagetable pt,void* addr){
    uint64* p = walk(pt,addr,0);

    // Check is the page is valid (ie. level 2 and level 1 and level 0)
    if (((uint64) p == 0) || ((*p & PTE_V) == 0)){
        return 0;
    } else {
        return PTE2PAGE(*p) + (((uint64) addr) % PAGESIZE);
    }
}

void printvm(){
    printf("MAXVA : %p\n",MAXVA);
    printf("TRAMPOLINE : %p\n",TRAMPOLINE);
    printf("TRAPFRAME : %p\n",TRAPFRAME);
    printf("STACK : %p\n",STACK);
}

void printmemory(){
    printf("KERNBASE = %p\n",KERNBASE);
    printf("etext    = %p\n",&etext);
    printf("erodata  = %p\n",&erodata);
    printf("edata    = %p\n",&edata);
    printf("end      = %p\n",&end);
    printf("PHYSTOP  = %p\n",PHYSTOP);
    
    return;
}

void print_pt_r(uint64* page, int level, uint64 va){
    if (level >= 0){
        for (int i = 0; i < (2 << 8); i++){
            uint64 pte = page[i];
            if(pte & PTE_V){
                print_pt_r((uint64*)PTE2PAGE(pte), level-1, va + ((uint64)i << (level * 9 + 12)));
            }
        }
    }
    else{
        printf("%p - %p\n",va,(uint64)page);
    }
    return;
}

// print "va - pa" for all pages mapped in pagetable [pt]
void print_pt(t_pagetable pt){
    print_pt_r(pt,2,0);
    return;
}

// print "va -pa" for page [va] in pagetable [pt]
void print_page(t_pagetable pt, uint64 va){
    int level;
    t_pagetable p;
    uint64 pte;
    
    for (level = 2, p = pt; 0 <= level ; level--, p = (uint64*) PTE2PAGE(pte)){
        pte = p[INDEXLEVEL(va,level)];
        if (pte & PTE_V){
            printf("Page not valid\n -level: %i\n -pte: %p\n",level,pte);
            panic("");
        }
    }
    printf("Mapping successfull\n");
    printf("Page va : %p , address %p\n",(va / PAGESIZE) * PAGESIZE,va);
    printf("Page pa : %p , address %p\n", PTE2PAGE(pte), PTE2PAGE(pte) + (va % PAGESIZE));
    printf("Page pa flags : %p\n", pte & PTE_CFG_MASK);
    return;
}