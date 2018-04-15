#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include "malloc.h"

// the big cheat
static char X[0x100000];
// current occupied index, next index is the free one
int index = 0;



void *_malloc(size_t size)
{
    void *ptr = malloc ( size );
    //X[index] = malloc ( size );
    //printf("_malloc ptr: %p\n",ptr);
    memcpy(&X[index],ptr,size);
    index = index + size;
    //printf("_malloc: %p\n",&X[0]);



    return &X;
}

void _free(void *ptr)
{
    int i;
    for(i = 0; i < index; i++)
    {
      if(&X[i] == ptr)
      {
        X[i] = '\0';
        //printf("free: %c\n",X[i]);
      }
    }
    // free ( ptr );
    ptr = NULL;
    //printf("free: %p\n",ptr);
}

void *_calloc(size_t nmemb, size_t size)
{
   return calloc ( nmemb, size );
}

void *_realloc(void *ptr, size_t size)
{
  return realloc ( ptr, size );
}
