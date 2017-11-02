#include <stdio.h>
#include <stdlib.h>

#define ASCII 0x8C
#define TOP4  0xC0
#define MASK2 0x
int main (void) {
    char *str1 = "abc\xE2\x86\xABdef";
    char *str2 = "abc\xE2\x86\xABdef";
    
    return 0;
}
