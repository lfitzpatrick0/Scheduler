#include <iostream>
#include <string>
using namespace std;

struct listNode {
	int arrival;
	int burst;
	string procName;
	struct listNode *next;
};

typedef struct listNode ListNode;
typedef ListNode *ListNodePtr;

void insert( ListNodePtr *sPtr, int burst, int arrival, string name );
void printList( ListNodePtr currentPtr, ListNodePtr *sPtr );
struct listNode* circular( struct listNode* head );
void removeProc(ListNodePtr *sPtr, string procName);

int main()
{
	ListNodePtr startPtr = NULL;
	insert( &startPtr, 8, 0, "P1" );
	insert( &startPtr, 6, 2, "P2" );
	insert( &startPtr, 1, 2, "P3" );
	insert( &startPtr, 9, 1, "P4" );
	insert( &startPtr, 3, 3, "P5" );

	
	// uncomment for circular linked list.
	
	listNode *scheduler = circular( startPtr );
	
	/*
	removeProc(&startPtr, "P3");
	
	printList(startPtr, &startPtr);
	*/

	printList(scheduler, &startPtr);
	return 0;
}

struct listNode* circular( struct listNode* head )
{
	struct listNode* start = head;
	while(head->next != NULL)
		head = head->next;
	head->next = start;
	return start;
}

void insert( ListNodePtr *sPtr, int burst, int arrival, string name )
{
	ListNodePtr newPtr;
	ListNodePtr previousPtr;
	ListNodePtr currentPtr;
		
	newPtr = new ListNode;
	if( newPtr != NULL )
	{
		newPtr->arrival = arrival;
		newPtr->burst = burst;
		newPtr->procName = name;
		newPtr->next = NULL;
		
		previousPtr = NULL;
		currentPtr = *sPtr;
		
		while( currentPtr != NULL && arrival >= currentPtr->arrival )
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->next;
		}
		if(previousPtr == NULL)
		{
			newPtr->next = *sPtr;
			*sPtr = newPtr;
		}
		else
		{
			previousPtr->next = newPtr;
			newPtr->next = currentPtr;
		}
	}
}

void printList( ListNodePtr currentPtr, ListNodePtr *sPtr )
{
	ListNodePtr head = *sPtr;
	int acc = 0;
	int qt = 1;
	while( currentPtr != NULL && currentPtr != currentPtr->next )
	{
		
		if(currentPtr->burst >= qt)
		{
			cout << acc << " " << currentPtr->procName << " " << currentPtr->burst << endl;
			acc += qt;
			//cout << currentPtr->burst << endl;
			currentPtr->burst -= qt;
			
		} else if( currentPtr->burst == 0 ) {
			//cout << " REMOVE" << endl;
			removeProc(&head, currentPtr->procName);
			//cout << acc << " " << currentPtr->procName << " " << currentPtr->burst << endl;
		}
		else
		{
			cout << " IDK" << endl;
		}
		//cout << acc << " " << currentPtr->procName << " " << currentPtr->burst << endl;
		//cout << currentPtr->burst << " ";
		//cout << endl;
		currentPtr = currentPtr->next;
	}
}

void removeProc(ListNodePtr *sPtr, string procName)
{
	ListNodePtr previousPtr;
	ListNodePtr currentPtr;
	ListNodePtr tempPtr;

	if( procName == (*sPtr)->procName )
	{
		tempPtr = *sPtr;
		*sPtr = (*sPtr)->next;
		//free( tempPtr );
	}
	else {
		previousPtr = *sPtr;
		currentPtr = (*sPtr)->next;
		while(currentPtr != NULL && currentPtr->procName != procName)
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->next;
		}
		if( currentPtr != NULL )
		{
			//cout << "removing: " << currentPtr->procName << endl;
			tempPtr = currentPtr;
			previousPtr->next = currentPtr->next;
			free( tempPtr );
		}
	}
}