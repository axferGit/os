#include "memlayout.h"
#include "types.h"
#include "printf.h"
#include "proc.h"
#include "riscv.h"


// Init spinlock [lk] with name [name]
void spinlockinit(struct spinlock* lk,uint8* name){
    lk->lock = 0;
    lk->name = name;
    lk->pc = 0;
    lk->cpui = 0;
    return;
}

// Acquire the spinlock [lk]
void acquire(struct spinlock *lk){
    uint32 nticks = 0;
    while(__sync_lock_test_and_set(&lk->lock,1) != 0){
        nticks++;
        if (nticks > (NTICKSMAX)){
            printf("Block on acquiring spin lock: %s\nacquired at pc: %p by cpu %i\n",lk->name,lk->pc,lk->cpui);
            panic("");
        }
    }
    uint64 ra = r_ra();
    //asm volatile("mv %0,ra" :"+r"(ra):);
    // printf("lk->cpui: %p\n",lk->cpui);
    lk->cpui = (uint32) (((uint64) mycpu()) - ((uint64) cpu_list));
    lk->pc = ra;//r_ra();
    return;
}

// Release spin lock [lk]
void release(struct spinlock * lk){
    if (lk->lock == 0){
        panic("Lock is unlocked !\n");
    }
    lk->pc = 0;
    lk->cpui = 0;
    __sync_synchronize();
    __sync_lock_release(&lk->lock);
    return;

}