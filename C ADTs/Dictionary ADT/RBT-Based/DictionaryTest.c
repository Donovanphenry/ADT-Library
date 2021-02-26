/****************************************************************************************
* Name: Donovan Henry
* CruzID: dphenry
* Assignment: PA6
* File: DictionaryTest.c
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"

#define DICT_MODEL

#ifdef DICT_MODEL
int main()
{
    Dictionary B = newDictionary(0);
    int pI[10];

    for (int i = 0; i < 10; i++)
        pI[i] = i;

    insert(B, "d", &pI[0]);
    insert(B, "d", &pI[1]);
    insert(B, "d", &pI[2]);

    printf("Printig dictionary\n");
    printDictionary(stdout, B, "in");

    insert(B, "d", &pI[3]);
    insert(B, "d", &pI[4]);
    insert(B, "d", &pI[5]);

    printf("Printig dictionary\n");
    printDictionary(stdout, B, "in");

    insert(B, "d", &pI[6]);
    insert(B, "d", &pI[7]);

    for (beginForward(B); currentVal(B) != VAL_UNDEF; next(B))
        printf("CurrentVal: %d\n", *currentVal(B));
    delete (B, "d");
    printf("Printig dictionary\n");
    printDictionary(stdout, B, "pre");
    printf("\n");
    if (*lookup(B, "d") != pI[4])
    {
        return 1;
    }
    delete (B, "d");
    printf("Printig dictionary\n");
    printDictionary(stdout, B, "pre");
    if (*lookup(B, "d") != pI[5])
    {
        printf("Lookup: %d, pI[5]: %d", *lookup(B, "d"), pI[5]);
        return 1;
    }
    return 0;
}
#endif

#if defined(DICT_CTOR_DTOR) || defined(DICT_ALL)

void ctorDtorTest()
{
    printf("\n=========== CTOR_DTOR TEST ===========\n");

    printf("Constructing and freeing unique and non-unique dictionary. Expect no mem leak or seg fault\n");

    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    freeDictionary(&A);
    freeDictionary(&B);
}

#ifndef DICT_ALL
int main()
{
    ctorDtorTest();
}
#endif

#endif

#if defined(DICT_SIZE) || defined(DICT_ALL)

void getSizeTest()
{
    printf("\n=========== GET_SIZE TEST ===========\n");

    printf("Constructing unique and non-unique dict then calling getSize. Expect: 0 0. Received: ");
    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);
    printf("%d %d\n", size(A), size(B));

    int a = 1, b_1 = 1, b_2 = 2, b_3 = 5, c = 10, d = 15, f = 1;

    insert(A, "b", &b_1);
    insert(A, "b", &b_2);
    insert(A, "f", &f);

    insert(B, "a", &a);
    insert(B, "b", &b_3);
    insert(B, "c", &c);
    insert(B, "d", &d);

    printf("Calling size() of A. Expect: 3. Received: %d\n", size(A));
    printf("Calling size() of B. Expect: 4. Received: %d\n", size(B));

    delete (A, "b");
    delete (B, "b");

    printf("Calling size() of A. Expect: 2. Received: %d\n", size(A));
    printf("Calling size() of B. Expect: 3. Received: %d\n", size(B));

    delete (A, "b");
    delete (B, "a");
    delete (A, "f");
    delete (B, "c");

    printf("Calling size() of A. Expect: 0. Received: %d\n", size(A));
    printf("Calling size() of B. Expect: 1. Received: %d\n", size(B));

    delete (B, "d");

    printf("Calling size() of A. Expect: 0. Received: %d\n", size(A));
    printf("Calling size() of B. Expect: 0. Received: %d\n", size(B));

    freeDictionary(&A);
    freeDictionary(&B);
}

#ifndef DICT_ALL
int main()
{
    getSizeTest();
}
#endif

#endif

#if defined(DICT_GETUNIQUE) || defined(DICT_ALL)

void getUniqueTest()
{
    printf("\n=========== GET_UNIQUE TEST ===========\n");

    printf("Constructing unique and non-unique dict then calling getUnique. Expect: 0 1. Received: ");
    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);
    printf("%d %d\n", getUnique(A), getUnique(B));

    freeDictionary(&A);
    freeDictionary(&B);
}

#ifndef DICT_ALL

int main()
{
    getUniqueTest();
}
#endif

#endif

#if defined(DICT_LOOKUP) || defined(DICT_ALL)

void lookupTest()
{
    printf("\n=========== LOOKUP TEST ===========\n");

    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    int a = 1, b_1 = 1, b_2 = 2, b_3 = 5, c = 10, d = 15, f = 1;

    insert(A, "b", &b_1);
    insert(A, "b", &b_2);
    insert(A, "f", &f);

    insert(B, "a", &a);
    insert(B, "b", &b_3);
    insert(B, "c", &c);
    insert(B, "d", &d);

    printf("Lookup on A with (k, v) = (b, 1). Expect: 1. Received: %d\n", *(lookup(A, "b")));
    delete (A, "b");
    printf("Lookup on A after deletion with (k, v) = (b, 2). Expect: 2. Received: %d\n", *(lookup(A, "b")));

    printf("Lookup on B with (k, v) = (a, 1). Expect: 1. Received: %d\n", *(lookup(B, "a")));
    printf("Lookup on B with (k, v) = (b, 5). Expect: 5. Received: %d\n", *(lookup(B, "b")));
    delete (B, "a");
    printf("Lookup on B with (k, v) = (a, 1). Expect: NULL. Received: %s\n", lookup(B, "a") == NULL ? "NULL" : "Not NULL");

    freeDictionary(&A);
    freeDictionary(&B);
}

#ifndef DICT_ALL
int main()
{
    lookupTest();
}
#endif

#endif

#if defined(DICT_INSERT) || defined(DICT_ALL)

void insertTest()
{
    printf("\n=========== INSERT TEST ===========\n");

    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    // printf("Printing A before insertion. Expect:\nReceived:\n");
    // printDictionary(stdout, A, "in");

    // printf("Printing B before insertion. Expect:\nReceived:\n");
    // printDictionary(stdout, B, "in");

    // int a = 1;
    int b_1 = 1, b_2 = 2;
    // int b_3 = 5, c = 10, d = 15;
    int f = 1;
    int t1 = 5, t2 = 4, t3 = 3, t4 = 4, t5 = 5;

    insert(A, "a", &b_1);
    insert(A, "b", &b_2);
    insert(A, "c", &f);
    insert(A, "d", &t1);
    insert(A, "e", &t2);
    insert(A, "f", &t3);
    insert(A, "g", &t4);
    insert(A, "h", &t5);

    printDictionary(stdout, A, "in");

    // insert(B, "a", &a);
    // insert(B, "b", &b_3);
    // insert(B, "c", &c);
    // insert(B, "d", &d);

    // printf("Printing A after insertion. Expect:\nb 1\nb 2\nf 1\nReceived:\n");
    // printDictionary(stdout, A, "in");

    // printf("Printing B after insertion. Expect:\na 1\nb 5\nc 10\nd 15\nReceived:\n");
    // printDictionary(stdout, B, "in");

    freeDictionary(&A);
    freeDictionary(&B);
}

#ifndef DICT_ALL
int main()
{
    insertTest();
}
#endif

#endif

#if defined(DICT_DELETE) || defined(DICT_ALL)

void deleteTest()
{
    printf("\n=========== DELETE TEST ===========\n");

    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    printf("Printing A before insertion. Expect:\nReceived:\n");
    printDictionary(stdout, A, "in");

    printf("Printing B before insertion. Expect:\nReceived:\n");
    printDictionary(stdout, B, "in");

    int a = 1, b_1 = 1, b_2 = 2, b_3 = 5, c = 10, d = 15, f = 1;

    insert(A, "b", &b_1);
    insert(A, "b", &b_2);
    insert(A, "f", &f);

    insert(B, "a", &a);
    insert(B, "b", &b_3);
    insert(B, "c", &c);
    insert(B, "d", &d);

    printf("Printing A after insertion. Expect:\nb 1\nb 2\nf 1\nReceived:\n");
    printDictionary(stdout, A, "in");

    printf("Printing B after insertion. Expect:\na 1\nb 5\nc 10\nd 15\nReceived:\n");
    printDictionary(stdout, B, "in");

    delete (A, "b");
    delete (A, "f");

    delete (B, "c");
    delete (B, "b");

    printf("Printing A after deletion. Expect:\nb 2\nReceived:\n");
    printDictionary(stdout, A, "in");

    printf("Printing B after deletion. Expect:\na 1\nd 15\nReceived:\n");
    printDictionary(stdout, B, "in");

    freeDictionary(&A);
    freeDictionary(&B);
}

#ifndef DICT_ALL
int main()
{
    deleteTest();
}
#endif

#endif

#if defined(DICT_MAKE_EMPTY) || defined(DICT_ALL)

void makeEmptyTest()
{
    printf("\n=========== MAKE_EMPTY TEST ===========\n");

    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    printf("Printing A before insertion. Expect:\nReceived:\n");
    printDictionary(stdout, A, "in");

    printf("Printing B before insertion. Expect:\nReceived:\n");
    printDictionary(stdout, B, "in");

    printf("Calling make empty on empty dictionaries. Expect no errors.\n");
    makeEmpty(A);
    makeEmpty(B);

    int a = 1, b_1 = 1, b_2 = 2, b_3 = 5, c = 10, d = 15, f = 1;

    insert(A, "b", &b_1);
    insert(A, "b", &b_2);
    insert(A, "f", &f);

    insert(B, "a", &a);
    insert(B, "b", &b_3);
    insert(B, "c", &c);
    insert(B, "d", &d);

    printf("Printing A after insertion. Expect:\nb 1\nb 2\nf 1\nReceived:\n");
    printDictionary(stdout, A, "in");

    printf("Printing B after insertion. Expect:\na 1\nb 5\nc 10\nd 15\nReceived:\n");
    printDictionary(stdout, B, "in");

    makeEmpty(A);
    makeEmpty(B);

    printf("Printing A after makeEmpty. Expect:\nReceived:\n");
    printDictionary(stdout, A, "in");

    printf("Printing B after makeEmpty. Expect:\nReceived:\n");
    printDictionary(stdout, B, "in");

    freeDictionary(&A);
    freeDictionary(&B);
}

#ifndef DICT_ALL
int main()
{
    makeEmptyTest();
}
#endif

#endif

#if defined(DICT_BEGIN_FORWARD) || defined(DICT_ALL)

void beginForwardTest()
{
    printf("\n=========== BEGIN_FORWARD TEST ===========\n");
    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    VAL_TYPE x = beginForward(A);
    VAL_TYPE y = beginForward(B);

    printf("BeginForward on non-unique dict. Expect: NULL. Received: %s\n", x == NULL ? "NULL" : "Not NULL");
    printf("BeginForward on unique dict. Expect: NULL. Received: %s\n", y == NULL ? "NULL" : "Not NULL");

    int a = 1, b = 1, C_1 = 2, C_2 = 5, D = 10, E = 15;

    insert(A, "A", &a);
    insert(A, "B", &b);
    insert(A, "C", &C_1);

    insert(B, "C", &C_2);
    insert(B, "D", &D);
    insert(B, "E", &E);

    x = beginForward(A);
    y = beginForward(B);

    printf("BeginForward on non-unique dict. Expect: 10. Received: %d\n", *x);
    printf("BeginForward on unique dict. Expect: 10. Received: %d\n", *y);

    delete (A, "C");
    delete (A, "B");
    delete (A, "A");

    makeEmpty(B);

    x = beginForward(A);
    y = beginForward(B);

    printf("BeginForward on non-unique dict. Expect: NULL. Received: %s\n", x == NULL ? "NULL" : "Not NULL");
    printf("BeginForward on unique dict. Expect: NULL. Received: %s\n", y == NULL ? "NULL" : "Not NULL");

    freeDictionary(&A);
    freeDictionary(&B);
}

#ifndef DICT_ALL
int main()
{
    beginForwardTest();
}
#endif

#endif

#if defined(DICT_BEGIN_REVERSE) || defined(DICT_ALL)

void beginReverseTest()
{
    printf("\n=========== BEGIN_REVERSE TEST ===========\n");
    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    VAL_TYPE x = beginReverse(A);
    VAL_TYPE y = beginReverse(B);

    printf("BeginReverse on non-unique dict. Expect: NULL. Received: %s\n", x == NULL ? "NULL" : "Not NULL");
    printf("BeginReverse on unique dict. Expect: NULL. Received: %s\n", y == NULL ? "NULL" : "Not NULL");

    int a = 10, b = 12, c_1 = 103, c_2 = 10, d = 120, e = 101;

    insert(A, "A", &a);
    insert(A, "B", &b);
    insert(A, "C", &c_1);

    insert(B, "C", &c_2);
    insert(B, "D", &d);
    insert(B, "E", &e);

    x = beginReverse(A);
    y = beginReverse(B);

    printf("BeginReverse on non-unique dict. Expect: 103. Received: %d\n", *x);
    printf("BeginReverse on unique dict. Expect: 101. Received: %d\n", *y);

    delete (A, "C");
    delete (A, "B");
    delete (A, "A");

    makeEmpty(B);

    x = beginReverse(A);
    y = beginReverse(B);

    printf("BeginReverse on non-unique dict. Expect: NULL. Received: %s\n", x == NULL ? "NULL" : "Not NULL");
    printf("BeginReverse on unique dict. Expect: NULL. Received: %s\n", y == NULL ? "NULL" : "Not NULL");

    freeDictionary(&A);
    freeDictionary(&B);
}

#ifndef DICT_ALL
int main()
{
    beginReverseTest();
}
#endif

#endif

#if defined(DICT_CURRENT_KEY) || defined(DICT_ALL)

void currentKeyTest()
{
    printf("\n=========== CURRENT_KEY TEST ===========\n");
    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    beginForward(A);
    beginForward(B);
    KEY_TYPE x = currentKey(A);
    KEY_TYPE y = currentKey(B);

    printf("BeginForward on non-unique dict. Expect: %p. Received: " KEY_FORMAT "\n", KEY_UNDEF, x);
    printf("BeginForward on unique dict. Expect: %p. Received: " KEY_FORMAT "\n", KEY_UNDEF, y);

    beginReverse(A);
    beginReverse(B);
    x = currentKey(A);
    y = currentKey(B);

    printf("BeginForward on non-unique dict. Expect: %p. Received: " KEY_FORMAT "\n", KEY_UNDEF, x);
    printf("BeginForward on unique dict. Expect: %p. Received: " KEY_FORMAT "\n", KEY_UNDEF, y);

    int a = 10, b = 12, c_1 = 103, c_2 = 10, d = 120, e = 101;

    insert(A, "A", &a);
    insert(A, "B", &b);
    insert(A, "C", &c_1);

    insert(B, "C", &c_2);
    insert(B, "D", &d);
    insert(B, "E", &e);

    beginForward(A);
    beginForward(B);
    x = currentKey(A);
    y = currentKey(B);

    printf("BeginForward on non-unique dict. Expect: A. Received: " KEY_FORMAT "\n", x);
    printf("BeginForward on unique dict. Expect: C. Received: " KEY_FORMAT "\n", y);

    beginReverse(A);
    beginReverse(B);
    x = currentKey(A);
    y = currentKey(B);

    printf("BeginReverse on non-unique dict. Expect: C. Received: " KEY_FORMAT "\n", x);
    printf("BeginReverse on unique dict. Expect: E. Received: " KEY_FORMAT "\n", y);

    delete (A, "C");
    delete (A, "B");
    delete (A, "A");

    makeEmpty(B);

    beginForward(A);
    beginForward(B);
    x = currentKey(A);
    y = currentKey(B);

    printf("BeginForward on non-unique dict. Expect: %p. Received: " KEY_FORMAT "\n", KEY_UNDEF, x);
    printf("BeginForward on unique dict. Expect: %p. Received: " KEY_FORMAT "\n", KEY_UNDEF, y);

    beginReverse(A);
    beginReverse(B);
    x = currentKey(A);
    y = currentKey(B);

    printf("BeginReverse on non-unique dict. Expect: %p. Received: " KEY_FORMAT "\n", KEY_UNDEF, x);
    printf("BeginReverse on unique dict. Expect: %p. Received: " KEY_FORMAT "\n", KEY_UNDEF, y);

    freeDictionary(&A);
    freeDictionary(&B);
}

#ifndef DICT_ALL
int main()
{
    currentKeyTest();
}
#endif

#endif

#if defined(DICT_CURRENT_VAL) || defined(DICT_ALL)

void currentValTest()
{
    printf("\n=========== CURRENT_VAL TEST ===========\n");
    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    beginForward(A);
    beginForward(B);
    VAL_TYPE x = currentVal(A);
    VAL_TYPE y = currentVal(B);

    printf("BeginForward on non-unique dict. Expect: NULL. Received: %s\n", x == NULL ? "NULL" : "Not NULL");
    printf("BeginForward on unique dict. Expect: NULL. Received: %s\n", y == NULL ? "NULL" : "Not NULL");

    beginReverse(A);
    beginReverse(B);
    x = currentVal(A);
    y = currentVal(B);

    printf("BeginForward on non-unique dict. Expect: NULL. Received: %s\n", x == NULL ? "NULL" : "Not NULL");
    printf("BeginForward on unique dict. Expect: NULL. Received: %s\n", y == NULL ? "NULL" : "Not NULL");

    int a = 10, b = 12, c_1 = 103, c_2 = 10, d = 120, e = 101;

    insert(A, "A", &a);
    insert(A, "B", &b);
    insert(A, "C", &c_1);

    insert(B, "C", &c_2);
    insert(B, "D", &d);
    insert(B, "E", &e);

    beginForward(A);
    beginForward(B);
    x = currentVal(A);
    y = currentVal(B);

    printf("BeginForward on non-unique dict. Expect: 10. Received: %d\n", *x);
    printf("BeginForward on unique dict. Expect: 10. Received: %d\n", *y);

    beginReverse(A);
    beginReverse(B);
    x = currentVal(A);
    y = currentVal(B);

    printf("BeginReverse on non-unique dict. Expect: 103. Received: %d\n", *x);
    printf("BeginReverse on unique dict. Expect: 101. Received: %d\n", *y);

    delete (A, "C");
    delete (A, "B");
    delete (A, "A");

    makeEmpty(B);

    beginForward(A);
    beginForward(B);
    x = currentVal(A);
    y = currentVal(B);

    printf("BeginForward on non-unique dict. Expect: NULL. Received: %s\n", x == NULL ? "NULL" : "Not NULL");
    printf("BeginForward on unique dict. Expect: NULL. Received: %s\n", y == NULL ? "NULL" : "Not NULL");

    beginReverse(A);
    beginReverse(B);
    x = currentVal(A);
    y = currentVal(B);

    printf("BeginReverse on non-unique dict. Expect: NULL. Received: %s\n", x == NULL ? "NULL" : "Not NULL");
    printf("BeginReverse on unique dict. Expect: NULL. Received: %s\n", y == NULL ? "NULL" : "Not NULL");

    freeDictionary(&A);
    freeDictionary(&B);
}

#ifndef DICT_ALL
int main()
{
    currentValTest();
}
#endif

#endif

#if defined(DICT_NEXT) || defined(DICT_ALL)

void nextTest()
{
    printf("\n=========== NEXT TEST ===========\n");

    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    printf("Printing A before insertion\nExpect:\nReceived:");
    for (beginForward(A); currentVal(A) != VAL_UNDEF; next(A))
        printf(" " KEY_FORMAT, currentKey(A));

    printf("\n");

    printf("Printing B before insertion\nExpect:\nReceived:");
    for (beginForward(B); currentVal(B) != VAL_UNDEF; next(B))
        printf(" " KEY_FORMAT, currentKey(B));

    printf("\n");

    int a = 1, b_1 = 1, b_2 = 2, b_3 = 5, c = 10, d = 15, f = 1;

    insert(A, "b", &b_1);
    insert(A, "b", &b_2);
    insert(A, "f", &f);

    insert(B, "a", &a);
    insert(B, "b", &b_3);
    insert(B, "c", &c);
    insert(B, "d", &d);

    printf("Iterating through dictionary\nExpect: b b f\nReceived:");
    for (beginForward(A); currentVal(A) != VAL_UNDEF; next(A))
        printf(" " KEY_FORMAT, currentKey(A));

    printf("\n");

    printf("Iterating through dictionary\nExpect: a b c d\nReceived:");
    for (beginForward(B); currentVal(B) != VAL_UNDEF; next(B))
        printf(" " KEY_FORMAT, currentKey(B));

    printf("\n");

    delete (A, "b");
    delete (A, "f");

    delete (B, "c");
    delete (B, "b");

    printf("Iterating through dictionary\nExpect: b\nReceived:");
    for (beginForward(A); currentVal(A) != VAL_UNDEF; next(A))
        printf(" " KEY_FORMAT, currentKey(A));

    printf("\n");

    printf("Iterating through dictionary\nExpect: a d\nReceived:");
    for (beginForward(B); currentVal(B) != VAL_UNDEF; next(B))
        printf(" " KEY_FORMAT, currentKey(B));

    printf("\n");

    freeDictionary(&A);
    freeDictionary(&B);
}

#ifndef DICT_ALL
int main()
{
    nextTest();
}
#endif

#endif

#if defined(DICT_PREV) || defined(DICT_ALL)

void prevTest()
{
    printf("\n=========== PREV TEST ===========\n");

    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    printf("Printing A before insertion. Expect:\nReceived:");
    for (beginReverse(A); currentVal(A) != VAL_UNDEF; prev(A))
        printf(" " KEY_FORMAT, currentKey(A));

    printf("\n");

    printf("Printing B before insertion. Expect:\nReceived:");
    for (beginReverse(B); currentVal(B) != VAL_UNDEF; prev(B))
        printf(" " KEY_FORMAT, currentKey(B));

    printf("\n");

    int a = 1, b_1 = 1, b_2 = 2, b_3 = 5, c = 10, d = 15, f = 1;

    insert(A, "b", &b_1);
    insert(A, "b", &b_2);
    insert(A, "f", &f);

    insert(B, "a", &a);
    insert(B, "b", &b_3);
    insert(B, "c", &c);
    insert(B, "d", &d);

    printf("Iterating through dictionary. Expect:\nf b b\nReceived:");
    for (beginReverse(A); currentVal(A) != VAL_UNDEF; prev(A))
        printf(" " KEY_FORMAT, currentKey(A));

    printf("\n");

    printf("Iterating through dictionary. Expect:\nd c b a\nReceived:");
    for (beginReverse(B); currentVal(B) != VAL_UNDEF; prev(B))
        printf(" " KEY_FORMAT, currentKey(B));

    printf("\n");

    delete (A, "b");
    delete (A, "f");

    delete (B, "c");
    delete (B, "b");

    printf("Iterating through dictionary. Expect:\nb\nReceived:");
    for (beginReverse(A); currentVal(A) != VAL_UNDEF; prev(A))
        printf(" " KEY_FORMAT, currentKey(A));

    printf("\n");

    printf("Iterating through dictionary. Expect:\nd a\nReceived:");
    for (beginReverse(B); currentVal(B) != VAL_UNDEF; prev(B))
        printf(" " KEY_FORMAT, currentKey(B));

    printf("\n");

    freeDictionary(&A);
    freeDictionary(&B);
}

#ifndef DICT_ALL
int main()
{
    prevTest();
}
#endif

#endif

#if defined(DICT_PRINT) || defined(DICT_ALL)

void printTest()
{
    printf("\n=========== PRINT TEST ===========\n");

    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    printf("Printing A before insertion. Expect:\nReceived:\n");
    printDictionary(stdout, A, "in");

    printf("Printing B before insertion. Expect:\nReceived:\n");
    printDictionary(stdout, B, "in");

    int a = 1, b_1 = 1, b_2 = 2, b_3 = 5, c = 10, d = 15, f = 1;

    insert(A, "b", &b_1);
    insert(A, "b", &b_2);
    insert(A, "f", &f);

    insert(B, "a", &a);
    insert(B, "b", &b_3);
    insert(B, "c", &c);
    insert(B, "d", &d);

    printf("Printing A after insertion. Expect:\nb 1\nb 2\nf 1\nReceived:\n");
    printDictionary(stdout, A, "in");

    printf("Printing B after insertion. Expect:\na 1\nb 5\nc 10\nd 15\nReceived:\n");
    printDictionary(stdout, B, "in");

    delete (A, "b");
    delete (A, "f");

    delete (B, "c");
    delete (B, "b");

    printf("Printing A after deletion. Expect:\nb 2\nReceived:\n");
    printDictionary(stdout, A, "in");

    printf("Printing B after deletion. Expect:\na 1\nd 15\nReceived:\n");
    printDictionary(stdout, B, "in");

    freeDictionary(&A);
    freeDictionary(&B);
}

#ifndef DICT_ALL
int main()
{
    printTest();
}
#endif

#endif

#ifdef DICT_ALL

int main()
{
    ctorDtorTest();
    getSizeTest();
    getUniqueTest();
    lookupTest();
    insertTest();
    deleteTest();
    makeEmptyTest();
    beginForwardTest();
    beginReverseTest();
    currentKeyTest();
    currentValTest();
    nextTest();
    prevTest();
    printTest();
    return 0;
}

#endif