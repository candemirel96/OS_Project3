#include <stdlib.h>
#include <stdio.h>
#include "memalloc.h"
#include <stdbool.h>

void* cpointer;
int   csize;
int   cmethod; 

typedef struct memory_ref{
    //char* name;
    int size;
    void* adress;
    struct memory_ref* next;
};



int mem_init (void *chunkpointer, int chunksize, int method){
    printf("initcalled\n");
    cpointer=chunkpointer;
    csize=chunksize;
    cmethod=method;
    return (0);// if success
    }
void *mem_allocate (int objectsize){
    printf("alloc called\n");
    return (NULL);// if not success
    }
void mem_free(void *objectptr){
    printf("free called\n");
    return;
    }
void mem_print (void){
    printf("print called\n");
    return;
    }