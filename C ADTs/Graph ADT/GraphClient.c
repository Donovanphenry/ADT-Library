//-----------------------------------------------------------------------------
// GraphClient.c
// Test client for the Graph ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char *argv[])
{
    int i, s, max, min, d, n = 35;
    List Central = newList(); // central vertices
    List P = newList();       // peripheral vertices
    List E = newList();       // eccentricities
    Graph G = NULL;

    // Build graph G
    G = newGraph(n);
    for (i = 1; i < n; i++)
    {
        if (i % 7 != 0)
            addEdge(G, i, i + 1);
        if (i <= 28)
            addEdge(G, i, i + 7);
    }
    addEdge(G, 9, 31);
    addEdge(G, 17, 13);
    addEdge(G, 14, 33);

    // Print adjacency list representation of G
    printGraph(stdout, G);

    // Calculate the eccentricity of each vertex
    for (s = 1; s <= n; s++)
    {
        BFS(G, s);
        max = getDist(G, 1);
        for (i = 2; i <= n; i++)
        {
            d = getDist(G, i);
            max = (max < d ? d : max);
        }
        append(E, max);
    }

    // Determine the Radius and Diameter of G, as well as the Central and
    // Peripheral vertices.
    append(Central, 1);
    append(P, 1);
    min = max = front(E);
    moveFront(E);
    moveNext(E);
    for (i = 2; i <= n; i++)
    {
        d = get(E);
        if (d == min)
        {
            append(Central, i);
        }
        else if (d < min)
        {
            min = d;
            clear(Central);
            append(Central, i);
        }
        if (d == max)
        {
            append(P, i);
        }
        else if (d > max)
        {
            max = d;
            clear(P);
            append(P, i);
        }
        moveNext(E);
    }

    // Print results
    printf("\n");
    printf("Radius = %d\n", min);
    printf("Central vert%s: ", length(Central) == 1 ? "ex" : "ices");
    printList(stdout, Central);
    printf("\n");
    printf("Diameter = %d\n", max);
    printf("Peripheral vert%s: ", length(P) == 1 ? "ex" : "ices");
    printList(stdout, P);
    printf("\n");

    // Free objects
    freeList(&Central);
    freeList(&P);
    freeList(&E);
    freeGraph(&G);

    n = 8;
    List S = newList();
    G = newGraph(n);
    Graph T = NULL, C = NULL;

    for (i = 1; i <= n; i++)
        append(S, i);

    addArc(G, 1, 2);
    addArc(G, 1, 5);
    addArc(G, 2, 5);
    addArc(G, 2, 6);
    addArc(G, 3, 2);
    addArc(G, 3, 4);
    addArc(G, 3, 6);
    addArc(G, 3, 7);
    addArc(G, 3, 8);
    addArc(G, 6, 5);
    addArc(G, 6, 7);
    addArc(G, 8, 4);
    addArc(G, 8, 7);
    printGraph(stdout, G);

    DFS(G, S);
    fprintf(stdout, "\n");
    fprintf(stdout, "x:  d  f  p\n");
    for (i = 1; i <= n; i++)
    {
        fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
    }
    fprintf(stdout, "\n");
    printList(stdout, S);
    fprintf(stdout, "\n");

    // T = transpose(G);
    T = newGraph(n);
    addArc(T, 2, 1);
    addArc(T, 2, 3);
    addArc(T, 4, 3);
    addArc(T, 4, 8);
    addArc(T, 5, 1);
    addArc(T, 5, 2);
    addArc(T, 5, 6);
    addArc(T, 6, 2);
    addArc(T, 6, 3);
    addArc(T, 7, 3);
    addArc(T, 7, 6);
    addArc(T, 7, 8);
    addArc(T, 8, 3);

    C = copyGraph(G);
    fprintf(stdout, "\nPrinting Copy: \n");
    printGraph(stdout, C);
    fprintf(stdout, "\n\nPrinting Transpose:\n");
    printGraph(stdout, T);
    fprintf(stdout, "\n");

    DFS(T, S);
    fprintf(stdout, "\nDFS results of transpose\n");
    fprintf(stdout, "x:  d  f  p\n");
    for (i = 1; i <= n; i++)
    {
        fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
    }
    fprintf(stdout, "\n");
    printList(stdout, S);
    fprintf(stdout, "\n");

    freeList(&S);
    freeGraph(&G);
    freeGraph(&T);
    freeGraph(&C);
    return (0);
}