#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _listNode
{
	void * data;
	struct _listNode * next;
	struct _listNode * previous;	
	
} ListNode;  //3 pointers 8 bytes each = 24 bytes
//total size of ListEntry:



