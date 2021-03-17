/****************************************************************************************
* Name: Donovan Henry
* CruzID: dphenry
* Assignment: PA7
* File: Arithmetic.c
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "BigInteger.h"
#include "List.h"

#define LINE_LENGTH 300

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Error: Too few command-line arguments in Arithmetic.c. Exiting..\n");
        exit(EXIT_FAILURE);
    }

    if (argc > 3)
    {
        printf("Error: Too many command-line arguments in Arithmetic.c. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    FILE *inFile = fopen(argv[1], "r");
    FILE *outFile = fopen(argv[2], "w");

    BigInteger A, B;
    char *power_a = (char *)malloc(sizeof(char) * LINE_LENGTH);
    char *power_b = (char *)malloc(sizeof(char) * LINE_LENGTH);
    char *string_a, *string_b;

    fscanf(inFile, "%s", power_a);
    long numberLength_a = atol(power_a);
    string_a = (char *)malloc(sizeof(char) * (numberLength_a + 2));
    fscanf(inFile, "%s", string_a);

    fscanf(inFile, "%s", power_b);
    long numberLength_b = atol(power_b);
    string_b = (char *)malloc(sizeof(char) * (numberLength_b + 2));
    fscanf(inFile, "%s", string_b);

    A = stringToBigInteger(string_a);
    B = stringToBigInteger(string_b);

    // Constants
    BigInteger two = stringToBigInteger("2");
    BigInteger three = stringToBigInteger("3");
    BigInteger nine = stringToBigInteger("9");
    BigInteger sixteen = stringToBigInteger("16");

    // Operations
    BigInteger addition = sum(A, B);
    BigInteger subtraction = diff(A, B);
    BigInteger additiveIdentity = diff(A, A);
    BigInteger a_mult3 = prod(A, three);
    BigInteger b_mult2 = prod(B, two);
    BigInteger a3_minus_b2 = diff(a_mult3, b_mult2);
    BigInteger product = prod(A, B);
    BigInteger aSquared = prod(A, A);
    BigInteger bSquared = prod(B, B);
    BigInteger a_4th_power = prod(aSquared, aSquared);
    BigInteger b_4th_power = prod(bSquared, bSquared);
    BigInteger b_5th_power = prod(b_4th_power, B);
    BigInteger a9_p4 = prod(nine, a_4th_power);
    BigInteger b16_p5 = prod(sixteen, b_5th_power);
    BigInteger a9_p4_plus_b16_p5 = sum(a9_p4, b16_p5);

    printBigInteger(outFile, A);

    fprintf(outFile, "\n\n");
    printBigInteger(outFile, B);

    fprintf(outFile, "\n\n");
    printBigInteger(outFile, addition);

    fprintf(outFile, "\n\n");
    printBigInteger(outFile, subtraction);

    fprintf(outFile, "\n\n");
    printBigInteger(outFile, additiveIdentity);

    fprintf(outFile, "\n\n");
    printBigInteger(outFile, a3_minus_b2);

    fprintf(outFile, "\n\n");
    printBigInteger(outFile, product);

    fprintf(outFile, "\n\n");
    printBigInteger(outFile, aSquared);

    fprintf(outFile, "\n\n");
    printBigInteger(outFile, bSquared);

    fprintf(outFile, "\n\n");
    printBigInteger(outFile, a9_p4_plus_b16_p5);

    fprintf(outFile, "\n");

    freeBigInteger(&a9_p4_plus_b16_p5);
    freeBigInteger(&b16_p5);
    freeBigInteger(&a9_p4);
    freeBigInteger(&b_5th_power);
    freeBigInteger(&b_4th_power);
    freeBigInteger(&a_4th_power);
    freeBigInteger(&addition);
    freeBigInteger(&subtraction);
    freeBigInteger(&additiveIdentity);
    freeBigInteger(&a_mult3);
    freeBigInteger(&b_mult2);
    freeBigInteger(&a3_minus_b2);
    freeBigInteger(&product);
    freeBigInteger(&aSquared);
    freeBigInteger(&bSquared);

    freeBigInteger(&two);
    freeBigInteger(&three);
    freeBigInteger(&nine);
    freeBigInteger(&sixteen);

    freeBigInteger(&A);
    freeBigInteger(&B);

    free(string_a);
    free(string_b);
    free(power_a);
    free(power_b);

    fclose(inFile);
    fclose(outFile);

    return 0;
}