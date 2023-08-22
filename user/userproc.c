#include "../kernel/types.h"
#include "../kernel/memlayout.h"
#include "userlib.h"

void f(){
    uint8* buf[64];
    uint32 fd = open("README.md",0);
    uint32 nb = read(fd,buf,64);
    uprint_str(buf);

    while(1){;};
    
    return;
}