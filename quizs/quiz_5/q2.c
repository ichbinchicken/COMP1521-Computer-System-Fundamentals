#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
int main () {
    int fd = open("xoxo",O_WRONLY|O_APPEND);
    if (fd < 0)
        printf("xoxo\n");
    char stuff[6] = "hello";
    ssize_t nbytes = write(fd, stuff, 2);
    printf("%ld\n", nbytes);
    return 0;
} 
