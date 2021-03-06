#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "memalloc.h"

int main(int argc, char* argv[]){
  void *chunkptr;
  void *endptr;
  char *charptr;
  int ret;
  int i;
  int size;
  void *x1, *x2, *x3;// object pointers
  if (argc != 2) {
    printf("usage: app <size in KB>\n");
    exit(1);

  }
  size = atoi(argv[1]);// unit is in KB
  chunkptr = sbrk(0); // end of data segment
  sbrk(size * 1024); // extend data segment by indicated amount (bytes)
  endptr = sbrk(0);// new end of data segment
  printf("chunkstart=%lx, chunkend=%lx, chunksize=%lu bytes\n",
  (unsigned long)chunkptr,
  (unsigned long)endptr,
  (unsigned long)(endptr -chunkptr));

  //test the chunk
  printf("---starting testing chunk\n");
  charptr = (char *)chunkptr;
  for (i = 0; i < size; ++i){
    charptr[i] = 0;
  }
  printf("---chunk test ended -success\n");
  ret = mem_init(chunkptr, size, 0);
  if (ret == -1) {
    printf("could not initialize \n");
    exit(1);
  }
  void* x4;
  // for allocate and deallocation
  x1 = mem_allocate(600);
  x2 = mem_allocate(700);
  x3 = mem_allocate(150);
  mem_print();
  //mem_free(x1);
  mem_free(x2);
  x4 = mem_allocate(400);
  //mem_free(x3);
  printf("\n");
  mem_print();
  return 0;
}
