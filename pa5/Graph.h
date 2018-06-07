/* Evan Suther
 * Cruzid: esuther
 * Assignment: PA5
 * Component: Graph.h
 * Function: exports the required functions of the Graph adt, along with constants NIL and INF
 * and defines Graph to be a pointer to a GraphObj
 */

#ifndef GRAPH_H
#define GRAPH_H
#include "List.h"
/* Spec-required exported constants */
#define NIL -99
#define UNDEF -100
/* Constructors-Destructors */
Graph newGraph(int n);
void freeGraph(Graph* pG);
/* Access functions */
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
/* Manipulation procedures */
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */
/* Other Functions */
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);
#endif