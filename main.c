
#include <stdlib.h>
#include <stdio.h>


#include "malloc.h"



int main ( int argc, char* argv[] )
{
   char* A = NULL;
   A = (char*) _malloc (10);
   A[0] = 'A'; A[1] = 'B'; A[2] = '\0';
   // printf("main:%p\n",A);
   printf( "A is %s \n",A);
   _free (A);
   // printf( "A is %p \n",A);
   // is A still equal to "AB"?
   printf( "A is %s \n",A);
   return 0;
}
