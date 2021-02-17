/****************************************************************************************
* Name: Donovan Henry
* CruzID: dphenry
* Assignment: PA3
* File: Graph.c
*****************************************************************************************/

#include "Graph.h"

typedef struct GraphObj
{
    List *adj;
    int *color;
    int *discover;
    int *distance;
    int *finish;
    int *parent;

    int lastSource;
    int order;
    int size;
} GraphObj;

// Constructors-Destructors
Graph newGraph(int n)
{
    Graph g = (Graph)malloc(sizeof(GraphObj));

    g->order = n;
    g->size = 0;
    g->lastSource = NIL;

    g->adj = (List *)malloc((n + 1) * sizeof(List));
    g->color = (int *)malloc((n + 1) * sizeof(int));
    g->discover = (int *)malloc((n + 1) * sizeof(int));
    g->finish = (int *)malloc((n + 1) * sizeof(int));
    g->parent = (int *)malloc((n + 1) * sizeof(int));
    g->distance = (int *)malloc(sizeof(int) * (n + 1));

    for (int i = 1; i <= g->order; i++)
    {
        g->adj[i] = newList();
        g->color[i] = 'w';
        g->discover[i] = UNDEF;
        g->finish[i] = UNDEF;
        g->parent[i] = NIL;
        g->distance[i] = INF;
    }

    return g;
}

void freeGraph(Graph *pG)
{
    if (pG != NULL && *pG != NULL)
    {
        for (int i = 1; i <= (*pG)->order; i++)
            freeList(&((*pG)->adj[i]));

        free((*pG)->adj);
        free((*pG)->color);
        free((*pG)->discover);
        free((*pG)->finish);
        free((*pG)->distance);
        free((*pG)->parent);
        free(*pG);
        *pG = NULL;
    }
}

// Helper functions
void DFSVisit(Graph G, List S, int u, int *time);

// Access functions
int getOrder(Graph G)
{
    if (G == NULL)
    {
        printf("Error: NULL Graph in getOrder. Exiting...");
        exit(EXIT_FAILURE);
    }

    return G->order;
}
int getSize(Graph G)
{
    if (G == NULL)
    {
        printf("Error: NULL Graph in getSize. Exiting...");
        exit(EXIT_FAILURE);
    }

    return G->size;
}

// Returns the most recent source vertex used in BFS
// Returns NIL if BFS has yet to be called
// Pre: G is not NULL
int getSource(Graph G)
{
    if (G == NULL)
    {
        printf("Error: G is NULL. Exiting...");
        exit(EXIT_FAILURE);
    }

    return G->lastSource;
}

int getParent(Graph G, int u)
{
    if (G == NULL)
    {
        printf("Error: NULL Graph in getParent. Exiting...");
        exit(EXIT_FAILURE);
    }

    if (u <= 0 || u > G->order)
    {
        printf("Error: Vertex out of bounds in getParent. Exiting...");
        exit(EXIT_FAILURE);
    }

    return G->parent[u];
}

// Returns the distance from a source to a given vertex U
// Returns  if BFS has yet to be called
// Pre: G is not NULL, 1 <= u <= order(Graph)
int getDist(Graph G, int u)
{
    if (G == NULL)
    {
        printf("Error: G is NULL in getDist. Exiting...");
        exit(EXIT_FAILURE);
    }

    if (u <= 0 || u > G->order)
    {
        printf("Error: Vertex out of bounds in getDist. Exiting...");
        exit(EXIT_FAILURE);
    }

    return G->distance[u];
}

// Returns the shortest path from a source to a given vertex
// Returns  if BFS has yet to be called
// Pre: G is not NULL, L is not NULL, 1 <= u <= order(Graph)
void getPath(List L, Graph G, int u)
{
    if (G == NULL)
    {
        printf("Error: Graph is NULL in getPath. Exiting...");
        exit(EXIT_FAILURE);
    }

    if (L == NULL)
    {
        printf("Error: List is NULL in getPath. Exiting...");
        exit(EXIT_FAILURE);
    }

    if (u <= 0 || u > G->order)
    {
        printf("Error: Source out of bounds in getPath. Exiting...");
        exit(EXIT_FAILURE);
    }

    if (G->parent[u] == NIL && u != G->lastSource)
    {
        append(L, NIL);
        return;
    }

    append(L, u);
    moveBack(L);

    while (u != G->lastSource)
    {
        u = G->parent[u];

        insertBefore(L, u);
        movePrev(L);
    }
}

/* Pre: 1<=u<=n=getOrder(G) */

int getDiscover(Graph G, int u)
{
    if (G == NULL)
    {
        printf("Error: NULL Graph in getDiscover. Exiting...");
        exit(EXIT_FAILURE);
    }

    if (u <= 0 || u > G->order)
    {
        printf("Error: Vertex out of bounds in getDiscover. Exiting...");
        exit(EXIT_FAILURE);
    }

    return G->discover[u];
}

/* Pre: 1<=u<=n=getOrder(G) */

int getFinish(Graph G, int u)
{
    if (G == NULL)
    {
        printf("Error: NULL Graph in getFinish. Exiting...");
        exit(EXIT_FAILURE);
    }

    if (u <= 0 || u > G->order)
    {
        printf("Error: Vertex out of bounds in getFinish. Exiting...");
        exit(EXIT_FAILURE);
    }

    return G->finish[u];
}

/* Pre: 1<=u<=n=getOrder(G) */

// Manipulation procedures

// Returns the graph to it's null state.
// Pre: G is not NULL
void makeNull(Graph G)
{
    if (G == NULL)
    {
        printf("Error: G is NULL in makeNull. Exiting...");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i <= G->order; i++)
    {
        clear(G->adj[i]);
    }

    G->size = 0;
}

void addArc(Graph G, int u, int v)
{
    if (G == NULL)
    {
        printf("Error: NULL Graph in addArc. Exiting...");
        exit(EXIT_FAILURE);
    }

    if (u <= 0 || u > G->order || v <= 0 || v > G->order)
    {
        printf("Error: Vertex out of bounds in addArc. Exiting...");
        exit(EXIT_FAILURE);
    }

    List adjVertices = G->adj[u];
    G->size++;

    if (length(adjVertices) == 0)
    {
        append(adjVertices, v);
        return;
    }

    int inserted = 0;

    for (moveFront(adjVertices); index(adjVertices) != -1; moveNext(adjVertices))
    {
        if (get(adjVertices) == v)
        {
            inserted = 1;
            G->size--;
            break;
        }
        else if (get(adjVertices) > v)
        {
            insertBefore(adjVertices, v);
            inserted = 1;
            break;
        }
    }

    if (inserted == 0)
    {
        append(adjVertices, v);
    }
}

/* Pre: 1<=u<=n, 1<=v<=n */

void addEdge(Graph G, int u, int v)
{
    if (G == NULL)
    {
        printf("Error: NULL Graph in addEdge. Exiting...");
        exit(EXIT_FAILURE);
    }

    if (u <= 0 || u > G->order || v <= 0 || v > G->order)
    {
        printf("Error: Vertex out of bounds in addEdge. Exiting...");
        exit(EXIT_FAILURE);
    }

    int oldSize = G->size;
    addArc(G, u, v);
    addArc(G, v, u);
    G->size = G->size == oldSize ? G->size : G->size - 1;
}

// Performs a breadth-first search to find the distance
// from a source to every other vertex v in the graph G.
// Pre: G is not NULL, 1 <= s <= order(Graph)
void BFS(Graph G, int s)
{
    if (G == NULL)
    {
        printf("Error: G is NULL in BFS. Exiting...");
        exit(EXIT_FAILURE);
    }

    if (s <= 0 || s >= getOrder(G) + 1)
    {
        printf("Error: Source isn't an element of V in BFS. Exiting...");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= G->order; i++)
    {
        if (i != s)
        {
            G->color[i] = 'w';
            G->distance[i] = INF;
            G->parent[i] = NIL;
        }
    }

    List queue = newList();
    prepend(queue, s);
    G->color[s] = 'g';
    G->distance[s] = 0;
    G->parent[s] = NIL;
    G->lastSource = s > 0 ? s : G->lastSource;

    while (length(queue) > 0)
    {
        int u = front(queue);
        deleteFront(queue);
        List adj = G->adj[u];

        if (length(adj) != 0)
        {
            for (moveFront(adj); index(adj) >= 0; moveNext(adj))
            {
                int v = get(adj);

                if (G->color[v] == 'w')
                {
                    G->color[v] = 'g';
                    append(queue, v);
                    G->distance[v] = G->distance[u] + 1;
                    G->parent[v] = u;
                }
            }
        }

        G->color[u] = 'b';
    }

    freeList(&queue);
}

/* Pre: 1<=u<=n, 1<=v<=n */

void DFS(Graph G, List S)
{
    if (G == NULL)
    {
        printf("Error: NULL Graph in DFS. Exiting...");
        exit(EXIT_FAILURE);
    }

    if (S == NULL)
    {
        printf("Error: NULL List in DFS. Exiting...");
        exit(EXIT_FAILURE);
    }

    if (length(S) != G->order)
    {
        printf("Error: Input list and Graph contain different number of vertices in DFS. Exiting...");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= G->order; i++)
    {
        G->color[i] = 'w';
        G->parent[i] = NIL;
    }

    int time = 0;

    int stackLength = length(S);
    moveBack(S);

    for (int i = 0; i < stackLength; i++)
    {
        if (index(S) != -1)
        {
            int u = front(S);

            if (G->color[u] == 'w')
            {
                DFSVisit(G, S, u, &time);
            }
            deleteFront(S);
        }
    }
}

void DFSVisit(Graph G, List S, int u, int *time)
{
    G->discover[u] = ++(*time);
    G->color[u] = 'g';

    if (length(G->adj[u]) > 0)
    {
        for (moveFront(G->adj[u]); index(G->adj[u]) != -1; moveNext(G->adj[u]))
        {
            if (G->color[get(G->adj[u])] == 'w')
            {
                G->parent[get(G->adj[u])] = u;
                DFSVisit(G, S, get(G->adj[u]), time);
            }
        }
    }

    G->color[u] = 'b';
    (*time)++;
    G->finish[u] = *time;
    insertAfter(S, u);
}

/* Pre: length(S)==getOrder(G) */

// Other Functions
Graph transpose(Graph G)
{
    if (G == NULL)
    {
        printf("Error: NULL Graph in transpose. Exiting...");
        exit(EXIT_FAILURE);
    }

    Graph transp = newGraph(G->order);

    for (int i = 1; i <= G->order; i++)
    {
        if (length(G->adj[i]) > 0)
        {
            for (moveFront(G->adj[i]); index(G->adj[i]) != -1; moveNext(G->adj[i]))
            {
                int v = get(G->adj[i]);
                addArc(transp, v, i);
            }
        }
    }

    return transp;
}

Graph copyGraph(Graph G)
{
    if (G == NULL)
    {
        printf("Error: NULL Graph in copyGraph. Exiting...");
        exit(EXIT_FAILURE);
    }

    Graph copy = newGraph(G->order);

    for (int i = 1; i <= G->order; i++)
    {
        freeList(&(copy->adj[i]));
        copy->adj[i] = copyList(G->adj[i]);
        copy->color[i] = G->color[i];
        copy->discover[i] = G->discover[i];
        copy->finish[i] = G->discover[i];
        copy->parent[i] = G->parent[i];
    }

    copy->size = G->size;
    copy->order = G->order;

    return copy;
}

void printGraph(FILE *out, Graph G)
{
    if (out == NULL)
    {
        printf("Error: NULL input file in printGraph. Exiting...");
        exit(EXIT_FAILURE);
    }

    if (G == NULL)
    {
        printf("Error: NULL Graph in printGraph. Exiting...");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= getOrder(G); i++)
    {
        fprintf(out, "%d: ", i);
        if (length(G->adj[i]) != 0)
        {
            printList(out, G->adj[i]);
        }

        fprintf(out, "%s", i == G->order ? "" : "\n");
    }
}