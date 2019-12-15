#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memalloc.h"

typedef struct BlockRecord_t{
  void* address;
  int size;
  struct BlockRecord_t* next;
} BlockRecord_t;

// global variables
void* chunkPointer;
int chunkSize;
int allocationMethod;
BlockRecord_t* recordStart;
BlockRecord_t* recordEnd;

// pthread_mutex_t global_malloc_lock;

int mem_init(void* input_chunkpointer, int input_chunksize, int input_method){
  // initializes the global variables to the parameters

  chunkPointer = input_chunkpointer;
  chunkSize = input_chunksize;
  allocationMethod = input_method;

  // initialize first and last block records
  recordStart = malloc(sizeof(BlockRecord_t));
  recordEnd = malloc(sizeof(BlockRecord_t));
  
  recordStart->address = chunkPointer;
  recordEnd->address = chunkPointer + chunkSize;
  recordStart->size = 0;
  recordEnd->size = 0;
  recordStart->next = recordEnd;
  recordEnd->next = NULL;

  /* printf("Chunk starts at %p and ends at %p\n", */
  /* 	 recordStart->address, recordEnd->address); */
  
  /* printf("recordStart is at %p\n", recordStart); */
  /* printf("recordStart->next is at %p\n\n", recordStart->next); */
  /* printf("recordEnd is at %p\n", recordEnd); */
  /* printf("recordEnd->next is at %p\n\n", recordEnd->next); */

  return 0;
}

void* firstFitHoleSearch(int size){
  void* availableAddress;
  return availableAddress;
}


void* memHoleSearch(int size){
  void* availableAddress;
  bool foundSpace = false;
  BlockRecord_t *head;  
  head = recordStart;
  
  while(head->next != NULL){    
    int memHole = head->next->address - (head->address+head->size);
    if((int)size <= (int)memHole){
      availableAddress = head->address+head->size;
      printf("Found an available spot at %p of size %d\n",
	     availableAddress, memHole);
      foundSpace = true;
      break;
    }
    head = head->next;
  }
  if (foundSpace) return availableAddress;
  else { printf("No available space (memHole) found.\n");return NULL;}
}

BlockRecord_t* traverseRecordsByAddr_le(void* checkAddr){
  BlockRecord_t *head, *p_head;
  p_head = recordStart;
  head = p_head->next;
  while(head->next != NULL){
    /* printf("Checking block %p\n", head); */
    if (head->address >= checkAddr){
      /* printf("The previous block was the answer.\n"); */
      break;
    }
    p_head = p_head->next;
    head = p_head->next;
  }
  return p_head;
}


BlockRecord_t* traverseRecordsByAddr_eq(void* checkAddr){
  BlockRecord_t *head, *p_head;
  p_head = recordStart;
  head = p_head->next;
  bool foundBlockRecord = false;
  while(head->next != NULL){
    /* printf("Checking block %p\n", head); */
    if (head->address == checkAddr){
      printf("Deleting Block Record at %p.\n", checkAddr);
      foundBlockRecord = true;
      break;
    }
    p_head = p_head->next;
    head = p_head->next;
  }
  if (foundBlockRecord) return p_head;
  else{
    printf("No Block record found at %p.\n", checkAddr);
    return NULL;
  }
}


BlockRecord_t* insertBlockRecord(void* availAddr, int size){
  BlockRecord_t* newBlockRecord;
  newBlockRecord->address = availAddr;
  newBlockRecord->size = size;

  BlockRecord_t* cursorBlock = traverseRecordsByAddr_le(availAddr);
  /* printf("cursorBlock is at %p\n", cursorBlock); */
  /* printf("cursorBlock->next is at %p\n\n", cursorBlock->next); */
  
  
  newBlockRecord->next = cursorBlock->next;
  cursorBlock->next = newBlockRecord;

  /* printf("newBlockRecord is at %p\n", newBlockRecord); */
  /* printf("newBlockRecord->next is at %p\n\n", newBlockRecord->next); */
  
  return newBlockRecord;
}

void* mem_allocate(int size){
  // find hole
  printf("Looking for holes of size %d and greater.\n", size);
  void* availAddr =  memHoleSearch(size);

  // update block records

  if (availAddr !=NULL) {
    BlockRecord_t* newBlockRecord = insertBlockRecord(availAddr, size);
    printf("Created BlockRecord for block %p of size %d.\n", availAddr, size);
    return newBlockRecord->address;
  }
  else {
    printf("Memory allocation failed.\n");
    return NULL;
  }

}

void mem_free(void* memAddr){
  BlockRecord_t *cursorBlock= traverseRecordsByAddr_eq(memAddr);
  if (cursorBlock != NULL){
    BlockRecord_t *blockToDelete = cursorBlock->next;
    cursorBlock->next = blockToDelete->next;
    
    printf("Memory at %p is freed up.\n", blockToDelete->address);  
    blockToDelete = NULL;
  }
  else{
    printf("Block record deletion failed.\n");
  }
  
}

void mem_print(){
  struct BlockRecord_t *head, *p_head;
  p_head = recordStart;
  head = p_head->next;

  printf("\n*************************\n****  Block Records  ****\n*************************\n");
  
  while(head->next != NULL){
    printf("Block Record: Size of %d Bytes, at %p.\n",
	   head->size, head->address);
    p_head = p_head->next;
    head = p_head->next;
  }
  
  printf("********** END **********\n\n");
}

