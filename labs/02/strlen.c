#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main (int argc, char *argv[]) {
    printf("strlen of %s is %lu\n", argv[1], strlen(argv[1]));
    return 0;
}
