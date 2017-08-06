#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
    int num = atoi(argv[1]);
    if ((num & 0x1) != 0) printf("It is odd.\n");
    else printf("haha\n");
    return 0;
}
