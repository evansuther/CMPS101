/* Evan Suther
 * Cruzid: esuther
 * Assignment: PA4
 * Component: Graph.h
 * Function: exports the required functions of the Graph adt, along with constants NIL and INF
 * and defines Graph to be a pointer to a GraphObj
 */
 
#ifndef GRAPH_H
#define GRAPH_H
#include "List.h"
// defined for use in BFS and checking results of it externally
#define NIL -99
#define INF -100
typedef struct GraphObj* Graph;
/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);
#endif