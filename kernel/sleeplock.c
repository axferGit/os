#include "types.h"
#include "spinlock.h"
#include "printf.h"
#include "proc.h"


// Init sleeplock [slk] with name [name]
void sleeplockinit(struct sleeplock* slk, uint8* name){
    spinlockinit(&slk->lk,name);
    slk->lock = 0;
    return;
}

// Acquire sleeplock [slk]
void acquiresleep(struct sleeplock* slk){
    acquire(&slk->lk);
    while(slk->lock == 1){
        sleep(&slk->lock,&slk->lk);
    }
    slk->lock = 1;
    release(&slk->lk);
    return;
}

// Release sleeplock [slk]
void releasesleep(struct sleeplock* slk){
    if (slk->lock == 0){
        panic("Can not release sleeplock, lock is 0\n");
    }
    acquire(&slk->lk);
    slk->lock = 0;
    release(&slk->lk);
    wakeup(&slk->lock);
    return;

}