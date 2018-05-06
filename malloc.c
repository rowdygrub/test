#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include "malloc.h"

// the big cheat
static char X[100000];

struct block{
  size_t size; /*Carries the size of the block described by it*/
  int free;  /*This flag is used to know whether the block described by the metadata structure is free or not -- > if free, it is set to 1. Otherwise 0.*/
  struct block *next; /*Points to the next metadata block*/
};

struct block *free_list = (void*)X;


void *_malloc(size_t size)
{
    // start the free_list for the first time
    if(free_list->size == 0)
    {
      free_list->size = 1000 - sizeof(struct block);
      free_list->free = 1;
      free_list->next = NULL;
    }

    void *tmp = NULL;
    struct block *current;

    // set the free list to current block
    current = free_list;

    // finds the next block to allocate
    while( current->next != NULL && ((current->size < size) || (current->free == 0))  )
    {

      current = current->next;
    }

    // exact fit
    if((current->size) == size)
    {
      current->free = 0;
      current++;
      tmp = current;
      return tmp;
    }
    // seperate smaller size block from free list
    else if((current->size) > (size + sizeof(struct block)))
    {
      _split(current, size);
      current++;
      tmp = current;
      return tmp;
    }
    // return NULL if no availiable size
    return tmp;
}

void _merge()
{
  struct block *current;

  current = free_list;

  while(current->next != NULL)
  {
    // adds the current and next block's size together
    // then moves 2 blocks
    if(current->free && current->next->free)
    {
      current->size = current->size + current->next->size + sizeof(struct block);
      current->next = current->next->next;
    }

      current = current->next;
  }
}

void _free(void *ptr)
{
  struct block* current = ptr;
  // set the previous header block to free(1) to merge correctly
  current = current - 1;
  current->free = 1;
  _merge();

  current->next = NULL;

  strncpy(ptr,"\0",1);
  ptr = NULL;

  if(current->next != NULL && ptr != NULL)
    printf("\nLeak Detected\n");

  current = NULL;

}

void _split(struct block *current_block, size_t size)
{
  // set up new free list
  struct block *new_free_list = current_block + size + sizeof(struct block);
  new_free_list->size = current_block->size - size - sizeof(struct block);
  new_free_list->free = 1;
  new_free_list->next = current_block->next;

  // update the requested block
  current_block->size = size;
  current_block->free = 0;
  current_block->next = new_free_list;
}


void *_calloc(size_t nmemb, size_t size)
{
   return calloc ( nmemb, size );
}

void *_realloc(void *ptr, size_t size)
{
  return realloc ( ptr, size );
}
