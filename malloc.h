
#include <stdlib.h>
#include <stddef.h>

// the big cheat
char X[1000];

struct block{
  size_t size; /*Carries the size of the block described by it*/
  int free;  /*This flag is used to know whether the block described by the metadata structure is free or not -- > if free, it is set to 1. Otherwise 0.*/
  struct block *next; /*Points to the next metadata block*/
};

struct block *freeList = (void*)X;

void initialize();

void merge();

void *_malloc(size_t size);

void _free(void *ptr);

void *_calloc(size_t nmemb, size_t size);

void *_realloc(void *ptr, size_t size);
