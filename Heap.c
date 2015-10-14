#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"



GenericHeap * emptyHeap(int maximumSize, int (*fnPtr) (void *, void*))
{

	GenericHeap * output =malloc(sizeof(GenericHeap));
	output->container = malloc(sizeof(void*) * (maximumSize+1) );
	output->lastIndex = 0; //empty heap, we never put anything in 0 index anyway. root is at index 1
	output->maxSize = maximumSize; 
	output->compareFn = fnPtr;
	return output;
}

void pushHeap(GenericHeap * hp, void * value)
{
	if(hp==NULL)
	{
		printf("Error: called pushHeap with null passed in for heap pointer\n");
		return;
	}
	if(hp->maxSize == hp->lastIndex)
	{
		printf("warning: called pushHeap on full heap, input was ignored\n");
		return; 
	}
	if(value==NULL)
	{
	printf("warning: called pushHeap with null input, function call was ignored\n");
		return; 
	}

	hp->container[(hp->lastIndex)+1] = value;
	hp->lastIndex = hp->lastIndex + 1;

	int currentIndex= hp->lastIndex;
	while(currentIndex>1)
	{
		int parentIndex = currentIndex/2;
		if(hp->compareFn(hp->container[currentIndex],hp->container[parentIndex]))
		{
			void * tmp = hp->container[currentIndex];
			hp->container[currentIndex] = hp->container[parentIndex];
			hp->container[parentIndex]= tmp; 
			currentIndex=parentIndex;
			continue;
		}
		break;
	}

	//now we need to bubble up:
}

void applyToHeap(GenericHeap* hp, void (*fnPtr)(void * ))
{
	void * index;
	int i;
	for(i=1; i<= hp->lastIndex ; i++)
	{
		index=hp->container[i];
		fnPtr(index);	
	}

}

void eraseHeap(GenericHeap * hp, void (*freeFn) (void*))
{
	if(hp==NULL)
	{
		printf("Error: tried to erase NULL heap\n");
		return;
	}
	if(freeFn==NULL)
	{
		printf("Error: called eraseHeap with NULL function pointer\n");
		return;
	}
	int i; //remember hp->container[0] is always null
	for(i=1; i<=hp->lastIndex; ++i)
	{
		if(hp->container[i] ==NULL)
		{
			printf("Warning: eraseHeap found NULL data and ignored");
		}
		else
		{
			freeFn(hp->container[i]);
		}
	}

	free(hp->container);
	free(hp);
}

//pick up the higher ranking child if exists. if no child exists, end
void boogieDown(GenericHeap * hp, int i)
{ 
//the code in this function can get factored significantly, but I chose to keep it this way, for clarity of logic
	//the compiler will (hopefully) optimize the code anyway
	 if(hp==NULL)
	 {
	 	printf("Error: attempted to call boogieDown on NULL heap\n");
	 	return;
	 }
	 if(hp->lastIndex < 2*i) //no children
	 {
	 	return; 
	 }

	 if(hp->lastIndex < (2*i) + 1 ) //only left child exists
	 {
	 	if(hp->compareFn(hp->container[2*i], hp->container[i]))
	 	{
	 	void * tmp = hp->container[i];
	 	hp->container[i] = hp->container[2*i];
	 	hp->container[2*i]=tmp;	
	 	}	
	 	//no need for recursive call, why? :)
	 	return;
	 }
	 //both children exist
	 if(hp->compareFn(hp->container[2*i], hp->container[2*i+1])) //left child should come up (potentially)
	 {
	 	if(hp->compareFn(hp->container[2*i], hp->container[i]))
	 	{
	 		void * tmp = hp->container[i];
	 		hp->container[i] = hp->container[2*i];
	 		hp->container[2*i] = tmp; 
	 		boogieDown(hp, 2*i);	
	 	}
	 	
	 		
	 }
	 else //right child should come up (potentially)
	 {
		if(hp->compareFn(hp->container[2*i+1], hp->container[i]))
	 	{
	 		void * tmp = hp->container[i];
	 		hp->container[i] = hp->container[2*i+1];
	 		hp->container[2*i+1] = tmp; 
	 		boogieDown(hp, 2*i+1);	
	 	}

	 }

}

void * getRoot(GenericHeap * hp)
{
	if(hp==NULL) 
	{
		printf("Error: tried to call getRoot on NULL heap");
		return NULL; 
	}

	if(hp->lastIndex==0)
	{
		printf("warning:tried to call getRoot on empty heap, NULL returned");
		return NULL;
	}

	void * output = hp->container[1];
	hp->container[1] = hp->container[hp->lastIndex]; 
	hp->container[hp->lastIndex]=NULL; //this is not necessary really

	hp->lastIndex = hp->lastIndex - 1; 

	if(hp->lastIndex==0)
	{
		return output; 
	}

	boogieDown(hp, 1); //boogie down from the root value; 
	return output;

}











