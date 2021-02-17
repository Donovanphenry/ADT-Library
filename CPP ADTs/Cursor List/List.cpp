/* ***************************************************************************************
* Name: Donovan Henry
* CruzID: dphenry
* Assignment: PA4
* File: List.cpp
**************************************************************************************** */

#include "List.h"
#include <stdio.h>

// using namespace std;
using std::cout;
using std::ostream;
using std::string;

// Class Constructors & Destructors ----------------------------------------

List::Node::Node(int x)
{
    this->data = x;
    this->prev = nullptr;
    this->next = nullptr;
}

// Creates new List in the empty state.
List::List()
{
    Node *sentinalFront = new Node(SENTINAL_VALUE);
    Node *sentinalBack = new Node(SENTINAL_VALUE);
    this->frontDummy = sentinalFront;
    this->backDummy = sentinalBack;
    this->frontDummy->next = this->backDummy;
    this->frontDummy->prev = nullptr;
    this->backDummy->prev = this->frontDummy;
    this->backDummy->next = nullptr;

    this->beforeCursor = this->frontDummy;
    this->afterCursor = this->backDummy;

    this->pos_cursor = 0;
    this->num_elements = 0;
}

// Copy constructor.
List::List(const List &L)
{
    Node *sentinalFront = new Node(SENTINAL_VALUE);
    Node *sentinalBack = new Node(SENTINAL_VALUE);
    this->frontDummy = sentinalFront;
    this->backDummy = sentinalBack;
    this->frontDummy->next = this->backDummy;
    this->frontDummy->prev = nullptr;
    this->backDummy->prev = this->frontDummy;
    this->backDummy->next = nullptr;

    this->beforeCursor = this->frontDummy;
    this->afterCursor = this->backDummy;
    this->num_elements = 0;
    this->pos_cursor = 0;

    for (Node *currL = L.frontDummy->next; currL != L.backDummy; currL = currL->next)
        this->insertBefore(currL->data);
}

// Destructor
List::~List()
{
    clear();
    delete this->frontDummy;
    delete this->backDummy;
}

// Access functions --------------------------------------------------------

// isEmpty()
// Returns true if this List is empty, false otherwise.
bool List::isEmpty()
{
    return this->num_elements == 0;
}

// size()
// Returns the size of this List.
int List::size()
{
    return this->num_elements;
}

// position()
// Returns the position of the cursor in this List. The value returned
// will be in the range 0 to size().
int List::position()
{
    return this->pos_cursor;
}

// Manipulation procedures -------------------------------------------------

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront()
{
    if (this->isEmpty() == false)
    {
        this->beforeCursor = this->frontDummy;
        this->afterCursor = this->beforeCursor->next;
        this->pos_cursor = 0;
    }
}

// moveBack()
// Moves cursor to position size() in this List.
void List::moveBack()
{
    if (this->isEmpty() == false)
    {
        this->afterCursor = this->backDummy;
        this->beforeCursor = this->afterCursor->prev;
        this->pos_cursor = num_elements;
    }
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<size()
int List::peekNext()
{
    if (this->pos_cursor >= num_elements)
    {
        cout << "Error: Called peekNext when cursor is at back of list. Exiting...";
        exit(EXIT_FAILURE);
    }

    return this->afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
int List::peekPrev()
{
    if (this->pos_cursor <= 0)
    {
        cout << "Error: Called peekNext when cursor is at back of list. Exiting...";
        exit(EXIT_FAILURE);
    }

    return this->beforeCursor->data;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<size()
int List::moveNext()
{
    if (pos_cursor >= num_elements)
    {
        cout << "Error: Called moveNext when cursor is at back of list. Exiting...";
        exit(EXIT_FAILURE);
    }

    this->afterCursor = this->afterCursor->next;
    this->beforeCursor = this->afterCursor->prev;

    pos_cursor++;
    return this->beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
int List::movePrev()
{
    if (pos_cursor <= 0)
    {
        cout << "Error: Called movePrev when cursor is at front of list. Exiting...";
        exit(EXIT_FAILURE);
    }

    this->beforeCursor = this->beforeCursor->prev;
    this->afterCursor = this->beforeCursor->next;

    pos_cursor--;
    return this->afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(int x)
{
    Node *inserted = new Node(x);
    this->beforeCursor->next = inserted;
    inserted->next = this->afterCursor;
    inserted->prev = this->afterCursor->prev;
    this->afterCursor->prev = inserted;
    this->afterCursor = inserted;

    this->num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(int x)
{
    Node *inserted = new Node(x);
    this->afterCursor->prev = inserted;
    inserted->prev = this->beforeCursor;
    inserted->next = this->beforeCursor->next;
    this->beforeCursor->next = inserted;
    this->beforeCursor = inserted;

    this->num_elements++;
    this->pos_cursor++;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<size()
void List::eraseAfter()
{
    if (pos_cursor >= num_elements)
    {
        cout << "Error: Called eraseAfter when cursor is at back of list. Exiting...";
        exit(EXIT_FAILURE);
    }

    Node *prev = this->afterCursor->prev;
    Node *next = this->afterCursor->next;
    next->prev = prev;
    prev->next = next;
    this->afterCursor->prev = nullptr;
    this->afterCursor->next = nullptr;

    Node *kill = this->afterCursor;
    this->afterCursor = next;

    delete kill;
    this->num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore()
{
    if (pos_cursor <= 0)
    {
        cout << "Error: Called eraseBefore when cursor is at front of list. Exiting...";
        exit(EXIT_FAILURE);
    }

    Node *kill = this->beforeCursor;
    this->beforeCursor->prev->next = this->beforeCursor->next;
    this->beforeCursor->next->prev = this->beforeCursor->prev;

    this->beforeCursor = this->beforeCursor->prev;

    kill->prev = nullptr;
    kill->next = nullptr;

    delete kill;

    this->num_elements--;
    this->pos_cursor--;
}

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of the element x.
// If x is found, places the cursor immediately after the found element (so
// eraseBefore() would remove the found element), and returns the final
// cursor position. If x is not found, places the cursor at position size(),
// and returns -1.
int List::findNext(int x)
{
    while (pos_cursor < num_elements)
    {
        if (moveNext() == x)
            return pos_cursor;
    }
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of the element x.
// If x is found, places the cursor immediately before the found element (so
// eraseAfter() would remove the found element), and returns the final
// cursor position. If x is not found, places the cursor at position 0, and
// returns -1.
int List::findPrev(int x)
{

    while (pos_cursor > 0)
    {
        if (movePrev() == x)
            return pos_cursor;
    }

    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique data
// values. The order of the remaining elements is obtained by retaining
// the frontmost occurrance of each element, and removing all other
// occurances. The cursor is not moved with respect to the retained
// elements, i.e. it lies between the same two retained elements that it
// did before cleanup() was called.
void List::cleanup()
{
    Node *curr = frontDummy->next;
    int currentPosition = 0;

    while (curr != backDummy)
    {
        int dupFound = 0;
        Node *future = curr->next;
        int futurePosition = currentPosition + 1;

        while (future != backDummy)
        {
            if (future->data == curr->data)
            {
                if (future == beforeCursor)
                    beforeCursor = beforeCursor->prev;
                else if (future == afterCursor)
                    afterCursor = afterCursor->next;

                future->prev->next = future->next;
                future->next->prev = future->prev;
                future->prev = nullptr;
                future->next = nullptr;
                delete future;

                dupFound = 1;
                pos_cursor = futurePosition < pos_cursor ? pos_cursor - 1 : pos_cursor;
                num_elements--;
                break;
            }

            future = future->next;
            futurePosition++;
        }

        curr = dupFound == 0 ? curr->next : curr;
        currentPosition = dupFound == 0 ? currentPosition + 1 : currentPosition;
    }
}

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear()
{
    moveFront();

    while (isEmpty() == false)
        eraseAfter();
}

// concat()
// Returns a new List consisting of the elements of this List, followed
// by the elements of L. The returned List's cursor will be at its front
// (position 0).
List List::concat(const List &L)
{
    List ret = List(*this);
    ret.moveBack();

    Node *curr = L.frontDummy->next;

    while (curr != L.backDummy)
    {
        ret.insertBefore(curr->data);
        curr = curr->next;
    }

    ret.moveFront();

    return ret;
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string()
{
    string listToString = "(";
    Node *curr = this->frontDummy->next;

    listToString += curr == backDummy ? "" : std::to_string(curr->data);
    curr = curr == backDummy ? backDummy : curr->next;

    while (curr != this->backDummy)
    {
        listToString += ", " + std::to_string(curr->data);
        curr = curr->next;
    }

    listToString += ")";

    return listToString;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List &R)
{
    if (R.num_elements != this->num_elements)
        return false;

    Node *curr = this->frontDummy->next;
    Node *rCurr = R.frontDummy->next;

    while (curr != this->backDummy && rCurr != R.backDummy)
    {
        if (curr->data != rCurr->data)
            return false;

        curr = curr->next;
        rCurr = rCurr->next;
    }

    return true;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
ostream &operator<<(ostream &stream, List &L)
{
    return stream << L.to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged are unchanged.
bool operator==(List &A, const List &B)
{
    return A.equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List &List::operator=(const List &L)
{
    if (this == &L)
        return *this;

    clear();

    for (Node *currL = L.frontDummy->next; currL != L.backDummy; currL = currL->next)
        insertBefore(currL->data);

    moveFront();

    return *this;
}