#include "memlayout.h"
#include "types.h"

// Acquire the spinlock [lk]
void acquire(struct spinlock *lk){
    while(__sync_lock_test_and_set(&lk->lock,1) == 1){
        ;
    }
    return;
}

// Release spin lock [lk]
void release(struct spinlock * lk){
    if (lk->lock == 0){
        panic("Lock is unlocked !\n");
    }
    __sync_synchronize();
    __sync_lock_release(&lk->lock);
    return;

}