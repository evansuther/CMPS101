/* Evan Suther
 * Cruzid: esuther
 * Assignment: PA5
 * Component: Graph.c
 * Function: *
 */
 
// Graph.c defines structure and functions declared in Graph.h
#include "Graph.h"
// stdlib for EXIT_FAILURE and others
#include <stdlib.h>
// stdio to print to a file
#include <stdio.h>
// define black, gray, white for use in BFS
#define black 1
#define gray 0
#define white -1

/* Private Function Declarations */

void sortedInsert(List L, int v);

/* end Private Declarations */

/* Graph ADT */
typedef struct GraphObj {
   List* Adj;
   int* color;
   int* dist;
   int* parent;
   int order, size;
} GraphObj;

/* Constructors-Destructors */

// newGraph() 
// returns a reference to a new graph object containing n vertices and no edges
Graph newGraph(int n) {
   Graph G;
   G = malloc(sizeof(GraphObj));
	// initialize list array for Adj list representation of new Graph
   G->Adj = malloc(sizeof(List) * (n + 1));
   for (int i = 1; i <= n; i++) {
		G->Adj[i] = newList();
   }
	// initialize vertex color attribute array
   G->color = malloc(sizeof(int) * (n + 1));
	for (int i = 1; i <= n; i++) {
		G->color[i] = white;
   }
	// initialize vertex parent attribute array
	G->parent = malloc(sizeof(int) * (n + 1));
	for (int i = 1; i <= n; i++) {
		G->parent[i] = NIL;
   }
	// initialize vertex discover time array
   G->d = malloc(sizeof(int) * (n + 1));
	for (int i = 1; i <= n; i++) {
		G->d[i] = UNDEF;
   }
	// initialize vertex finish time array
	G->f = malloc(sizeof(int) * (n + 1));
	for (int i = 1; i <= n; i++) {
		G->f[i] = UNDEF;
   }
	// initialize fields
   G->order = n;
   G->size = 0;
   return (G);
}

// freeGraph()
// frees all heap memory associated with a graph and sets its Graph argument to NULL
void freeGraph(Graph* pG) {
   if (pG != NULL && *pG != NULL) {
		// free List refs in Adj list array
      for (int i = 1; i <= getOrder(*pG); i++) {
         freeList(&((*pG)->Adj[i]));
      }
		// free the arrays
      free((*pG)->Adj);
      free((*pG)->color);
		free((*pG)->parent);
      free((*pG)->d);
      free((*pG)->f);
      free(*pG);
      *pG = NULL;
   }
   return;
}

/* end Constructors-Destructors */

/* Access functions */

// getOrder()
// returns order(|v(G)|) of graph G
int getOrder(Graph G) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: getOrder(G) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
   return (G->order);
}

// getSize()
// returns size(|E(G)|) of graph G
int getSize(Graph G) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: getSize(G) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
   return (G->size);
}

// getParent()
// returns the parent of vertex u in the Depth-First Forest
// created by DFS(), or NIL if DFS() has not yet been called
/* Pre: 1<=u<=n=getOrder(G) */
int getParent(Graph G, int u) {
   if (G == NULL){
		fprintf(stderr, "Graph Error: getParent(G, u) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
	if  (!(1 <= u ) || !( u <= getOrder(G))){
		fprintf(stderr, "Graph Error: getParent(G, u) precondition not met: {1<= u <= getOrder(G)} \n");
		exit(EXIT_FAILURE);
	}
   return (G->parent[u]);
} 

// getDiscover()
// returns the discover time of vertex u,
// or UNDEF if DFS() has not yet been called
/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u) {
   if (G == NULL){
		fprintf(stderr, "Graph Error: getParent(G, u) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
	if  (!(1 <= u ) || !( u <= getOrder(G))){
		fprintf(stderr, "Graph Error: getDiscover(G, u) precondition not met: {1<= u <= getOrder(G)} \n");
		exit(EXIT_FAILURE);
	}
   return (G->d[u]);
} 
// getFinish()
// returns the finish time of vertex u,
// or UNDEF if DFS() has not yet been called
/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u) {
   if (G == NULL){
		fprintf(stderr, "Graph Error: getParent(G, u) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
	if  (!(1 <= u ) || !( u <= getOrder(G))){
		fprintf(stderr, "Graph Error: getFinish(G, u) precondition not met: {1<= u <= getOrder(G)} \n");
		exit(EXIT_FAILURE);
	}
   return (G->f[u]);
}  

/* end Access functions */

/* Manipulation procedures */

// addArc()
/* Pre: 1<=u<=n, 1<=v<=n */
void addArc(Graph G, int u, int v) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: addArc(G, u, v) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
	// spec preconditions
	if  (!(1 <= u ) || !( u <= getOrder(G))){
		fprintf(stderr, "Graph Error: addArc(G, u, v) precondition not met: {1<= u <= getOrder(G)}\n");
		exit(EXIT_FAILURE);
	}
	if  (!(1 <= v ) || !( v <= getOrder(G))){
		fprintf(stderr, "Graph Error: addArc(G, u, v) precondition not met: {1<= v <= getOrder(G)}\n");
		exit(EXIT_FAILURE);
	}
	// use helper function to keep lists sorted
	sortedInsert(G->Adj[u], v);
	G->size++;
	return;
} 

// addEdge()
/* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: addEdge(G, u, v) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
	// spec preconditions
	if  (!(1 <= u ) || !( u <= getOrder(G))){
		fprintf(stderr, "Graph Error: addEdge(G, u, v) precondition not met: {1<= u <= getOrder(G)}\n");
		exit(EXIT_FAILURE);
	}
	if  (!(1 <= v ) || !( v <= getOrder(G))){
		fprintf(stderr, "Graph Error: addEdge(G, u, v) precondition not met: {1<= v <= getOrder(G)}\n");
		exit(EXIT_FAILURE);
	}
	// use helper function to keep lists sorted
	sortedInsert(G->Adj[v], u);
	sortedInsert(G->Adj[u], v);
	G->size++;
	return;
} 

// DFS()
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */

/* end Manipulation procedures */

/* Other Functions */

// transpose()
Graph transpose(Graph G) {
	Graph T = newGraph(getOrder(G));
	for (int i = 1; i <= getOrder(G); i++) {
		moveFront((*List) G->Adj[i]);
		while (index((*List) G->Adj[i]) >= 0) {
			sortedInsert(get((*List) G->Adj[i]), (i);
			moveNext((*List) G->Adj[i]);
		}
	}
	return T;
}

// copyGraph()
Graph copyGraph(Graph G) {
	Graph cpy = newGraph(getOrder(G));
	for (int i = 1; i <= getOrder(G); i++) {
		if (length(G->Adj[i]) != 0) {
			cpy->Adj[i] = copyList(G->Adj[i]);
		}
	} 
}

// printGraph()
void printGraph(FILE* out , Graph G){
	// non-required preconditions
	if (G == NULL){
		fprintf(stderr, "Graph Error: printGraph(out, G) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (out == NULL){
		fprintf(stderr, "Graph Error: printGraph(out, G) called on NULL file reference\n");
		exit(EXIT_FAILURE);
	}
	// use printlist for all non-empty lists in G
	for (int i = 1; i <= getOrder(G); i++){
		fprintf(out, "%d: ", i);
		if (length(G->Adj[i]) >= 1){
			printList(out, (G->Adj[i]));
		}
		fprintf(out, "\n");
	}
	return;
}

// private function sortedInsert()
// inserts v into list L maintaining vertices in increasing order
void sortedInsert(List L, int v) {
	if (L == NULL){
		fprintf(stderr, "Graph Error: sortedInsert(Q, v) called on NULL Queue reference\n");
		exit(EXIT_FAILURE);
	}
	moveFront(L);
	int placed = 0;
	while ((index(L) >= 0) && !placed){
		if (v == get(L)) return;
		if (v < get(L)){
			insertBefore(L, v);
			placed = 1;
		}
		moveNext(L);
	}
	if (!placed){
		append(L, v);
	}
	return;
}
