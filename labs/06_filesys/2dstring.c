#include <stdio.h>
#include <stdlib.h>

int cmp (const void *a, const void *b);
int main () {
    char *strArray[5] = {"tyo","abr","phi","dty","lwe"};
    qsort(strArray, 5, sizeof(char *), cmp);
    printf("%s\n", strArray[0]);
    return 0;
}
#if 0
int cmp (const void *a, const void *b) {
    //printf("%c\n", **(char **)a);
    return (**((char *)*)a - **((char *)*)b);
}
#endif 
// a pointer to the element you are comparing. 
#if 0
int cmp (const void *a, const void *b) {
    printf("%c\n", **(char *)a);
    return (**(char *)a - **(char *)b);
}
#endif
