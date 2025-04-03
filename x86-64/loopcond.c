
#include <stdio.h>

int globalx;
int globali;

int sum(int v1, int v2, int v3)
{
   v1 = v2 & v3;
   if (globalx > 100 && globalx < 200) {
      globali = 9;
   } else {
      globali = 7;
   }
   printf("globali=%d\n",globali);
   while (globali > 1) {
      printf("*\n");
      globali--;
   }
   
   
   return v1+v2+v3;
}

int main(int argc, char** argv)
{
   globalx = 42;
   globalx = sum(7, globalx, 11);
   printf("globalx = %d\n", globalx);
   return 0;
}

