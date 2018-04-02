#include <iostream>
using namespace std;

struct listNode {
	int data;
	struct listNode *next;
};

typedef struct listNode ListNode;
typedef ListNode *ListNodePtr;

void insert( ListNodePtr *sPtr, int data );
void printList( ListNodePtr currentPtr );
struct listNode* circular( struct listNode* head );

int main()
{
	ListNodePtr startPtr = NULL;
	insert( &startPtr, 1 );
	insert( &startPtr, 2 );
	insert( &startPtr, 4 );
	insert( &startPtr, 3 );
	insert( &startPtr, 4 );
	
	listNode *scheduler = circular( startPtr );
	
	printList( scheduler );
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

void insert( ListNodePtr *sPtr, int value )
{
	ListNodePtr newPtr;
	ListNodePtr previousPtr;
	ListNodePtr currentPtr;
		
	newPtr = new ListNode;
	if( newPtr != NULL )
	{
		newPtr->data = value;
		newPtr->next = NULL;
		
		previousPtr = NULL;
		currentPtr = *sPtr;
		
		while( currentPtr != NULL && value > currentPtr->data )
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

//this will loop infinitely
//add a loop counter
void printList( ListNodePtr currentPtr )
{
	while( currentPtr != NULL )
	{
		cout << currentPtr->data << endl;
		currentPtr = currentPtr->next;
	}
}
