#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListEntry.h"
#include "GenList.h"
#include <assert.h>

GenericList * emptyList(void * cln)
{
	GenericList * output = malloc(sizeof(GenericList));

	if(output==NULL) 
	{
		printf("malloc failed in emptyList function");
		return NULL;
	}
	output->size = 0;
	output->head = NULL;
	output->tail = NULL;
	output->cleaner = cln;
	return output;

}

//pushBack
void pushBack(GenericList * lst, void * dt)
{
	if (lst ==NULL)
	{
		printf("error: pushBack(GenericList * lst, void * dt) passed in NULL for lst\n");
		return;
	}
	if(dt==NULL)
	{
		printf("warning: pushBack(GenericList * lst, void * dt) passed in NULL for dt\n");
		printf("this is legal, but not recommended.");
	}

	ListNode * tmp = malloc(sizeof(ListNode));
	if(tmp==NULL)
	{
		printf("error: malloc failed in pushBack\n");
		return;
	}

	tmp->previous = lst->tail; //works wether lst is empty or not
	tmp->next = NULL;
	tmp->data = dt;
	lst->size= lst->size + 1;

	//especial case: empty list: (remember we just increased the size by 1)
	if(lst->size==1)
	{
		assert (lst->head==NULL);
		assert (lst->tail==NULL);
		lst->head=tmp;
	}
	else
	{
		lst->tail->next = tmp;
	}
	
	lst->tail=tmp;
}

//pushFront
void pushFront(GenericList * lst, void * dt)
{
	if (lst==NULL)
	{
		printf("error: pushBack(GenericList * lst, void * dt) passed in NULL for lst\n");
		return;
	}
	if(dt==NULL)
	{
		printf("warning: pushFront(GenericList * lst, void * dt) passed in NULL for dt\n");
		printf("this is legal, but not recommended.");
	}

	ListNode * tmp = malloc(sizeof(ListNode));

	tmp->data = dt;
	tmp->next=lst->head;
	tmp->previous=NULL;
	lst->size = lst->size +1 ;

	if(lst->size ==1)
	{
		lst->tail=tmp;
	}
	else
	{
		lst->head->previous = tmp;
	}
	lst->head=tmp;
}

void applyToList(GenericList *lst, void (* toDo) (void *))
{

	if(lst==NULL) 
	{
		printf("Error: tried to call applyToAll on null list");
		return;
	}
	if(toDo==NULL)
	{
		printf("Error: tried to call applyToAll with null function pointer passed");
		return;
	}

	ListNode* index=lst->head;
	while(index!=NULL)
	{
		//toDo function must be indempotent and not change the values, for example print
		toDo(index->data);
		index=index->next;
	}

}

//popBack:
//after the data pointer is returned to user, the list is no longer responsible for freeing it
void * popBack(GenericList * lst)
{

	if(lst==NULL) 
	{
		printf("error: attempted to popBack on NULL list\n");
		return NULL;
	}
	if(lst->size==0)
	{
		printf("error: attempted to popBack on empty list\n");
		return NULL;
	}

	void * output = lst->tail->data; 
	lst->size = lst->size-1;
	ListNode * toDelete= lst->tail;
	if(lst->size==0)
	{
		lst->head= NULL;
		lst->tail=NULL;
	}
	else
	{
		lst->tail->previous->next=NULL;
		lst->tail= lst->tail->previous; 
	}
	
	free(toDelete);
	return output;
}




//popFront
//returns the data pointer
void * popFront(GenericList * lst)
{
	if(lst==NULL) 
	{
		printf("error: attempted to popFront on NULL list\n");
		return NULL;
	}
	if(lst->size==0)
	{
		printf("error: attempted to popFront on empty list\n");
		return NULL;
	}

	assert(lst->head!=NULL);
	void * output = (lst->head)->data;
	ListNode* toDelete = lst->head; 
	lst->size = lst->size - 1;

	//special case: only 1 item (note we already decremented the size)
	if(lst->size==0)
	{

		lst->head=NULL;
		lst->tail=NULL;
	}
	else
	{
	assert(lst->head->next->previous == lst->head);
	lst->head->next->previous = NULL; 
	lst->head = lst->head->next;

	}

	//more than 1 item:	
	free(toDelete);
	return output;
}



//delete entire list
//must not pass in NULL for lst
int deleteList(GenericList * lst)
{
	if(lst==NULL) 
	{
		printf("Error: passed in NULL for lst in deleteList");
		return 0; //0 indicates failure
	}

	ListNode * index = lst->head;

	while(index!=NULL)
	{
		ListNode * toDelete = index;
			index =index->next;
		if(toDelete->data ==NULL) //this is legal but not recommended
		{}
		else
		{
			//free(toDelete->data);	//free the memory for data on the heap associated to Node Object
			lst->cleaner(toDelete->data);
		}

	free(toDelete); //free the heap allocated memory for the node object itself (3 pointers: data, next previous)
	}

//we have delted all the nodes, but we need to delete the List object itself
	//our list object still has the following:(int size, head ptr, tail ptr) allocated on heap
	free(lst);
return 1;
}


int getListSize(GenericList * lst)
{
	return lst->size;
}

int listIsEmpty(GenericList * lst)
{
	if (lst->size==0) return 1;
	return 0;
}


