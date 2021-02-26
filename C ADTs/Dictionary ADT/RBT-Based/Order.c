/****************************************************************************************
* Name: Donovan Henry
* CruzID: dphenry
* Assignment: PA6
* File: Order.c
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

#define MAX_LEN 250

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Error: Too few arguments\n");
        exit(EXIT_FAILURE);
    }

    if (argc > 3)
    {
        fprintf(stderr, "Error: Too many arguments\n");
        exit(EXIT_FAILURE);
    }

    int line_count = 0;
    char line[MAX_LEN];

    FILE *fP = fopen(argv[1], "r");

    while (fgets(line, MAX_LEN, fP) != NULL)
        line_count++;

    fclose(fP);
    fP = fopen(argv[1], "r");
    char **inputStrings = (char **)malloc(line_count * sizeof(char *));
    int *valueArray = (int *)malloc(line_count * sizeof(int));
    Dictionary dict = newDictionary(0);

    line_count = 0;
    int val = 0;
    while (fgets(line, MAX_LEN, fP) != NULL)
    {
        inputStrings[line_count] = (char *)malloc(MAX_LEN * sizeof(char) + 1);
        valueArray[line_count] = val++;

        strcpy(inputStrings[line_count], line);

        if (strstr(line, "\n") == NULL)
            strcat(inputStrings[line_count], "\n");

        insert(dict, inputStrings[line_count], &(valueArray[line_count]));
        // printf("Attempted insert of inputStrings[%d] for key %s test", line_count, inputStrings[line_count]);
        // printf("Printing Dictionary now\n");
        // printDictionary(stdout, dict, "in");
        line_count++;
    }

    fclose(fP);

    fP = fopen(argv[2], "w");

    fprintf(fP, "******************************************************\n");
    fprintf(fP, "PRE-ORDER:\n");
    fprintf(fP, "******************************************************\n");
    printDictionary(fP, dict, "pre");

    fprintf(fP, "\n\n******************************************************\n");
    fprintf(fP, "IN-ORDER:\n");
    fprintf(fP, "******************************************************\n");
    printDictionary(fP, dict, "in");

    fprintf(fP, "\n\n******************************************************\n");
    fprintf(fP, "POST-ORDER:\n");
    fprintf(fP, "******************************************************\n");
    printDictionary(fP, dict, "post");
    fprintf(fP, "\n");

    fclose(fP);

    for (int i = 0; i < line_count; i++)
        free(inputStrings[i]);

    free(valueArray);
    free(inputStrings);
    freeDictionary(&dict);

    return 0;
}
