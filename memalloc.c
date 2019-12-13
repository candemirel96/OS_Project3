#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memalloc.h"

typedef struct BlockHeader{
  int size;
  struct BlockHeader* next;
} BlockHeader;

// global variables
void* chunkPointer;
int chunkSize;
int allocationMethod;
BlockHeader* head;
int remaningsize;
BlockHeader* firstBlock;
// push method for the linkedlist

// pthread_mutex_t global_malloc_lock;

int mem_init(void* chunkpointer, int chunksize, int method){
  // initializes the global variables to the parameters
  chunkPointer = chunkpointer;
  chunkSize = chunksize;
  allocationMethod = method;
  remaningsize=chunkSize;
  memset(chunkPointer, 0, chunkSize); // initializes the memory
  firstBlock=chunkPointer;
  firstBlock->size=0;
  firstBlock->next=NULL;
  return 0;
}


void *mem_allocate(int size){
  if(remaningsize>=size){
    BlockHeader* newBlock;

    newBlock=randomMethod(size);
    head=firstBlock;

    while (head->next!=NULL)
    {
      if(newBlock<head){
        break;
      }
      head=head->next;
    }
    newBlock->next =head;
    head->next=newBlock;
    newBlock->size=size;
//    printf("Created At:%p\n",newBlock);
//    printf("Ends At:%p\n",newBlock->next);
    remaningsize-=size;
      printf("New Block Created At :%p Up to: %p\n",newBlock,newBlock->next);
    return  newBlock;
  }
}
void* randomMethod(int size){
  head=firstBlock;
  while (head->next!=NULL)
    {
      printf("%d\n",(int)head->next-(int)head);
      printf("%d\n",size);
      if((int)head->next-(int)head>=size){
        printf("founded");
        break;
      }
      head->size=head->next->size;
      head=head->next;
    }
  return head;
}
void mem_free(void* objectptr){
}

void mem_print(void){

  int i = 0;
  BlockHeader* currentBlock;
  currentBlock = firstBlock;
  
     
  while (currentBlock->next!=NULL)
    {
      printf("%d: Address: %p, Size: %d\n", i, currentBlock, currentBlock->size);
      i++;
      currentBlock=currentBlock->next;
    }
}
