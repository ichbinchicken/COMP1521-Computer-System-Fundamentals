#include <stdio.h>

int main(void) {
    unsigned char a = 1;
    a = a * 85;
    printf("%x\n", a);
    a = a * 85;
    printf("%x\n", a);
    a = a * 85;
    printf("%x\n", a);
   
    a = 0xff;
    printf("hex=%x, dec=%d\n", a, a);
    a++;
    printf("hex=%x, dec=%d\n", a, a);
   

    return 0;
}
