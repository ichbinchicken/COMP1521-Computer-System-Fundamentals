#include <stdio.h>
#include <string.h>

int main () {
    char a[10];
    char *sr = "hehe";
    strlcpy(a, sr,3);
    printf("the string a: %s\n", a);
    return 0;
}
