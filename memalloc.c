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
  BlockHeader* blockHeader = firstBlock;
  while(blockHeader->next != NULL){
    blockHeader = blockHeader->next;
  }
  return blockHeader; // the address of the last block
}


void *mem_allocate(int size){
  if(firstBlock == NULL){
    BlockHeader* newBlock = (BlockHeader*)(chunkPointer);
    newBlock->size = size;
    newBlock->next = NULL;
    firstBlock = newBlock;
    return newBlock + sizeof(BlockHeader);
  }
  if(allocationMethod == 0){ // for the first fit algorithm
    BlockHeader* lastBlock = firstFitAddress(size);
    BlockHeader* newBlock = insertBlock(lastBlock, size); // address of the new block inserted
    return newBlock + sizeof(BlockHeader);
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
    printf("We are cool in while.\n");
    prevBlock = prevBlock->next;
  }

  prevBlock->next = block->next; // detach
  block->next = NULL;
  memset(block, 0, block->size + sizeof(BlockHeader)); // resets the memory
}

void mem_free(void* objectptr){
  for (int i = 0; i < 200; i++){
    char *asd = (char *)firstBlock + i;
    printf("pegahin: %c si\n", *asd);
  }
  BlockHeader* blockHeader = (BlockHeader*)((char*)objectptr - sizeof(BlockHeader));
  printf("%dsize: \n", blockHeader->size);
  printf("We are cool in memfree.\n");
  // removeBlock(blockHeader);
}
void mem_print(void){

  int i = 0;
  BlockHeader* currentBlock;
  currentBlock = firstBlock;


  while (currentBlock!=NULL)
    {
      printf("%d: Address: %lu, Size: %d\n", i, (char*)currentBlock - (char *)chunkPointer, currentBlock->size);
      i++;
      currentBlock=currentBlock->next;
    }
}
