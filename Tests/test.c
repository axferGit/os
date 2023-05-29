__attribute__ ((aligned (16))) char stack0[4096];

void start(){
    *((unsigned char *) 0x10000000UL) = 0x61;    
    return;
}
