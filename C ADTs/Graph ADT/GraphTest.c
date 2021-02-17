/****************************************************************************************
* Name: Donovan Henry
* CruzID: dphenry
* Assignment: PA3
* File: GraphTest.c
*****************************************************************************************/

#include "Graph.h"

#define ALL

#if defined(CONSTRUCTOR_DESTRUCTOR) || defined(ALL)

#ifndef ALL

int main()
{
    constructorDestructor();
}

#endif

void constructorDestructor()
{
    printf("\n========== CONSTRUCTOR/DESTRUCTOR TEST ===========\n");
    printf("Test will have succeeded if no seg faults. Constructing graph of size 4 and immediately destructing. Then creating graph of size 4 adding an edge between vertex 1 and 4 and then destructing.\n");

    Graph g = newGraph(4);

    freeGraph(&g);

    Graph h = newGraph(4);

    addEdge(h, 1, 4);

    freeGraph(&h);
}

#endif

#if defined(GET_ORDER) || defined(ALL)

#ifndef ALL

int main()
{
    orderTest();
}

#endif

void orderTest()
{
    printf("\n========== GET_ORDER TEST ===========\n");

    Graph g = newGraph(4);

    printf("Created graph of size 4. Calling get order - Expectation: 4. getOrder returns: %d\n", getOrder(g));

    freeGraph(&g);
}

#endif

#if defined(GET_SIZE) || defined(ALL)

#ifndef ALL

int main()
{
    sizeTest();
}

#endif

void sizeTest()
{
    printf("\n========== GET_SIZE TEST ===========\n");

    Graph g = newGraph(4);

    printf("Testing size of graph with no edges. Expect size: 0. getSize returns: %d\n", getSize(g));

    addEdge(g, 1, 4);
    addEdge(g, 1, 2);
    addArc(g, 2, 3);

    printf("Added 2 edges and one arc. Expect size: 3. getSize returns: %d\n", getSize(g));

    addEdge(g, 1, 4);
    addArc(g, 2, 3);

    printf("Added a duplicate edge and a duplicate arc. Expect size: 3. getSize returns: %d\n", getSize(g));

    freeGraph(&g);
}

#endif

#if defined(GET_SOURCE) || defined(ALL)

#ifndef ALL

int main()
{
    sourceTest();
}

#endif

void sourceTest()
{
    printf("\n========== GET_SOURCE TEST ===========\n");

    Graph g = newGraph(4);

    printf("Graph with no edges. BFS not called yet. Expect source: NIL (-1). getSource returns: %d\n", getSource(g));

    BFS(g, 1);

    printf("Graph with no edges. BFS has been called. Expect source: 1. getSource returns: %d\n", getSource(g));

    addEdge(g, 1, 4);
    addEdge(g, 2, 3);
    addEdge(g, 2, 4);

    printf("Graph with edges. Expect source: 1. getSource returns: %d\n", getSource(g));

    BFS(g, 4);

    printf("Graph with edges. Expect source: 4. getSource returns: %d\n", getSource(g));

    freeGraph(&g);
}

#endif

#if defined(GET_PARENT) || defined(ALL)

#ifndef ALL

int main()
{
    parentTest();
}

#endif

void parentTest()
{
    printf("\n========== GET_PARENT TEST ===========\n");

    Graph g = newGraph(10);

    for (int i = 2; i < getOrder(g); i++)
    {
        addEdge(g, i, i - 1);
    }

    printf("Pre-BFS call. Expect all parents to be NIL (result of 'n'). Any parents found to be not NIL? [y/n]: ");

    char nonNILParent = 'n';

    for (int i = 1; i < getOrder(g); i++)
    {
        if (getParent(g, i) != NIL)
        {
            nonNILParent = 'y';
        }
    }

    printf("%c\n", nonNILParent);

    BFS(g, 1);

    printf("BFS has been called. Calling parent of source vertex. Expect: NIL (-1). getParent returns: %d\n", getParent(g, 1));
    printf("Calling parent of vertex adjacent to source. Expect: 1. getParent returns: %d\n", getParent(g, 2));
    printf("Calling parent of disconnected vrtex. Expect: NIL (-1). getParent returns: %d\n", getParent(g, 10));

    freeGraph(&g);
}

#endif

#if defined(GET_DIST) || defined(ALL)

#ifndef ALL

int main()
{
    distanceTest();
}

#endif

void distanceTest()
{
    printf("\n========== GET_DISTANCE TEST ===========\n");

    Graph g = newGraph(10);

    for (int i = 2; i < getOrder(g); i++)
    {
        addEdge(g, i, i - 1);
    }

    printf("Pre-BFS call. Expect all distances to be INF (result of 'n'). Any distances found to be not INF? [y/n]: ");

    char nonINFDIST = 'n';

    for (int i = 1; i < getOrder(g); i++)
    {
        if (getDist(g, i) != INF)
        {
            nonINFDIST = 'y';
        }
    }

    printf("%c\n", nonINFDIST);

    BFS(g, 1);

    printf("BFS has been called. Calling dist of source vertex. Expect: 0. getDist returns: %d\n", getDist(g, 1));
    printf("Calling dist of vertex adjacent to source. Expect: 1. getDist returns: %d\n", getDist(g, 2));
    printf("Calling dist of disconnected vrtex. Expect: INF (-12). getDist returns: %d\n", getDist(g, 10));

    freeGraph(&g);
}

#endif

#if defined(GET_DISCOVER) || defined(ALL)

#ifndef ALL

int main()
{
    discoverTest();
}

#endif

void discoverTest()
{
    printf("\n========== GET_DISCOVER TEST ===========\n");
    List S = newList();

    Graph g = newGraph(4);

    addEdge(g, 1, 2);
    addEdge(g, 2, 3);
    addEdge(g, 3, 4);
    append(S, 1);
    append(S, 2);
    append(S, 3);
    append(S, 4);

    printf("Pre-DFS call. Expect all discovers to be UNDEF (result of 'n'). Any discovers found to be not UNDEF? [y/n]: ");

    char nonUNDEFDIST = 'n';

    for (int i = 1; i < getOrder(g); i++)
    {
        if (getDiscover(g, i) != UNDEF)
        {
            nonUNDEFDIST = 'y';
        }
    }

    printf("%c\n", nonUNDEFDIST);

    DFS(g, S);

    printf("DFS has been called. Calling dist of first vertex. Expect: 1. getDiscover returns: %d\n", getDiscover(g, 1));
    printf("Calling Discover of lowest vertex adjacent to source. Expect: 2. getDiscover returns: %d\n", getDiscover(g, 2));

    freeList(&S);
    freeGraph(&g);
}

#endif

#if defined(GET_FINISH) || defined(ALL)

#ifndef ALL

int main()
{
    finishTest();
}

#endif

void finishTest()
{
    printf("\n========== GET_FINISH TEST ===========\n");

    Graph g = newGraph(4);
    List S = newList();

    addArc(g, 1, 2);
    addArc(g, 2, 3);
    addArc(g, 3, 4);
    append(S, 1);
    append(S, 2);
    append(S, 3);
    append(S, 4);

    printf("Pre-DFS call. Expect all finishes to be UNDEF (result of 'n'). Any finishes found to be not UNDEF? [y/n]: ");

    char nonUNDEFDIST = 'n';

    for (int i = 1; i < getOrder(g); i++)
    {
        if (getFinish(g, i) != UNDEF)
        {
            nonUNDEFDIST = 'y';
        }
    }

    printf("%c\n", nonUNDEFDIST);

    DFS(g, S);

    printf("DFS has been called. Calling dist of first vertex. Expect: 2 * |V| = 8 getFinish returns: %d\n", getFinish(g, 1));
    printf("Calling Finish of lowest vertex adjacent to source. Expect: 2 * |V| - 1 = 7. getFinish returns: %d\n", getFinish(g, 2));

    freeList(&S);
    freeGraph(&g);
}

#endif

#if defined(GET_PATH) || defined(ALL)

#ifndef ALL

int main()
{
    pathTest();
}

#endif

void pathTest()
{
    printf("\n========== GET_PATH TEST ===========\n");

    Graph g = newGraph(10);

    for (int i = 2; i < getOrder(g); i++)
    {
        addEdge(g, i, i - 1);
    }

    printf("Pre-BFS call. Expect all paths to be length 1 (result of 'n'). Any lengths found to be not 1? [y/n]: ");

    char nonEmptyPath = 'n';

    for (int i = 1; i < getOrder(g); i++)
    {
        List shortestPath = newList();

        getPath(shortestPath, g, i);

        if (length(shortestPath) != 1)
        {
            nonEmptyPath = 'y';
        }

        freeList(&shortestPath);
    }

    printf("%c\n", nonEmptyPath);

    BFS(g, 1);

    List tempPath = newList();

    getPath(tempPath, g, 1);
    printf("BFS has been called. Calling getPath of source vertex. Expect: 1. getPath yields: ");
    printList(stdout, tempPath);
    clear(tempPath);

    getPath(tempPath, g, 2);
    printf("\nCleared list. Calling getPath of vertex adjacent to source. Expect: 1 2. getPath yields: ");
    printList(stdout, tempPath);

    getPath(tempPath, g, 10);
    printf("\nDid not clear list. Calling getPath of disconnected vrtex. Expect: 1 2 NIL(-1). getPath yields: ");
    printList(stdout, tempPath);

    freeList(&tempPath);
    freeGraph(&g);
}

#endif

#if defined(MAKE_NULL) || defined(ALL)

#ifndef ALL

int main()
{
    makeNullTest();
}

#endif

void makeNullTest()
{
    printf("\n========== MAKE_NULL TEST ===========\n");

    Graph g = newGraph(4);

    addEdge(g, 1, 2);
    addEdge(g, 2, 3);
    addEdge(g, 3, 4);

    printf("Print Graph before make null:\n");
    printGraph(stdout, g);

    makeNull(g);

    printf("\nPrint graph after make null:\n");
    printGraph(stdout, g);

    freeGraph(&g);
}

#endif

#if defined(ADD_EDGE) || defined(ALL)

#ifndef ALL

int main()
{
    edgeTest();
}

#endif

void edgeTest()
{
    printf("\n========== ADD_EDGE TEST ===========\n");

    Graph g = newGraph(4);

    printf("Print graph before adding edges:\n");
    printGraph(stdout, g);

    addEdge(g, 1, 4);
    addEdge(g, 2, 3);
    addEdge(g, 2, 4);

    printf("\nPrint graph after adding edges. Expect:\n1: 4\n2: 3 4\n3: 2\n4: 1 2\nPrintGraph yields:\n");
    printGraph(stdout, g);

    freeGraph(&g);
}

#endif

#if defined(ADD_ARC) || defined(ALL)

#ifndef ALL

int main()
{
    arcTest();
}

#endif

void arcTest()
{
    printf("\n========== ADD_ARC TEST ===========\n");

    Graph g = newGraph(4);

    printf("Print graph before adding arcs:\n");
    printGraph(stdout, g);

    addArc(g, 1, 4);
    addArc(g, 2, 3);
    addArc(g, 2, 4);

    printf("\nPrint graph after adding arcs. Expect:\n1: 4\n2: 3 4\n3: \n4: \nPrintGraph yields:\n");
    printGraph(stdout, g);

    freeGraph(&g);
}

#endif

#if defined(BFS) || defined(ALL)

#ifndef ALL

int main()
{
    bfsTest();
}

#endif

void bfsTest()
{
    printf("\n========== BFS TEST ===========\n");

    printf("BFS has been tested throughout the program. If expected values above are correct then BFS will have succeeded in all.\n");
}

#endif

#if defined(DFS) || defined(ALL)

#ifndef ALL

int main()
{
    dfsTest();
}

#endif

void dfsTest()
{
    printf("\n========== DFS TEST ===========\n");
}

#endif

#if defined(PRINT_GRAPH) || defined(ALL)

#ifndef ALL

int main()
{
    printGraphTest();
}

#endif

void printGraphTest()
{
    printf("\n========== PRINT_GRAPH TEST ===========\n");

    Graph g = newGraph(4);

    printf("Calling printGraph on an edgeless graph. Expect:\n1:\n2:\n3:\n4:\nPrintGraph yields:\n");
    printGraph(stdout, g);

    addEdge(g, 1, 2);
    addEdge(g, 3, 4);
    addEdge(g, 2, 3);
    addEdge(g, 2, 4);

    printf("\nCalling printGraph on graph with edges. Expect:\n1: 2\n2: 1 3 4\n3: 2 4\n4: 2 3\nPrintGraph yields:\n");
    printGraph(stdout, g);

    freeGraph(&g);
}

#endif

#if defined(COPY_GRAPH) || defined(ALL)

#ifndef ALL
int main(int argc, char *argv[])
{
    copyTest(argc, argv);
    return 0;
}
#endif

void copyTest()
{
    printf("\n============ COPYGRAPH_TEST ==============\n");

    Graph A = newGraph(5);
    Graph B = newGraph(5);

    // printf("Pre-insertions expect EXIT_FAILURE: %d", back(A));

    addArc(A, 1, 4);
    addArc(A, 1, 3);
    addArc(A, 2, 1);
    addArc(A, 2, 4);
    addArc(A, 3, 4);
    addArc(A, 3, 1);
    addArc(A, 4, 1);

    addArc(B, 1, 2);
    addArc(B, 1, 4);
    addArc(B, 2, 3);
    addArc(B, 2, 1);
    addArc(B, 3, 1);
    addArc(B, 3, 2);
    addArc(B, 4, 2);

    printf("Equals | Post-insertion on B with diff values, expect diff print results. Print A:\n");
    printGraph(stdout, A);
    printf("\n\nPrint B:\n");
    printGraph(stdout, B);

    makeNull(B);

    addArc(B, 1, 4);
    addArc(B, 1, 3);
    addArc(B, 2, 1);
    addArc(B, 2, 4);
    addArc(B, 3, 4);
    addArc(B, 3, 1);
    addArc(B, 4, 1);

    printf("\nEquals | Post-insertion on B with diff values, expect same print results. Print A:\n");
    printGraph(stdout, A);
    printf("\n\nPrint B:\n");
    printGraph(stdout, B);

    makeNull(B);
    freeGraph(&B);

    B = copyGraph(A);

    printf("\nEquals | Post-insertion copy, expect same print results. Print A:\n");
    printGraph(stdout, A);
    printf("\n\nPrint B:\n");
    printGraph(stdout, B);
    printf("\n\n");

    freeGraph(&A);
    freeGraph(&B);
}

#endif

#if defined(TRANSPOSE_GRAPH) || defined(ALL)

#ifndef ALL
int main(int argc, char *argv[])
{
    transposeTest(argc, argv);
    return 0;
}
#endif

void transposeTest()
{
    printf("\n============ TRANSPOSE_TEST ==============\n");

    Graph A = newGraph(4);
    Graph B;

    // printf("Pre-insertions expect EXIT_FAILURE: %d", back(A));

    for (int i = 1; i <= 3; i++)
        addEdge(A, i, i + 1);

    printf("Equals | Graph A:\n");
    printGraph(stdout, A);

    B = transpose(A);

    printf("\nEquals | Printing Transposed_Graph A. Expect:\n1: 2\n2: 1 3\n3: 2 4\n4: 3\n\n");
    printGraph(stdout, B);

    freeGraph(&A);
    freeGraph(&B);
}

#endif

#ifdef ALL

int main()
{
    constructorDestructor();
    printf("\nConstructor/Destructor executed without error.\n");

    orderTest();
    printf("\nOrderTest executed without error.\n");

    sizeTest();
    printf("\nSizeTest executed without error.\n");

    sourceTest();
    printf("\nSourceTest executed without error.\n");

    parentTest();
    printf("\nParentTest executed without error.\n");

    distanceTest();
    printf("\nDistanceTest executed without error.\n");

    discoverTest();
    printf("\nDiscoverTest executed without error.\n");

    finishTest();
    printf("\nFinishTest executed without error.\n");

    pathTest();
    printf("\n\nPathTest executed without error.\n");

    makeNullTest();
    printf("\n\nMakeNullTest executed without error.\n");

    edgeTest();
    printf("\n\nEdgeTest executed without error.\n");

    arcTest();
    printf("\n\nArcTest executed without error.\n");

    bfsTest();
    printf("\nBFSTest executed without error.\n");

    dfsTest();
    printf("\nDFSTest executed without error.\n");

    copyTest();
    printf("\n\nCopyGraphTest executed without error.\n");

    transposeTest();
    printf("\n\nTransposeGraphTest executed without error.\n");

    printGraphTest();
    printf("\n\nPrintGraphTest executed without error.\n");
}

#endif