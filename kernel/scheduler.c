#include "proc.h"
#include "types.h"
#include "memlayout.h"
#include "ssys.h"
#include "swtch.h"
#include "printf.h"

// run next RUNNABLE process on hart
// never return, keep looping !
void scheduler(){
    uint64 id = hartid();
    struct proc * p;
    while(1){
        for(p = &proc_list[0] ; p <= &proc_list[NPROC] ; p++){
            if (p->state == RUNNABLE){
                
                printf("Proc choosen :%i\n",p -> pid); 

                cpu_list[id].proc = p;
                p->state = RUNNING;

                // switch to proc
                swtch(&(cpu_list[id].context), &(p->context));
                // return from proc

            }
        }
        //printf("No process found !\n");
    };
    return;
}