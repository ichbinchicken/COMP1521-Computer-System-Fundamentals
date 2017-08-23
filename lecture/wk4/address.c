#include <stdio.h>

int main(void) {
    unsigned long long x = 0x7fff54791e00;
    char *p = (char *) x;
    printf("p points to %p\n", p);
    printf("x's address is %p\n", &x);

    return 0;
}
