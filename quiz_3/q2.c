#include <stdio.h>
#include <stdlib.h>

int f(char* y);

int main (int argc, char* argv[]) {
    printf("z is %d\n", f(argv[1]));
    return 0;
}

int f(char* y) {
    int z = 0;
    while (*y ++ != '\0') z++;
    return z;
}

