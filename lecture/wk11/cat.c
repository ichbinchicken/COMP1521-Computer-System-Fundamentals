#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main () {
    int ch;
    char buffer[50];
    FILE *F = fopen("cat.c", "r");
    while (1) {
        printf("%c\n", getc(F));
    }
    return 0;
}
