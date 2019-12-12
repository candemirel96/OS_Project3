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
BlockHeader* head;
void* address = chunkPointer;
// push method for the linkedlist

// pthread_mutex_t global_malloc_lock;

int mem_init(void* chunkpointer, int chunksize, int method){
  // initializes the global variables to the parameters
  chunkPointer = chunkpointer;
  chunkSize = chunksize;
  allocationMethod = method;

  memset(chunkPointer, 0, chunkSize); // initializes the memory
  return 0;
}

void *mem_allocate(int size){
  // return &chunkPointer[20];
  // return chunkPointer + 20;
  BlockHeader* previousBlock;
  address = chunkPointer + size; // the return value of 0,1,2 functions
  // BlockHeader newBlock  = address;
  BlockHeader* newBlock  = (BlockHeader*)address;
  newBlock->size = size;
  newBlock->nextBlock = previousBlock->nextBlock;
  previousBlock->nextBlock = newBlock;

  if( head == NULL ){
    head = previousBlock;
  }
  return address + sizeof(BlockHeader);
}

void mem_free(void* objectptr){

  printf("\nfree called\n");
  return;
}

void mem_print(void){
  int i = 0;
  BlockHeader* currentBlock;
  currentBlock = head;
  // printf("%d\n" ,&head);
  // printf("%d\n" ,head->nextBlock);

  // printf("%d: Address: %d, Size: %d\n", 1, (char*)currentBlock - (char*)chunkPointer, currentBlock->size);
  // currentBlock = currentBlock->nextBlock;
  // printf("%d: Address: %d, Size: %d\n", 2, (char*)currentBlock - (char*)chunkPointer, currentBlock->size);


  while(currentBlock != NULL){
    printf("%d: Address: %d, Size: %d\n", i, (char*)currentBlock - (char*)chunkPointer, currentBlock->size);
    currentBlock = currentBlock->nextBlock;
    // printf("%d: Address: %d, Size: %d\n", i, (char*)currentBlock - (char*)chunkPointer, currentBlock->size);
    i++;
  }
}
