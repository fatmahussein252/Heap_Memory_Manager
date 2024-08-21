void *HmmAlloc(size_t);
void HmmFree(void*);

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
#endif

