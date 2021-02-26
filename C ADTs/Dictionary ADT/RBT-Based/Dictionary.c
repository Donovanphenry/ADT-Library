/****************************************************************************************
* Name: Donovan Henry
* CruzID: dphenry
* Assignment: PA6
* File: Dictionary.c
*****************************************************************************************/

#include "Dictionary.h"

#define NIL_VAL -69
#define NIL_KEY "(Nil)"

// private NodeObj type
typedef struct NodeObj
{
    KEY_TYPE key;
    VAL_TYPE value;
    char color;

    struct NodeObj *parent;
    struct NodeObj *left;
    struct NodeObj *right;
    struct NodeObj *next;
    struct NodeObj *prev;
} NodeObj;

// private Node type
typedef NodeObj *Node;

typedef struct DictionaryObj
{
    int unique;
    int size;

    Node root;
    Node curr;
    Node nil;
} DictionaryObj;

typedef DictionaryObj *Dictionary;

// Method signatures ---------------------------------------------------
void rbtInsertFixUp(Dictionary D, Node inserted);
void rbtDeleteFixUp(Dictionary D, Node x);
void rbtTransplant(Dictionary D, Node u, Node v);
void leftRotate(Dictionary D, Node x);
void rightRotate(Dictionary D, Node x);
void clearTree(Dictionary D, Node curr);
void printTreePreOrder(FILE *out, Dictionary D, Node curr);
void printTreeInOrder(FILE *out, Dictionary D, Node curr);
void printTreePostOrder(FILE *out, Dictionary D, Node curr);

// Constructors-Destructors ---------------------------------------------------

Node newNode(KEY_TYPE k, VAL_TYPE v, char color)
{
    Node inserted = (Node)malloc(sizeof(NodeObj));

    inserted->key = k;
    inserted->value = v;
    inserted->color = color;

    inserted->parent = NULL;
    inserted->left = NULL;
    inserted->right = NULL;
    inserted->next = NULL;
    inserted->prev = NULL;

    return inserted;
}

void freeNode(Node *pN)
{
    if (pN == NULL || *pN == NULL)
        return;

    // might need to free the key prop?
    (*pN)->parent = NULL;
    (*pN)->left = NULL;
    (*pN)->right = NULL;
    (*pN)->next = NULL;
    (*pN)->prev = NULL;

    free(*pN);
    *pN = NULL;
}

// newDictionary()
// Creates a new empty Dictionary. If unique==false (0), then the Dictionary
// will accept duplicate keys, i.e. distinct pairs with identical keys. If
// unique==true (1 or any non-zero value), then duplicate keys will not be
// accepted. In this case, the operation insert(D, k) will enforce the
// precondition: lookup(D, k)==VAL_UNDEF
Dictionary newDictionary(int unique)
{
    Dictionary dict = (Dictionary)malloc(sizeof(DictionaryObj));
    dict->unique = unique;
    dict->size = 0;

    dict->nil = newNode(KEY_UNDEF, VAL_UNDEF, 'b');
    dict->nil->parent = dict->nil;
    dict->nil->left = dict->nil;
    dict->nil->right = dict->nil;
    dict->nil->prev = dict->nil;
    dict->nil->next = dict->nil;

    dict->root = dict->nil;
    dict->curr = dict->nil;

    return dict;
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary *pD)
{
    if (pD == NULL && *pD == NULL)
        return;

    makeEmpty(*pD);
    freeNode(&((*pD)->nil));
    free(*pD);
}

// Access functions -----------------------------------------------------------

// size()
// Returns the number of (key, value) pairs in Dictionary D.
int size(Dictionary D)
{
    if (D == NULL)
    {
        printf("Error: Dictionary is null in size(). Exiting...");
        exit(EXIT_FAILURE);
    }

    return D->size;
}

// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Dictionary D)
{
    if (D == NULL)
    {
        printf("Error: Dictionary is null in getUnique(). Exiting...");
        exit(EXIT_FAILURE);
    }

    return D->unique;
}

Node rbtMinimum(Dictionary D, Node curr)
{
    while (curr->left != D->nil)
        curr = curr->left;

    return curr;
}

Node rbtMaximum(Dictionary D, Node curr)
{
    while (curr->right != D->nil)
        curr = curr->right;

    return curr;
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Dictionary D, KEY_TYPE k)
{
    if (D == NULL)
    {
        printf("Error: Dictionary is null in lookup(). Exiting...");
        exit(EXIT_FAILURE);
    }

    Node curr = D->root;

    while (curr != D->nil)
    {
        if (KEY_CMP(k, curr->key) < 0)
            curr = curr->left;
        else if (KEY_CMP(k, curr->key) > 0)
            curr = curr->right;
        else
            return curr->value;
    }

    return VAL_UNDEF;
}

// Manipulation procedures ----------------------------------------------------

Node rbtPredecessor(Dictionary D, Node curr)
{
    if (curr->left != D->nil)
        return rbtMaximum(D, curr->left);

    Node parent = curr->parent;

    while (parent != D->nil && parent->left == curr)
    {
        curr = parent;
        parent = parent->parent;
    }

    return parent;
}

Node rbtSuccessor(Dictionary D, Node curr)
{
    if (curr->right != D->nil)
        return rbtMinimum(D, curr->right);

    Node parent = curr->parent;

    while (parent != D->nil && parent->right == curr)
    {
        curr = parent;
        parent = parent->parent;
    }

    return parent;
}

void leftRotate(Dictionary D, Node x)
{
    // set y
    Node y = x->right;

    // turn y's left subtree into x's right subtree
    x->right = y->left;
    if (y->left != D->nil) // not necessary if using sentinal nil node
        y->left->parent = x;

    // link y's parent to x
    y->parent = x->parent;
    if (x->parent == D->nil)
        D->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    // put x on y's left
    y->left = x;
    x->parent = y;
}

void rightRotate(Dictionary D, Node x)
{
    // set y
    Node y = x->left;

    // turn y's right subtree into x's left subtree
    x->left = y->right;
    if (y->right != D->nil) // not necessary if using sentinal nil node
        y->right->parent = x;

    // link y's parent to x
    y->parent = x->parent;
    if (x->parent == D->nil)
        D->root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    // put x on y's right
    y->right = x;
    x->parent = y;
}

// insert()
// Insert the pair (k,v) into Dictionary D.
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced.
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v)
{
    if (D == NULL)
    {
        printf("Error: Dictionary is null in insert(). Exiting...");
        exit(EXIT_FAILURE);
    }

    if (D->unique == 1 && lookup(D, k) != VAL_UNDEF)
    {
        printf("Error: Dictionary is supposed to be unique but key already exists in dictionary in insert(). Exiting...");
        exit(EXIT_FAILURE);
    }

    Node curr = D->root;
    Node parent = curr->parent;

    Node inserted = newNode(k, v, 'r');
    inserted->prev = D->nil;
    inserted->next = D->nil;

    while (curr != D->nil)
    {
        parent = curr;

        if (KEY_CMP(inserted->key, curr->key) < 0)
            curr = curr->left;
        else
            curr = curr->right;
    }

    if (parent == D->nil)
        D->root = inserted;
    else if (KEY_CMP(inserted->key, parent->key) < 0)
        parent->left = inserted;
    else
        parent->right = inserted;

    inserted->parent = parent;
    inserted->left = D->nil;
    inserted->right = D->nil;

    rbtInsertFixUp(D, inserted);

    D->size++;
}

void rbtInsertFixUp(Dictionary D, Node curr)
{
    while (curr->parent->color == 'r')
    {
        if (curr->parent == curr->parent->parent->left)
        {
            Node y = curr->parent->parent->right;
            if (y->color == 'r')
            {
                curr->parent->color = 'b';
                y->color = 'b';
                curr->parent->parent->color = 'r';
                curr = curr->parent->parent;
            }
            else
            {
                if (curr == curr->parent->right)
                {
                    curr = curr->parent;
                    leftRotate(D, curr);
                }

                curr->parent->color = 'b';
                curr->parent->parent->color = 'r';

                rightRotate(D, curr->parent->parent);
            }
        }
        else
        {
            Node parent = curr->parent;
            Node uncle = parent->parent->left;

            if (uncle->color == 'r')
            {
                parent->color = 'b';
                uncle->color = 'b';
                parent->parent->color = 'r';
                curr = parent->parent;
            }
            else
            {
                if (curr == curr->parent->left)
                {
                    curr = parent;
                    rightRotate(D, curr);
                }

                curr->parent->color = 'b';
                curr->parent->parent->color = 'r';
                leftRotate(D, curr->parent->parent);
            }
        }
    }

    D->root->color = 'b';
}

// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete (Dictionary D, KEY_TYPE k)
{
    if (D == NULL)
    {
        printf("Error: Dictionary is null in delete(). Exiting...");
        exit(EXIT_FAILURE);
    }

    if (lookup(D, k) == VAL_UNDEF)
    {
        printf("Error: Attempting to delete a node not in the dictionary in delete(). Exiting...");
        exit(EXIT_FAILURE);
    }

    if (D->size == 0)
        return;

    Node kill = D->root;

    while (kill != D->nil)
    {
        if (KEY_CMP(kill->key, k) < 0)
            kill = kill->right;
        else if (KEY_CMP(kill->key, k) > 0)
            kill = kill->left;
        else
            break;
    }
    Node y = kill;
    Node x = D->nil;
    char y_original_color = y->color;

    if (kill->left == D->nil)
    {
        x = kill->right;
        rbtTransplant(D, kill, kill->right);
    }
    else if (kill->right == D->nil)
    {
        x = kill->left;
        rbtTransplant(D, kill, kill->left);
    }
    else
    {
        y = rbtMinimum(D, kill->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == kill)
            x->parent = y;
        else
        {
            rbtTransplant(D, y, y->right);
            y->right = kill->right;
            y->right->parent = y;
        }
        rbtTransplant(D, kill, y);
        y->left = kill->left;
        y->left->parent = y;
        y->color = kill->color;
    }
    if (y_original_color == 'b')
        rbtDeleteFixUp(D, x);

    if (D->curr == kill)
        D->curr = D->nil;
    freeNode(&kill);
    D->size--;
}

void rbtTransplant(Dictionary D, Node u, Node v)
{
    if (u->parent == D->nil)
        D->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

void rbtDeleteFixUp(Dictionary D, Node x)
{
    while (x != D->root && x->color == 'b')
    {
        if (x == x->parent->left)
        {
            Node w = x->parent->right;
            if (w->color == 'r')
            {
                w->color = 'b';           // case 1
                x->parent->color = 'r';   // case 1
                leftRotate(D, x->parent); // case 1
                w = x->parent->right;     // case 1
            }
            if (w->left->color == 'b' && w->right->color == 'b')
            {
                w->color = 'r'; // case 2
                x = x->parent;  // case 2
            }
            else
            {
                if (w->right->color == 'b')
                {
                    w->left->color = 'b'; // case 3
                    w->color = 'r';       // case 3
                    rightRotate(D, w);    // case 3
                    w = x->parent->right; // case 3
                }
                w->color = x->parent->color; // case 4
                x->parent->color = 'b';      // case 4
                w->right->color = 'b';       // case 4
                leftRotate(D, x->parent);    // case 4
                x = D->root;                 // case 4
            }
        }
        else
        {
            Node w = x->parent->left;
            if (w->color == 'r')
            {
                w->color = 'b';            // case 5
                x->parent->color = 'r';    // case 5
                rightRotate(D, x->parent); // case 5
                w = x->parent->left;       // case 5
            }
            if (w->right->color == 'b' && w->left->color == 'b')
            {
                w->color = 'r'; // case 6
                x = x->parent;  // case 6
            }
            else
            {
                if (w->left->color == 'b')
                {
                    w->right->color = 'b'; // case 7
                    w->color = 'r';        // case 7
                    leftRotate(D, w);      // case 7
                    w = x->parent->left;   // case 7
                }
                w->color = x->parent->color; // case 8
                x->parent->color = 'b';      // case 8
                w->left->color = 'b';        // case 8
                rightRotate(D, x->parent);   // case 8
                x = D->root;                 // case 8
            }
        }
    }
    x->color = 'b';
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D)
{
    if (D == NULL)
    {
        printf("Error: Dictionary is null in makeEmpty(). Exiting...");
        exit(EXIT_FAILURE);
    }

    if (D->size == 0)
        return;

    clearTree(D, D->root);
    D->size = 0;
    D->curr = D->nil;
    D->root = D->nil;
}

void clearTree(Dictionary D, Node curr)
{
    if (curr == D->nil)
        return;

    clearTree(D, curr->left);
    clearTree(D, curr->right);
    freeNode(&curr);
}

// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginForward(Dictionary D)
{
    if (D == NULL)
    {
        printf("Error: Dictionary is null in beginForward(). Exiting...");
        exit(EXIT_FAILURE);
    }

    D->curr = rbtMinimum(D, D->root);

    return D->curr == D->nil ? VAL_UNDEF : D->curr->value;
}

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D)
{
    if (D == NULL)
    {
        printf("Error: Dictionary is null in beginReverse(). Exiting...");
        exit(EXIT_FAILURE);
    }

    D->curr = rbtMaximum(D, D->root);

    return D->curr == D->nil ? VAL_UNDEF : D->curr->value;
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D)
{
    if (D == NULL)
    {
        printf("Error: Dictionary is null in currentKey(). Exiting...");
        exit(EXIT_FAILURE);
    }

    return D->curr == D->nil ? KEY_UNDEF : D->curr->key;
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the
// value corresponding to the current key. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D)
{
    if (D == NULL)
    {
        printf("Error: Dictionary is null in currentVal(). Exiting...");
        exit(EXIT_FAILURE);
    }

    return D->curr == D->nil ? VAL_UNDEF : D->curr->value;
}

// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE next(Dictionary D)
{
    if (D == NULL)
    {
        printf("Error: Dictionary is null in next(). Exiting...");
        exit(EXIT_FAILURE);
    }

    D->curr = rbtSuccessor(D, D->curr);

    return D->curr == D->nil ? VAL_UNDEF : D->curr->value;
}

// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE prev(Dictionary D)
{
    if (D == NULL)
    {
        printf("Error: Dictionary is null in prev(). Exiting...");
        exit(EXIT_FAILURE);
    }

    D->curr = rbtPredecessor(D, D->curr);

    return D->curr == D->nil ? VAL_UNDEF : D->curr->value;
}

// Other operations -----------------------------------------------------------

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE *out, Dictionary D, const char *order)
{
    if (D == NULL)
    {
        printf("Error: Dictionary is null in printDictionary(). Exiting...");
        exit(EXIT_FAILURE);
    }

    if (out == NULL)
    {
        printf("Error: Output file is null in printDictionary(). Exiting...");
        exit(EXIT_FAILURE);
    }

    if (strcmp(order, "pre") == 0)
        printTreePreOrder(out, D, D->root);
    else if (strcmp(order, "in") == 0)
        printTreeInOrder(out, D, D->root);
    else if (strcmp(order, "post") == 0)
        printTreePostOrder(out, D, D->root);
}

void printTreePreOrder(FILE *out, Dictionary D, Node curr)
{
    if (curr == D->nil)
        return;

    fprintf(out, "%s", curr->key);
    printTreePreOrder(out, D, curr->left);
    printTreePreOrder(out, D, curr->right);
}

void printTreeInOrder(FILE *out, Dictionary D, Node curr)
{
    if (curr == D->nil)
        return;

    printTreeInOrder(out, D, curr->left);
    fprintf(out, "%s", curr->key);
    printTreeInOrder(out, D, curr->right);
}

void printTreePostOrder(FILE *out, Dictionary D, Node curr)
{
    if (curr == D->nil)
        return;

    printTreePostOrder(out, D, curr->left);
    printTreePostOrder(out, D, curr->right);
    fprintf(out, "%s", curr->key);
}