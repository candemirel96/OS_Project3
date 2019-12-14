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
int remaningSize;
BlockHeader* firstBlock;
// push method for the linkedlist

// pthread_mutex_t global_malloc_lock;

int mem_init(void* chunkpointer, int chunksize, int method){
  // initializes the global variables to the parameters
  chunkPointer = chunkpointer;
  firstBlock = chunkPointer;
  chunkSize = chunksize;
  allocationMethod = method;
  remaningSize=chunkSize;
  memset(chunkPointer, 0, chunkSize); // initializes the memory
  return 0;
}

BlockHeader* insertBlock(BlockHeader* lastBlock, int size){
  BlockHeader* newBlock = (BlockHeader*)((char*)lastBlock + sizeof(BlockHeader) + lastBlock->size);
  newBlock->size = size;
  newBlock->next = NULL;
  lastBlock->next = newBlock;
  return newBlock; // returns the address of the new block inserted
}

BlockHeader* firstFitAddress(int size){
  // finds the first avalable space in the chunk
  BlockHeader* blockHeader = firstBlock; // replace with cutrrent block
  int gap;
  while(blockHeader->next != NULL){ // && (blockHeader->next - blockHeader >= remaningSize)
    printf("\nWhile\n");
    gap = ((char*) blockHeader->next - ((char*) blockHeader + blockHeader->size + sizeof(BlockHeader)));
    printf("Gap Value Is: %d\n" , gap);
    blockHeader = blockHeader->next;
  }
  return blockHeader; // the address of the last block
}

// BlockHeader* bestFit()

void *mem_allocate(int size){
  if(firstBlock == NULL){
    BlockHeader* newBlock = (BlockHeader*)(chunkPointer);
    newBlock->size = size;
    newBlock->next = NULL;
    firstBlock = newBlock;
    remaningSize -= size;
    return (char*)newBlock + sizeof(BlockHeader);

  }
  if(allocationMethod == 0){ // for the first fit algorithm
    BlockHeader* lastBlock = firstFitAddress(size);
    BlockHeader* newBlock = insertBlock(lastBlock, size); // address of the new block inserted
    return (char* )newBlock + sizeof(BlockHeader);
  }

//   if(remaningsize>=size){
//     BlockHeader* newBlock;
//
//     newBlock=randomMethod(size);
//     head=firstBlock;
//
//     while (head->next!=NULL)
//     {
//       if(newBlock<head){
//         break;
//       }
//       head=head->next;
//     }
//     newBlock->next =head;
//     head->next=newBlock;
//     newBlock->size=size;
// //    printf("Created At:%p\n",newBlock);
// //    printf("Ends At:%p\n",newBlock->next);
//     remaningsize-=size;
//     printf("New Block Created At :%p Up to: %p\n",newBlock,newBlock->next);
//     return  newBlock;
//   }
}






// void* randomMethod(int size){
//   head=firstBlock;
//   while (head->next!=NULL)
//     {
//       printf("%d\n",(int)head->next-(int)head);
//       printf("%d\n",size);
//       if((int)head->next-(int)head>=size){
//         printf("founded");
//         break;
//       }
//       head->size=head->next->size;
//       head=head->next;
//     }
//   return head;
// }

void removeBlock(BlockHeader* block){
  // traverse the linkedlist for one block before the delete-block
  BlockHeader* prevBlock = firstBlock;
  while((prevBlock != NULL) && (prevBlock->next != block)){
    prevBlock = prevBlock->next;
  }

  prevBlock->next = block->next; // detach
  block->next = NULL;
  memset(block, 0, block->size + sizeof(BlockHeader)); // resets the memory
}

void mem_free(void* objectptr){
  BlockHeader* blockHeader = (BlockHeader*)((char*)objectptr - sizeof(BlockHeader));
  removeBlock(blockHeader);
}
void mem_print(void){

  int i = 0;
  BlockHeader* currentBlock;
  currentBlock = firstBlock;


  while (currentBlock!=NULL)
    {
      printf("%d: Address: %p, Size: %d\n", i, (char*)currentBlock - (char *)chunkPointer, currentBlock->size);
      i++;
      currentBlock=currentBlock->next;
    }
}
