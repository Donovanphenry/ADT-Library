/****************************************************************************************
* Name: Donovan Henry
* CruzID: dphenry
* Assignment: PA7
* BigIntegerTest.c
* Test client for BigInteger ADT
*****************************************************************************************/

#include "BigInteger.h"
#include "List.h"

#define BIG_CLIENT

#if defined(BIG_SIGN) || defined(BIG_ALL)

void signTest()
{
    printf("\n========== SIGN_TEST ============\n");
    BigInteger A = stringToBigInteger("+120");
    BigInteger B = stringToBigInteger("120");
    BigInteger C = stringToBigInteger("0");
    BigInteger D = stringToBigInteger("-120");
    BigInteger E = stringToBigInteger("-121");
    BigInteger F = stringToBigInteger("119");

    printf("Printing sign of A. Expect: 1. Received: %d\n", sign(A));
    printf("Printing sign of B. Expect: 1. Received: %d\n", sign(B));
    printf("Printing sign of C. Expect: 0. Received: %d\n", sign(C));
    printf("Printing sign of D. Expect: -1. Received: %d\n", sign(D));
    printf("Printing sign of E. Expect: -1. Received: %d\n", sign(E));
    printf("Printing sign of F. Expect: 1. Received: %d\n", sign(F));

    BigInteger G = diff(A, F);
    printf("Printing sign of A - F. Expect: 1. Received: %d\n", sign(G));
    freeBigInteger(&G);

    G = diff(F, A);
    printf("Printing sign of F - A. Expect: -1. Received: %d\n", sign(G));
    freeBigInteger(&G);

    G = sum(F, A);
    printf("Printing sign of -F + A. Expect: 1. Received: %d\n", sign(G));
    freeBigInteger(&G);

    G = sum(A, F);
    printf("Printing sign of A + (-F). Expect: 1. Received: %d\n", sign(G));
    freeBigInteger(&G);

    G = sum(A, C);
    printf("Printing sign of A + C. Expect: 1. Received: %d\n", sign(G));
    freeBigInteger(&G);

    G = sum(C, A);
    printf("Printing sign of C + A. Expect: 1. Received: %d\n", sign(G));
    freeBigInteger(&G);

    G = sum(E, C);
    printf("Printing sign of E + C. Expect: -1. Received: %d\n", sign(G));
    freeBigInteger(&G);

    G = sum(C, E);
    printf("Printing sign of C + E. Expect: -1. Received: %d\n", sign(G));
    freeBigInteger(&G);

    G = sum(C, C);
    printf("Printing sign of C + C. Expect: 0. Received: %d\n", sign(G));
    freeBigInteger(&G);

    G = diff(A, A);
    printf("Printing sign of A - A. Expect: 0. Received: %d\n", sign(G));
    freeBigInteger(&G);

    G = prod(A, F);
    printf("Printing sign of A * F. Expect: 1. Received: %d\n", sign(G));
    freeBigInteger(&G);

    G = prod(A, C);
    printf("Printing sign of A * E. Expect: 0. Received: %d\n", sign(G));
    freeBigInteger(&G);

    G = prod(A, E);
    printf("Printing sign of A * E. Expect: -1. Received: %d\n", sign(G));
    freeBigInteger(&G);

    freeBigInteger(&G);
    freeBigInteger(&F);
    freeBigInteger(&E);
    freeBigInteger(&D);
    freeBigInteger(&C);
    freeBigInteger(&B);
    freeBigInteger(&A);
}

#ifndef BIG_ALL
int main()
{
    signTest();
    return 0;
}
#endif

#endif

#if defined(BIG_COMPARE) || defined(BIG_ALL)

void compareTest()
{
    printf("\n========== COMPARE_TEST ============\n");
    BigInteger A = stringToBigInteger("103123913901");
    BigInteger B = stringToBigInteger("-103123913901");
    BigInteger C = stringToBigInteger("103123913901");
    BigInteger D = stringToBigInteger("105123913901");
    BigInteger E = stringToBigInteger("-103123913901");
    BigInteger F = stringToBigInteger("-105123913901");
    BigInteger G = stringToBigInteger("0");

    int comparison = 0;

    comparison = compare(A, B);
    printf("Comparing A and B. Expect: 1. Received: %d\n", comparison);

    comparison = compare(A, C);
    printf("Comparing A and C. Expect: 0. Received: %d\n", comparison);

    comparison = compare(A, D);
    printf("Comparing A and D. Expect: -1. Received: %d\n", comparison);

    comparison = compare(A, G);
    printf("Comparing A and G. Expect: 1. Received: %d\n", comparison);

    comparison = compare(G, A);
    printf("Comparing G and A. Expect: -1. Received: %d\n", comparison);

    comparison = compare(E, F);
    printf("Comparing E and F. Expect: 1. Received: %d\n", comparison);

    comparison = compare(B, E);
    printf("Comparing B and E. Expect: 0. Received: %d\n", comparison);

    freeBigInteger(&G);
    freeBigInteger(&F);
    freeBigInteger(&E);
    freeBigInteger(&D);
    freeBigInteger(&C);
    freeBigInteger(&B);
    freeBigInteger(&A);
}

#ifndef BIG_ALL
int main()
{
    compareTest();
    return 0;
}
#endif

#endif

#if defined(BIG_EQUALS) || defined(BIG_ALL)

void equalsTest()
{
    printf("\n========== EQUALS_TEST ============\n");
    BigInteger A = stringToBigInteger("103123913901");
    BigInteger B = stringToBigInteger("-103123913901");
    BigInteger C = stringToBigInteger("103123913901");
    BigInteger D = stringToBigInteger("105123913901");
    BigInteger E = stringToBigInteger("-103123913901");
    BigInteger F = stringToBigInteger("-105123913901");
    BigInteger G = stringToBigInteger("0");

    int equality = 0;

    equality = equals(A, B);
    printf("Comparing A and B. Expect: 0. Received: %d\n", equality);

    equality = equals(A, C);
    printf("Comparing A and C. Expect: 1. Received: %d\n", equality);

    equality = equals(A, D);
    printf("Comparing A and D. Expect: 0. Received: %d\n", equality);

    equality = equals(A, G);
    printf("Comparing A and G. Expect: 0. Received: %d\n", equality);

    equality = equals(G, A);
    printf("Comparing G and A. Expect: 0. Received: %d\n", equality);

    equality = equals(E, F);
    printf("Comparing E and F. Expect: 0. Received: %d\n", equality);

    equality = equals(B, E);
    printf("Comparing B and E. Expect: 1. Received: %d\n", equality);

    freeBigInteger(&G);
    freeBigInteger(&F);
    freeBigInteger(&E);
    freeBigInteger(&D);
    freeBigInteger(&C);
    freeBigInteger(&B);
    freeBigInteger(&A);
}

#ifndef BIG_ALL
int main()
{
    equalsTest();
    return 0;
}
#endif

#endif

#if defined(BIG_MZ) || defined(BIG_ALL)

void mzTest()
{
    printf("\n========== MZ_TEST ============\n");
    BigInteger A = stringToBigInteger("4203984");
    BigInteger B = newBigInteger();
    makeZero(A);

    printf("Printing Equality. Expect: 1. Received: %d\n", equals(A, B));

    freeBigInteger(&A);
    freeBigInteger(&B);
}

#ifndef BIG_ALL

int main()
{
    mzTest();
}

#endif

#endif

#if defined(BIG_NEGATE) || defined(BIG_ALL)

void negateTest()
{
    printf("\n========== NEGATE_TEST ============\n");

    BigInteger A = stringToBigInteger("1");
    BigInteger B = stringToBigInteger("0");
    BigInteger C = stringToBigInteger("-1");

    negate(A);
    printf("Negating A and calling sign. Expect: -1. Received: %d\n", sign(A));

    negate(B);
    printf("Negating B and calling sign. Expect: 0. Received: %d\n", sign(B));

    negate(C);
    printf("Negating C and calling sign. Expect: 1. Received: %d\n", sign(C));

    freeBigInteger(&C);
    freeBigInteger(&B);
    freeBigInteger(&A);
}

#ifndef BIG_ALL
int main()
{
    negateTest();
}
#endif

#endif

#if defined(BIG_STRING_TO_BIG_INT) || defined(BIG_ALL)

void stringifyTest()
{
    printf("\n========== STRING_TO_BIG_INT_TEST ============\n");
    BigInteger A = stringToBigInteger("123");
    BigInteger B = stringToBigInteger("-123");
    BigInteger C = stringToBigInteger("+123");
    BigInteger D = stringToBigInteger("0");

    printf("Printing A. Expect: 123. Received: ");
    printBigInteger(stdout, A);
    printf("\n");

    printf("Printing B. Expect: -123. Received: ");
    printBigInteger(stdout, B);
    printf("\n");

    printf("Printing C. Expect: 123. Received: ");
    printBigInteger(stdout, C);
    printf("\n");

    printf("Printing D. Expect: 0. Received: ");
    printBigInteger(stdout, D);
    printf("\n");

    freeBigInteger(&D);
    freeBigInteger(&C);
    freeBigInteger(&B);
    freeBigInteger(&A);
}

#ifndef BIG_ALL
int main()
{
    stringifyTest();
}
#endif

#endif

#if defined(BIG_COPY) || defined(BIG_ALL)

void copyTest()
{
    printf("\n========== COPY_TEST ============\n");

    BigInteger A = stringToBigInteger("123");
    BigInteger B = newBigInteger();
    BigInteger X = stringToBigInteger("-123");
    BigInteger C = copy(A);
    BigInteger D = copy(B);
    BigInteger Y = copy(X);

    int comparison = equals(A, C);
    printf("Calling equals on A and C. Expect: 1. Received: %d\n", comparison);

    comparison = equals(B, D);
    printf("Calling equals on B and D. Expect: 1. Received: %d\n", comparison);

    comparison = equals(X, Y);
    printf("Calling equals on X and Y. Expect: 1. Received: %d\n", comparison);

    freeBigInteger(&Y);
    freeBigInteger(&D);
    freeBigInteger(&C);
    freeBigInteger(&X);
    freeBigInteger(&B);
    freeBigInteger(&A);
}

#ifndef BIG_ALL
int main()
{
    copyTest();
}
#endif

#endif

#if defined(BIG_ADD) || defined(BIG_ALL)

void addTest()
{
    printf("\n========== ADD_TEST ============\n");
    BigInteger zero = stringToBigInteger("0");
    BigInteger A = stringToBigInteger("42759459832403984");
    BigInteger B = stringToBigInteger("0928409278590");
    BigInteger result = newBigInteger();

    printf("A->sign = %d B->sign = %d\n", sign(A), sign(B));

    // A + B
    add(result, A, B);

    printf("Adding A and B. Expect: %s. Received: ", "42760388241682574");
    printBigInteger(stdout, result);
    printf("\n");
    freeBigInteger(&result);
    freeBigInteger(&B);

    // A + (-B)
    B = stringToBigInteger("-298034710947298075298");
    result = newBigInteger();
    add(result, A, B);

    printf("Adding A and B. Expect: -297991951487465671314. Received: ");
    printBigInteger(stdout, result);
    printf("\n");

    freeBigInteger(&result);
    freeBigInteger(&B);

    // -A + B
    freeBigInteger(&A);
    A = stringToBigInteger("-403298408435798");
    B = stringToBigInteger("89741877784654");
    result = sum(A, B);

    printf("Adding A and B. Expect: -313556530651144. Received: ");
    printBigInteger(stdout, result);
    printf("\n");

    // -A + -B = -1 * (A + B)
    freeBigInteger(&result);
    freeBigInteger(&B);

    B = stringToBigInteger("-3546876344545647");
    result = sum(A, B);

    printf("Adding A and B. Expect: -3950174752981445. Received: ");
    printBigInteger(stdout, result);
    printf("\n");

    freeBigInteger(&result);
    freeBigInteger(&B);
    freeBigInteger(&A);

    /* TEST 2 */

    // A + (-A)
    A = stringToBigInteger("423");
    B = stringToBigInteger("-423");

    result = sum(A, B);

    printf("Additive inverse test. Expect: 0. Received: ");
    printBigInteger(stdout, result);
    printf("\n");

    freeBigInteger(&result);
    freeBigInteger(&B);

    // *(&A) + *(&A)
    result = newBigInteger();
    add(result, A, A);

    printf("Same operand test. Expect: 846. Received: ");
    printBigInteger(stdout, result);
    freeBigInteger(&result);
    // freeBigInteger(&A);
    printf("\n");

    // Deprecated. No clue at all why this doesn't work. // *(&A) = *(&A) + *(&A)
    add(A, A, A);

    printf("Same operands as result. Expect: 846. Received: ");
    printBigInteger(stdout, A);
    printf("\n");

    add(A, A, zero);

    printf("Same operand as result. Additive identity added to A. Expect: 846. Received: ");
    printBigInteger(stdout, A);
    printf("\n");

    add(zero, zero, zero);

    printf("Same operand as result. Additive identity added to itself. Expect: 0. Received: ");
    printBigInteger(stdout, zero);
    printf("\n");

    freeBigInteger(&A);
    freeBigInteger(&zero);
}

#ifndef BIG_ALL

int main()
{
    addTest();
}

#endif

#endif

#if defined(BIG_SUB) || defined(BIG_ALL)
void subTest()
{
    printf("\n========== SUBTRACT_TEST ============\n");
    BigInteger zero = stringToBigInteger("0");
    BigInteger A = stringToBigInteger("42759459832403984");
    BigInteger B = stringToBigInteger("0928409278590");
    BigInteger result = newBigInteger();

    // A + B
    subtract(result, A, B);

    printf("Subtracting A and B. Expect: %s. Received: ", "42758531423125394");
    printBigInteger(stdout, result);
    printf("\n");
    freeBigInteger(&result);
    freeBigInteger(&B);

    // A + (-B)
    B = stringToBigInteger("-298034710947298075298");
    result = newBigInteger();
    subtract(result, A, B);

    printf("Subtracting A and B. Expect: 298077470407130479282. Received: ");
    printBigInteger(stdout, result);
    printf("\n");

    freeBigInteger(&result);
    freeBigInteger(&B);

    // -A + B
    freeBigInteger(&A);
    A = stringToBigInteger("-403298408435798");
    B = stringToBigInteger("89741877784654");
    result = diff(A, B);

    printf("Subtracting A and B. Expect: -493040286220452. Received: ");
    printBigInteger(stdout, result);
    printf("\n");

    // -A + -B = -1 * (A + B)
    freeBigInteger(&result);
    freeBigInteger(&B);

    B = stringToBigInteger("-3546876344545647");
    result = diff(A, B);

    printf("Subtracting A and B. Expect: 3143577936109849. Received: ");
    printBigInteger(stdout, result);
    printf("\n");

    freeBigInteger(&result);
    freeBigInteger(&B);
    freeBigInteger(&A);

    /* TEST 2 */

    // A + (-A)
    A = stringToBigInteger("423");
    B = stringToBigInteger("-423");

    result = diff(A, B);

    printf("Additive inverse test. Expect: 846. Received: ");
    printBigInteger(stdout, result);
    printf("\n");

    freeBigInteger(&result);
    freeBigInteger(&B);

    // *(&A) + *(&A)
    result = newBigInteger();
    subtract(result, A, A);

    printf("Same operand test. Expect: 0. Received: ");
    printBigInteger(stdout, result);
    printf("\n");
    freeBigInteger(&result);

    subtract(A, A, A);

    printf("Same operands as result. Expect: 0. Received: ");
    printBigInteger(stdout, A);
    printf("\n");

    subtract(A, zero, A);
    printf("Same operand as result. A subtracted from additive identity. Expect: 0. Received: ");
    printBigInteger(stdout, A);
    printf("\n");

    subtract(zero, zero, zero);
    printf("Same operands as result, additive identity subtracting itself. Expect: 0. Received: ");
    printBigInteger(stdout, zero);
    printf("\n");

    freeBigInteger(&A);
    freeBigInteger(&zero);
}

#ifndef BIG_ALL
int main()
{
    subTest();
    return 0;
}
#endif
#endif

#if defined(BIG_MULT) || defined(BIG_ALL)

void multTest()
{
    printf("\n========== MULT_TEST ============\n");
    BigInteger zero = stringToBigInteger("0");
    BigInteger A, B, result;
    A = stringToBigInteger("123");
    B = stringToBigInteger("-123");

    result = prod(zero, A);
    printf("Additive identity test. Expect: 0. Received: ");
    printBigInteger(stdout, result);
    printf("\n");
    freeBigInteger(&result);

    result = prod(B, zero);
    printf("Additive identity test. Expect: 0. Received: ");
    printBigInteger(stdout, result);
    printf("\n");
    freeBigInteger(&result);
    freeBigInteger(&B);
    freeBigInteger(&A);

    A = stringToBigInteger("42759459832403984");
    B = stringToBigInteger("0928409278590");
    result = newBigInteger();

    // A + B
    multiply(result, A, B);

    printf("Multiplying A and B. Expect: %s. Received: ", "39698279255900265090881902560");
    printBigInteger(stdout, result);
    printf("\n");
    freeBigInteger(&result);
    freeBigInteger(&B);

    // A + (-B)
    B = stringToBigInteger("-298034710947298075298");
    result = newBigInteger();
    multiply(result, A, B);

    printf("Multiplying A and B. Expect: -12743803251413123974303075695587187232. Received: ");
    printBigInteger(stdout, result);
    printf("\n");

    freeBigInteger(&result);
    freeBigInteger(&B);

    // -A + B
    freeBigInteger(&A);
    A = stringToBigInteger("-403298408435798");
    B = stringToBigInteger("89741877784654");
    result = prod(A, B);

    printf("Multiplying A and B. Expect: -36192756480590855885628643892. Received: ");
    printBigInteger(stdout, result);
    printf("\n");

    // -A + -B = -1 * (A + B)
    freeBigInteger(&result);
    freeBigInteger(&B);

    B = stringToBigInteger("-3546876344545647");
    result = prod(A, B);

    printf("Multiplying A and B. Expect: 1430449584673840535630279871306. Received: ");
    printBigInteger(stdout, result);
    printf("\n");

    freeBigInteger(&result);
    freeBigInteger(&B);
    freeBigInteger(&A);

    /* TEST 2 */

    // A + (-A)
    A = stringToBigInteger("423");
    B = stringToBigInteger("-423");

    result = prod(A, B);

    printf("Additive inverse test. Expect: -178929. Received: ");
    printBigInteger(stdout, result);
    printf("\n");

    freeBigInteger(&result);
    freeBigInteger(&B);

    // *(&A) + *(&A)
    result = newBigInteger();
    multiply(result, A, A);

    printf("Same operand test. Expect: 178929. Received: ");
    printBigInteger(stdout, result);
    printf("\n");
    freeBigInteger(&result);

    multiply(A, A, A);

    printf("Same operands as result. Expect: 178929. Received: ");
    printBigInteger(stdout, A);
    printf("\n");

    multiply(A, A, zero);
    printf("Same operands, additive identity. Expect: 0. Received: ");
    printBigInteger(stdout, A);
    printf("\n");

    multiply(zero, zero, zero);
    printf("Same operands, additive identity multiplying itself. Expect: 0. Received: ");
    printBigInteger(stdout, zero);
    printf("\n");

    freeBigInteger(&A);
    freeBigInteger(&zero);
}

#ifndef BIG_ALL
int main()
{
    multTest();
    return 0;
}
#endif
#endif

#ifdef BIG_ALL

int main()
{
    signTest();
    compareTest();
    equalsTest();
    mzTest();
    negateTest();
    stringifyTest();
    copyTest();
    addTest();
    subTest();
    multTest();
}

#endif

#ifdef BIG_CLIENT

int main()
{
    BigInteger a = stringToBigInteger("+3189566462487811091227227147402491544571291393281176312010139755183236974267609213743829302511376449515674273975676687352572518277600691452752596601664144527083407266659844566250423081394323224205730559497731244908570258144382434993615527715279245458575748425704011410298353791455241119422656334302248789271390496295471505776230634488226949885438099736336409507725258176249154397617753804468121862768108593416975113077179372125187496569012066512508747121545329655991775552998807087585823693748186205718827916166245131445981248415414272479358931252807709759245072390948637992472622863358323632418033419204070741782370274963765779284394139044160259284632154032117532364506639020707270283728265349082169279155655370345259801545194868771871546876263377836263396178582214952131999431684844172624978653962647169147456332619657924544736921766535731192788585927985444965822955936037220695260423130291458872058646826899875092739993949986439558415554520788443434205350057161718519501608309051089633921255113060");
    BigInteger b = stringToBigInteger("3729150928554702442414149175620649235932141254958609994754881086870354096432680978993974017043517393400280356415203677444742476780562224472222470125604137189551277980367362171212444067225678772359177116881449546540702038965861964164395654700469546344046303360514086169267280531990390968431018269967602725536356259464264923063986493485397252686907417460537701591125888290685214292533968150707980477146032778794315480469863328540030290972792502783859859312394797018261343321636183470041086019167175518395121825556034255391119033649639704413255260359955129701152148110535199153752017052945142999636863598376486516579220721168164096768678790800097521542472312143230487291626846272595887082025564868641148258377596132372685002001938955882516194044765800040395427510589581300192931326584649602225549954316147167407238954252097008977547037150046068855444291240639911613631879542764207788151538410067602495753941387332622510027115559538659227916526367307536124261995940902191801615884809192434029710130888164");

    BigInteger c = prod(a, b);

    printf("a*b = ");
    printBigInteger(stdout, c);
    printf("\n");

    freeBigInteger(&c);
    freeBigInteger(&b);
    freeBigInteger(&a);
    return 0;
}

#endif