#include <stdio.h>
#include <stdlib.h>

int main () {
    int a = 0xFFFFFF81;
    printf("a is %d\n", a);
    printf("right shift 2 is %x in hex\n", (a>>2));
    return 0;
}
