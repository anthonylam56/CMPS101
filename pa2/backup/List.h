//---------------------------------------------------------------------------------------
//Name  : Anthony Lam
//Course: CMPS101
//
//List.h
//List header obj
//
//---------------------------------------------------------------------------------------


#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_
#include<stdio.h>

//Exported type--------------------------------------------------------------------------
typedef struct ListObj* List;

//Constructors-Destructors---------------------------------------------------------------

//newList()
//Returns reference to new empty list object.
List newList(void);

//freeQueue()
//Frees all heap memory associated with List *pL, and sets *pL to null.
void freeList(List* pL);

//Access functions-----------------------------------------------------------------------

//getLength()
//Returns the length of L.
int length(List L);

//index(List L)
//Returns index of cursor.
int index(List L);

//getFront()
//Returns the value at the front of L.
//Pre: !isEmpty(L)
int front(List L);

//back()
//Returns the value at back of L.
int back(List L);

//get(List L)
//Returns cursor element in List L.
int get(List L);

//equals(List A, List B)
//Returns 1 if and only if the integer sequence of List A and List B are identical.
//Otherwise, if not returns 0.
int equals(List A, List B);

// Manipulation procedures---------------------------------------------------------------

//clear(List L)
//Clears the list L to empty state.
void clear(List L);

//moveFront(List L)
//Moves cursor to front of List L.
void moveFront(List L);

//moveBack(List L)
//Moves cursor to back of list L.
void moveBack(List L);

//movePrev(List L)
//Moves cursor to previous Node of current Node in List L.
void movePrev(List L);

//moveNext(List L)
//Moves cursor to next Node of current Node in list L.
void moveNext(List L);

//prepend(List L, int data)
//Inserts data to the front of the list.
void prepend(List L, int data);

//append(List L, int data)
//Inserts data to the back of the list.
void append(List L, int data);

//insertBefore(List L, int data)
//Inserts element before the cursor element in the list L.
void insertBefore(List L, int data);

//insertAfter(List L, int data)
//Inserts element after the cursor element in the list L.
void insertAfter(List L, int data);

//deleteFront(List L)
//Deletes element at the front of list L.
void deleteFront(List L);

//deleteBack(List L)
//Deletes element at the back of list L.
void deleteBack(List L);

//delete(List L)
//Deletes cursor element in list L.
void delete(List L);

//Other operations-----------------------------------------------------------------------

//printList(FILE* out, List L)
//Prints list L to File out.
void printList(FILE* out, List L);

//copyList(List L)
//Makes a copy of list L.
List copyList(List L);

#endif
