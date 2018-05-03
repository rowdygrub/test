#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include "malloc.h"

// the big cheat
static char X[1000];

struct block{
  size_t size; /*Carries the size of the block described by it*/
  int free;  /*This flag is used to know whether the block described by the metadata structure is free or not -- > if free, it is set to 1. Otherwise 0.*/
  struct block *next; /*Points to the next metadata block*/
};

struct block *freeList = (void*)X;

// current occupied index, next index is the free one


void *_malloc(size_t size)
{
    // start the freelist for the first time
    if(!(freeList->size))
    {
      freeList->size = 1000 - sizeof(struct block);
      freeList->free = 1;
      freeList->next = NULL;
      // printf("Memory initialized\n");
    }

    void *result = NULL;
    struct block *current;
    struct block *prev;

    current = freeList;

    while((((current->size) < size) || ((current->free) == 0)) && (current->next != NULL))
    {
      prev = current;
      current = current->next;
      // printf("One block checked\n");
    }

    if((current->size) == size)
    {
      current->free = 0;
      result = (void*)(++current);
      // printf("Exact fitting block allocated\n");
      return result;
    }
    else if((current->size) > (size + sizeof(struct block)))
    {
      split(current,size);
      result = (void*)(++current);
      // printf("Fitting block allocated with a split\n");
      return result;
    }
    return result;
}

void merge()
{
 struct block *current,*prev;
 current = freeList;

 while((current->next) != NULL)
 {
  if((current->free) && (current->next->free))
  {
   current->size += (current->next->size) + sizeof(struct block);
   current->next = current->next->next;
  }
  prev = current;
  current = current->next;
 }
}

void _free(void *ptr)
{

  // check if the pointer is within the memory block (the big cheat)X
  if(((void*)X <= ptr) && (ptr <= (void*)(X + 1000)))
  {
    struct block* current = ptr;
    --current;
    current->free = 1;
    merge();
    current = NULL;
  }
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


void *_calloc(size_t nmemb, size_t size)
{
   return calloc ( nmemb, size );
}

void *_realloc(void *ptr, size_t size)
{
  return realloc ( ptr, size );
}
