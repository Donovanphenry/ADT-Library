/****************************************************************************************
* Name: Donovan Henry
* CruzID: dphenry
* Assignment: PA7
* File: List.c
*****************************************************************************************/

#include "List.h"

// -------- Private Method Signatures -----------
int isEmpty(List L);

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj
{
    LIST_ELEMENT data;
    struct NodeObj *next;
    struct NodeObj *prev;
} NodeObj;

// private Node type
typedef NodeObj *Node;

typedef struct ListObj
{
    int count;
    int index;
    Node head;
    Node cursor;
    Node tail;
} ListObj;

// ------- Node methods -----------

// Creates new node with the node's next &
// previous pointers being set to NULL. The data
// passed into the constructor is assigned to the
// node's data value. A new node object is returned.
// No preconditions.
Node newNode(LIST_ELEMENT data)
{
    Node node = malloc(sizeof(NodeObj));
    node->next = NULL;
    node->prev = NULL;
    node->data = data;

    return (node);
}

// Frees the memory that *pN points to.
// Pre: pN != NULL && *pN != NULL.
void freeNode(Node *pN)
{
    if (pN == NULL || *pN == NULL)
    {
        return;
    }

    (*pN)->prev = NULL;
    (*pN)->next = NULL;
    free(*pN);
    *pN = NULL;
}

// Constructs a new list object and returns it.
List newList()
{
    List list = (List)malloc(sizeof(ListObj));
    list->head = NULL;
    list->cursor = NULL;
    list->tail = NULL;
    list->count = 0;
    list->index = -1;

    return (list);
}

// frees the list held by the *pL. pL and
// *pL must both be non-NULL.
void freeList(List *pL)
{
    if (pL != NULL && *pL != NULL)
    {
        while (isEmpty(*pL) == 0)
        {
            deleteFront(*pL);
        }

        (*pL)->head = NULL;
        (*pL)->cursor = NULL;
        (*pL)->tail = NULL;
        free(*pL);
        *pL = NULL;
    }
}

// ------- Access functions -------
// Returns the number of elements in L.
int length(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    return L->count;
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    return L->index;
}

LIST_ELEMENT front(List L) // Returns front element of L. Pre: length()>0
{
    if (L == NULL)
    {
        printf("List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) == 0)
    {
        printf("List Error: calling back() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    return L->head->data;
}
LIST_ELEMENT back(List L) // Returns back element of L. Pre: length()>0
{
    if (L == NULL)
    {
        printf("List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) == 0)
    {
        printf("List Error: calling back() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    return L->tail->data;
}

LIST_ELEMENT get(List L) // Returns cursor element of L. Pre: length()>0, index()>=0
{
    if (L == NULL)
    {
        printf("List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) == 0)
    {
        printf("List Error: calling get() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    if (index(L) == -1)
    {
        printf("List Error: calling get() on List reference with NULL cursor\n");
        exit(EXIT_FAILURE);
    }

    return L->cursor->data;
}

// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
int listEquals(List A, List B)
{
    if (length(A) != length(B))
    {
        return 0;
    }

    Node curr_A = A->head;
    Node curr_B = B->head;

    while (curr_A != NULL)
    {
        if (curr_A->data != curr_B->data)
        {
            return 0;
        }

        curr_A = curr_A->next;
        curr_B = curr_B->next;
    }

    return 1;
}

// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling getFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    while (isEmpty(L) == 0)
    {
        deleteFront(L);
    }

    L->index = -1;
}

// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, LIST_ELEMENT x)
{
    if (L == NULL)
    {
        printf("List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(L))
    {
        printf("List Error: calling set() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    if (index(L) == -1)
    {
        printf("List Error: calling set() when index == -1\n");
        exit(EXIT_FAILURE);
    }

    L->cursor->data = x;
}

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(L))
    {
        printf("List Error: calling moveFront() on empty List reference");
        exit(EXIT_FAILURE);
    }

    L->cursor = L->head;
    L->index = 0;
}

void moveBack(List L) // If L is non-empty, sets cursor under the back element, otherwise does nothing.
{
    if (L == NULL)
    {
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(L))
    {
        printf("List Error: calling moveBack() on empty List reference");
        exit(EXIT_FAILURE);
    }

    L->cursor = L->tail;
    L->index = L->count - 1;
}

// If cursor is defined and not at front, move cursor one step toward the front of L;
// if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(L) == 1)
    {
        printf("List Error: calling movePrev() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == NULL)
        return;

    L->cursor = L->cursor->prev;
    L->index--;
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(L) == 1)
    {
        printf("List Error: calling moveNext() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == NULL)
    {
        return;
    }

    L->cursor = L->cursor->next;
    L->index = L->cursor == NULL ? -1 : L->index + 1;
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, LIST_ELEMENT x)
{
    if (L == NULL)
    {
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    Node newHead = newNode(x);
    newHead->next = L->head;
    newHead->prev = NULL;

    if (index(L) != -1)
    {
        L->index++;
    }

    if (isEmpty(L) == 1)
    {
        L->tail = newHead;
    }
    else
    {
        L->head->prev = newHead;
    }

    L->head = newHead;
    L->count++;
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, LIST_ELEMENT x)
{
    if (L == NULL)
    {
        printf("List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    Node newTail = newNode(x);
    newTail->prev = L->tail;
    newTail->next = NULL;

    if (isEmpty(L) == 1)
    {
        L->head = newTail;
    }
    else
    {
        L->tail->next = newTail;
    }

    L->tail = newTail;
    L->count++;
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, LIST_ELEMENT x)
{
    if (L == NULL)
    {
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(L) == 1)
    {
        printf("List Error: calling insertBefore() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    if (index(L) == -1)
    {
        printf("List Error: calling insertBefore() on List reference with NULL cursor\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == L->head)
    {
        prepend(L, x);
        return;
    }

    Node node = newNode(x);
    node->next = L->cursor;
    node->prev = L->cursor->prev;

    L->cursor->prev->next = node;
    L->cursor->prev = node;
    L->count++;
    L->index++;
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, LIST_ELEMENT x)
{
    if (L == NULL)
    {
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(L) == 1)
    {
        printf("List Error: calling insertAfter() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    if (index(L) == -1)
    {
        printf("List Error: calling insertAfter() on List reference with NULL cursor\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == L->tail)
    {
        append(L, x);
        return;
    }

    Node node = newNode(x);
    node->prev = L->cursor;
    node->next = L->cursor->next;

    L->cursor->next->prev = node;
    L->cursor->next = node;
    L->count++;
}

// Delete the front element. Pre: length()>0
void deleteFront(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) == 0)
    {
        printf("List Error: calling deleteFront() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor != NULL)
    {
        L->index--;
    }

    if (L->head == L->cursor)
    {
        L->cursor = NULL;
        L->index = -1;
    }

    if (L->head == L->tail)
    {
        L->tail = NULL;
    }

    Node kill = L->head;
    L->head = L->head->next;
    if (L->head != NULL)
    {
        L->head->prev = NULL;
    }
    freeNode(&kill);
    L->count--;
}

// Delete the back element. Pre: length()>0
void deleteBack(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(L) == 1)
    {
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->tail == L->cursor)
    {
        L->cursor = NULL;
        L->index = -1;
    }

    if (L->tail == L->head)
    {
        L->head = NULL;
    }

    Node kill = L->tail;
    L->tail = L->tail->prev;
    if (L->tail != NULL)
    {
        L->tail->next = NULL;
    }
    freeNode(&kill);
    L->count--;
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete (List L)
{
    if (L == NULL)
    {
        printf("List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(L) == 1)
    {
        printf("List Error: calling delete() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    if (index(L) == -1)
    {
        printf("List Error: calling delete() on List reference with NULL cursor\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor->prev == NULL)
    {
        // implicitly means that the cursor is the head
        deleteFront(L);
        return;
    }
    else if (L->cursor->next == NULL)
    {
        // implicitly means that cursor is the tail
        deleteBack(L);
        return;
    }
    else
    {
        // From the original if's, we know that there must
        // exist a previous and next node for the cursor
        Node kill = L->cursor->prev;
        kill->next = L->cursor->next;
        L->cursor->next->prev = kill;
        kill = L->cursor;
        freeNode(&kill);
    }

    L->cursor = NULL;
    L->index = -1;
    L->count--;
}

// Other operations -----------------------------------------------------------

// Returns an integer mapping to a boolean value where
// a value of 1 represents true and a 0 represents false.
// Functions checks to see if a list is empty, ie has no
// nodes, and if it does, it returns 1, ie the statement
// that the list is empty is true. If the list is not empty,
// then a 0 is returned representing that the propositon "the list
// is empty" is false. I define a NULL list as empty, but this is
// convention. You could justifiably exit with an error code if you like.
int isEmpty(List l)
{
    if (l == NULL || l->count == 0)
    {
        return 1;
    }

    return 0;
}

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
void printList(FILE *out, List L)
{
    if (out == NULL)
    {
        printf("ERROR: File open unsuccessful.");
        exit(EXIT_FAILURE);
    }
    Node curr = L->head;

    while (curr != NULL)
    {
        fprintf(out, "%ld ", curr->data);
        curr = curr->next;
    }
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L)
{
    List list = newList();

    Node curr = L->head;

    while (curr != NULL)
    {
        append(list, curr->data);
        curr = curr->next;
    }

    list->cursor = NULL;
    list->index = -1;

    return list;
}

// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged. Pre: exit if A or B
// are NULL
List concatList(List A, List B)
{
    if (A == NULL || B == NULL)
    {
        printf("Error: Attempting to concatenate with a NULL list. Exiting...");
        exit(EXIT_FAILURE);
    }
    List list = newList();

    Node curr = A->head;

    while (curr != NULL)
    {
        append(list, curr->data);
        curr = curr->next;
    }

    curr = B->head;

    while (curr != NULL)
    {
        append(list, curr->data);
        curr = curr->next;
    }

    return list;
}
