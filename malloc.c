#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include "malloc.h"


// current occupied index, next index is the free one
int index = 0;

void *_malloc(size_t size)
{
    void *result;
    struct block *curr,*prev;

    if(!(freeList->size))
    {
      initialize();
      printf("Memory initialized\n");
    }

    curr = freeList;

    while((((curr->size) < size) || ((curr->free) == 0)) && (curr->next != NULL))
    {
      prev = curr;
      curr = curr->next;
      printf("One block checked\n");
    }

    if((curr->size) == size){
      curr->free = 0;
      result = (void*)(++curr);
      printf("Exact fitting block allocated\n");
      return result;
    }
    else if((curr->size) > (size + sizeof(struct block))){
      split(curr,size);
      result = (void*)(++curr);
      printf("Fitting block allocated with a split\n");
      return result;
    }
    else{
     result = NULL;
     printf("Sorry. No sufficient memory to allocate\n");
     return result;
    }
}

void merge()
{
 struct block *curr,*prev;
 curr = freeList;
 printf("%p",curr);
 while((curr->next) != NULL)
 {
  if((curr->free) && (curr->next->free))
  {
   curr->size += (curr->next->size) + sizeof(struct block);
   curr->next = curr->next->next;
  }
  prev = curr;
  curr = curr->next;
 }
}

void _free(void *ptr)
{
   if(((void*)X <= ptr) && (ptr <= (void*)(X + 1000))){
     struct block* curr = ptr;
     --curr;
     curr->free = 1;
     merge();
   }
   else printf("Please provide a valid pointer allocated by MyMalloc\n");
}

void split(struct block *fitting_slot,size_t size)
{
   struct block *new = (void*)((void*)fitting_slot + size + sizeof(struct block));
   new->size = (fitting_slot->size) - size - sizeof(struct block);
   new->free = 1;
   new->next = fitting_slot->next;
   fitting_slot->size = size;
   fitting_slot->free = 0;
   fitting_slot->next = new;
}

void initialize()
{
   freeList->size = 1000 - sizeof(struct block);
   freeList->free = 1;
   freeList->next = NULL;
}

void *_calloc(size_t nmemb, size_t size)
{
   return calloc ( nmemb, size );
}

void *_realloc(void *ptr, size_t size)
{
  return realloc ( ptr, size );
}
