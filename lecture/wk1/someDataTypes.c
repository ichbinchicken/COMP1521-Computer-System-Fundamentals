#include <stdio.h>

int main () {
    int a;
    int b;
    printf("%%o");
    scanf("%o", &a);
    printf("%%i");
    scanf("%i", &b);
    //printf("%X\n", a);
    printf("a: hexi %x\n", a);
    printf("a: oct %o\n", a);
    printf("a: decimal %d and i:%i\n", a,a);
    printf("b: hexi %x\n", b);
    printf("b: oct %o\n", b);
    printf("b: decimal %d and i:%i\n", b,b);
    return 0;
}
