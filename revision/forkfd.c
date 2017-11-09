#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main (void) {
    int fd = open("test.txt",O_RDONLY);
    char *buf = calloc(7, 1);
    printf("begin forking..\n");
    int pid;
    if ((pid = fork()) != 0) {
        printf("child pid is %d\n", pid);
        printf("my pid is %d\n", getpid());
    } else {
       read(fd, buf, 7);
       printf("child: %s\n", buf);
    }
    return 0;
}
