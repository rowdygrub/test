#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "malloc.c"

static inline unsigned long long rdtsc (void)
{
   unsigned int hi,lo;
   __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
   return ( (unsigned long long) lo) | ( (unsigned long long) hi<<32 ) ;
}
double diffTime ( struct timespec t0, struct timespec t1 )
{
   return t1.tv_sec - t0.tv_sec +  (t1.tv_nsec - t0.tv_nsec) / 1e9;
}

int main ( int argc, char* argv[] )
{
   {
    FILE * fp = fopen("output_long.txt","w");
     char* A = NULL;
     struct timespec t0;
     struct timespec t1;
     double min = 999999.0;
     double max = 0.0;
     // ignore the time on the first one
     A = (char*) _malloc (10);
     for (int i=0;i<100000;i++)
     {
        clock_gettime ( CLOCK_MONOTONIC, &t0 );
        A = (char*) _malloc (10);
        clock_gettime ( CLOCK_MONOTONIC, &t1 );
        double dt = diffTime ( t0, t1 );
        // might want to print dt out and graph it
        // really long print 100000 times

        fprintf (fp," %lld\n", dt );
        if (dt < min)
          min = dt;
        if (dt >max)
          max = dt;
     }
     fprintf (fp, "min = %f max = %f \n", min, max );
     fclose(fp);
   }
   // try a different kind of clock
   {
     FILE * fp = fopen("output.txt","w");
     char* A = NULL;
     long long unsigned int t0;
     long long unsigned int t1;
     long long unsigned int min = 0xfffffff; // a big number
     long long unsigned int max = 0.0;       // a small number
     // ignore the time on the first one
     A = (char*) _malloc (10);
     for (int i=0;i<100;i++)
     {
        t0 = rdtsc ();
        A = (char*) _malloc (10);
        t1 = rdtsc ();
        unsigned long long int dt = t1 - t0;
        // might want to print dt out and graph it
        fprintf (fp," %lld\n", dt );
        if (dt < min)
          min = dt;
        if (dt >max)
          max = dt;
     }
     fprintf (fp, "min = %lld max = %lld \n", min, max );
     fclose(fp);
   }
   return 0;
}
