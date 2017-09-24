#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main () {
    int fp = open("test.txt",O_RDONLY);
    char buff[6];
    ssize_t size = read(fp, buff, 5);
    if (size < 0) printf("you fail\n");
    else {
        printf("read in %zd\n", size);
    }
    buff[5] = 0;
    printf("This is output for buff...\n");
    char *p;
    for(p = buff;*p != 0;p++) printf("%c",*p);
    printf("\n");
    close(fp);
    FILE *f; char tmp[6];
    tmp[5] = 0;
    f = fopen("test.txt", "r");
    fread(tmp, 1, 5, f);
    printf("This is output for tmp...\n");
    for(p = tmp;*p != 0;p++) printf("%c",*p);
    fclose(f);
    return 0;
}

