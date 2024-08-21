#include <stdio.h>
#include "./header.h" 
#include <stdlib.h>
#include <string.h>

#define HEAP_SIZE 209715200
#define HEAP_LAST_BYTE 209715199
#define MY_BREAK_MARGIN 1000

// initialize heap and break pointer 
char myHeap[HEAP_SIZE] = {0};
void *mybrk = myHeap;   // The simulated break
void *oldbrk = myHeap;  // used as the return pointer in HmmAlloc
struct freelst* head = NULL; // the head of the free linked nodes
struct freelst* tail = NULL; // the tail points to the last node before mybrk


/*--------------------------------------------------------------------------*/
/***HmmAlloc and its helping functions***/

void *HmmAlloc(size_t size)
{	
	
	if (head == NULL){// handle first allocation	
		mybrk = mybrk + size + MY_BREAK_MARGIN;
		CreatNode(oldbrk, size);
		oldbrk = oldbrk + sizeof(size);	 // skip the part reserved for the size of the allocated part
		return oldbrk;
	}else{	
		oldbrk = (void*)searchfree(size); // search for free node with fit size
		if(oldbrk != tail){ // free node with fit size between head and tail found
		oldbrk = oldbrk + sizeof(size);
		return oldbrk;
		}else if (tail->size > size + sizeof(struct freelst)){ // check if the tail size is enough
		deletefree(tail,size);   // remove the allocated part from the tail and mark the mew tail
		oldbrk = oldbrk+ sizeof(size);
		return oldbrk;
		}else{ 
			if ((char*)mybrk + size + 1000 > &myHeap[HEAP_LAST_BYTE]) // check for the validity of new allocation to increase mybrk
			return NULL;
			else{
			mybrk = mybrk + size + MY_BREAK_MARGIN;
			CreatNode(oldbrk, size);
			oldbrk = oldbrk+ sizeof(size);
			return oldbrk;
			}
		}	
	}
}
/*Description:
This function is used to create a new node for the first allocation or allocation at the tail.
It saves the size allocated and calls insertEndfree function to mark the new tail.*/
void CreatNode(void *oldbrk, size_t size) 
{
    struct freelst* newNode = (struct freelst*) oldbrk;
    newNode->size = sizeof(struct freelst) + size;
    insertEndfree((void*)newNode,size);
    return;   
}

/*Description:
This function is used to handle the last free node after allocation*/

void insertEndfree(void *freeptr,size_t size)            
{
	if (head == NULL) // first free node (the space before mybrk)
	{
	struct freelst *temp = (struct freelst*) freeptr;
	head = freeptr + temp->size;
	head->size = (char*)mybrk - (char*)head;
    	head->next = mybrk;
    	tail = head;
    	return;
	}
	else if (freeptr == tail)
	{
	deletefree(tail,size);
	}
	
	
}

/*Description:
This function is used to search in the free nodes for fit size for new allocation, if suitable node found it calls deletefree function to remove this node from the free linked nodes, if no node found it returns the tail*/

struct freelst *searchfree(size_t size)
{	
	struct freelst *temp = head;
	while (temp != tail)
	{	
		if (temp->size >= size + sizeof(struct freelst)) // suitable free node found
		{
			deletefree(temp,size);
			return temp;
		}
		else
		temp = temp->next;
	}
	return temp;
}

/*Description:
This function is used to delete node from the free linked nodes*/
void deletefree(struct freelst *delete,size_t size)       
{	
	
	if (delete == head)
	{
		if (head == tail) // last node befor mybrk
		{ 
		delete->size = size + sizeof(struct freelst);
		struct freelst *temp = head;
		head = (char*)head + size + sizeof(struct freelst);
		head->size = (char*)mybrk - (char*)head;
		head->next = mybrk;
		tail = head;
		} 
		else 
		{
		head = head->next;
		}
	}
	else if (delete == tail)
	{
	delete->size = size + sizeof(struct freelst);
	struct freelst *temp = head;
	while(temp->next != tail)
		temp = temp->next;
	tail = (char*)tail + size + sizeof(struct freelst);
	temp->next = tail;
	tail->size = (char*)mybrk - (char*)tail;
	tail->next = mybrk;	

	}
	else if (delete > head && delete < tail)
	{struct freelst *temp = head;
	while (temp != tail)
	{
		if (temp->next == delete)
		{
			temp->next = temp->next->next;
			break;
		}
		else	
		temp = temp->next;
	
	}
	}
}


/*--------------------------------------------------------------------------*/
/***HmmFree and its helping functions***/

void HmmFree(void *freeptr)
{	
	
	insertfree(freeptr-sizeof(size_t));

}

/*Description:
This function is used to insert new free node*/
void insertfree(void *freeptr)
{
	struct freelst *free = (struct freelst *)freeptr;
	if (free < head) // insert before head
	{	
		
		struct freelst *temp = head;
		head = free;
		head->next = temp;
		// check for two adjacent free nodes
		catfree(head,head->next);
		return;
	}
	else if (free > head && free < tail)
	{struct freelst* current = head;
	while(current != tail)
	{
		if (free > current && free < current->next)
		{struct freelst* temp = current->next;
		current->next = free;
		free->next = temp;
		// check for two adjacent free nodes
		catfree(current,free);
		break;
		}
		else
		current = current->next;
	}
	}
	
	
	
}
 /* Description:
 This function is used to concatenate to adjacent free nodes if exist*/
void catfree(struct freelst *node, struct freelst *adjacent)
{
	if ((char*)node + node->size == (char*)adjacent){
		node->size = node->size + adjacent->size;
		node->next = adjacent->next;
		if (adjacent == tail){
		tail = node;
		return;
		}else
		catfree(node,node->next);
	}
}



