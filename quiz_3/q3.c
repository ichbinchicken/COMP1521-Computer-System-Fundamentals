#include <stdio.h>
#include <stdlib.h>

union _all {
   int   ival;
   char  cval;
   char  sval[4];
   float fval;
   unsigned int uval;
} u;

int main () {
    u.uval = 0x00216948;
    printf("%s\n", u.sval);
    return 0;
}
