#include <stdio.h>
#include <stdlib.h>

int recr (int n);
int main (int argc, char *argv[]) {
    int n = atoi(argv[1]);
    printf("%d! = %d\n", n, recr(n));
    return 0;
}

int recr (int n) {
    if (n == 1) return 1;
    else return n * recr(n-1);
}
