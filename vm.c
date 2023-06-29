#include "alloc.h"
#include "riscv.h"
#include "memlayout.h"
#include "printf.h"
#include "vm.h"

t_pagetable pagetable; 
extern uint64 etext;
extern uint64 erodata;
extern uint64 edata;
extern uint64 end;

void printmemory(){
    printf("KERNBASE = %p\n",KERNBASE);
    printf("etext    = %p\n",&etext);
    printf("erodata  = %p\n",&erodata);
    printf("edata    = %p\n",&edata);
    printf("end      = %p\n",&end);
    printf("PHYSTOP  = %p\n",PHYSTOP);
    
    return;
}

void print_pt(t_pagetable pt){
    uint64 l1, l2, l3;
    uint64 pte1, pte2, pte3;
    uint64 addr;
    t_pagetable p1,p2,p3;

    for(l1 = 0, p1 = pt; l1 < (2<<8); l1 ++){
        pte1 = pt[l1];

        if (pte1 & 0x1){
            p2 = (uint64*)((pte1 >> 10) << 12);

            for(l2 = 0; l2 < (2<<8); l2 ++){
                pte2 = p2[l2];
                if (pte2 & 0x1){
                    p3 = (uint64*)((pte2 >> 10) << 12);
                    
                    for(l3 = 0 ; l3 < (2<<8); l3++){
                        pte3 = p3[l3];
                        
                        if(pte3 & 0x1){
                            addr = ((l1 << 18) + (l2 << 9) + l3) << 12;
                            printf("%p - %p\n",addr,(pte3 >> 10) << 12);
                        }
                    }

                }
            }

        }
    }

}


void kvminit(){
    printmemory();
    //allocate page table
    if ((pagetable = alloc()) == 0){
        panic("Fail to allocate page table\n");
    }
    
    // UART
    mappages(pagetable, (void*) UART0, PAGESIZE, (void*) UART0, PTE_READ | PTE_WRITE);

    // .text section
    mappages(pagetable, (void*) KERNBASE, (uint64) &etext - KERNBASE, (void*) KERNBASE, PTE_READ | PTE_EXECUTE);

    // .rodata section
    mappages(pagetable, (void*) &etext, (uint64) &erodata - (uint64) &etext, (void*) &etext, PTE_READ);

    // .data .bss sections
    mappages(pagetable, (void*) &erodata, (uint64) &edata - (uint64) &erodata, (void*) &erodata, PTE_READ | PTE_WRITE);

    // Unused DRAM
    mappages(pagetable,(void*) &end, PHYSTOP - (uint64) &end, (void*) &end, PTE_READ | PTE_WRITE);

    return;
}

void kvminithart(){
    w_satp(SV39 | ((uint64)pagetable / PAGESIZE));
    sfence_vma();
    return;
}

// Map the virtual pages starting from [va] with size [sz] to physical pages starting from [pa], with permissions [perm]
// panic on error.
void mappages(t_pagetable pagetable, void* va, uint64 sz, void* pa, uint64 perm){
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
    *pte = ((((uint64) pa / PAGESIZE) << PTE_CFG_BITS)| (perm & PTE_CFG_MASK) | PTE_VALID);
    return;
}

// Return the address of the PTE that corresponds to virtual address [va] in pagetable [pagetable]
// [b_allocate] tells if allocation of intermediary pages is allowed
// return 0 on failure.
void* walk(t_pagetable pagetable, void* va, int bool_alloc){

    int level;
    uint64* p ;
    
    for (level = 2, p = pagetable; 0 < level ; level--){

        int index = INDEXLEVEL((uint64)va,level);  
        uint64 pte = p[index];

        if ((pte & PTE_VALID) == 0){
            if(bool_alloc){
                
                void* page;
                
                if((page = alloc()) == 0){
                    printf("Alloc failed\n");
                }
                p[index] = ((((uint64)page / PAGESIZE) << PTE_CFG_BITS) | 0 & PTE_CFG_MASK | PTE_VALID);
                p = (uint64*) page;
            }
            else {
                return 0;
            }
        }
        else{
            p = (uint64*) ((p[index] >> PTE_CFG_BITS) * PAGESIZE);
        }
    }
    return &p[INDEXLEVEL((uint64)va,level)];
}