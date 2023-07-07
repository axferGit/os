#include "printf.h"

void traphandler(){
    panic("\ntrap S mode\n");
    return;
}