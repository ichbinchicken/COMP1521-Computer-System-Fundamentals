#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "allocator.h"
typedef unsigned char byte;

int main (int argc, char * argv[]) {
   
   vlad_init(2013);
   byte *p1 = vlad_malloc(76);
   byte *p2 = vlad_malloc(40);
   byte *p3 = vlad_malloc(52);
   byte *p4 = vlad_malloc(60);
   vlad_stats();
   vlad_free(p3);
   vlad_stats();
   byte *p5 = vlad_malloc(1780);
   assert(p5 !=NULL);

   printf("Pass\n");
   vlad_free(p1);
   vlad_free(p2);
   vlad_free(p4);
   vlad_free(p5);
   vlad_end();
   return 0;
}
