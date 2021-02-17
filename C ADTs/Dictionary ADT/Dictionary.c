//-----------------------------------------------------------------------------
// Dictionary.c
// Source file for Dictionary ADT storing (key, value) pairs of types KEY_TYPE
// and VAL_TYPE.
//-----------------------------------------------------------------------------
#include "Dictionary.h"

#define NIL_VAL -69
#define NIL_KEY "(Nil)"

// private NodeObj type
typedef struct NodeObj
{
    KEY_TYPE key;
    VAL_TYPE value;

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
void clearTree(Dictionary D, Node curr);
void printTree(FILE *out, Dictionary D, Node curr);
void transplant(Dictionary D, Node u, Node v);

// Constructors-Destructors ---------------------------------------------------

Node newNode(KEY_TYPE k, VAL_TYPE v)
{
    Node inserted = (Node)malloc(sizeof(NodeObj));
    inserted->key = k;
    inserted->value = v;
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

    dict->nil = newNode(KEY_UNDEF, VAL_UNDEF);
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

    if (D->size == 0)
    {
        D->root = newNode(k, v);
        D->root->parent = D->nil;
        D->root->left = D->nil;
        D->root->right = D->nil;
        D->root->prev = D->nil;
        D->root->next = D->nil;
        D->size++;
        return;
    }

    Node curr = D->root;

    while (curr != D->nil)
    {
        if (KEY_CMP(k, curr->key) < 0)
        {
            if (curr->left == D->nil)
            {
                Node prev = curr->prev;
                Node inserted = newNode(k, v);
                inserted->parent = curr;
                inserted->left = D->nil;
                inserted->right = D->nil;
                curr->left = inserted;

                inserted->prev = prev;
                if (prev != D->nil)
                    prev->next = inserted;
                inserted->next = curr;
                curr->prev = inserted;

                D->size++;
                return;
            }
            else
            {
                curr = curr->left;
            }
        }
        else
        {
            if (curr->right == D->nil)
            {
                Node next = curr->next;
                Node inserted = newNode(k, v);
                inserted->parent = curr;
                inserted->left = D->nil;
                inserted->right = D->nil;
                curr->right = inserted;

                inserted->next = next;
                if (next != D->nil)
                    next->prev = inserted;
                inserted->prev = curr;
                curr->next = inserted;

                D->size++;
                return;
            }
            else
            {
                curr = curr->right;
            }
        }
    }
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

    D->size--;
    Node curr = D->root;

    while (curr != D->nil)
    {
        if (KEY_CMP(k, curr->key) < 0)
            curr = curr->left;
        else if (KEY_CMP(k, curr->key) > 0)
            curr = curr->right;
        else
            break;
    }

    if (curr->left == D->nil)
        transplant(D, curr, curr->right);
    else if (curr->right == D->nil)
        transplant(D, curr, curr->left);
    else
    {
        Node subTreeMax = curr->right;

        while (subTreeMax->left != D->nil)
            subTreeMax = subTreeMax->left;

        if (subTreeMax->parent != curr)
        {
            transplant(D, subTreeMax, subTreeMax->right);
            subTreeMax->right = curr->right;
            subTreeMax->right->parent = subTreeMax;
        }

        transplant(D, curr, subTreeMax);
        subTreeMax->left = curr->left;
        subTreeMax->left->parent = subTreeMax;
    }

    Node prev = curr->prev;
    Node next = curr->next;

    if (prev != D->nil)
        prev->next = next;
    if (next != D->nil)
        next->prev = prev;

    D->curr = D->curr == curr ? D->nil : D->curr;
    freeNode(&curr);
}

void transplant(Dictionary D, Node u, Node v)
{
    if (u->parent == D->nil)
    {
        D->root = v;
        v->parent = D->nil;
    }
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != D->nil)
        v->parent = u->parent;
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

    D->curr = D->root;

    while (D->curr->left != D->nil)
        D->curr = D->curr->left;

    return D->curr->value;
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

    D->curr = D->root;

    while (D->curr->right != D->nil)
        D->curr = D->curr->right;

    return D->curr->value;
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

    D->curr = D->curr->next;

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

    D->curr = D->curr->prev;

    return D->curr == D->nil ? VAL_UNDEF : D->curr->value;
}

// Other operations -----------------------------------------------------------

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE *out, Dictionary D)
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

    printTree(out, D, D->root);
}

void printTree(FILE *out, Dictionary D, Node curr)
{
    if (curr == D->nil)
        return;

    printTree(out, D, curr->left);
    fprintf(out, "%s %d\n", curr->key, curr->value);
    printTree(out, D, curr->right);
}