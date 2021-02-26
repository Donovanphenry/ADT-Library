//-----------------------------------------------------------------------------
// DictionaryClient.c
// Test client for Dictionary ADT
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Dictionary.h"

int main(int argc, char *argv[])
{

    int i, n = 26;
    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);
    char *word[] = {"n", "z", "w", "k", "i", "c", "l", "d", "t", "a",
                    "e", "y", "b", "h", "v", "f", "s", "m", "x", "r",
                    "o", "u", "p", "g", "j", "q"};
    VAL_TYPE x;
    VAL_TYPE y;

    // add pairs to A --------------------------------------
    for (i = 0; i < n; i++)
    {
        insert(A, word[i], i);
    }

    // add pairs to B
    for (i = n - 1; i >= 0; i--)
    {
        insert(B, word[i], i);
    }

    // forward iteration over A ----------------------------
    printf("forward A:\n");
    for (x = beginForward(A); currentVal(A) != VAL_UNDEF; x = next(A))
    {
        printf("key: " KEY_FORMAT " value: " VAL_FORMAT "\n", currentKey(A), x);
    }
    printf("\n\n");

    // reverse iteratation over B
    printf("reverse B:\n");
    for (y = beginReverse(B); currentVal(B) != VAL_UNDEF; y = prev(B))
    {
        printf("key: " KEY_FORMAT " value: " VAL_FORMAT "\n", currentKey(B), y);
    }
    printf("\n\n");

    // print Dictionary A ----------------------------------
    printf("Dictionary A (%sunique keys):\n", (getUnique(A) ? "" : "non-"));
    printDictionary(stdout, A);
    printf("\n");

    // print Dictionary B
    printf("Dictionary B (%sunique keys):\n", (getUnique(B) ? "" : "non-"));
    printDictionary(stdout, B);
    printf("\n");

    // delete keys from A ----------------------------------
    for (i = 0; i < n; i += 2)
    {
        delete (A, word[i]);
    }

    // print Dictionary A after deletions
    printf("Dictionary A (%sunique keys):\n", (getUnique(A) ? "" : "non-"));
    printf("after deletions:\n");
    printDictionary(stdout, A);
    printf("\n");

    // delete keys from B ----------------------------------
    for (i = 1; i < n; i += 2)
    {
        delete (B, word[i]);
    }

    // print Dictionary B after deletions
    printf("Dictionary B (%sunique keys):\n", (getUnique(B) ? "" : "non-"));
    printf("after deletions:\n");
    printDictionary(stdout, B);
    printf("\n");

    // insert duplicates into A ----------------------------
    for (i = 1; i < n; i += 2)
    {
        insert(A, word[i], i);
    }

    // print Dictionary A after insertions
    printf("Dictionary A (%sunique keys):\n", (getUnique(A) ? "" : "non-"));
    printf("after insertions:\n");
    printDictionary(stdout, A);
    printf("\n");

    // uncomment line below to get error message
    // insert(B, word[10], 10);
    // Dictionary Error:
    // calling insert() on existing key: e

    // free heap memory ------------------------------------
    freeDictionary(&A);
    freeDictionary(&B);

    return (0);
}
