#ifndef OLDMALLOCS_H
#define OLDMALLOCS_H
void *HmmAlloc(size_t);
void HmmFree(void*);
#endif

#ifndef MALLOCS_H
#define MALLOCS_H
void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *allocatedptr, size_t size);
void free(void *ptr);
#endif

#ifndef LIST_H
#define LIST_H

// free list nodes
struct freelst {
    size_t size;
    struct freelst* next;
};

void CreatNode(void*, size_t);
void insertEndfree(void*,size_t);
void insertfree(void *);
struct freelst *searchfree(size_t);
void deletefree(struct freelst *,size_t);
void catfree(struct freelst *, struct freelst *);
void splitNode(struct freelst *,struct freelst *, size_t);
void splitLastNode(struct freelst *, size_t);
#endif

