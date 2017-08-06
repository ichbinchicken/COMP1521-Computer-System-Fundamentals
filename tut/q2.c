#include <stdio.h>
 int main(void)
{
   int n = 1234;
   int *p;
   char *c;
 
   p = &n;
   c = (char *) &n;
   n++;
   printf("%d\n", *p);
   printf("%p\n", p);
   p++;
   c++;
   printf("%p\n", p);
   printf("%p\n", c);
   return 0;
} 
