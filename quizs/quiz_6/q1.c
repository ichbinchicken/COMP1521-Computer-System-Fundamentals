#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach/error.h>
int main(void)
{
       pid_t id;  int stat;
#ifdef bug 
       printf("hahaha\n");
#endif
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
