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

using std::cout;
using std::endl;

#define LIST_MODEL

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
    List A = List();

    A.insertAfter(5);
    printf("InsertAfter | After first insertion, printing list, expect (5): ");
    cout << A << endl;

    A.insertAfter(10);
    cout << "InsertAfter | After second insertion, printing list, expect (10, 5): " << A << endl;
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
    List A = List();

    A.insertBefore(5);
    printf("InsertBefore | Before first insertion, printing list, expect (5): ");
    cout << A << endl;

    A.insertBefore(10);
    cout << "InsertBefore | After second insertion, printing list, expect (5, 10): " << A << endl;
}

#endif

#if defined(LIST_PEEKNEXT) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    peekNextTest(argc, argv);
    return 0;
}
#endif

void peekNextTest(int argc, char *argv[])
{
    printf("\n============ PEEK_NEXT ==============\n");

    List A = List();

    for (int i = 0; i <= 2; i++)
    {
        A.insertBefore(i);
    }

    A.moveBack();
    A.movePrev();
    printf("Get | After moveBack then movePrev call, Expect 2: %d\n", A.peekNext());

    A.moveFront();
    printf("Get | After moveBack call, Expect 0: %d\n", A.peekNext());
}

#endif

#if defined(LIST_PEEKPREV) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    peekPrevTest(argc, argv);
    return 0;
}
#endif

void peekPrevTest(int argc, char *argv[])
{
    printf("\n============ PEEK_PREV ==============\n");

    List A = List();

    for (int i = 0; i <= 2; i++)
    {
        A.insertBefore(i);
    }

    A.moveBack();
    printf("Get | After moveBack call, Expect %d: %d\n", 2, A.peekPrev());

    A.moveFront();
    A.moveNext();
    printf("Get | After moveBack call, Expect 0: %d\n", A.peekPrev());
}

#endif

#if defined(LIST_ERASEAFTER) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    eraseAfterTest(argc, argv);
    return 0;
}
#endif

void eraseAfterTest(int argc, char *argv[])
{
    printf("\n============ DELETE FRONT ==============\n");
    List A = List();

    A.insertBefore(5);
    A.moveBack();
    A.insertBefore(10);
    A.insertAfter(20);

    A.eraseAfter();
    printf("EraseAfter | Inserted 5 10 | 20. After deletion, print list, expect: (5, 10). Received: ");
    cout << A;

    A.moveFront();
    A.eraseAfter();
    printf("\nEraseAfter | After deletion, printing list, expect (10). Received: ");
    cout << A << endl;
}

#endif

#if defined(LIST_ERASEBEFORE) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    eraseBeforeTest(argc, argv);
    return 0;
}
#endif

void eraseBeforeTest(int argc, char *argv[])
{
    printf("\n============ ERASE BEFORE ==============\n");
    List A = List();

    A.insertBefore(5);
    A.moveBack();
    A.insertBefore(10);
    A.insertAfter(20);

    A.eraseBefore();
    printf("EraseBefore | Inserted 5 10 | 20. After deletion, print list, expect: (5, 20). Received: ");
    cout << A;

    A.eraseBefore();
    printf("\nEraseBefore | After deletion, printing list, expect (20). Received: ");
    cout << A << endl;
}

#endif

#if defined(LIST_SIZE) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    sizeTest(argc, argv);
    return 0;
}
#endif

void sizeTest(int argc, char *argv[])
{
    printf("\n============ SIZE ==============\n");

    List A = List();

    cout << "Size | Printing A.size() before adding an element. Expect 0: Received: " << A.size() << endl;

    A.insertBefore(1);
    cout << "Size | Printing A.size() after adding an element. Expect 1: Received: " << A.size() << endl;

    A.insertBefore(1);
    cout << "Size | Printing A.size() after adding another element. Expect 2: Received: " << A.size() << endl;

    A.eraseBefore();
    cout << "Size | Printing A.size() after erasing an element. Expect 1: Received: " << A.size() << endl;

    A.eraseBefore();
    cout << "Size | Printing A.size() after erasing another element. Expect 0: Received: " << A.size() << endl;
}

#endif

#if defined(LIST_POSITION) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    positionTest(argc, argv);
    return 0;
}
#endif

void positionTest(int argc, char *argv[])
{
    printf("\n============ POSITION ==============\n");

    List A = List();

    cout << "Position | Printing A.position() before adding an element. Expect 0: Received: " << A.position() << endl;

    A.insertBefore(1);
    cout << "Position | Printing A.position() after adding an element. Expect 1: Received: " << A.position() << endl;

    A.insertBefore(1);
    cout << "Position | Printing A.position() after adding another element. Expect 2: Received: " << A.position() << endl;

    A.eraseBefore();
    cout << "Position | Printing A.position() after erasing an element. Expect 1: Received: " << A.position() << endl;

    A.insertAfter(1);
    cout << "Position | Printing A.position() after adding another element behind cursor. Expect 1: Received: " << A.position() << endl;

    A.eraseBefore();
    cout << "Position | Printing A.position() after erasing another element. Expect 0: Received: " << A.position() << endl;
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

    List A = List();

    cout << "MoveBack | Iteratively adding elements and calling move back, printing. Expect: 0 1 2. Received:";

    for (int i = 0; i <= 2; i++)
    {
        A.insertAfter(i);
        A.moveBack();
        cout << " " << A.peekPrev();
    }

    cout << "\nMoveBack | Calling moveBack twice and outputting value. Expect: 2 2. Received: ";
    A.moveBack();
    cout << A.peekPrev() << " ";
    A.moveBack();
    cout << A.peekPrev() << endl;
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

    List A = List();

    cout << "MoveFront | Iteratively adding elements and printing. Expect: 0 1 2. Received:";

    for (int i = 0; i <= 2; i++)
    {
        A.insertAfter(i);
        cout << " " << A.peekNext();
    }

    cout << "\nMoveFront | Calling moveFront twice and outputting value. Expect: 2 2. Received: ";
    A.moveFront();
    cout << A.peekNext() << " ";
    A.moveFront();
    cout << A.peekNext() << endl;
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
    List A = List();

    for (int i = 0; i <= 2; i++)
    {
        A.insertBefore(i);
    }

    printf("Executing while-loop to traverse list using moveNext, expect: 0 -> 1 -> 2 -> Null. Printining Received: ");

    for (A.moveFront(); A.position() < A.size(); A.moveNext())
    {
        printf("%d -> ", A.peekNext());
    }

    printf("Null\n");
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

    List A = List();

    for (int i = 0; i <= 2; i++)
    {
        A.insertBefore(i);
    }

    printf("Executing while-loop to traverse list using movePrev, expect: 2 1 0. Printing Received:");

    for (A.moveBack(); A.position() > 0; A.movePrev())
    {
        printf(" %d", A.peekPrev());
    }

    cout << endl;
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

    List A = List();

    for (int i = 0; i <= 2; i++)
    {
        A.insertBefore(i);
    }

    printf("Clear | Printing pre-clear: Expect 0 -> 1 -> 2 -> Null. Received: ");

    for (A.moveFront(); A.position() < A.size(); A.moveNext())
    {
        printf("%d -> ", A.peekNext());
    }

    printf("Null\n");

    A.clear();

    printf("Clear | Printing post-clear: Expect: Null. Received: ");

    for (A.moveFront(); A.position() < A.size(); A.moveNext())
    {
        printf("%d -> ", A.peekNext());
    }

    printf("Null\n");
}

#endif

#if defined(LIST_EQUALS_COPYCTOR_AND_ASSIGNOP) || defined(LIST_ALL)

void equalsCopyAndAssignOpTest(int argc, char *argv[]);

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    equalsCopyAndAssignOpTest(argc, argv);
    return 0;
}
#endif

void equalsCopyAndAssignOpTest(int argc, char *argv[])
{
    printf("\n============ EQUALS, COPY_CTOR AND ASSIGN_OP_OVERLOAD ==============\n");

    List A;
    List B = List();

    for (int i = 0; i <= 2; i++)
    {
        A.insertBefore(i);
        B.insertBefore(i + 1);
    }

    printf("Equals | Post-insertion on B with diff values, expect: 0. Received: %d\n", A.equals(B));

    List C = B;

    printf("Equals | Called copy-constructor to initialize C with B, calling equals, expect: 1. Received: %d\n", C.equals(B));

    B.clear();

    for (int i = 0; i <= 2; i++)
    {
        B.insertBefore(i);
    }

    printf("Equals | Post-clear and re-insertion on B with same values, expect: 1. Received: %d\n", A.equals(B));

    B.clear();

    B = A;

    printf("Equals | Post-clear and copy using assgin operator, expect: 1. Received: %d\n", A.equals(B));
}

#endif

#if defined(LIST_ISEMPTY) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    isEmptyTest(argc, argv);
    return 0;
}
#endif

void isEmptyTest(int argc, char *argv[])
{
    printf("\n============ ISEMPTY ==============\n");

    List A = List();

    cout << "IsEmpty | Printing A.isEmpty() before adding an element. Expect 1: Received: " << A.isEmpty() << endl;

    A.insertBefore(1);
    cout << "IsEmpty | Printing A.isEmpty() after adding an element. Expect 0: Received: " << A.isEmpty() << endl;

    A.eraseBefore();
    cout << "IsEmpty | Printing A.isEmpty() after erasing an element. Expect 1: Received: " << A.isEmpty() << endl;
}

#endif

#if defined(LIST_FINDNEXT) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    findNextTest(argc, argv);
    return 0;
}
#endif

void findNextTest(int argc, char *argv[])
{
    printf("\n============ FINDNEXT ==============\n");

    List A = List();

    for (int i = 0; i <= 2; i++)
    {
        A.insertBefore(i);
    }

    A.moveFront();
    A.moveNext();

    cout << "FindNext | Moving cursor to middle, searching for 0, then for 2 and finally for 3. Expect: -1 3 -1. Received: ";
    cout << A.findNext(0) << " ";
    A.moveFront();
    A.moveNext();
    cout << A.findNext(2) << " ";
    A.moveFront();
    A.moveNext();
    cout << A.findNext(3) << endl;
}

#endif

#if defined(LIST_FINDPREV) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    findPrevTest(argc, argv);
    return 0;
}
#endif

void findPrevTest(int argc, char *argv[])
{
    printf("\n============ FINDPREV ==============\n");

    List A = List();

    for (int i = 0; i <= 2; i++)
    {
        A.insertBefore(i);
    }

    A.moveBack();
    A.movePrev();

    cout << "FindPrev | Moving cursor to middle, searching for 0, then for 2 and finally for 3. Expect: 0 -1 -1. Received: ";
    cout << A.findPrev(0) << " ";
    A.moveBack();
    A.movePrev();
    cout << A.findPrev(2) << " ";
    A.moveBack();
    A.movePrev();
    cout << A.findPrev(3) << endl;
}

#endif

#if defined(LIST_CLEANUP) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    cleanupTest(argc, argv);
    return 0;
}
#endif

void cleanupTest(int argc, char *argv[])
{
    printf("\n============ CLEANUP ==============\n");

    List A = List();

    for (int i = 0; i <= 2; i++)
    {
        A.insertBefore(1);
    }

    printf("Cleanup | Printing pre-cleanup: Expect 1 -> 1 -> 1 -> Null. Received: ");

    for (A.moveFront(); A.position() < A.size(); A.moveNext())
    {
        printf("%d -> ", A.peekNext());
    }

    printf("Null\n");

    A.cleanup();

    printf("Clear | Printing post-cleanup: Expect: 1 -> Null. Received: ");

    for (A.moveFront(); A.position() < A.size(); A.moveNext())
    {
        printf("%d -> ", A.peekNext());
    }

    printf("Null\n");

    A.insertBefore(2);
    A.insertBefore(3);

    printf("Cleanup | Printing pre-cleanup: Expect 1 -> 2 -> 3 -> Null. Received: ");

    for (A.moveFront(); A.position() < A.size(); A.moveNext())
    {
        printf("%d -> ", A.peekNext());
    }

    printf("Null\n");

    A.cleanup();

    printf("Clear | Printing post-cleanup: Expect: 1 -> 2 -> 3 -> Null. Received: ");

    for (A.moveFront(); A.position() < A.size(); A.moveNext())
    {
        printf("%d -> ", A.peekNext());
    }

    printf("Null\n");
}

#endif

#if defined(LIST_CONCAT) || defined(LIST_ALL)

#ifndef LIST_ALL
int main(int argc, char *argv[])
{
    concatTest(argc, arv);

    return 0;
}
#endif

void concatTest(int argc, char *argv[])
{
    printf("\n============ CONCAT ==============\n");

    List A = List();
    List B = List();

    for (int i = 0; i < 4; i++)
    {
        A.insertBefore(i);
        B.insertBefore(i);
    }

    cout << "Concat | Pre-concat print of A. Expect: (0, 1, 2, 3). Received: " << A << endl;

    A = A.concat(B);
    cout << "Concat | Post-concat print of A with B. Expect: (0, 1, 2, 3, 0, 1, 2, 3). Received: " << A << endl;

    A = A.concat(A);
    cout << "Concat | Post-concat print of A with A. Expect: (0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3). Received: " << A << endl;

    A.cleanup();
    cout << "Concat | Post-concat, post-cleanup. Expect: (0, 1, 2, 3). Received: " << A << endl;
}

#endif

#ifdef LIST_ALL

int main(int argc, char *argv[])
{
    insertAfterTest(argc, argv);
    insertBeforeTest(argc, argv);
    peekNextTest(argc, argv);
    peekPrevTest(argc, argv);
    eraseAfterTest(argc, argv);
    eraseBeforeTest(argc, argv);
    sizeTest(argc, argv);
    positionTest(argc, argv);
    moveBackTest(argc, argv);
    moveFrontTest(argc, argv);
    moveNextTest(argc, argv);
    movePrevTest(argc, argv);
    clearTest(argc, argv);
    equalsCopyAndAssignOpTest(argc, argv);
    isEmptyTest(argc, argv);
    findNextTest(argc, argv);
    findPrevTest(argc, argv);
    cleanupTest(argc, argv);
    concatTest(argc, argv);

    return 0;
}

#endif

#ifdef LIST_MODEL

int main()
{
    List A, B;
    A.insertBefore(34);
    A.insertBefore(77);
    A.insertBefore(77);
    A.insertBefore(1);
    A.insertBefore(34);
    A.insertBefore(1);
    A.insertBefore(55);
    A.insertBefore(77);
    if (A.findPrev(99) != -1)
        return 1;
    if (A.position() != 0)
        return 2;

    A.moveBack();
    if (A.findPrev(1) != 5)
        return 3;
    if (A.findPrev(1) != 3)
        return 4;
    if (A.findPrev(1) != -1)
        return 5;

    A.moveBack();
    // A.cleanup();
    if (A.findPrev(1) != 2)
        return 6;
    // if (A.findPrev(1) != -1)
    //     return 7;
    return 0;
}

#endif