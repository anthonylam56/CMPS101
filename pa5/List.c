//---------------------------------------------------------------------------------------
//Name  : Anthony Lam
//Course: CMPS101
//
//List.c
//Implementation file for List ADT
//
//---------------------------------------------------------------------------------------


#include<stdio.h>
#include<stdlib.h>
 
#include"List.h"

//structs--------------------------------------------------------------------------------

//private NodeObj type
typedef struct NodeObj{
	int length;
	struct NodeObj* next;
	struct NodeObj* prev;
	int data;
} NodeObj;

//private Node type
typedef NodeObj* Node;

//private ListObj type
typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int index;
	int length;
} ListObj;

//Constructors-Destructors---------------------------------------------------------------

//newNode()
//Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data){
	Node N = malloc(sizeof(NodeObj));
	N -> data = data;
	N -> next = NULL;
	N -> prev = NULL;
	return (N);
}

//freeNode()
//Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
	if(pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

//newList()
//Returns reference to new empty List object.
List newList(void){
	List L = malloc(sizeof(ListObj));
	L -> front = L -> back = NULL;
	L -> index = -1;
	L -> length = 0;
	return L;
}


//freeList()
//Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List* pL){
	if(pL != NULL && *pL != NULL){
		while(length(*pL) > 0){
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

//Access functions-----------------------------------------------------------------------

//getLength()
//Returns the length of L.
int length(List L){
	if(L == NULL){
		printf("List Error: calling getLength() on NULL List reference/n");
		exit(1);
	}
	return L->length;
}

//index(List L)
//Returns the index of the cursor in list.
int index(List L){
	if(L == NULL){
		printf("List Error: calling index() on NULL List reference.\n");
		exit(1);
	}
	if(length(L) <= 0){
		return -1;
	}
	return L -> index;
}

//front(List L)
//Returns the front element of the list.
int front(List L){
	if(L == NULL){
		printf("List Error: calling front(List L) on NULL list reference.\n");
		exit(1);
	}
	if(length(L) <= 0){
		printf("List Error: calling front(List L) on empty list.\n");
		exit(1);
	}
	return L->front->data;
}

//back(List L)
//Returns the back element of the list.
int back(List L){
	if(L == NULL){
		printf("List Error: calling back(List L) on NULL list reference.\n");
		exit(1);
	}
	if(length(L) <= 0){
		printf("List Error: calling back(List L) on empty list.\n");
		exit(1);
	}
	return L->back->data;
}

//get(List L)
//Returns the cursor element.
int get(List L){
	if(L == NULL){
		printf("List Error: calling get(List L) on a NULL list reference.\n");
		exit(1);
	}
	if(length(L) <= 0){
		printf("List Error: calling get(List L) on a empty list.\n");
		exit(1);
	}
	if( L -> cursor == NULL){
		printf("List Error: calling get(List L) on NULL cursor.\n");
		exit(1);
	}
	return L-> cursor -> data;
}

//equals(List A, List B)
//Returns true if and only if List A and B are the same integer sequence.
//The states of the cursors in the two lists are not used in determining equality.

int equals(List A, List B){
	int eq = 0;
	if(A == NULL|| B == NULL){
		printf("List Error: calling equals(List A, List B) with at least one NULL list reference.\n");
		exit(1);
	}

	eq = (A -> length == B -> length);
	Node M = A -> front;
	Node N = B -> front;
	
	while( eq && N != NULL){
		eq = (N -> data == M -> data);
		N = N -> next;
		M = M -> next;
	}
	return eq;
}

//Manipulation procedures----------------------------------------------------------------

//clear(List L)
//Clears List L to empty state.
void clear(List L){
	if(L == NULL){
		printf("List Error: calling clear(List L) on NULL list reference.\n");
		exit(1);
	}

	while(length(L) > 0){
		deleteFront(L);
	}
	L-> length = 0;
	L-> index = -1;
	L-> front = L-> back = L -> cursor = NULL;
}

//moveFront(List L)
//Moves cursor to the front.
void moveFront(List L){
	if(L == NULL){
		printf("List Error: calling moveFront(List L) on NULL list reference.\n");
		exit(1);
	}
	if(length(L) > 0){
		L -> cursor = L -> front;
		L -> index = 0;
	}
}

//moveBack(List L)
//Moves cursor to the back.
void moveBack(List L){
	if(L == NULL){
		printf("List Error: calling moveBack(List L) on NULL list reference.\n");
		exit(1);
	}
	if(length(L) > 0){
		L -> cursor = L -> back;
		L -> index = (L -> length) - 1;
	}
}

//moveNext(List L)
//Moves cursor to next node of current Node.
void moveNext(List L){
	if(L == NULL){
		printf("List Error: calling moveNext(List L) on NULL list reference.\n");
	}
	if(L -> cursor == L -> back){
		L -> cursor = NULL;
		L -> index = -1;
	}
	else{
		L -> cursor = L -> cursor -> next;
		L -> index++;
	}
}

//movePrev(List L)
//Moves cursor to previous node of current Node.
void movePrev(List L){
	if(L == NULL){
		printf("List Error: calling movePrev(List L) on NULL list reference.\n");
		exit(1);
	}
	if(L -> cursor == L -> front){
		L -> cursor = NULL;
		L -> index = -1;
	}
	else{
		L -> cursor = L -> cursor -> prev;
		L -> index--;
	}
}

//prepend(List L, int data)
//Inserts new element into the list, if not empty, inserts element
//before the front element.
void prepend(List L, int data){
	if(L == NULL){
		printf("List Error: calling prepend(List L, int data) on NULL list reference.\n");
		exit(1);
	}

	

	if(L -> front == NULL){
		Node N = newNode(data);
		L -> front = L -> back = N;
		L -> cursor = L -> front;
	}
	else{
		Node N = newNode(data);
		L -> front -> prev = N;
		N -> next = L -> front;
		L -> front = N;
		L -> index++;
	}
	L -> length++;
}

//append(List L, int data)
//Inserts new element into the list, if not empty, inserts element
//after the back element.
void append(List L, int data){
	if(L == NULL){
		printf("List Error: calling append(ListL, int data) on NULL list reference.\n");
		exit(1);
	}

	if(L -> back == NULL){
		Node N = newNode(data);
		L -> front = L -> back = N;
		L -> cursor = L -> back;
	}
	else{
		Node N = newNode(data);
		L -> back -> next = N;
		N -> prev = L -> back;
		L -> back = N;
		N -> next = NULL;
	}
	L -> length++;
}

//insertBefore(List L, int data)
//Inserts new element before cursor.
void insertBefore(List L, int data){
	if(L == NULL){
		printf("List Error: calling insertBefore(List L, int data) on NULL list reference.\n");
		exit(1);

	}
	if(L -> cursor == NULL){
		printf("List Error: calling insertBefore(List L, int data) with NULL cursor.\n");
		exit(1);
	}
	
	if(L -> length <= 0){
		prepend(L, data);
	}
	if(L -> cursor == L -> front){
		prepend(L, data);
	}
	else{
		Node N = newNode(data);
		N -> next = L -> cursor;
		N -> prev = L -> cursor -> prev;
		L -> cursor -> prev -> next = N;
		L -> cursor -> prev = N;
		L -> index++;
		L -> length++;
	}
}

//insertAfter(List L, int data)
//Inserts new element after cursor.
void insertAfter(List L, int data){
	if(L == NULL){
		printf("List Error: calling insertAfter(List L, int data) on NULL list reference.\n");
		exit(1);
	}
	if(L -> cursor == NULL){
		printf("List Error: calling insertAfter(List L, int data) with NULL cursor.\n");
		exit(1);
	}

	if(L -> cursor == L -> back){
		append(L, data);
	}
	else{
		Node N = newNode(data);
		L -> cursor -> next -> prev = N;
		N -> prev = L -> cursor;
		N -> next = L -> cursor -> next;
		L -> cursor -> next = N;
		L -> length++;
	}
}

//deleteFront(List L)
//Deletes element at the front of the list L.
void deleteFront(List L){
	if(L == NULL){
		printf("List Error: calling deleteFront(List L) on NULL list reference.\n");
		exit(1);
	}
	if(L -> length <= 0){
		printf("List Error: calling deleteFront(List L) on empty list.\n");
		exit(1);
	}
	else{
			if(L-> length == 1){
				Node N = L -> front;
				L -> front = L -> back = NULL;
				freeNode(&N);
				L -> index = -1;
				L -> cursor = NULL;
			}
			else{
				Node N = L -> front;
				L -> front = L -> front -> next;
				L -> front -> prev = NULL;
				if(L -> cursor != NULL){
					L -> index--;
				}
				freeNode(&N);
			}
			//freeNode(&N);
			L -> length--;
	}
	
}

//deleteBack(List L)
//Delete element at the back of the list L.
void deleteBack(List L){
	if(L ==NULL){
		printf("List Error: calling deleteFront(List L) on NULL list reference.\n");
		exit(1);
	}
	if(L -> length <= 0){
		printf("List Error: calling deleteFront(List L) on empty list.\n");
		exit(1);
	}
	else{
			if(L -> length == 1){
				Node N = L -> back;
				L -> front = L -> back = NULL;
				freeNode(&N);
				L -> index = -1;
				L -> cursor = NULL;
				
			}
			else{
				Node N = L -> back;
				L -> back = L -> back -> prev;
				L -> back -> next = NULL;
				if(L -> index == L -> length -1){
					L -> index = -1;
				}
				freeNode(&N);
			}
			//freeNode(&N);
			L -> length--;
		}		
}



//delete(List L)
//Deletes element at cursor element.
void delete(List L){
	if(L == NULL){
		printf("List Error: calling delete(List L) on NULL list reference.\n");
		exit(1);
	}
	if(L -> length <= 0){
		printf("List Error: calling delete(List L) on empty list.\n");
		exit(1);
	}
	if(L -> cursor == L -> front){
		deleteFront(L);
	}
	else if(L -> cursor == L -> back){
		deleteBack(L);
	}
	else{
		Node N = L -> cursor;
		L -> cursor -> prev -> next = L -> cursor -> next;
		L -> cursor -> next -> prev = L -> cursor -> prev;
		L -> cursor = NULL;
		freeNode(&N);
		L -> length--;
		
	}
	
	L -> index =-1;	
}



//Other operations-----------------------------------------------------------------------


//printList(FILE* out, List L)
//Returns List as a string representation.
void printList(FILE* out, List L){
	if(L == NULL){
		printf("List Error: calling printList(FILE* out, List L) on NULL list reference.\n");
		exit(1);
	}
	Node N = L -> front;
	while(N != NULL){
		fprintf(out, "%d ", N -> data);
		N = N -> next;
	}
	printf("\n");
}

//List copyList(List L)
//Makes a new list and copies L to the new list.
List copyList(List L){
	Node N = L -> front;
	List M = newList();
	if(L -> length > 0){
		while(N != NULL){
			append(M, N -> data);
			N = N -> next;
		}
	}
	M -> cursor = NULL;
	M -> index = -1;
	return M;
}



/* deleteback
Node N = L -> back;
		if( L -> length == 1){
			L -> front = L -> back = NULL;
			L -> index = -1;
			L -> cursor = NULL;
		}
		else{
			if(L -> cursor == L -> back){
				L -> index = -1;
			}

			L -> back = L -> back -> prev;
			L -> back -> next = NULL;


deletefront
Node N = L -> front;
		if(L -> length == 1){
			L -> front = L -> back = NULL;
			L -> index = -1;
			L -> cursor = NULL;
		}
		else{
			if(L -> cursor != NULL){
				L -> index--;
			}

			L -> front = L -> front -> next;
			L -> front -> prev = NULL;
*/