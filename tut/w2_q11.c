#include <stdio.h>
#include <stdlib.h>
typedef unsigned int Word;
void show(Word a) {
    printf("%d: ", a);
    int j;
    int one = 0;
    for(j = 31;j >= 0;j--){
        if ((a & (1u<<j)) != 0) {
            printf("1");
            one ++;
        } else {
            printf("0");
        }
    }
    printf("\n");
    printf("PS: There are %d of 1s\n", one);
}
Word reverse(Word n) {
    int i;
    Word rev = 0;
    for(i = 31;i >= 0;i --) {
        if (((1u << i) & n) != 0) rev = (1u << (31 - i)) | rev;       
    }
    return rev;
}

int main (void) {
    Word n;
    scanf("%x", &n);
    show(n);
    Word r = reverse(n);
    show(r);
    printf("The reverse num in hex is %x\n", r);
    return 0; 
}
