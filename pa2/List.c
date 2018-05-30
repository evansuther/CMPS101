/* Evan Suther
 * Cruzid: esuther
 * Assignment: PA2
 * Component: List.c
 * Function: Doubly linked list with front/back references and a cursor
 * defines List adt operations and uses private Nodes to accomplish list
 */
//List.c
//stlib for EXIT_FAILURE
#include <stdlib.h>
//stdio to print to file
#include<stdio.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
	int data;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;
// private Node type
typedef struct NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
	Node cursor;
   int length;
	int iCursor;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// private newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
	N->prev = NULL;
   return(N);
}

// private freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
	return;
}
// newList()
// Creates a new empty list. returns address of list
List newList(void){
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = L->cursor = NULL;
	L->length = L->iCursor = 0;
	return(L);
}
// freeList()
// Must be passed an address to a list reference so reference can be set to NULL
// Repeatedly calls deleteFront to free the list node by node then frees List reference
void freeList(List* pL){
	if(pL!=NULL && *pL!=NULL) { 
      while( length(*pL) > 0 ) { 
         deleteFront(*pL); 
      }
      free(*pL);
      *pL = NULL;
   }
	return;
}
// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in this List.
int length(List L){
	if (L != NULL){
		return(L->length);
	}
	else{return (0);}
}
// index()
// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1.
int index(List L){
	if ((L != NULL) && (L->cursor != NULL)){
		return(L-> iCursor);
	}
	else{
		return(-1);
	}
}
// front()
// Returns front element. Pre: length()>0
int front(List L){
	if (L == NULL){
		fprintf(stderr, "List Error: front(L) called on NULL list reference");
		exit(EXIT_FAILURE);
	}
	if (!(L->length > 0)){
		fprintf(stderr, "List Error: front(L) called on empty list");
		exit(EXIT_FAILURE);
	}
	return (L->front->data);
}
// back()
// Returns back element. Pre: length()>0
int back(List L){
	if (L == NULL){
		fprintf(stderr, "List Error: back(L) called on NULL list reference");
		exit(EXIT_FAILURE);
	}
	if (!(L->length > 0)){
		fprintf(stderr, "List Error: back(L) called on empty list");
		exit(EXIT_FAILURE);
	}
	return (L->back->data);
}
// get()
// Returns cursor element. Pre: length()>0, index()>=0
int get(List L){
	if (L == NULL){
		fprintf(stderr, "List Error: get(L) called on NULL list reference");
		exit(EXIT_FAILURE);
	}
	if (!(L->length > 0)){
		fprintf(stderr, "List Error: get(L) called on empty list");
		exit(EXIT_FAILURE);
	}
	if (!(L->iCursor >= 0)){
		fprintf(stderr, "List Error: get(L) called on undefined cursor");
		exit(EXIT_FAILURE);
	}
	return (L->cursor->data);
}

// equals()
// Returns true if and only if this List and L are the same
// integer sequence. The states of the cursors in the two Lists
// are not used in determining equality.
int equals(List A, List B){
	if (A == NULL || B == NULL){
		fprintf(stderr, "List Error: equals(L) called on NULL list reference(s)");
		exit(EXIT_FAILURE);
	}
	int eq = 0;
	if( A==NULL || B==NULL ){
		return eq;
	}
	// uses two dummy nodes
	Node N, M;
	N = M = NULL;
	eq = (A->length == B->length);
	// dummy nodes pointed at fronts
	if (eq){
		N = A->front;
		M = B->front;
	}
	// nodes traverse list until eq evaluates false or a list's end is reached
	while(eq && (N != NULL) && (M != NULL)){
		eq = (N->data == M->data);
		N = N->next;
      M = M->next;
	}
	return (eq);
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets this List to its original empty state.
void clear(List L){
	if(L!=NULL) { 
      while( length(L) > 0 ) { 
         deleteFront(L); 
      }
   }
	return;
}
// moveFront()
// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
	if ((L != NULL) && (L->front != NULL)){
		L->cursor = L->front;
		L->iCursor = 0;
	}
	return;
}

// moveBack()
// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
	if ((L != NULL) && (L->back != NULL)){
		L->cursor = L->back;
		L->iCursor = length(L)-1;
	}
	return;
}
// movePrev()
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L){
	if ((L != NULL) && (L->cursor != NULL)){
		if (L->cursor != L->front){
			L->cursor = L->cursor->prev;
			L->iCursor--;
		}
		// make cursor undefined if at front
		else{
			L->cursor = NULL;
			L->iCursor = -1;
		}
	}
	return;
}
// moveNext()
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L){
	if ((L != NULL) && (L->cursor != NULL)){
		if (L->cursor != L->back){
			L->cursor = L->cursor->next;
			L->iCursor++;
		}
		// make cursor undefined if at back
		else{
			L->cursor = NULL;
			L->iCursor = -1;
		}
	}
	return;
}
// prepend()
// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data){
	if (L == NULL){
		fprintf(stderr, "List Error: prepend(L, data) called on NULL list reference");
		exit(EXIT_FAILURE);
	}
	Node N = newNode(data);
	// empty list case
	if (L->length == 0){
		L->front = L->back = N;
		L->length++;
	}
	// non-empty list case
	else{
		L->front->prev = N;
		N->next = L->front;
		L->front = N;
		L->length++;
		// cursor is defined
		if (L->cursor != NULL){
			L->iCursor++;
		}
	}
	return;
}

// append()
// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data){
	if (L == NULL){
		fprintf(stderr, "List Error: append(L, data) called on NULL list reference");
		exit(EXIT_FAILURE);
	}
	Node N = newNode(data);
	// empty list case
	if (L->length == 0){
		L->front = L->back = N;
		L->length++;
	}
	// non-empty list case
	else{
		L->back->next = N;
		N->prev = L->back;
		L->back = N;
		L->length++;
	}
	return;
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){
	if (L == NULL){
		fprintf(stderr, "List Error: insertBefore(L, data) called on NULL list reference");
		exit(EXIT_FAILURE);
	}
	if (!(L->length > 0)){
		fprintf(stderr, "List Error: insertBefore(L, data) called on empty list");
		exit(EXIT_FAILURE);
	}
	if (!(L->iCursor >= 0)){
		fprintf(stderr, "List Error: insertBefore(L, data) called on undefined cursor");
		exit(EXIT_FAILURE);
	}
	// if cursor is the front, let prepend handle
	if (L->cursor->prev == NULL){
		prepend(L, data);
	}
	else{
		Node N = newNode(data);
		// handle 4 pointers to insert
		N->prev = L->cursor->prev;
		N->next = L->cursor;
		L->cursor->prev = N;
		N->prev->next = N;
		L->length++;
		L->iCursor++;
	}
	return;
}
// insertAfter()
// Inserts new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
	if (L == NULL){
		fprintf(stderr, "List Error: insertAfter(L, data) called on NULL list reference");
		exit(EXIT_FAILURE);
	}
	if (!(L->length > 0)){
		fprintf(stderr, "List Error: insertAfter(L, data) called on empty list");
		exit(EXIT_FAILURE);
	}
	if (!(L->iCursor >= 0)){
		fprintf(stderr, "List Error: insertAfter(L, data) called on undefined cursor");
		exit(EXIT_FAILURE);
	}
	// if the cursor is at the end, append can handle it
	if (L->cursor->next == NULL){
		append(L, data);
	}
	else{
		Node N = newNode(data);
		// handle 4 pointers to insert
		N->next = L->cursor->next;
		N->prev = L->cursor;
		L->cursor->next = N;
		N->next->prev = N;
		L->length++;
	}
	return;
}

// deleteFront()
// Deletes the front element. Pre: length()>0
void deleteFront(List L){
	if (L == NULL){
		fprintf(stderr, "List Error: deleteFront(L) called on NULL list reference");
		exit(EXIT_FAILURE);
	}
	if (!(L->length > 0)){
		fprintf(stderr, "List Error: deleteFront(L) called on empty list");
		exit(EXIT_FAILURE);
	}
	Node N = NULL;
	// special case where cursor is on the front, set to null and reset index
	if (L->cursor == L->front){
		L->cursor = NULL;
		L->iCursor = -1;
	}
	N = L->front;
	// 2 different things to do depending on list length
	if (L->length > 1){
		L->front = L->front->next;
		L->front->prev = NULL;
	}
	else{
		L->front = L->back = NULL;
	}
	// if the cursor was defined, index should be decremented
	if(L->cursor != NULL){
		L->iCursor--;
	}
	L->length--;
	freeNode(&N);
}

// deleteBack()
// Deletes the back element. Pre: length()>0
void deleteBack(List L){
	if (L == NULL){
		fprintf(stderr, "List Error: deleteBack(L) called on NULL list reference");
		exit(EXIT_FAILURE);
	}
	if (!(L->length > 0)){
		fprintf(stderr, "List Error: deleteBack(L) called on empty list");
		exit(EXIT_FAILURE);
	}
	Node N = NULL;
	// special case where cursor is on the back, set to null and reset index
	if (L->cursor == L->back){
		L->cursor = NULL;
		L->iCursor = -1;
	}
	N = L->back;
	// 2 different things to do depending on list length
	if (L->length > 1){
		L->back = L->back->prev;
		L->back->next = NULL;
	}
	else{
		L->front = L->back = NULL;
	}
	L->length--;
	freeNode(&N);
}

// delete()
// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
	if (L == NULL){
		fprintf(stderr, "List Error: delete(L) called on NULL list reference");
		exit(EXIT_FAILURE);
	}
   if (!(L->length > 0)) {
      fprintf(stderr, "List Error: delete(L) called on empty list");
      exit(EXIT_FAILURE);
   }
   if (!(L->iCursor >= 0)) {
      fprintf(stderr, "List Error: delete(L) called on undefined cursor");
      exit(EXIT_FAILURE);
   }
	// let other functions handle the special cases
	if (L->cursor == L->front){
		deleteFront(L);
	}
	else if (L->cursor == L->back){
		deleteBack(L);
	}
	else{
		Node N = L->cursor;
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		L->cursor = NULL;
		L->iCursor = -1;
		L->length--;
		freeNode(&N);
	}
	return;
}
// Other operations -----------------------------------------------------------
// printList()
// Overrides Object's toString method. Returns a String
// representation of this List consisting of a space
// separated sequence of integers, with front on left.
void printList(FILE* out, List L){
	if (L == NULL){
		fprintf(stderr, "List Error: printList(out, L) called on NULL list reference");
		exit(EXIT_FAILURE);
	}
	if (out == NULL){
		fprintf(stderr, "List Error: printList(out, L) called on NULL file reference");
		exit(EXIT_FAILURE);
	}
	// use dummy node to loop through the list and print the data in the nodes
	Node N = NULL;
	for(N = L->front; N != NULL; N = N->next){
		fprintf(out, "%d%s", N->data, N->next!=null? " ": "");
	}
	//fprintf(out, "\n");
	return;
}
// copyList()
// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L){
	if (L == NULL){
		fprintf(stderr, "List Error: copy(L) called on NULL list reference");
		exit(EXIT_FAILURE);
	}
	Node temp = L->front;
	List cpy = newList();
	while(temp != NULL){
		append(cpy, temp->data);
		temp = temp->next;
	}
	return(cpy);
}
// *** OPTIONAL ***
// List concatList(A, B)
// Returns a new List which is the concatenation of
// A list followed by B. The cursor in the new List
// is undefined, regardless of the states of the cursors
// in A List and B. The states of A List and B are
// unchanged.
List concatList(List A, List B){
	if (A == NULL || B == NULL){
		fprintf(stderr, "List Error: concatList(L) called on NULL list reference(s)");
		exit(EXIT_FAILURE);
	}
	List both = copyList(A);
	Node temp = B->front;
	while (temp != NULL){
		append(both, temp->data);
		temp = temp->next;
	}
	return (both);
}