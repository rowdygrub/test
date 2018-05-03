
#include <stdlib.h>
#include <stdio.h>


#include "malloc.c"



int main ( int argc, char* argv[] )
{
   char* A = NULL;
   char* B = NULL;

   A = (char*) _malloc (10);
   A[0] = 'A'; A[1] = 'B'; A[2] = '\0';

   B = (char*) _malloc (10);
   B[0] = 'A'; B[1] = 'B'; B[2] = '\0';

   printf( "A is %s \n",A);

   _free (A);
   _free (B);

   // is A still equal to "AB"?
   printf( "A is %s \n",A);
   printf("B is %s\n",B);

   return 0;
}
