#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void handler(int sig)
{
       printf("Quitting...\n");
          exit(0);
}
 
int main(int argc, char *argv[])
{
       struct sigaction act;
          memset (&act, 0, sizeof(act));
             act.sa_handler = &handler;
                sigaction(SIGHUP, &act, NULL);
                   sigaction(SIGINT, &act, NULL);
                      sigaction(SIGKILL, &act, NULL);
                         while (1) sleep(5);
                            return 0;
} 
