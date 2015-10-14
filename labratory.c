#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GenList.h"
#include "Heap.h"
struct soldier
{
	int id;
	char * name;
	struct weapon * wpn;
};


int SoldierComparison(void * s1, void* s2)
{
	if(s1==NULL || s2==NULL)
	{
		printf("error: called soldier comparison with null soldier\n");
		return 0;
	}
	struct soldier * a = (struct soldier *) s1;
	struct soldier * b = (struct soldier *) s2;
	if(a->id > b->id)
	{
		return 0;
	}
	else 
	{
		return 1;
	}
}

void * stringOnHeap(char * input)
{
	char * output = malloc(strlen(input) +1);
	strcpy(output, input);
	return output;
}



struct weapon
{
	int id;
	char * name;
	int damage;
	int cost;
	int range;

}; 



void soldierDestructor(void * input)
{
	if(input==NULL)
	{
		printf("Error: tried to destroy NULL soldier");
		return;
	}
	//remember to destoy the weapon first!
	struct soldier * soldierToDestroy = (struct soldier *) input;
	struct weapon * weaponToDestroy = soldierToDestroy->wpn;
	char * nameToDestroy = soldierToDestroy->name;
	if(nameToDestroy==NULL)
	{
	printf("Error: Soldier we are about to destroy has NULL for name");
	return;
	}
	free(nameToDestroy);
	//soldier can legitimately be without a weapon, print warning anyway;
	if(weaponToDestroy==NULL)
	{
		printf("Soldier we are about to destroy has NULL for weapon");
	}
	else
	{
		if(weaponToDestroy->name!=NULL) free(weaponToDestroy->name);
		free(weaponToDestroy);
	}

	//now we can free soldier without memory leak:
	free(soldierToDestroy);
}	

struct soldier * createSoldier(char * weaponName, int weaponID, int weaponDamage,
 int weaponCost, int weaponRange, char * soldierName, int soldierID)
{
	struct weapon * newWpn = malloc(sizeof(struct weapon));
 	newWpn->id= weaponID;
 	newWpn->name= stringOnHeap(weaponName);
 	newWpn->damage=weaponDamage;
 	newWpn->cost=weaponCost;
 	newWpn->range=weaponRange; 

	struct soldier * newSoldier = malloc(sizeof(struct soldier));
	newSoldier->id = soldierID;
	newSoldier->name= stringOnHeap(soldierName);
	newSoldier->wpn = newWpn;

	return newSoldier;

}

void printSoldier (void * input)
{

	struct soldier * toPrint = (struct soldier *) input;
	printf("Soldier %d:  %s ", toPrint->id, toPrint->name);
	printf("weapon:%s weaponRange: %d", toPrint->wpn->name, toPrint->wpn->range);
	printf("\n\n");

}

int main(int argc, char **argv)
{
 
 GenericHeap * myHeap = emptyHeap(15, SoldierComparison);



 //list of soldiers!!

 	//struct soldier * kingArthur = createSoldier ( "Excalibur!", 0, 12, 1550,5,"King Arthur",15);
 	struct soldier * RobinHood = createSoldier ( "Longbow", 1, 4, 1200,29,"Robin Hood",24);
 	struct soldier * Saladdin = createSoldier ( "Scimitar", 2, 10, 1150,5,"Saladdin",33);
 	struct soldier * Musashi = createSoldier ( "Katana", 3 , 12, 1550,5,"Miyamoto Musashi",20);
 	struct soldier * Maximus = createSoldier ( "Gladius", 4, 4, 1210, 2,"Maximus",19);
	struct soldier * Napoleon = createSoldier ( "Musket", 5, 3, 3150,44,"Napoleon Bonaparte",50);

 	//pushHeap(myHeap,kingArthur );
 	pushHeap(myHeap,RobinHood);
 	pushHeap(myHeap,Saladdin);
 	pushHeap(myHeap,Musashi );
 	pushHeap(myHeap,Maximus);
 	pushHeap(myHeap,Napoleon);

 	applyToHeap(myHeap, printSoldier);
 	printf("\n\n\n");
 	soldierDestructor(getRoot(myHeap));
 	applyToHeap(myHeap, printSoldier);
 	printf("\n\n\n");
 	soldierDestructor(getRoot(myHeap));
 	soldierDestructor(getRoot(myHeap));
 	applyToHeap(myHeap,printSoldier);
 	eraseHeap(myHeap,soldierDestructor);
/*
	GenericList * soldierList = emptyList(soldierDestructor); 	
	pushBack(soldierList, kingArthur);
	pushFront(soldierList, RobinHood);
	pushBack(soldierList, Saladdin);
	pushFront(soldierList, Musashi);
	pushBack(soldierList, Maximus);
	pushBack(soldierList, Napoleon);

	soldierDestructor(popFront(soldierList));//need to free popped soldiers ourself. 
	
	printf("size of soldier list is %d\n", getListSize(soldierList));
	void (*pointerToPrinter) (void *) = printSoldier;
	applyToList(soldierList,pointerToPrinter);
	deleteList(soldierList);
	//soldierDestructor(kingArthur);
	//soldierDestructor(RobinHood);
	//soldierDestructor(Saladdin);

*/

/*
	list of strings:
	GenericList * myList = emptyList(memoryDeleter);
	//pushBack(myList, vdptr);

	pushBack(myList,param) ;
	pushBack(myList,stringOnHeap("my ")) ;
	pushFront(myList,stringOnHeap("name ")) ;
	pushFront(myList,stringOnHeap("is ")) ;
	pushBack(myList,stringOnHeap("Dan")) ;

	void * gimmie = popFront(myList);
	printf("%s\n", (char *) gimmie);
	free(gimmie);

	deleteList(myList);
*/


	return 0;
}
