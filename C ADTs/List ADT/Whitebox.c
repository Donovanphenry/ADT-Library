/****************************************************************************************
* Name: Donovan Henry
* CruzID: dphenry
* Assignment: PA1
*  ListClient.c
*  Test client for List ADT
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include <string.h>

#define LIST_CLIENT

#if defined(LIST_DELETE) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    deleteTest(argc, argv);
    return 0;
}
#endif

void deleteTest(int argc, char *argv[])
{
    printf("\n============ DELETE ==============\n");
    List A = newList();

    append(A, 5);
    moveBack(A);
    printf("Delete | After first insertion, called moveBack, calling get, expect 5: %d\n\n", get(A));

    prepend(A, 10);
    append(A, 20);

    printf("Delete | Prepended 10 & Appended 20\n\n");

    delete (A);
    printf("Delete | After deletion, calling index, expect -1: %d\n\n", index(A));
    printf("Delete | After deletion, calling front, expect 10: %d\n\n", front(A));
    printf("Delete | After deletion, calling back, expect 20: %d\n\n", back(A));

    moveFront(A);
    delete (A);
    printf("Delete | After moveFront call & deletion, calling index, still expect -1: %d\n\n", index(A));
    printf("Delete | After deletion, calling front, expect 20: %d\n\n", front(A));
    printf("Delete | After deletion, calling back, expect 20: %d\n\n", back(A));

    append(A, 25);
    moveBack(A);
    delete (A);
    printf("Delete | After moveBack call & deletion, calling index, still expect -1: %d\n\n", index(A));
    printf("Delete | After deletion, calling front, expect 20: %d\n\n", front(A));
    printf("Delete | After deletion, calling back, expect 20: %d\n\n", back(A));

    freeList(&A);
}

#endif

#if defined(LIST_DELETEBACK) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    deleteBackTest(argc, argv);
    return 0;
}
#endif

void deleteBackTest(int argc, char *argv[])
{
    printf("\n============ DELETE BACK ==============\n");
    List A = newList();

    append(A, 5);
    moveBack(A);
    printf("DeleteBack | After first insertion, called moveBack, calling get, expect 5: %d\n\n", get(A));

    prepend(A, 10);
    append(A, 20);

    printf("DeleteBack | Appended 10 & 20\n\n");

    deleteBack(A);
    printf("DeleteBack | After deletion, calling get, expect 5: %d\n\n", get(A));
    printf("DeleteBack | After deletion, calling front, expect 10: %d\n\n", front(A));
    printf("DeleteBack | After deletion, calling back, expect 5: %d\n\n", back(A));

    deleteBack(A);
    printf("DeleteBack | After deletion, calling get, still expect -1: %d\n\n", index(A));
    printf("DeleteBack | After deletion, calling front, expect 10: %d\n\n", front(A));
    printf("DeleteBack | After deletion, calling back, expect 10: %d\n\n", back(A));

    freeList(&A);
}

#endif

#if defined(LIST_DELETEFRONT) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    deleteFrontTest(argc, argv);
    return 0;
}
#endif

void deleteFrontTest(int argc, char *argv[])
{
    printf("\n============ DELETE FRONT ==============\n");
    List A = newList();

    append(A, 5);
    moveFront(A);
    printf("DeleteFront | After first insertion, set index of A to 0, calling get, expect 5: %d\n\n", get(A));

    prepend(A, 10);
    append(A, 20);

    printf("DeleteFront | Appended 10 & 20\n\n");

    deleteFront(A);
    printf("DeleteFront | After deletion, calling get, expect 5: %d\n\n", get(A));
    printf("DeleteFront | After deletion, calling front, expect 5: %d\n\n", front(A));
    printf("DeleteFront | After deletion, calling back, expect 20: %d\n\n", back(A));

    deleteFront(A);
    printf("DeleteFront | After deletion, calling get, still expect -1: %d\n\n", index(A));
    printf("DeleteFront | After deletion, calling front, expect 20: %d\n\n", front(A));
    printf("DeleteFront | After deletion, calling back, expect 20: %d\n\n", back(A));

    freeList(&A);
}

#endif

#if defined(LIST_INSERTAFTER) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    insertAfterTest(argc, argv);
    return 0;
}
#endif

void insertAfterTest(int argc, char *argv[])
{
    printf("\n============ INSERT AFTER ==============\n");
    List A = newList();

    append(A, 5);
    moveFront(A);
    printf("InsertAfter | After first insertion, calling get, expect 5: %d\n\n", get(A));

    insertAfter(A, 10);
    printf("InsertAfter | After second insertion, calling get, still expect 5: %d\n\n", get(A));
    printf("InsertAfter | After second insertion, calling front, expect 5: %d\n\n", front(A));
    printf("InsertAfter | After second insertion, calling back, expect 10: %d\n\n", back(A));

    freeList(&A);
}

#endif

#if defined(LIST_INSERTBEFORE) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    insertBeforeTest(argc, argv);
    return 0;
}
#endif

void insertBeforeTest(int argc, char *argv[])
{
    printf("\n============ INSERT BEFORE ==============\n");
    List A = newList();

    append(A, 5);
    moveFront(A);
    printf("InsertBefore | After first insertion, calling get, expect 5: %d\n\n", get(A));

    insertBefore(A, 10);
    printf("InsertBefore | After second insertion, calling get, still expect 5: %d\n\n", get(A));
    printf("InsertBefore | After second insertion, calling front, expect 10: %d\n\n", front(A));
    printf("InsertBefore | After second insertion, calling back, expect 5: %d\n\n", back(A));

    freeList(&A);
}

#endif

#if defined(LIST_APPEND) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    appendTest(argc, argv);
    return 0;
}
#endif

void appendTest(int argc, char *argv[])
{
    printf("\n============ APPEND ==============\n");

    List A = newList();

    append(A, 5);
    printf("Append | After first insertion, calling back, expect 5: %d\n\n", back(A));

    append(A, 10);
    moveBack(A);
    printf("Append | After second insertion calling moveBack, back, expect 10: %d\n\n", back(A));
    printf("Append | After second insertion calling moveBack, get, expect 10: %d\n\n", get(A));
    printf("Append | After second insertion calling moveBack, front, expect 5: %d\n\n", front(A));

    append(A, 20);
    printf("Append | After third insertion calling back, expect 20: %d\n\n", back(A));
    printf("Append | After third insertion calling get, expect 10: %d\n\n", get(A));
    printf("Append | After third insertion calling front, expect 5: %d\n\n", front(A));

    freeList(&A);
}

#endif

#if defined(LIST_PREPEND) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    prependTest(argc, argv);
    return 0;
}
#endif

void prependTest(int argc, char *argv[])
{
    printf("\n============ PREPEND ==============\n");

    List A = newList();

    prepend(A, 5);
    printf("Prepend | After first insertion, calling front, expect 5: %d\n\n", front(A));
    printf("Prepend | After first insertion, calling back, expect 5: %d\n\n", back(A));

    prepend(A, 10);
    moveFront(A);
    printf("Prepend | After second insertion calling moveFront, back, expect 5: %d\n\n", back(A));
    printf("Prepend | After second insertion calling moveFront, get, expect 10: %d\n\n", get(A));
    printf("Prepend | After second insertion calling moveFront, front, expect 10: %d\n\n", front(A));

    prepend(A, 20);
    printf("Prepend | After third insertion calling back, expect 5: %d\n\n", back(A));
    printf("Prepend | After third insertion calling get, expect 10: %d\n\n", get(A));
    printf("Prepend | After third insertion calling front, expect 20: %d\n\n", front(A));

    freeList(&A);
}

#endif

#if defined(LIST_MOVENEXT) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    moveNextTest(argc, argv);
    return 0;
}
#endif

void moveNextTest(int argc, char *argv[])
{
    printf("\n============ MOVENEXT ==============\n");
    List A = newList();

    for (int i = 0; i <= 2; i++)
    {
        append(A, i);
    }

    printf("Executing while-loop to traverse list using moveNext, expect 0 -> 1 -> 2 -> Null\n");

    for (moveFront(A); index(A) != -1; moveNext(A))
    {
        printf("%d -> ", get(A));
    }

    printf("Null");

    freeList(&A);
}

#endif

#if defined(LIST_MOVEPREV) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    movePrevTest(argc, argv);
    return 0;
}
#endif

void movePrevTest(int argc, char *argv[])
{
    printf("\n============ MOVEPREV ==============\n");

    List A = newList();

    for (int i = 0; i <= 2; i++)
    {
        append(A, i);
    }

    printf("Executing while-loop to traverse list using movePrev, expect 2 -> 1 -> 0 -> Null\n");

    for (moveBack(A); index(A) != -1; movePrev(A))
    {
        printf("%d -> ", get(A));
    }

    printf("Null");

    freeList(&A);
}

#endif

#if defined(LIST_MOVEBACK) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    moveBackTest(argc, argv);
    return 0;
}
#endif

void moveBackTest(int argc, char *argv[])
{
    printf("\n============ MOVEBACK ==============\n");

    List A = newList();

    for (int i = 0; i <= 2; i++)
    {
        append(A, i);
    }

    printf("MoveBack | Pre-moveBack A, expect -1: %d\n\n", index(A));

    moveBack(A);
    printf("MoveBack | Post-moveBack A, calling get, expect 2: %d\n\n", get(A));
    printf("MoveBack | Post-moveBack A, calling front, expect 0: %d\n\n", front(A));
    printf("MoveBack | Post-moveBack A, calling front, expect 2: %d\n\n", back(A));

    freeList(&A);
}

#endif

#if defined(LIST_MOVEFRONT) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    moveFrontTest(argc, argv);
    return 0;
}
#endif

void moveFrontTest(int argc, char *argv[])
{
    printf("\n============ MOVEFRONT ==============\n");

    List A = newList();

    for (int i = 0; i <= 2; i++)
    {
        append(A, i);
    }

    printf("MoveFront | Pre-moveFront A, expect -1: %d\n\n", index(A));

    moveFront(A);
    printf("MoveFront | Post-moveFront A, calling get, expect 0: %d\n\n", get(A));
    printf("MoveFront | Post-moveFront A, calling front, expect 0: %d\n\n", front(A));
    printf("MoveFront | Post-moveFront A, calling front, expect 2: %d\n\n", back(A));

    freeList(&A);
}

#endif

#if defined(LIST_SET) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    setTest(argc, argv);
    return 0;
}
#endif

void setTest(int argc, char *argv[])
{
    printf("\n============ SET ==============\n");

    List A = newList();

    for (int i = 0; i <= 2; i++)
    {
        append(A, i);
    }

    moveFront(A);

    printf("Set | Pre-set A, expect 0: %d\n\n", get(A));

    set(A, 25);
    printf("Set | Post-set A, expect 25: %d\n\n", get(A));

    printf("Set | Printing A, expect 25 -> 1 -> 2 -> Null\n");

    for (moveFront(A); index(A) != -1; moveNext(A))
    {
        printf("%d -> ", get(A));
    }

    printf("Null\n");

    freeList(&A);
}

#endif

#if defined(LIST_CLEAR) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    clearTest(argc, argv);
    return 0;
}
#endif

void clearTest(int argc, char *argv[])
{
    printf("\n============ CLEAR ==============\n");

    List A = newList();

    for (int i = 0; i <= 2; i++)
    {
        append(A, i);
    }

    printf("Clear | Printing pre-copy: Expect 0 -> 1 -> 2 -> Null\n\n");

    for (moveFront(A); index(A) != -1; moveNext(A))
    {
        printf("%d -> ", get(A));
    }

    printf("Null\n\n");

    clear(A);

    freeList(&A);
}

#endif

#if defined(LIST_EQUALS_AND_COPY) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    equalsAndCopyTest(argc, argv);
    return 0;
}
#endif

void equalsAndCopyTest(int argc, char *argv[])
{
    printf("\n============ EQUALS AND COPY ==============\n");

    List A = newList();
    List B = newList();

    // printf("Pre-insertions expect EXIT_FAILURE: %d", back(A));

    for (int i = 0; i <= 2; i++)
    {
        append(A, i);
        append(B, i + 1);
    }

    printf("Equals | Post-insertion on B with diff values, expect 0: %d\n\n", equals(A, B));

    clear(B);

    for (int i = 0; i <= 2; i++)
    {
        append(B, i);
    }

    printf("Equals | Post-clear and re-insertion on B with same values, expect 1: %d\n\n", equals(A, B));

    clear(B);
    freeList(&B);

    B = copyList(A);

    printf("Equals | Post-clear and copy, expect 1: %d\n\n", equals(A, B));

    freeList(&A);
    freeList(&B);
}

#endif

#if defined(LIST_BACK) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    backTest(argc, argv);
    return 0;
}
#endif

void backTest(int argc, char *argv[])
{
    printf("\n============ BACK ==============\n");

    List A = newList();

    // printf("Pre-insertions expect EXIT_FAILURE: %d", back(A));

    for (int i = 0; i <= 2; i++)
    {
        append(A, i);
    }

    printf("Back | Post-insertion & pre-delete Expect 2: %d\n\n", back(A));
    deleteBack(A);
    printf("Back | Post-delete_1 Expect 1: %d\n\n", back(A));

    printf("Back | pre-append Expect 1: %d\n\n", back(A));
    append(A, 10);
    printf("Back | Post-append Expect 10: %d\n\n", back(A));

    printf("Back | Pre-clear Expect 10: %d\n\n", back(A));

    clear(A);
    // printf("Back | Post-clear, calling back Expect stderr:\n\n");
    // printf("%d\n\n", back(A));

    freeList(&A);
}

#endif

#if defined(LIST_FRONT) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    frontTest(argc, argv);
    return 0;
}
#endif

void frontTest(int argc, char *argv[])
{
    printf("\n============ FRONT TEST ==============\n");

    List A = newList();

    for (int i = 0; i <= 2; i++)
    {
        append(A, i);
    }

    printf("Front | Post-insertion & pre-delete Expect 0: %d\n\n", front(A));
    deleteFront(A);
    printf("Front | Post-delete_1 Expect 1: %d\n\n", front(A));

    prepend(A, 10);
    printf("Front | Post-prepend Expect 10: %d\n\n", front(A));

    clear(A);
    printf("Front | Post-clear, calling length Expect 0: %d\n\n", length(A));

    // printf("Front | Post-clear call on front, expect EXIT_FAILURE\n\n");
    // printf("%d\n", front(A));

    freeList(&A);
}

#endif

#if defined(LIST_GET) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    getTest(argc, argv);
    return 0;
}
#endif

void getTest(int argc, char *argv[])
{
    printf("\n============ GET ==============\n");

    List A = newList();

    for (int i = 0; i <= 2; i++)
    {
        append(A, i);
    }

    printf("Get | Before moveBack call, Expect -1: %d\n\n", index(A));
    moveBack(A);
    printf("Get | After moveBack call, Expect 2: %d\n\n", get(A));

    // clear(A);
    // printf("Get | Post-clear Expect stderr\n");
    // printf("%d\n", get(A));

    clear(A);
    freeList(&A);
}

#endif

#ifdef LIST_ALL

int main(int argc, char *argv[])
{
    deleteTest(argc, argv);
    deleteFrontTest(argc, argv);
    deleteBackTest(argc, argv);
    insertBeforeTest(argc, argv);
    insertAfterTest(argc, argv);
    appendTest(argc, argv);
    prependTest(argc, argv);
    moveFrontTest(argc, argv);
    moveBackTest(argc, argv);
    movePrevTest(argc, argv);
    moveNextTest(argc, argv);
    setTest(argc, argv);
    clearTest(argc, argv);
    equalsAndCopyTest(argc, argv);
    backTest(argc, argv);
    frontTest(argc, argv);
    getTest(argc, argv);
    return 0;
}

#endif

#if defined(LIST_CLIENT)
/****************************************************************************************
*  ListClient.c
*  Test client for List ADT
*****************************************************************************************/

int main(int argc, char *argv[])
{

    List A = newList();
    List B = newList();
    List C = NULL;
    int i;

    for (i = 1; i <= 20; i++)
    {
        append(A, i);
        prepend(B, i);
    }

    printList(stdout, A);
    printf("\n");
    printList(stdout, B);
    printf("\n");

    for (moveFront(A); index(A) >= 0; moveNext(A))
    {
        printf("%d ", get(A));
    }
    printf("\n");
    for (moveBack(B); index(B) >= 0; movePrev(B))
    {
        printf("%d ", get(B));
    }
    printf("\n");

    C = copyList(A);
    printf("%s\n", equals(A, B) ? "true" : "false");
    printf("%s\n", equals(B, C) ? "true" : "false");
    printf("%s\n", equals(C, A) ? "true" : "false");

    moveFront(A);
    for (i = 0; i < 5; i++)
        moveNext(A);     // at index 5
    insertBefore(A, -1); // at index 6
    for (i = 0; i < 9; i++)
        moveNext(A); // at index 15
    insertAfter(A, -2);
    for (i = 0; i < 5; i++)
        movePrev(A); // at index 10
    delete (A);
    printList(stdout, A);
    printf("\n");
    printf("%d\n", length(A));
    clear(A);
    printf("%d\n", length(A));

    freeList(&A);
    freeList(&B);
    freeList(&C);

    return (0);
}

/*
Output of this program:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
false
false
true
1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
21
0
*/

#endif