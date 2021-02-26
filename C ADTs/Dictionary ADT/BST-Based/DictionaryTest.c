#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"

#define DICT_ALL

#if defined(DICT_CTOR_DTOR) || defined(DICT_ALL)

#ifndef DICT_ALL
int main()
{
    ctorDtorTest();
}
#endif

void ctorDtorTest()
{
    printf("\n=========== CTOR_DTOR TEST ===========\n");

    printf("Constructing and freeing unique and non-unique dictionary. Expect no mem leak or seg fault\n");

    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    freeDictionary(&A);
    freeDictionary(&B);
}

#endif

#if defined(DICT_SIZE) || defined(DICT_ALL)

#ifndef DICT_ALL
int main()
{
    getSizeTest();
}
#endif

void getSizeTest()
{
    printf("\n=========== GET_SIZE TEST ===========\n");

    printf("Constructing unique and non-unique dict then calling getSize. Expect: 0 0. Received: ");
    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);
    printf("%d %d", size(A), size(B));

    // insert(A, "b", 1);
    // insert(A, "b", 1);
    // insert(A, "f", 1);

    // insert(B, "a", 1);
    // insert(B, "b", 1);
    // insert(B, "c", 1);
    // insert(B, "d", 1);

    // printf("Calling size() of A. Expect: 3. Received: %d\n", size(A));
    // printf("Calling size() of B. Expect: 4. Received: %d\n", size(B));

    // delete (A, "b");
    // delete (B, "b");

    // printf("Calling size() of A. Expect: 2. Received: %d\n", size(A));
    // printf("Calling size() of B. Expect: 3. Received: %d\n", size(B));

    // delete (A, "b");
    // delete (B, "a");
    // delete (A, "f");
    // delete (B, "c");

    // printf("Calling size() of A. Expect: 0. Received: %d\n", size(A));
    // printf("Calling size() of B. Expect: 1. Received: %d\n", size(B));

    // delete (B, "d");

    // printf("Calling size() of A. Expect: 0. Received: %d\n", size(A));
    // printf("Calling size() of B. Expect: 0. Received: %d\n", size(B));

    freeDictionary(&A);
    freeDictionary(&B);
}

#endif

#if defined(DICT_GETUNIQUE) || defined(DICT_ALL)

#ifndef DICT_ALL
int main()
{
    getUniqueTest();
}
#endif

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

#endif

#if defined(DICT_LOOKUP) || defined(DICT_ALL)

void lookupTest()
{
    printf("\n=========== LOOKUP TEST ===========\n");

    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    insert(A, "b", 1);
    insert(A, "b", 2);
    insert(A, "f", 1);

    printf("Shut the fuck up bitch\n");
    insert(B, "a", 1);
    insert(B, "b", 5);
    insert(B, "c", 10);
    insert(B, "d", 15);

    printf("Lookup on A with (k, v) = (b, 1). Expect: 1. Received: " VAL_FORMAT "\n", lookup(A, "b"));
    delete (A, "b");
    printf("Lookup on A after deletion with (k, v) = (b, 2). Expect: 2. Received: " VAL_FORMAT "\n", lookup(A, "b"));

    printf("Lookup on B with (k, v) = (a, 1). Expect: 1. Received: " VAL_FORMAT "\n", lookup(B, "a"));
    printf("Lookup on B with (k, v) = (b, 5). Expect: 5. Received: " VAL_FORMAT "\n", lookup(B, "b"));
    delete (B, "a");
    printf("Lookup on B with (k, v) = (a, 1). Expect: %p. Received: " VAL_FORMAT "\n", NULL, lookup(B, "a"));

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

#ifndef DICT_ALL
int main()
{
    insertTest();
}
#endif

void insertTest()
{
    printf("\n=========== INSERT TEST ===========\n");

    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    printf("Printing A before insertion. Expect:\nReceived:\n");
    printDictionary(stdout, A);

    printf("Printing B before insertion. Expect:\nReceived:\n");
    printDictionary(stdout, B);

    insert(A, "b", 1);
    insert(A, "b", 2);
    insert(A, "f", 1);

    insert(B, "c", 10);
    insert(B, "a", 1);
    insert(B, "b", 5);
    insert(B, "d", 15);

    printf("Printing A after insertion. Expect:\nb 1\nb 2\nf 1\nReceived:\n");
    printDictionary(stdout, A);

    printf("Printing B after insertion. Expect:\na 1\nb 5\nc 10\nd 15\nReceived:\n");
    printDictionary(stdout, B);

    freeDictionary(&A);
    freeDictionary(&B);
}
#endif

#if defined(DICT_DELETE) || defined(DICT_ALL)

#ifndef DICT_ALL
int main()
{
    deleteTest();
}
#endif

void deleteTest()
{
    printf("\n=========== DELETE TEST ===========\n");

    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    printf("Printing A before insertion. Expect:\nReceived:\n");
    printDictionary(stdout, A);

    printf("Printing B before insertion. Expect:\nReceived:\n");
    printDictionary(stdout, B);

    insert(A, "b", 1);
    insert(A, "b", 2);
    insert(A, "f", 1);

    insert(B, "c", 10);
    insert(B, "a", 1);
    insert(B, "b", 5);
    insert(B, "d", 15);

    printf("Printing A after insertion. Expect:\nb 1\nb 2\nf 1\nReceived:\n");
    printDictionary(stdout, A);

    printf("Printing B after insertion. Expect:\na 1\nb 5\nc 10\nd 15\nReceived:\n");
    printDictionary(stdout, B);

    delete (A, "b");
    delete (A, "f");

    delete (B, "c");
    delete (B, "b");

    printf("Printing A after deletion. Expect:\nb 2\nReceived:\n");
    printDictionary(stdout, A);

    printf("Printing B after deletion. Expect:\na 1\nd 15\nReceived:\n");
    printDictionary(stdout, B);

    freeDictionary(&A);
    freeDictionary(&B);
}

#endif

#if defined(DICT_MAKE_EMPTY) || defined(DICT_ALL)

#ifndef DICT_ALL
int main()
{
    makeEmptyTest();
}
#endif

void makeEmptyTest()
{
    printf("\n=========== MAKE_EMPTY TEST ===========\n");

    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    printf("Printing A before insertion. Expect:\nReceived:\n");
    printDictionary(stdout, A);

    printf("Printing B before insertion. Expect:\nReceived:\n");
    printDictionary(stdout, B);

    printf("Calling make empty on empty dictionaries. Expect no errors.\n");
    makeEmpty(A);
    makeEmpty(B);

    insert(A, "b", 1);
    insert(A, "b", 2);
    insert(A, "f", 1);

    insert(B, "c", 10);
    insert(B, "a", 1);
    insert(B, "b", 5);
    insert(B, "d", 15);

    printf("Printing A after insertion. Expect:\nb 1\nb 2\nf 1\nReceived:\n");
    printDictionary(stdout, A);

    printf("Printing B after insertion. Expect:\na 1\nb 5\nc 10\nd 15\nReceived:\n");
    printDictionary(stdout, B);

    makeEmpty(A);
    makeEmpty(B);

    printf("Printing A after makeEmpty. Expect:\nReceived:\n");
    printDictionary(stdout, A);

    printf("Printing B after makeEmpty. Expect:\nReceived:\n");
    printDictionary(stdout, B);

    freeDictionary(&A);
    freeDictionary(&B);
}

#endif

#if defined(DICT_BEGIN_FORWARD) || defined(DICT_ALL)

#ifndef DICT_ALL
int main()
{
    beginForwardTest();
}
#endif

void beginForwardTest()
{
    printf("\n=========== BEGIN_FORWARD TEST ===========\n");
    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    VAL_TYPE x = beginForward(A);
    VAL_TYPE y = beginForward(B);

    printf("BeginForward on non-unique dict. Expect: " VAL_FORMAT ". Received: " VAL_FORMAT "\n", VAL_UNDEF, x);
    printf("BeginForward on unique dict. Expect: " VAL_FORMAT ". Received: " VAL_FORMAT "\n", VAL_UNDEF, y);

    insert(A, "A", 10);
    insert(A, "B", 12);
    insert(A, "C", 103);

    insert(B, "C", 10);
    insert(B, "D", 120);
    insert(B, "E", 101);

    x = beginForward(A);
    y = beginForward(B);

    printf("BeginForward on non-unique dict. Expect: 10. Received: " VAL_FORMAT "\n", x);
    printf("BeginForward on unique dict. Expect: 10. Received: " VAL_FORMAT "\n", y);

    delete (A, "C");
    delete (A, "B");
    delete (A, "A");

    makeEmpty(B);

    x = beginForward(A);
    y = beginForward(B);

    printf("BeginForward on non-unique dict. Expect: " VAL_FORMAT ". Received: " VAL_FORMAT "\n", VAL_UNDEF, x);
    printf("BeginForward on unique dict. Expect: " VAL_FORMAT ". Received: " VAL_FORMAT "\n", VAL_UNDEF, y);

    freeDictionary(&A);
    freeDictionary(&B);
}

#endif

#if defined(DICT_BEGIN_REVERSE) || defined(DICT_ALL)

#ifndef DICT_ALL
int main()
{
    beginReverseTest();
}
#endif

void beginReverseTest()
{
    printf("\n=========== BEGIN_REVERSE TEST ===========\n");
    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    VAL_TYPE x = beginReverse(A);
    VAL_TYPE y = beginReverse(B);

    printf("BeginReverse on non-unique dict. Expect: " VAL_FORMAT ". Received: " VAL_FORMAT "\n", VAL_UNDEF, x);
    printf("BeginReverse on unique dict. Expect: " VAL_FORMAT ". Received: " VAL_FORMAT "\n", VAL_UNDEF, y);

    insert(A, "A", 10);
    insert(A, "B", 12);
    insert(A, "C", 103);

    insert(B, "C", 10);
    insert(B, "D", 120);
    insert(B, "E", 101);

    x = beginReverse(A);
    y = beginReverse(B);

    printf("BeginReverse on non-unique dict. Expect: 103. Received: " VAL_FORMAT "\n", x);
    printf("BeginReverse on unique dict. Expect: 101. Received: " VAL_FORMAT "\n", y);

    delete (A, "C");
    delete (A, "B");
    delete (A, "A");

    makeEmpty(B);

    x = beginReverse(A);
    y = beginReverse(B);

    printf("BeginReverse on non-unique dict. Expect: " VAL_FORMAT ". Received: " VAL_FORMAT "\n", VAL_UNDEF, x);
    printf("BeginReverse on unique dict. Expect: " VAL_FORMAT ". Received: " VAL_FORMAT "\n", VAL_UNDEF, y);

    freeDictionary(&A);
    freeDictionary(&B);
}

#endif

#if defined(DICT_CURRENT_KEY) || defined(DICT_ALL)

#ifndef DICT_ALL
int main()
{
    currentKeyTest();
}
#endif

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

    insert(A, "A", 10);
    insert(A, "B", 12);
    insert(A, "C", 103);

    insert(B, "C", 10);
    insert(B, "D", 120);
    insert(B, "E", 101);

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

#endif

#if defined(DICT_CURRENT_VAL) || defined(DICT_ALL)

#ifndef DICT_ALL
int main()
{
    currentValTest();
}
#endif

void currentValTest()
{
    printf("\n=========== CURRENT_VAL TEST ===========\n");
    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    beginForward(A);
    beginForward(B);
    VAL_TYPE x = currentVal(A);
    VAL_TYPE y = currentVal(B);

    printf("BeginForward on non-unique dict. Expect: " VAL_FORMAT ". Received: " VAL_FORMAT "\n", VAL_UNDEF, x);
    printf("BeginForward on unique dict. Expect: " VAL_FORMAT ". Received: " VAL_FORMAT "\n", VAL_UNDEF, y);

    beginReverse(A);
    beginReverse(B);
    x = currentVal(A);
    y = currentVal(B);

    printf("BeginForward on non-unique dict. Expect: " VAL_FORMAT ". Received: " VAL_FORMAT "\n", VAL_UNDEF, x);
    printf("BeginForward on unique dict. Expect: " VAL_FORMAT ". Received: " VAL_FORMAT "\n", VAL_UNDEF, y);

    insert(A, "A", 10);
    insert(A, "B", 12);
    insert(A, "C", 103);

    insert(B, "C", 10);
    insert(B, "D", 120);
    insert(B, "E", 101);

    beginForward(A);
    beginForward(B);
    x = currentVal(A);
    y = currentVal(B);

    printf("BeginForward on non-unique dict. Expect: 10. Received: " VAL_FORMAT "\n", x);
    printf("BeginForward on unique dict. Expect: 10. Received: " VAL_FORMAT "\n", y);

    beginReverse(A);
    beginReverse(B);
    x = currentVal(A);
    y = currentVal(B);

    printf("BeginReverse on non-unique dict. Expect: 103. Received: " VAL_FORMAT "\n", x);
    printf("BeginReverse on unique dict. Expect: 101. Received: " VAL_FORMAT "\n", y);

    delete (A, "C");
    delete (A, "B");
    delete (A, "A");

    makeEmpty(B);

    beginForward(A);
    beginForward(B);
    x = currentVal(A);
    y = currentVal(B);

    printf("BeginForward on non-unique dict. Expect: " VAL_FORMAT ". Received: " VAL_FORMAT "\n", VAL_UNDEF, x);
    printf("BeginForward on unique dict. Expect: " VAL_FORMAT ". Received: " VAL_FORMAT "\n", VAL_UNDEF, y);

    beginReverse(A);
    beginReverse(B);
    x = currentVal(A);
    y = currentVal(B);

    printf("BeginReverse on non-unique dict. Expect: " VAL_FORMAT ". Received: " VAL_FORMAT "\n", VAL_UNDEF, x);
    printf("BeginReverse on unique dict. Expect: " VAL_FORMAT ". Received: " VAL_FORMAT "\n", VAL_UNDEF, y);

    freeDictionary(&A);
    freeDictionary(&B);
}

#endif

#if defined(DICT_NEXT) || defined(DICT_ALL)

#ifndef DICT_ALL
int main()
{
    nextTest();
}
#endif

void nextTest()
{
    printf("\n=========== NEXT TEST ===========\n");

    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    printf("Printing A before insertion. Expect:\nReceived:");
    for (VAL_TYPE x = beginForward(A); currentVal(A) != VAL_UNDEF; x = next(A))
        printf(" (" KEY_FORMAT ", " VAL_FORMAT ")", currentKey(A), x);

    printf("\n");

    printf("Printing B before insertion. Expect:\nReceived:");
    for (VAL_TYPE x = beginForward(B); currentVal(B) != VAL_UNDEF; x = next(B))
        printf(" (" KEY_FORMAT ", " VAL_FORMAT ")", currentKey(B), x);

    printf("\n");

    insert(A, "b", 1);
    insert(A, "b", 2);
    insert(A, "f", 1);

    insert(B, "c", 10);
    insert(B, "a", 1);
    insert(B, "b", 5);
    insert(B, "d", 15);

    printf("Iterating through dictionary. Expect: (b, 1) (b, 2) (f, 1)\nReceived:");
    for (VAL_TYPE x = beginForward(A); currentVal(A) != VAL_UNDEF; x = next(A))
        printf(" (" KEY_FORMAT ", " VAL_FORMAT ")", currentKey(A), x);

    printf("\n");

    printf("Iterating through dictionary. Expect: (a, 1) (b, 5) (c, 10) (d, 15)\nReceived:");
    for (VAL_TYPE x = beginForward(B); currentVal(B) != VAL_UNDEF; x = next(B))
        printf(" (" KEY_FORMAT ", " VAL_FORMAT ")", currentKey(B), x);

    printf("\n");

    delete (A, "b");
    delete (A, "f");

    delete (B, "c");
    delete (B, "b");

    printf("Iterating through dictionary. Expect: (b, 2)\nReceived:");
    for (VAL_TYPE x = beginForward(A); currentVal(A) != VAL_UNDEF; x = next(A))
        printf(" (" KEY_FORMAT ", " VAL_FORMAT ")", currentKey(A), x);

    printf("\n");

    printf("Iterating through dictionary. Expect: (a, 1) (d, 15)\nReceived:");
    for (VAL_TYPE x = beginForward(B); currentVal(B) != VAL_UNDEF; x = next(B))
        printf(" (" KEY_FORMAT ", " VAL_FORMAT ")", currentKey(B), x);

    printf("\n");

    freeDictionary(&A);
    freeDictionary(&B);
}

#endif

#if defined(DICT_PREV) || defined(DICT_ALL)

void prevTest()
{
    printf("\n=========== PREV TEST ===========\n");

    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    printf("Printing A before insertion. Expect:\nReceived:");
    for (VAL_TYPE x = beginReverse(A); currentVal(A) != VAL_UNDEF; x = prev(A))
        printf(" (" KEY_FORMAT ", " VAL_FORMAT ")", currentKey(A), x);

    printf("\n");

    printf("Printing B before insertion. Expect:\nReceived:");
    for (VAL_TYPE x = beginReverse(B); currentVal(B) != VAL_UNDEF; x = prev(B))
        printf(" (" KEY_FORMAT ", " VAL_FORMAT ")", currentKey(B), x);

    printf("\n");

    insert(A, "b", 1);
    insert(A, "b", 2);
    insert(A, "f", 1);

    insert(B, "c", 10);
    insert(B, "a", 1);
    insert(B, "b", 5);
    insert(B, "d", 15);

    printf("Iterating through dictionary. Expect: (f, 1) (b, 2) (b, 1)\nReceived:");
    for (VAL_TYPE x = beginReverse(A); currentVal(A) != VAL_UNDEF; x = prev(A))
        printf(" (" KEY_FORMAT ", " VAL_FORMAT ")", currentKey(A), x);

    printf("\n");

    printf("Iterating through dictionary. Expect: (d, 15) (c, 10) (b, 5) (a, 1)\nReceived:");
    for (VAL_TYPE x = beginReverse(B); currentVal(B) != VAL_UNDEF; x = prev(B))
        printf(" (" KEY_FORMAT ", " VAL_FORMAT ")", currentKey(B), x);

    printf("\n");

    delete (A, "b");
    delete (A, "f");

    delete (B, "c");
    delete (B, "b");

    printf("Iterating through dictionary. Expect: (b, 2)\nReceived:");
    for (VAL_TYPE x = beginReverse(A); currentVal(A) != VAL_UNDEF; x = prev(A))
        printf(" (" KEY_FORMAT ", " VAL_FORMAT ")", currentKey(A), x);

    printf("\n");

    printf("Iterating through dictionary. Expect: (d, 15) (a, 1)\nReceived:");
    for (VAL_TYPE x = beginReverse(B); currentVal(B) != VAL_UNDEF; x = prev(B))
        printf(" (" KEY_FORMAT ", " VAL_FORMAT ")", currentKey(B), x);

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

#ifndef DICT_ALL
int main()
{
    printTest();
}
#endif

void printTest()
{
    printf("\n=========== PRINT TEST ===========\n");

    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    printf("Printing A before insertion. Expect:\nReceived:\n");
    printDictionary(stdout, A);

    printf("Printing B before insertion. Expect:\nReceived:\n");
    printDictionary(stdout, B);

    insert(A, "b", 1);
    insert(A, "b", 2);
    insert(A, "f", 1);

    insert(B, "c", 10);
    insert(B, "a", 1);
    insert(B, "b", 5);
    insert(B, "d", 15);

    printf("Printing A after insertion. Expect:\nb 1\nb 2\nf 1\nReceived:\n");
    printDictionary(stdout, A);

    printf("Printing B after insertion. Expect:\na 1\nb 5\nc 10\nd 15\nReceived:\n");
    printDictionary(stdout, B);

    delete (A, "b");
    delete (A, "f");

    delete (B, "c");
    delete (B, "b");

    printf("Printing A after deletion. Expect:\nb 2\nReceived:\n");
    printDictionary(stdout, A);

    printf("Printing B after deletion. Expect:\na 1\nd 15\nReceived:\n");
    printDictionary(stdout, B);

    freeDictionary(&A);
    freeDictionary(&B);
}

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