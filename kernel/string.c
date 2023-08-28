#include "types.h"

// Compare strings [s1] and [s2]
// return 0 if equal, -1 if not
uint32 strcmp(uint8* s1, uint8* s2){
    if (s1[0] == s2[0]){
        if(s1[0] == 0){
            return 0;
        } else {
            return strcmp(s1+1,s2+1);
        }
    } else {
        return -1;
    }
}