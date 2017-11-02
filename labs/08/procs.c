// COMP1521 17s2 Lab08 ... processes competing for a resource
 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <sys/file.h>
#define MAXLINE BUFSIZ

void copyInput(char *);

int main(void)
{
   struct sigaction act;
   memset (&act, 0, sizeof(act));
   act.sa_handler = SIG_IGN;
   int lock = open("hello.txt", O_RDONLY | O_CREAT);
   if (fork() != 0) {
      sigaction(SIGINT, &act, NULL);  
      if(flock(lock, LOCK_EX)){
        perror("blah");
      }
      copyInput("Parent");
      flock(lock, LOCK_UN);
   }
   else if (fork() != 0) {
      sigaction(SIGINT, &act, NULL);  
      if(flock(lock, LOCK_EX)){
        perror("blah");
      }
      copyInput("Child");
      flock(lock, LOCK_UN);
   }
   else {
      if(flock(lock, LOCK_EX)){
        perror("blah");
      }
      copyInput("Grand-child");
      flock(lock, LOCK_UN);
   }
   return 0;
}

void copyInput(char *name)
{
   pid_t mypid = getpid();
   char  line[MAXLINE];
   printf("%s (%d) ready\n", name, mypid);
   while (fgets(line, MAXLINE, stdin) != NULL) {
      printf("%s: %s", name, line);
      sleep(random()%3);
      //sleep(rand()%3);
   }
   printf("%s quitting\n", name);
   return;
}
