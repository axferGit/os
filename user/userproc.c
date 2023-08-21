#include "../kernel/types.h"
#include "../kernel/memlayout.h"
#include "userlib.h"

void f(){
    while(1){
        print_user("hello");
    };
    return;
}