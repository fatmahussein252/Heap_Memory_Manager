#include <stdio.h>
#include <string.h>
#include "./header.h"


int main()
{
	int *ptr1 = (int*)HmmAlloc(1000);
	int age = 22;
	*ptr1 = age;
	
	int *ptr2 = (int*)HmmAlloc(sizeof(int));
	int age2 = 23;
	*ptr2 = age2;
	
	int *ptr3 = (int*)HmmAlloc(sizeof(int));
	*ptr3 = 24;
	
	int *ptr4 = (int*)HmmAlloc(1050);
	*ptr3 = 25;

	int *ptr5 = (int*)HmmAlloc(5*sizeof(int));
	*ptr5 = 26;
	
	int *ptr6 = (int*)HmmAlloc(2*sizeof(int));
	*ptr6 = 27;
	

	int *ptr7 = (int*)HmmAlloc(500);
	*ptr7 = 28;

	int *ptr8 = (int*)HmmAlloc(5*sizeof(char));
	*ptr8 = 29;

	int *ptr9 = (int*)HmmAlloc(5*sizeof(char));
	*ptr9 = 30;

	int *ptr10 = (int*)HmmAlloc(9000);
	*ptr10 = 31;

	int *ptr11 = (int*)HmmAlloc(5*sizeof(int));
	*ptr11 = 32;

	int *ptr12 = (int*)HmmAlloc(60*sizeof(int));
	*ptr12 = 33;

	HmmFree(ptr1);
	HmmFree(ptr2);
	HmmFree(ptr3);
	HmmFree(ptr4);
	HmmFree(ptr5);
	HmmFree(ptr6);
	HmmFree(ptr7);
	HmmFree(ptr8);
	HmmFree(ptr9);
	HmmFree(ptr10);
	HmmFree(ptr11);
	HmmFree(ptr12);

	
	
	
	return 0;
	


}
