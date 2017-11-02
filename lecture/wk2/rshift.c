#include <stdio.h>
#include <stdlib.h>

void show(short a);
int main () {
    short a = -127;
    show(a);
    a = a >> 5;
    show(a);
    unsigned short b = 65535;
    show(b);
    b = b >> 5;
    show(b);
    return 0; 
}

void show(short a) {
    printf("%d: ", a);
    int j;
    int one = 0;
    for(j = 15;j >= 0;j--){
        if ((a & (1u<<j)) != 0) {
            printf("1");
            one ++;
        } else {
            printf("0");
        }
    }
    printf("\n");
    printf("There are %d of 1s\n", one);
}
