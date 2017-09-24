#include <stdio.h>
int main () {
    char test[100] = "word1          word2      , word3";
    char a[15], b[15];
    char res[15]; 
    //sscanf(test, "%s%[^,]%s", res, a, b);
    //sscanf(test, "%s%s%s", res, a, b);
    sscanf(test, "%s %[^ ] , %s", res, a, b);
    //sscanf(test, "%s%[^,], %s", res, a, b);
    //sscanf(test, "%s%[^,] %*[,]%s", res, a, b);
     
    printf("%s|%s|%s|\n", res, a, b);
    return 0;
}
