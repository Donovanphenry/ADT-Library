/****************************************************************************************
* Name: Donovan Henry
* CruzID: dphenry
* Assignment: PA7
* File: List.c
*****************************************************************************************/

#include "BigInteger.h"

#define POWER 9
#define BASE 1e9

// Exported type -------------------------------------------------------------
// BigInteger reference type
typedef struct BigIntegerObj
{
    int sign;
    List digits;
} BigIntegerObj;

// Constructors-Destructors ---------------------------------------------------

// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger()
{
    BigInteger bigInt = (BigInteger)malloc(sizeof(BigIntegerObj));
    bigInt->digits = newList();
    bigInt->sign = 0;

    return bigInt;
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger *pN)
{
    if (pN != NULL && *pN != NULL)
    {
        freeList(&((*pN)->digits));
        free(*pN);
        *pN = NULL;
    }
}

// Helper functions -----------------------------------------------------------
LIST_ELEMENT getCarry(LIST_ELEMENT value);
LIST_ELEMENT truncateValue(LIST_ELEMENT value);
void stripLeadZeros(List digits);
void copyInPlace(BigInteger dest, BigInteger source);

// Access functions -----------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N)
{
    if (N == NULL)
    {
        printf("Error: BigInteger instance is NULL in sign(). Exiting...");
        exit(EXIT_FAILURE);
    }

    return N->sign;
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B)
{
    if (A == NULL || B == NULL)
    {
        printf("Error: Operand is NULL in compare(). Exiting...\n");
        exit(EXIT_FAILURE);
    }

    if (A == B)
        return 0;

    // Check signs of bigints
    if (A->sign < B->sign)
        return -1;
    else if (A->sign > B->sign)
        return 1;

    // Check length of digits of bigints
    if (length(A->digits) < length(B->digits))
        return -1;
    else if (length(A->digits) > length(B->digits))
        return 1;

    int bothNeg = A->sign == -1 && B->sign == -1;

    // Check individual digits of bigints
    moveFront(A->digits);
    moveFront(B->digits);

    while (index(A->digits) != -1 && index(B->digits) != -1)
    {
        if (bothNeg)
        {
            if (get(A->digits) > get(B->digits))
                return -1;
            else if (get(A->digits) < get(B->digits))
                return 1;
        }
        else
        {
            if (get(A->digits) < get(B->digits))
                return -1;
            else if (get(A->digits) > get(B->digits))
                return 1;
        }
        moveNext(A->digits);
        moveNext(B->digits);
    }

    return 0;
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B)
{
    if (A == NULL || B == NULL)
    {
        printf("Error: Operand(s) are NULL in equals(). Exiting...\n");
        exit(EXIT_FAILURE);
    }

    if (A == B)
        return 1;

    if (A->sign != B->sign)
        return 0;

    return listEquals(A->digits, B->digits);
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N)
{
    if (N == NULL)
    {
        printf("Error: BigInteger is NULL in makeZero(). Exiting...\n");
        exit(EXIT_FAILURE);
    }

    clear(N->digits);
    N->sign = 0;
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N)
{
    if (N == NULL)
    {
        printf("Error: BigInteger is NULL in negate(). Exiting...\n");
        exit(EXIT_FAILURE);
    }

    N->sign = N->sign * -1;
}

// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char *s)
{
    if (s == NULL)
    {
        printf("Error: String is NULL in stringToBigInteger(). Exiting...\n");
        exit(EXIT_FAILURE);
    }

    BigInteger big = newBigInteger();

    if (s[0] == '-')
    {
        big->sign = -1;
        s += 1;
    }
    else if (s[0] == '+')
    {
        big->sign = 1;
        s += 1;
    }
    else
        big->sign = 1;

    int stringLength = 0;

    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] < 48 || s[i] > 57)
        {
            printf("Error: Invalid character passed into stringToBigInt(). Exiting...\n");
            exit(EXIT_FAILURE);
        }

        stringLength++;
    }

    for (int i = stringLength - 1; i >= 0;)
    {
        int initialIndex = i;
        char sub[POWER];
        sub[POWER] = '\0';
        int subIndex = POWER - 1;

        while (i > initialIndex - POWER)
        {
            sub[subIndex] = i >= 0 ? s[i] : '0';
            i--;
            subIndex--;
        }

        long x = atol(sub);
        prepend(big->digits, x);
    }

    stripLeadZeros(big->digits);
    if (length(big->digits) == 1 && front(big->digits) == 0)
        makeZero(big);

    return big;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N)
{
    if (N == NULL)
    {
        printf("Error: BigInteger is NULL in copy(). Exiting...\n");
        exit(EXIT_FAILURE);
    }

    BigInteger bigInt = newBigInteger();

    if (length(N->digits) == 0)
        return bigInt;

    freeList(&(bigInt->digits));
    bigInt->digits = copyList(N->digits);

    bigInt->sign = N->sign;

    return bigInt;
}

void copyInPlace(BigInteger dest, BigInteger source)
{
    if (dest == NULL || source == NULL)
    {
        printf("Error: NULL BigInteger in copyInPlace(). Exting...\n");
        exit(EXIT_FAILURE);
    }

    dest->sign = source->sign;
    freeList(&(dest->digits));
    dest->digits = copyList(source->digits);
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B)
{
    if (S == NULL)
    {
        printf("Error: Sum result BigInteger is NULL in add(). Exiting...\n");
        exit(EXIT_FAILURE);
    }

    if (A == NULL || B == NULL)
    {
        printf("Error: Operand BigInteger is NULL in add(). Exiting...\n");
        exit(EXIT_FAILURE);
    }

    int s_is_a = 0, s_is_b = 0, b_is_a = 0;

    if (B == A)
    {
        b_is_a = 1;
        B = copy(A);
    }

    if (S == A)
    {
        s_is_a = 1;
        A = copy(A);
    }
    else if (S == B)
    {
        s_is_b = 1;
        B = copy(B);
    }

    if (A->sign == 0)
    {
        copyInPlace(S, B);

        if (s_is_a)
            freeBigInteger(&A);
        else if (s_is_b)
            freeBigInteger(&B);

        // This would only segfault if s equals b and b equals a, where we've already freed B in the else if above.
        // However, that else is only reached if s does not equal a, and therefore if s equals b and s does not equal
        // a, then a does not equal b, so this can never segfault.
        if (b_is_a)
            freeBigInteger(&B);

        return;
    }

    if (B->sign == 0)
    {
        copyInPlace(S, A);

        if (s_is_a)
            freeBigInteger(&A);
        else if (s_is_b)
            freeBigInteger(&B);

        // This would only segfault if s equals b and b equals a, where we've already freed B in the else if above.
        // However, that else is only reached if s does not equal a, and therefore if s equals b and s does not equal
        // a, then a does not equal b, so this can never segfault.
        if (b_is_a)
            freeBigInteger(&B);

        return;
    }

    if (A->sign == -1 && B->sign == -1)
    {
        // -A - B == -(A + B)
        S->sign = -1;
    }
    else if (A->sign == -1)
    {
        // -A + B == B - A
        A->sign = 1;
        subtract(S, B, A);
        A->sign = -1;

        if (s_is_a)
            freeBigInteger(&A);
        else if (s_is_b)
            freeBigInteger(&B);

        // This would only segfault if s equals b and b equals a, where we've already freed B in the else if above.
        // However, that else is only reached if s does not equal a, and therefore if s equals b and s does not equal
        // a, then a does not equal b, so this can never segfault.
        if (b_is_a)
            freeBigInteger(&B);

        return;
    }
    else if (B->sign == -1)
    {
        // A + (-B) == A - B
        B->sign = 1;
        subtract(S, A, B);
        B->sign = -1;

        if (s_is_a)
            freeBigInteger(&A);
        else if (s_is_b)
            freeBigInteger(&B);

        // This would only segfault if s equals b and b equals a, where we've already freed B in the else if above.
        // However, that else is only reached if s does not equal a, and therefore if s equals b and s does not equal
        // a, then a does not equal b, so this can never segfault.
        if (b_is_a)
            freeBigInteger(&B);

        return;
    }
    else
        S->sign = 1;

    moveBack(A->digits);
    moveBack(B->digits);

    clear(S->digits);

    LIST_ELEMENT prevCarry = 0;

    while (index(A->digits) != -1 || index(B->digits) != -1)
    {
        LIST_ELEMENT a_ithDigit = index(A->digits) != -1 ? get(A->digits) : 0;
        LIST_ELEMENT b_ithDigit = index(B->digits) != -1 ? get(B->digits) : 0;
        LIST_ELEMENT sum = a_ithDigit + b_ithDigit;

        int borrowed = sum >= BASE ? 1 : 0;

        LIST_ELEMENT normalizedSum = borrowed ? truncateValue(sum) : sum;
        prepend(S->digits, normalizedSum + prevCarry);

        prevCarry = borrowed == 1 ? getCarry(sum) : 0;

        // Move onto next iteration
        // printf("Setting up next iteration\n");
        movePrev(A->digits);
        movePrev(B->digits);
    }

    if (prevCarry != 0)
        prepend(S->digits, prevCarry);

    if (length(S->digits) == 1 && front(S->digits) == 0)
        S->sign = 0;

    if (s_is_a)
        freeBigInteger(&A);
    else if (s_is_b)
        freeBigInteger(&B);

    // This would only segfault if s equals b and b equals a, where we've already freed B in the else if above.
    // However, that else is only reached if s does not equal a, and therefore if s equals b and s does not equal
    // a, then a does not equal b, so this can never segfault.
    if (b_is_a)
        freeBigInteger(&B);

    return;
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B)
{
    if (A == NULL || B == NULL)
    {
        printf("Error: Operand is NULL in sum(). Exiting...\n");
        exit(EXIT_FAILURE);
    }

    BigInteger sum = newBigInteger();

    add(sum, A, B);
    return sum;
}

// Helper function used to shave off every part of an integer except the first
// (from right to left) POWER digits. Used to help normalize a value.
LIST_ELEMENT truncateValue(LIST_ELEMENT value)
{
    char sumString[POWER];
    sprintf(sumString, "%ld", value);

    int sumStringLength = 0;

    for (int index = 0; sumString[index] != '\0'; index++)
        sumStringLength++;

    int truncatedSumEnd = sumStringLength - POWER;
    char truncatedSumString[POWER];

    int truncIndex = POWER - 1;
    for (int ogIndex = sumStringLength - 1; ogIndex >= truncatedSumEnd; ogIndex--)
    {
        truncatedSumString[truncIndex] = sumString[ogIndex];
        // printf("truncatedString[%d]: %c\n", truncIndex + 1, truncatedSumString[truncIndex + 1]);
        truncIndex--;
    }
    truncatedSumString[POWER] = '\0';

    LIST_ELEMENT truncatedSum = atoi(truncatedSumString);

    return truncatedSum;
}

// Helper function to obtain and return the carry of a value passed into it.
LIST_ELEMENT getCarry(LIST_ELEMENT value)
{
    char sumString[POWER] = "";
    sprintf(sumString, "%ld", value);

    int sumStringLength = 0;

    for (int index = 0; sumString[index] != '\0'; index++)
        sumStringLength++;

    int carryStringLength = sumStringLength - POWER;
    char *carryString = malloc(sizeof(char) * (carryStringLength + 1));
    // carryString[POWER] = '\0';

    for (int i = 0; i < carryStringLength; i++)
        carryString[i] = '0';

    for (int i = carryStringLength - 1; i >= 0; i--)
        carryString[i] = sumString[i];

    int pow = 1;

    LIST_ELEMENT carry = 0;
    for (int i = carryStringLength - 1; i >= 0; i--)
    {
        LIST_ELEMENT curr = (long)carryString[i] - 48;
        carry += curr * pow;
        pow = pow * 10;
    }

    free(carryString);

    return carry;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B)
{
    if (D == NULL)
    {
        printf("Error: Subtracition result BigInteger is NULL in subtract(). Exiting...\n");
        exit(EXIT_FAILURE);
    }

    if (A == NULL || B == NULL)
    {
        printf("Error: Operand BigInteger is NULL in subtract(). Exiting...\n");
        exit(EXIT_FAILURE);
    }

    int d_is_a = 0, d_is_b = 0, b_is_a = 0;

    if (B == A)
    {
        b_is_a = 1;
        B = copy(A);
    }

    if (D == A)
    {
        d_is_a = 1;
        A = copy(A);
    }
    else if (D == B)
    {
        d_is_b = 1;
        B = copy(B);
    }

    if (A->sign == 0)
    {
        copyInPlace(D, B);

        if (d_is_a)
            freeBigInteger(&A);
        else if (d_is_b)
            freeBigInteger(&B);

        if (b_is_a)
            freeBigInteger(&B);

        return;
    }

    if (B->sign == 0)
    {
        copyInPlace(D, A);

        if (d_is_a)
            freeBigInteger(&A);
        else if (d_is_b)
            freeBigInteger(&B);

        if (b_is_a)
            freeBigInteger(&B);

        return;
    }

    if (A->sign == -1 && B->sign != -1) // -A - B = -(A + B)
    {
        A->sign = 1;
        B->sign = 1;
        add(D, A, B);

        A->sign = -1;
        B->sign = 1;
        D->sign = -1;

        if (d_is_a)
            freeBigInteger(&A);
        else if (d_is_b)
            freeBigInteger(&B);

        if (b_is_a)
            freeBigInteger(&B);

        return;
    }
    else if (A->sign == -1 && B->sign == -1) // -A - (-B) = -A + B = B - A
    {
        B->sign = 1;
        A->sign = 1;
        subtract(D, B, A);

        B->sign = -1;
        A->sign = -1;

        if (d_is_a)
            freeBigInteger(&A);
        else if (d_is_b)
            freeBigInteger(&B);

        if (b_is_a)
            freeBigInteger(&B);

        return;
    }
    else if (A->sign == 1 && B->sign == -1) // A - (-B) = A + B
    {
        B->sign = 1;
        add(D, A, B);

        B->sign = -1;
        D->sign = 1;

        if (d_is_a)
            freeBigInteger(&A);
        else if (d_is_b)
            freeBigInteger(&B);

        if (b_is_a)
            freeBigInteger(&B);

        return;
    }

    BigInteger larger;
    BigInteger lesser;

    if (compare(A, B) == 1)
    {
        larger = copy(A);
        lesser = B;
        D->sign = 1;
    }
    else
    {
        larger = copy(B);
        lesser = A;
        D->sign = -1;
    }

    moveBack(larger->digits);
    moveBack(lesser->digits);

    clear(D->digits);

    while (index(larger->digits) != -1 || index(lesser->digits) != -1)
    {
        LIST_ELEMENT p_ithDigit = index(larger->digits) != -1 ? get(larger->digits) : 0;
        LIST_ELEMENT n_ithDigit = index(lesser->digits) != -1 ? get(lesser->digits) : 0;
        LIST_ELEMENT carry = 0;
        LIST_ELEMENT diff = p_ithDigit - n_ithDigit;
        carry = diff < 0 ? BASE : 0;
        diff = diff < 0 ? diff + carry : diff;

        prepend(D->digits, diff);

        // Move onto next iteration
        movePrev(larger->digits);
        if (carry != 0)
        {
            if (index(larger->digits) != -1)
                set(larger->digits, get(larger->digits) - 1);
            else
            {
                moveFront(larger->digits);
                set(larger->digits, get(larger->digits) * -1);
                larger->sign = -1;
            }
        }
        movePrev(lesser->digits);
    }

    stripLeadZeros(D->digits);

    if (length(D->digits) == 1 && front(D->digits) == 0)
        D->sign = 0;

    freeBigInteger(&larger);

    if (d_is_a)
        freeBigInteger(&A);
    else if (d_is_b)
        freeBigInteger(&B);

    if (b_is_a)
        freeBigInteger(&B);
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B)
{
    if (A == NULL || B == NULL)
    {
        printf("Error: Operand is NULL in diff(). Exiting...\n");
        exit(EXIT_FAILURE);
    }

    BigInteger diff = newBigInteger();

    subtract(diff, A, B);
    return diff;
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B)
{
    if (A == NULL || B == NULL || P == NULL)
    {
        printf("Error: NULL BigInteger reference in multiply(). Exiting...\n");
        exit(EXIT_FAILURE);
    }

    int p_is_a = 0, p_is_b = 0, b_is_a = 0;

    if (B == A)
    {
        b_is_a = 1;
        B = copy(A);
    }

    if (P == A)
    {
        p_is_a = 1;
        A = copy(A);
    }
    else if (P == B)
    {
        p_is_b = 1;
        B = copy(B);
    }

    BigInteger primary = A;
    BigInteger secondary = B;

    makeZero(P);

    if (primary->sign == 0 || secondary->sign == 0)
    {
        if (p_is_a)
            freeBigInteger(&A);
        else if (p_is_b)
            freeBigInteger(&B);

        if (b_is_a)
            freeBigInteger(&B);

        return;
    }

    int primaryShorterThanSecondary = length(primary->digits) < length(secondary->digits);
    BigInteger larger, smaller;

    if (primaryShorterThanSecondary)
    {
        larger = secondary;
        smaller = primary;
    }
    else
    {
        larger = primary;
        smaller = secondary;
    }

    if (larger->sign == smaller->sign * -1)
        P->sign = -1;
    else if (larger->sign == smaller->sign && larger->sign != 0)
        P->sign = 1;
    else
        P->sign = 0;

    int startColumn = 0;

    LIST_ELEMENT prevCarry = 0;

    int digitRequiresCarry = 0;
    int carryRequired = 0;

    for (int i = 0; i < length(larger->digits) - 1; i++)
        prepend(P->digits, 0);

    for (moveBack(larger->digits); index(larger->digits) != -1; movePrev(larger->digits))
    {
        prepend(P->digits, prevCarry);
        prevCarry = 0;

        moveBack(P->digits);
        for (int i = 0; i < startColumn; i++)
            movePrev(P->digits);

        for (moveBack(smaller->digits); index(smaller->digits) != -1; movePrev(smaller->digits))
        {
            long product = get(smaller->digits) * get(larger->digits);
            carryRequired = product >= BASE ? 1 : 0;
            long normalizedProduct = carryRequired ? truncateValue(product) : product;

            long i_thDigit = normalizedProduct + prevCarry + get(P->digits);
            digitRequiresCarry = i_thDigit >= BASE;
            long normalized_ith_digit = digitRequiresCarry ? truncateValue(i_thDigit) : i_thDigit;

            prevCarry = carryRequired ? getCarry(product) : 0;
            prevCarry += digitRequiresCarry ? getCarry(i_thDigit) : 0;

            set(P->digits, normalized_ith_digit);

            movePrev(P->digits);
        }

        if (index(P->digits) != -1)
        {
            if (get(P->digits) != 0)
            {
                prepend(P->digits, prevCarry);
            }
            else
                set(P->digits, prevCarry);

            prevCarry = 0;
        }

        startColumn++;
    }

    if (prevCarry != 0)
        prepend(P->digits, prevCarry);

    while (length(P->digits) > 1 && front(P->digits) == 0)
        deleteFront(P->digits);

    if (p_is_a)
        freeBigInteger(&A);
    else if (p_is_b)
        freeBigInteger(&B);

    if (b_is_a)
        freeBigInteger(&B);
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B)
{
    if (A == NULL || B == NULL)
    {
        printf("Error: operand is NULL in prod(). Exiting...\n");
        exit(EXIT_FAILURE);
    }

    BigInteger product = newBigInteger();
    multiply(product, A, B);

    return product;
}

// Other operations -----------------------------------------------------------

void stripLeadZeros(List digits)
{
    if (digits == NULL)
    {
        printf("Error: Digit list is NULL in stripLeadDigits. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    while (length(digits) > 1 && front(digits) == 0)
        deleteFront(digits);
}

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE *out, BigInteger N)
{
    if (N == NULL)
    {
        printf("Error: BigInteger instance is NULL in printBigInteger(). Exiting...\n");
        exit(EXIT_FAILURE);
    }

    if (out == NULL)
    {
        printf("Error: Output file is NULL in printBigInteger(). Exiting...\n");
        exit(EXIT_FAILURE);
    }

    if (N->sign == 0)
    {
        // printf("%0*d", POWER, 0);
        fprintf(out, "0");
        return;
    }

    moveFront(N->digits);

    if (N->sign == -1)
        fprintf(out, "-");

    fprintf(out, "%ld", get(N->digits));

    moveNext(N->digits);

    for (; index(N->digits) != -1; moveNext(N->digits))
        fprintf(out, "%0*ld", POWER, get(N->digits));
}