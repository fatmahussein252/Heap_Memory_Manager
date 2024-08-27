#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>
#include "myHMMheader.h" 

#define MY_BREAK_MARGIN (4*1024)
#define ALLIGNMENT 8

// break pointer 

void *mybrk = NULL;   // The simulated break
void *oldbrk = NULL;  // used as the return pointer in HmmAlloc
struct freelst* head = NULL; // the head of the free linked nodes
struct freelst* tail = NULL; // the tail points to the last node before mybrk


/*--------------------------------------------------------------------------*/
/***HmmAlloc and its helping functions***/

void *HmmAlloc(size_t size)
{	
	size_t allocated_size =floor((size + sizeof(struct freelst) + ALLIGNMENT - 1)/ALLIGNMENT) * ALLIGNMENT;
	if (head == NULL){// handle first allocation
		oldbrk = sbrk(0);	
		sbrk(MY_BREAK_MARGIN + allocated_size);
		mybrk = sbrk(0);
		CreatNode(oldbrk, allocated_size);
		oldbrk = (char*)oldbrk + sizeof(size);	 // skip the part reserved for the size of the allocated part
		return oldbrk;
	}else{	
		oldbrk = (void*)searchfree(allocated_size); // search for free node with fit size
		if(oldbrk != tail){ // free node with fit size between head and tail found
		oldbrk = (char*)oldbrk + sizeof(size);
		return oldbrk;
		}else if (tail->size > allocated_size){ // check if the tail size is enough
		deletefree(tail,allocated_size);   // remove the allocated part from the tail and mark the mew tail
		oldbrk = (char*)oldbrk+ sizeof(size);
		return oldbrk;
		}else{ 
			if (sbrk(MY_BREAK_MARGIN + allocated_size) == (void*)-1) // check for the validity of new allocation to increase mybrk
			return NULL;
			else{
			mybrk = sbrk(0);
			CreatNode(oldbrk, allocated_size);
			oldbrk = (char*)oldbrk+ sizeof(size);
			return oldbrk;
			}
		}	
	}
}
/*Description:
This function is used to create a new node for the first allocation or allocation at the tail.
It calls insertEndfree function to mark the new tail.*/
void CreatNode(void *oldbrk, size_t size) 
{
    struct freelst* newNode = (struct freelst*) oldbrk;
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
	temp->size = size;
	head = (char*)freeptr + size;//temp->size;
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
		if (temp->size >= size) // suitable free node found
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
	
	if (delete == head && head == tail) // freelist has one Node before mybrk
	{	
		head->next = mybrk;
		splitLastNode(delete,size);  //split the node
		tail = head;
	}
	else if (delete == head)
	{
		head = head->next;
	}
	else if (delete == tail)
	{
	delete->size = size;
	struct freelst *temp = head;
	while(temp->next != tail)
		temp = temp->next;
	tail = (char*)tail + size;
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
			if (delete->size < (size + sizeof(struct freelst))){
			temp->next = temp->next->next;
			break;
			}else{
			splitNode(temp,delete,size);
			break;
			}
		}
		else	
		temp = temp->next;
	
	}
	}
}

/* Description:
This Function is used to split the tail (last node before the brk) when head = tail (only one node exists).
*/
void splitLastNode(struct freelst *delete, size_t size)
{
	struct freelst *temp = head;
	head = (char*)head + size;
	head->size = (char*)(temp->next) - (char*)head;
	head->next = temp->next;
	delete->size = size;
	//assert(head->size < 10000);
	return;
}

/*Description:
This Function is used to split the free node (if available) to allocate in part of it.
*/
void splitNode(struct freelst *brev, struct freelst *delete, size_t size)
{	
	brev->next = (char*)delete + size;
	brev->next->size = delete->size - size;
	//assert(brev->next->size < 10000);
	brev->next->next = delete->next;
	delete->size = size;
	//assert(delete->size < 10000);
	return;
}

/*--------------------------------------------------------------------------*/
/***HmmFree and its helping functions***/

void HmmFree(void *freeptr)
{	
	
	insertfree((char*)freeptr-sizeof(size_t));

}

/*Description:
This function is used to insert new free node*/
void insertfree(void *freeptr)
{
	struct freelst *newNode = (struct freelst *)freeptr;
	if (newNode < head) // insert before head
	{	
		
		struct freelst *temp = head;
		head = newNode;
		head->next = temp;
		// check for two adjacent free nodes
		mergefree(head,head->next);
		return;
	}
	else if (newNode > head && newNode < tail)
	{struct freelst* current = head;
	while(current != tail)
	{
		if (newNode > current && newNode < current->next)
		{struct freelst* temp = current->next;
		current->next = newNode;
		newNode->next = temp;
		// check for two adjacent free nodes
		mergefree(current,newNode);
		break;
		}
		else
		current = current->next;
	}
	}
	if (tail->size > 4 * MY_BREAK_MARGIN){
	if(brk((char*)tail + 4 * MY_BREAK_MARGIN) == 0){
	tail->size = 4 * MY_BREAK_MARGIN;
	mybrk = sbrk(0);
	tail->next = mybrk;
	}
	}
	
	
	
}
 /* Description:
 This function is used to concatenate two adjacent free nodes if exist*/
void mergefree(struct freelst *node, struct freelst *adjacent)
{
	if ((char*)node + node->size == (char*)adjacent){
		node->size = node->size + adjacent->size;
		node->next = adjacent->next;
		if (adjacent == tail){
		tail = node;
		return;
		}else
		mergefree(node,node->next);
	}
}



