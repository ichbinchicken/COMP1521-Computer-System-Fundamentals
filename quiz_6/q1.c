#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
       pid_t id;  int stat;

          if ((id = fork()) != 0) {
                    sleep(3);
                    printf("A = %d\n", id);
                          wait(&stat);
                          printf("stat is %d\n", stat);
                                return 1;
                                   }
             else {
                       printf("B = %d\n", getppid());
                             return 0;
                                }
}
