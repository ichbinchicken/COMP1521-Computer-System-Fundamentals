#include <stdio.h>
#include <stdlib.h>

int main()
{
   char str[33] = "11111111111111111111111111111111";
   char *ptr;
   long ret;

   ret = strtol(str, &ptr, 2);
   printf("%lx\n", ret);
   //printf("String part is |%s|", ptr);

   return(0);
}
