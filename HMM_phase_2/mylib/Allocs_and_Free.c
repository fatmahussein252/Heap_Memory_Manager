#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include "myHMMheader.h"

void *retptr = NULL;

void *malloc(size_t size)
{
	retptr = HmmAlloc(size);
	return retptr;
}

void *calloc(size_t nmemb, size_t size)
{	

	if (size != 0){
		retptr = HmmAlloc(size * nmemb);
		if (retptr == NULL)
			return NULL;
		else{
		 void *retmeta = (char*)retptr - sizeof(size_t);
		struct freelst *temp = (struct freelst*)retmeta;
		size_t initsize =  temp->size - sizeof(size_t);
		memset(retptr, 0, initsize);
		return retptr;
		}
	}else{
		retptr = HmmAlloc(0);
		return retptr;
	}	
}

void *realloc(void *allocatedptr, size_t size)
{	
	//sleep(2);
	// Case 1: allocatedptr is NULL
	if (allocatedptr == NULL){
		retptr = HmmAlloc(size);
		return retptr;
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
    	  void *allocatedmeta = (char*)allocatedptr - sizeof(size_t);
	struct freelst *allocated = (struct freelst*)allocatedmeta;
	
	void *retmeta = (char*)retptr - sizeof(size_t);
	struct freelst *ret = (struct freelst*)retmeta;
	
	size_t copy_size = allocated->size < ret->size ? (allocated->size-(sizeof(size_t))) : size;
	memcpy(retptr, allocatedptr, copy_size);
	HmmFree(allocatedptr);
	return retptr;
	
	
			
}

void free(void *ptr)
{
	if (ptr != NULL)
	HmmFree(ptr);
	return;

}




