#include <stdlib.h>
#include <stdio.h>
int main () {
    int a[10];
    a[0]=0;
    a[1]=1;
    a[2]=3;
    printf("%p, %p, %p\n", &a[0], &a[1], &a[2]);
    return 0;
}
