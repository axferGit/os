void main(){
    unsigned long x = 0;
    asm volatile("dsds, %1, %0,%0" : "+r"(x): "m" (x));
    
    return;
}