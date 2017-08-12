#include <stdio.h>

int main(void) {
    unsigned char a = 1;
    int i;
    for (i = 0; i < 170; i++)
        a = a*85;

    unsigned char b = 1;
    for (i = 0; i < 170; i++)
        b = b*a;

    printf("hex=%x, dec=%d\n", b, b);
    return 0;
}
