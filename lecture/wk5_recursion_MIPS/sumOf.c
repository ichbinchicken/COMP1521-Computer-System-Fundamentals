#include <stdio.h>

int array[10] = {5,4,7,6,8,9,1,2,3,0};


int sumOf(int a[], int lo, int hi);
int main(void)
{
   printf("%d\n", sumOf(array,0,9));
   return 0;
}

int sumOf(int a[], int lo, int hi)
{
   if (lo > hi)
      return 0;
   else
      return a[lo] + sumOf(a,lo+1,hi);
}
