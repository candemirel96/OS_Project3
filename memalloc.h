#ifndef MEMALLOC_H
#define MEMALLOC_H

int mem_init(void*, int, int);
void* mem_allocate(size_t);
void mem_free(void*);
void mem_print(void);
struct header_t *get_free_block(size_t);

#endif
