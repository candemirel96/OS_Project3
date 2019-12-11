#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
// #include "memalloc.h"

// global variables
void* chunkPointer;
int chunkSize;
int chunkMethod;
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

header_t *head, *tail; // global

int mem_init(void* chunkpointer, int chunksize, int method){
  // just do it for the first fit algorthm
  if(method == 0){
    printf("\nUsing first fit algorithm!\n");

  }
  printf("\ninit called\n");
  return(0); // case of success
}


void *mem_allocate(size_t size){
  size_t total_size; // initiate a size_t for total size
  void* block;
  block = sbrk(size);
  header_t* header;
  if(block == (void*)-1){
    return NULL; // case if failure
  }

  pthread_mutex_lock(&global_malloc_lock);
  header =(header_t*)get_free_block(size);
  if (header) {
		header->s.is_free = 0;
		pthread_mutex_unlock(&global_malloc_lock);
		return (void*)(header + 1); //
	}
  total_size = sizeof(header_t) + size;
  block = sbrk(total_size);
  if (block == (void*) -1) {
  pthread_mutex_unlock(&global_malloc_lock);
  return NULL;
  }

  header = block;
	header->s.size = size;
	header->s.is_free = 0;
	header->s.next = NULL;
  if (!head)
		head = header;
	if (tail)
		tail->s.next = header;
	tail = header;
	pthread_mutex_unlock(&global_malloc_lock);
	return (void*)(header + 1);
}

header_t* get_free_block(size_t size)
{
	header_t *curr = head;
	while(curr) {
		if (curr->s.is_free && curr->s.size >= size)
			return curr;
		curr = curr->s.next;
	}
	return NULL;
}

void mem_free(void* objectptr){
  printf("\nfree called\n");
  return;
}

void mem_print(void){
  printf("\nprint called\n");
  return;
}
