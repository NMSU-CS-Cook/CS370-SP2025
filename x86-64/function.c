
#include <stdio.h>

int globalx;

int sum(int v1, int v2, int v3)
{
   return v1+v2+v3;
}

int main(int argc, char** argv)
{
   globalx = 42;
   globalx = sum(7, globalx, 11);
   printf("globalx = %d\n", globalx);
   return 0;
}

