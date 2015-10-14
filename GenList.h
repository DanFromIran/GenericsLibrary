//	         documentation for generic lists: 
//		This file defines a doubly linked list data structure
//		any data type may be added to the list 
//		it is required that void* data that is being added to the list is already allocated on the heap 
//		and only the pointer to the data is passed in one of the append functions
//		However, the delete functions will free the memory for the data 
//		
//
//
//
//

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListEntry.h"

typedef void (* destructorPtr) (void * );
typedef struct _genericList 
{
	int size;
	ListNode * head;
	ListNode * tail; 
	destructorPtr cleaner;

} GenericList;


//the following creates an empty list
// DO NOT free this memory, 
// use deleteList instead. 
//returns NULL if unsuccessful, 
//returns pointer to an empty list if successful
GenericList * emptyList(void * cleaner);

//pushBack
//will print a warning if null list is passed in and return
//will push the value of data at the back of the list
void pushBack(GenericList * lst, void * data);

//pushFront
void pushFront(GenericList * lst, void * data);

//popBack:
//after the data pointer is returned to user, the list is no longer responsible for freeing it
//returns NULL if list is empty
void * popBack(GenericList * lst);

//popFront
void * popFront(GenericList * lst);

//delete entire list, returns 1 on success, 0 on false
//print wraning if passed in lst is nuLL
int deleteList(GenericList * lst);

//will print a warning if null list is passed and return -1
int getListSize(GenericList * lst);

//will print a warning if lst passed in is NULL, 
//return 1 if list is Empty, 0 otherwise
int listIsEmpty(GenericList * lst);

//will take in a generic list and a function pointer as input
//applies the function to every data in the list
void applyToList(GenericList *lst, void (* toDo) (void *));