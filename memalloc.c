#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memalloc.h"


typedef struct BlockHeader{
  size_t size;
  struct BlockHeader* nextBlock;
} BlockHeader;

// global variables
void* chunkPointer;
int chunkSize;
int allocationMethod;


pthread_mutex_t global_malloc_lock;

struct header_t{
  size_t size;
  struct header_t* next;
  unsigned is_free;
};

typedef char ALIGN[16];
union header {
	struct {
		size_t size;
		unsigned is_free;
		union header *next;
	} s;
	ALIGN stub;
};
typedef union header header_t;

header_t *head = NULL, *tail = NULL; // global

int mem_init(void* chunkpointer, int chunksize, int method){
  chunkPointer = chunkpointer;
  chunkSize = chunksize;
  allocationMethod = method;

  memset(chunkPointer, 0, chunkSize); // initializes the memory
  return 0;
}

// header_t* get_free_block(size_t size)
// {
// 	header_t *curr = head;
// 	while(curr) {
// 		if (curr->s.is_free && curr->s.size >= size)
// 			return curr;
// 		curr = curr->s.next;
// 	}
// 	return NULL;
// }

void *mem_allocate(size_t size){
  return &chunkPointer[20];
  return chunkPointer + 20;
  blockHeader + sizeof(BlockHeader);
}

void mem_free(void* objectptr){

  printf("\nfree called\n");
  return;
}

void mem_print(void){
  printf("\nprint called\n");
  return;
}
