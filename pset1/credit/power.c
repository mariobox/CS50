#include <stdio.h>
#include <cs50.h>

long long pwr(long long x, int y);

int main () {

   /* local variable definition */
   long long a = 10;
   int b = 6;
   long long res;

   /* calling a function to get max value */
   res = pwr(a, b);

   printf( "%llu at the %i power is: %llu\n", a, b, res );

   return 0;
}

// create power function
long long pwr(long long x, int y)
{ long long res = 1;
  for(int i = 1; i <= y; i++)
    {
      res *= x;
    }
    return res;
}
