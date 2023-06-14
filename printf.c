#include "uart.h"

void myprintf(char* s, ...){
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
                print_i( __builtin_va_arg(ap,int));
                break;
            
            case '\0':
                uartputc('%');
                break;
            }

            
        }

    }
    return;
}

void print_decimal(int i){

    switch (i)
    {
    case 0:
        uartputc('0');
        break;
    case 1:
        uartputc('1');
        break;
    case 2:
        uartputc('2');
        break;
    case 3:
        uartputc('3');
        break;
    case 4:
        uartputc('4');
        break;
    case 5:
        uartputc('5');
        break;
    case 6:
        uartputc('6');
        break;
    case 7:
        uartputc('7');
        break;
    case 8 :
        uartputc('8');
        break;
    case 9:
        uartputc('9');
        break;
    }

    return;

}

void print_i(int i){
    int v = i;
    int b = 10;
    int p = 1;
    while((v/p) >= b){
        p = p * b;
    }
    while(p){
        print_decimal(v / p);
        v = v % p;
        p = p / b;
    }
    
    return;
}