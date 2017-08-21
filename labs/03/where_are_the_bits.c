// where_are_the_bits.c ... determine bit-field order
// COMP1521 Lab 03 Exercise
// Written by Ziming Zheng

#include <stdio.h>
#include <stdlib.h>

struct _bit_fields {
   unsigned int a : 4,
                b : 8,
                c : 20;
};

int main(void)
{
   struct _bit_fields *p = malloc(sizeof(32));
   p->a = 1;
   p->b = 1;
   p->c = 1;
   unsigned int *q = (unsigned int *)p;
   printf("%d\n", *q);
   return 0;
}
