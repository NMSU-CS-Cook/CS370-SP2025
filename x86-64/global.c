
#include <stdio.h>

int globalx;

int main(int argc, char** argv)
{
   globalx = 42;
   printf("globalx = %d\n", globalx);
   return 0;
}

