#include "uart.h"
#include "printf.h"

volatile char panicked = 0;

static char digits[] = "0123456789abcdef";

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
            case 'i': //hexa
                print_int( __builtin_va_arg(ap,int),10,1);
                break;
            
            case 'x':
                printf("0x");
                print_int( __builtin_va_arg(ap,int),16,0);
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

//print int [i] on base [b] depending on its signess [s]
void print_int(int i,int b,int s){
    
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

// Block all cores and print string [s].
void panic(char* s){
    printf(s);
    panicked = 1;
    while(1){}
    return;
}
