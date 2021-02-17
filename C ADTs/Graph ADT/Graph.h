/****************************************************************************************
* Name: Donovan Henry
* CruzID: dphenry
* Assignment: PA3
* File: Graph.h
*****************************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include "List.h"

#define NIL -1
#define UNDEF 0
#define INF -12

typedef struct GraphObj *Graph;

// Constructors-Destructors
Graph newGraph(int n);
void freeGraph(Graph *pG);
// Access functions

int getOrder(Graph G);
int getSize(Graph G);

// Returns the most recent source vertex used in BFS
// Returns NIL if BFS has yet to be called
// Pre: G is not NULL
int getSource(Graph G);

// Returns the distance from a source to a given vertex U
// Returns  if BFS has yet to be called
// Pre: G is not NULL, 1 <= u <= order(Graph)
int getDist(Graph G, int u);

// Returns the shortest path from a source to a given vertex
// Returns  if BFS has yet to be called
// Pre: G is not NULL, L is not NULL, 1 <= u <= order(Graph)
void getPath(List L, Graph G, int u);

int getParent(Graph G, int u);   /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u);   /* Pre: 1<=u<=n=getOrder(G) */
// Manipulation procedures

// Returns the graph to it's null state.
// Pre: G is not NULL
void makeNull(Graph G);
void addArc(Graph G, int u, int v);  /* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
// Performs a breadth-first search to find the distance
// from a source to every vertex v in the graph G.
// Pre: G is not NULL, 1 <= s <= order(Graph)
void BFS(Graph G, int s);
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */
// Other Functions
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE *out, Graph G);

#endif