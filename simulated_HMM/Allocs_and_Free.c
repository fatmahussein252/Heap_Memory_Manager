#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include "myHMMheader.h"

void *retptr = NULL;

void *malloc(size_t size)
{
	if (size != 0){
		//sleep(2);
		retptr = HmmAlloc(size);
		return retptr;
	}else
		return NULL;
}

void *calloc(size_t nmemb, size_t size)
{	
	
	if (size != 0){
		retptr = HmmAlloc(size * nmemb);
		if (retptr == NULL)
			return NULL;
		else{
		memset(retptr, 0, size);
		return retptr;
		}
	}else
		return NULL;	
}

void *realloc(void *allocatedptr, size_t size)
{
	// Case 1: allocatedptr is NULL
	if (allocatedptr == NULL){
	if (size != 0){
		retptr = HmmAlloc(size);
		return retptr;
	}else
		return NULL;
	}
	
	// Case 2: size is 0 (deallocate the memory)
	if (size == 0){
	HmmFree(allocatedptr);
	return NULL;
	}
	
	 // Case 3: allocatedptr is not NULL and size is not 0
   	 retptr = HmmAlloc(size);
  	  if (retptr == NULL) {
      	  // Allocation failed, return NULL without freeing the original block
      	  return NULL;
    	  }
	
	void *allocatedmeta = allocatedptr - sizeof(size_t);
	struct freelst *temp = (struct freelst*)allocatedmeta;
	size_t copy_size = temp->size < (size + sizeof(struct freelst)) ? temp->size : (size + sizeof(struct freelst));
	memcpy(retptr, allocatedmeta, copy_size);
	HmmFree(allocatedptr);
	return retptr;
	
	
			
}

void free(void *ptr)
{
	if (ptr != NULL)
	HmmFree(ptr);
	return;

}




