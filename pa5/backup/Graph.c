/* Evan Suther
 * Cruzid: esuther
 * Assignment: PA5
 * Component: Graph.c
 * Function: stores a Graph in Adj list representation,
 * has vertex attributes for DFS for PA5 spec
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
void visit(Graph G, List S, int x, int* time);

/* end Private Declarations */

/* Graph ADT */

// GraphObj definition, header makes Graph a pointer to a GraphObj
typedef struct GraphObj {
   List* Adj;
   int* color;
	int* parent;
   int* d;
   int* f;
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
   for (int i = 1; i <= n; i++) 
		G->Adj[i] = newList();
	// initialize vertex color attribute array
   G->color = malloc(sizeof(int) * (n + 1));
	for (int i = 1; i <= n; i++) 
		G->color[i] = white;
	// initialize vertex parent attribute array
	G->parent = malloc(sizeof(int) * (n + 1));
	for (int i = 1; i <= n; i++) 
		G->parent[i] = NIL;
	// initialize vertex discover time array
   G->d = malloc(sizeof(int) * (n + 1));
	for (int i = 1; i <= n; i++) 
		G->d[i] = UNDEF;
	// initialize vertex finish time array
	G->f = malloc(sizeof(int) * (n + 1));
	for (int i = 1; i <= n; i++) 
		G->f[i] = UNDEF;
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
      for (int i = 1; i <= getOrder(*pG); i++) 
			freeList(&((*pG)->Adj[i]));
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
	if (G == NULL) {
		fprintf(stderr, "Graph Error: getOrder(G) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
   return (G->order);
}

// getSize()
// returns size(|E(G)|) of graph G
int getSize(Graph G) {
	if (G == NULL) {
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
   if (G == NULL) {
		fprintf(stderr, "Graph Error: getParent(G, u) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
	if  (!(1 <= u ) || !( u <= getOrder(G))) {
		fprintf(stderr, "Graph Error: getParent(G, u) precondition not met: {1<= u <= getOrder(G)}\n");
		exit(EXIT_FAILURE);
	}
   return (G->parent[u]);
} 

// getDiscover()
// returns the discover time of vertex u,
// or UNDEF if DFS() has not yet been called
/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u) {
   if (G == NULL) {
		fprintf(stderr, "Graph Error: getDiscover(G, u) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
	if  (!(1 <= u ) || !( u <= getOrder(G))) {
		fprintf(stderr, "Graph Error: getDiscover(G, u) precondition not met: {1<= u <= getOrder(G)}\n");
		exit(EXIT_FAILURE);
	}
   return (G->d[u]);
} 

// getFinish()
// returns the finish time of vertex u,
// or UNDEF if DFS() has not yet been called
/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u) {
   if (G == NULL) {
		fprintf(stderr, "Graph Error: getFinish(G, u) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
	if  (!(1 <= u ) || !( u <= getOrder(G))) {
		fprintf(stderr, "Graph Error: getFinish(G, u) precondition not met: {1<= u <= getOrder(G)}\n");
		exit(EXIT_FAILURE);
	}
   return (G->f[u]);
}  

/* end Access functions */

/* Manipulation procedures */

// addArc()
// inserts a new directed edge from u to v,
// i.e. v is added to the adjacency List of u
// (but not u to the adjacency List of v)
/* Pre: 1<=u<=n, 1<=v<=n */
void addArc(Graph G, int u, int v) {
	if (G == NULL) {
		fprintf(stderr, "Graph Error: addArc(G, u, v) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
	if  (!(1 <= u ) || !( u <= getOrder(G))) {
		fprintf(stderr, "Graph Error: addArc(G, u, v) precondition not met: {1<= u <= getOrder(G)}\n");
		exit(EXIT_FAILURE);
	}
	if  (!(1 <= v ) || !( v <= getOrder(G))) {
		fprintf(stderr, "Graph Error: addArc(G, u, v) precondition not met: {1<= v <= getOrder(G)}\n");
		exit(EXIT_FAILURE);
	}
	// use helper function to keep lists sorted
	sortedInsert(G->Adj[u], v);
	G->size++;
	return;
} 

// addEdge()
// inserts a new edge joining u to v,
// i.e. u is added to the adjacency List of v,
// and v to the adjacency List of u
/* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v) {
	if (G == NULL) {
		fprintf(stderr, "Graph Error: addEdge(G, u, v) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
	if  (!(1 <= u ) || !( u <= getOrder(G))) {
		fprintf(stderr, "Graph Error: addEdge(G, u, v) precondition not met: {1<= u <= getOrder(G)}\n");
		exit(EXIT_FAILURE);
	}
	if  (!(1 <= v ) || !( v <= getOrder(G))) {
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
// perform the depth first search algorithm on G
// L defines the order in which vertices will be processed in the main loop(While loop) of DFS
// L alsoe stores the vertices in order of decreasing finish times when exiting DFS
/* Pre: length(S)==getOrder(G) */
void DFS(Graph G, List S) {
	if (G == NULL) {
		fprintf(stderr, "Graph Error: DFS(G, S) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
	if  (!(length(S) == getOrder(G))) {
		fprintf(stderr, "Graph Error: DFS(G, S) precondition not met: {length(S)==getOrder(G))}\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= getOrder(G); i++) {
		G->color[i] = white;
		G->parent[i] = NIL;
	}
	int time = 0;
	moveBack(S);
	int v;
	while (index(S) >= 0) {
		v = front(S);
		if  (!(1 <= v ) || !( v <= getOrder(G))) {
			fprintf(stderr, "Graph Error: DFS(G, S) element v in List S precondition not met: {1<= v <= getOrder(G)}\n");
			exit(EXIT_FAILURE);
		}
		if (G->color[v] == white)
			visit(G, S, v, &time);
		deleteFront(S);
	}
	return;
} 

/* end Manipulation procedures */

/* Other Functions */

// transpose()
// returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G) {
	Graph T = newGraph(getOrder(G));
	if (G != NULL) {
		int v;
		for (int i = 1; i <= getOrder(G); i++) {
			moveFront(G->Adj[i]);
			while (index(G->Adj[i]) >= 0) {
				v = get(G->Adj[i]);
				sortedInsert(T->Adj[v] , i);
				moveNext(G->Adj[i]);
			}
		}
		T->size = G->size;
	}
	return T;
}

// copyGraph()
// returns a reference to a new graph which is a copy of G
Graph copyGraph(Graph G) {
	Graph cpy = newGraph(getOrder(G));
	
	if (G != NULL) {
		for (int i = 1; i <= getOrder(G); i++) {
			if (length(G->Adj[i]) != 0) {
				freeList(&(cpy->Adj[i]));
				cpy->Adj[i] = copyList(G->Adj[i]);
			}
				
		}
		cpy->size = G->size;
	}
	return cpy;
}

// printGraph()
// prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out , Graph G) { 
	if (G == NULL) {
		fprintf(stderr, "Graph Error: printGraph(out, G) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (out == NULL) {
		fprintf(stderr, "Graph Error: printGraph(out, G) called on NULL file reference\n");
		exit(EXIT_FAILURE);
	}
	// use printlist for all non-empty lists in G
	for (int i = 1; i <= getOrder(G); i++) {
		fprintf(out, "%d: ", i);
		if (length(G->Adj[i]) >= 1)
			printList(out, (G->Adj[i]));
		fprintf(out, "\n");
	}
	return;
}

/* end Other Functions */

/* private functions */

// private function sortedInsert()
// inserts v into list L maintaining vertices in increasing order
void sortedInsert(List L, int v) {
	if (L == NULL) {
		fprintf(stderr, "Graph Error: sortedInsert(Q, v) called on NULL Queue reference\n");
		exit(EXIT_FAILURE);
	}
	moveFront(L);
	int placed = 0;
	while ((index(L) >= 0) && !placed) {
		if (v == get(L)) 
			return;
		if (v < get(L)) {
			insertBefore(L, v);
			placed = 1;
		}
		moveNext(L);
	}
	if (!placed) 
		append(L, v);
	return;
}

// private function visit()
// this is the helper function for DFS, it recursively explores vertices
// as vertices finish, Visit 'pushes' x onto the stack portion of list Suther
// every vertex gets visited so the stack will necessarily be complete
void visit(Graph G, List S, int x, int* time) {
	int u;
	G->color[x] = gray;
	G->d[x] = ++(*time);
	for (moveFront(G->Adj[x]); index(G->Adj[x]) >= 0; moveNext(G->Adj[x])) {
		u = get(G->Adj[x]);
		if (G->color[u] == white) {
			G->parent[u] = x;
			visit(G, S, u, time);
		}
	}
	G->color[x] = black;
	G->f[x] = ++(*time);
	insertAfter(S, x);
	return;
}

/* end private functions */
