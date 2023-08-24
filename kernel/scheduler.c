#include "proc.h"
#include "types.h"
#include "memlayout.h"
#include "ssys.h"
#include "swtch.h"
#include "printf.h"
#include "spinlock.h"

// run next RUNNABLE process on hart
// p->lk is locked
// never return, keep looping !
void scheduler(){
    uint64 id = hartid();
    struct proc * p;
    while(1){
        for(p = &proc_list[0] ; p <= &proc_list[NPROC] ; p++){

            acquire(&p->lk);

            if (p->state == RUNNABLE){
                
                printf("Proc choosen :%i\n",p -> pid); 

                cpu_list[id].proc = p;
                p->state = RUNNING;

                // switch to proc
                swtch(&(cpu_list[id].context), &(p->context));
                // return from proc

            }

            release(&p->lk);
        }
        //printf("No process found !\n");
    };
    return;
}