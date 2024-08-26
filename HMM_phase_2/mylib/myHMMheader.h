#ifndef MYLIB_H

void *HmmAlloc(size_t);
void HmmFree(void*);

void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *allocatedptr, size_t size);
void free(void *ptr);

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
void mergefree(struct freelst *, struct freelst *);
void splitNode(struct freelst *,struct freelst *, size_t);
void splitLastNode(struct freelst *, size_t);

#endif

