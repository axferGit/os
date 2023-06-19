#include "uart.h"
#include "printf.h"
#include "riscv.h"

volatile char panicked = 0;

static char digits[] = "0123456789abcdef";

//print int [i] on base [b] depending on its signess [s]
static void print_int(int i,int b,int s){
    
    int v;
    int p = 1;

    if (s && (s = (i < 0))){
        v = -i;
    }
    else{
        v = i;
    }

    while((v/p) >= b){
        p = p * b;
    }

    if (s){
        uartputc('-');
    }

    while(p){
        uartputc(digits[v/p]);
        v = v % p;
        p = p / b;
    }
    
    return;
}

static void print_ptr(uint64 v){
    uartputc('0');
    uartputc('x');

    for (int i = 0; i < (sizeof(uint64) * 2) ; i++){
        uartputc(digits[(v >> ((sizeof(uint64) *2 - 1 - i)*4)) & 0xf]);
    }

    return;
}


void printf(char* s, ...){
    //Builtin
    __builtin_va_list ap;
    __builtin_va_start(ap,s);

    int i;
    char c;
    
    for( i = 0 , c = s[i] ; c != '\0' ; c = s[++i] ){
        if (c != '%'){
            uartputc(c);
        }
        else{
            c = s[++i];
            switch (c)
            {
            case 'i':
                print_int( __builtin_va_arg(ap,int),10,1);
                break;
            
            case 'p':
                print_ptr( __builtin_va_arg(ap,uint64));
                break;

            case '\0':
                uartputc('%');
                --i;
                break;
            }           
        }
    }
    return;
}

// Block all cores and print string [s].
void panic(char* s){
    printf(s);
    panicked = 1;
    while(1){}
    return;
}
