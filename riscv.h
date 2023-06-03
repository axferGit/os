typedef unsigned long uint64;

void w_mtvec(uint64);
uint64 r_mstatus();
void w_mstatus(uint64);
void s_mstatus(uint64);
uint64 r_mie();
void w_mie(uint64);
uint64 cpuid();
uint64 r_mcause();
