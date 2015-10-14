#include <stdio.h>
#include <stdlib.h>
#include "HeapNode.h"



typedef struct _heap
{
void ** container;
int maxSize;
int lastIndex;
int (* compareFn) (void*,void*);
} GenericHeap;


GenericHeap * emptyHeap(int maxSize , int (*cmpFn) (void*,void*));

//adds value to heap, heap will readjust as necessary
void pushHeap( GenericHeap* hp, void* value);
//applyToHeap will iterate through the heap and apply the function to all. 
void applyToHeap(GenericHeap* hp, void (*fnPtr)(void * ));
//eraseHeap will free memory of the heap along with any input that the heap holds. 
//totice that "container" is heap allocated.
//eraseHeap takes in a function pointer that shold be a function that frees memory for elements in the heap
void eraseHeap(GenericHeap * hp, void (*freeFn) (void*));

//returns the data for the root, which either has the highest or lowest value, depending on the comparison fucntion defined
//after root is returned, user is responsible to free its memory. 
void * getRoot(GenericHeap * hp);