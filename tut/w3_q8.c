#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TOP4 0xF0
#define ASCII 0x80
#define MASK2 0xC0
#define MASK3 0xE0
#define MASK4 0xF0
#define MASKX 0x80
void show(int x) {
    int i;
    for(i = 31; i >= 0; i--) {
        if ((x & (1u << i)) != 0) printf("1");
        else printf("0");
    }
}
void unicode2html(unsigned char *str) {
    unsigned char bytes[4];
    int i = 0;
    if ((*str & ASCII) == 0) {
        while (*str != 0) {
            if (i == 0) bytes[i] = *str & ~ASCII;
            else bytes[i] = *str & ~MASKX;
            str++;
            i++;
        }    
    } else if ((*str & TOP4) == MASK2) {
        while (*str != 0) {
            if (i == 0) bytes[i] = *str & ~MASK2;
            else bytes[i] = *str & ~MASKX;
            str++;
            i++;
        }    
    } else if ((*str & TOP4) == MASK3) {
        while (*str != 0) {
            if (i == 0) bytes[i] = *str & ~MASK3;
            else bytes[i] = *str & ~MASKX;
            str++;
            i++;
        }    
    } else if ((*str & TOP4) == MASK4) {
        while (*str != 0) {
            if (i == 0) bytes[i] = *str & ~MASK4;
            else bytes[i] = *str & ~MASKX;
            str++;
            i++;
        }    
    }
    show((int)bytes[1]);
    int x = 0;
    int j;
    for(j = i - 1;j >= 0;j--) {
        x = x | ((int)bytes[j] << ((i-1-j)*6));
    }  
    printf("\n&#x%04X\n", x);
    
}
int main (void) {
    char s[10] = {'a','b','c','\xC2','\xA2','d','e','f','\0'}; 
    printf("%ld\n", strlen(s));
    int total = 0;
    char *c = s;
    while (*c != 0) {
        if ((*c & TOP4) == ASCII) c++;
        else if ((*c & TOP4) == MASK2) c += 2;
        else if ((*c & TOP4) == MASK3) c+= 3;
        else if ((*c & TOP4) == MASK4) c+= 4;
        else c++;
        total ++;
    }
    printf("%d---\n", total);
    unsigned char unicode[4] = {'\xE2', '\x86','\xAB', 0};
    unicode2html(unicode);
    return 0;
}
