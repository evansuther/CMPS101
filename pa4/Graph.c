/* Evan Suther
 * Cruzid: esuther
 * Assignment: PA4
 * Component: Graph.c
 * Function: implements Graph ADT specs from PA4.
 * graph can be directed or undirected, and use BFS to find a shortest path in a graph
 */

// Graph.c
#include "Graph.h"
// stdlib for EXIT_FAILURE and others
#include <stdlib.h>
// stdio to print to a file
#include <stdio.h>
// define black, gray, white for use in BFS
#define black 1
#define gray 0
#define white -1

// Private function declarations--------------------------------------------------------------
typedef struct QueueObj* Queue;
Queue newQueue();
void freeQueue(Queue* pQ);
void enqueue(Queue Q, int v);
int dequeue(Queue Q);
int isEmpty(Queue Q);
void sortedInsert(List L, int v);
// end private declarations

// Graph ADT ---------------------------------------------------------------------------------
typedef struct GraphObj {
   List* Adj;
   int* color;
   int* dist;
   int* parent;
   int order, size, source;
} GraphObj;

/* Constructors-Destructors ------------------------------------------- */

// newGraph() - constructor
// returns a Graph pointing to a newly created GraphObj
// representing a graph having n vertices and no edges
Graph newGraph(int n) {
   Graph G;
   G = malloc(sizeof(GraphObj));
	// initialize Adj list representation for new Graph
   G->Adj = malloc(sizeof(List) * (n + 1));
   for (int i = 1; i <= n; i++) {
		G->Adj[i] = newList();
   }
	// initialize the BFS vertex attribute arrays
   G->color = malloc(sizeof(int) * (n + 1));
	for (int i = 1; i <= n; i++) {
		G->color[i] = white;
   }
   G->dist = malloc(sizeof(int) * (n + 1));
	for (int i = 1; i <= n; i++) {
		G->dist[i] = INF;
   }
   G->parent = malloc(sizeof(int) * (n + 1));
	for (int i = 1; i <= n; i++) {
		G->parent[i] = NIL;
   }
	// initialize fields
   G->order = n;
   G->size = 0;
   G->source = NIL;
   return (G);
}

// freeGraph() - destructor
// frees all dynamic memory associated with the Graph
// *pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG) {
   if (pG != NULL && *pG != NULL) {
		// Free List adts in Adj list array
      for (int i = 1; i <= getOrder(*pG); i++) {
         freeList(&((*pG)->Adj[i]));
      }
		// Free the arrays
      free((*pG)->Adj);
      free((*pG)->color);
      free((*pG)->dist);
      free((*pG)->parent);
      free(*pG);
      *pG = NULL;
   }
   return;
}

/* Access functions ----------------------------------------------------*/
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

// getSource()
// returns the source vertex most recently used in
// function BFS(), or NIL if BFS() has not yet been called
int getSource(Graph G) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: getSource(G) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
   return (G->source);
}

// getParent()
// returns the parent of vertex u in the BreadthFirst
// tree created by BFS(), or NIL if BFS() has not yet been called
// precondition: 1<= u <= getOrder(G)
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

// getDist()
// returns the distance from the most recent BFS source
// to vertex u, or INF if BFS() has not yet been called
// precondition: 1<= u <= getOrder(G)
int getDist(Graph G, int u) {
   if (G == NULL){
		fprintf(stderr, "Graph Error: getDist(G, u) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
	if  (!(1 <= u ) || !( u <= getOrder(G))){
		fprintf(stderr, "Graph Error: getDist(G, u) precondition not met: {1<= u <= getOrder(G)}\n");
		exit(EXIT_FAILURE);
	}
   return (G->dist[u]);
}

// getPath()
// appends to the List L the vertices of a shortest path
// in G from source to u, or appends to L the value NIL
// if no such path exists
// precondition: getSource(G)!=NIL, so BFS() must
//   be called before getPath()
// precondition: 1<= u <= getOrder(G)
void getPath(List L, Graph G, int u){
	// c preconditions
	if (G == NULL){
		fprintf(stderr, "Graph Error: getPath(L, G, u) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (L == NULL){
		fprintf(stderr, "Graph Error: getPath(L, G, u) called on NULL list reference\n");
		exit(EXIT_FAILURE);
	}
	// spec preconditions
	if (getSource(G) == NIL){
		fprintf(stderr, "Graph Error: getPath(L, G, u) precondition not met: BFS() not called first\n");
		exit(EXIT_FAILURE);
	}
	if  (!(1 <= u ) || !( u <= getOrder(G))){
		fprintf(stderr, "Graph Error: getPath(L, G, u) precondition not met: {1<= u <= getOrder(G)}\n");
		exit(EXIT_FAILURE);
	}
	
	//---------------
	// required recursive algorithm
	if (u == getSource(G)){
		append(L, getSource(G));
	}
	// if no path exists case
	else if (getParent(G, u) == NIL){
		append(L, NIL);
		return;
	}
	else{
		getPath(L, G, getParent(G, u));
		append(L, u);
	}
	return;
}


/* Manipulation procedures ---------------------------------------------*/

// makeNull()
// deletes all edges of G, restoring it to its
// original (no edge) state
void makeNull(Graph G){
	if (G == NULL){
		fprintf(stderr, "Graph Error: makeNull(G) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
	// reset all Adj lists and arrays
	int n = getOrder(G);
   for (int i = 1; i <= n; i++) {
		clear(G->Adj[i]);
   }
	for (int i = 1; i <= n; i++) {
		G->color[i] = white;
   }
	for (int i = 1; i <= n; i++) {
		G->dist[i] = INF;
   }
	for (int i = 1; i <= n; i++) {
		G->parent[i] = NIL;
   }
	// reset fields
   G->size = 0;
   G->source = NIL;
   return;
}

// addEdge()
// inserts a new edge joining u to v,
// i.e. u is added to the adjacency List of v,
// and v to the adjacency List of u
// precondition: 1<= u <= getOrder(G) && 1<= v <= getOrder(G)
void addEdge(Graph G, int u, int v){
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

// addArc()
// inserts a new directed edge from u to v,
// i.e. v is added to the adjacency List of u
// (but not u to the adjacency List of v)
// precondition: 1<= u <= getOrder(G) && 1<= v <= getOrder(G)
void addArc(Graph G, int u, int v){
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

// BFS()
// runs the BFS algorithm on the Graph G with source s,
// setting the color, distance, parent,
// and source fields of G accordingly
void BFS(Graph G, int s) {
	// non-required preconditions
	if (G == NULL){
		fprintf(stderr, "Graph Error: BFS(G, s) called on NULL graph reference\n");
		exit(EXIT_FAILURE);
	}
	if  (!(1 <= s ) || !( s <= getOrder(G))){
		fprintf(stderr, "Graph Error: BFS(G, s) called on out of bounds source\n");
		exit(EXIT_FAILURE);
	}
	// initialize vertex attributes
	for (int i = 1; i <= getOrder(G); i++){
		if (i == s){continue;}
		G->color[i] = white;
		G->dist[i] = INF;
		G->parent[i] = NIL;
	}
	// setting source attributes
	G->color[s] = gray;
	G->dist[s] = 0;
	G->parent[s] = NIL;
	G->source = s;
	// use a Queue as per the BFS spec
	Queue Q = newQueue();
	enqueue(Q, s);
	int x, y;
	while (!isEmpty(Q)){
		// explore vertices adjacent to dequeued vertex
		x = dequeue(Q);
		for (moveFront(G->Adj[x]); index(G->Adj[x]) >= 0; moveNext(G->Adj[x])){
			y = get(G->Adj[x]);
			// only explore undiscovered vertices
			if (G->color[y] == white){
				G->color[y] = gray;
				G->dist[y] = G->dist[x] + 1;
				G->parent[y] = x;
				enqueue(Q, y);
			}
		}
		G->color[x] = black;
	}
	freeQueue(&Q);
	return;
}

/* Other operations ----------------------------------------------------*/

// printGraph()
// prints the adjacency list representation of G to
// the file pointed to by out
void printGraph(FILE* out, Graph G){
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

/* Private Queue definitions -------------------------------------------*/
// Queue is built on list
typedef struct QueueObj {
	List L;
} QueueObj;

// newQueue()
// private constructor for queue
Queue newQueue() {
	Queue Q = malloc (sizeof(QueueObj));
	Q->L = newList();
	return (Q);
} 
// freeQueue()
// private destructor for queue
void freeQueue(Queue* pQ){
	if (pQ != NULL && *pQ != NULL) {
		freeList(&((*pQ)->L));
		(*pQ)->L = NULL;
		free(*pQ);
		*pQ = NULL;
	}
	return;
}

// enqueue()
// private function using append
void enqueue(Queue Q, int v){
	if (Q == NULL) {
		fprintf(stderr, "Graph(Queue) Error: enqueue(Q, v) called on NULL Queue reference\n");
		exit(EXIT_FAILURE);
	}
	append((Q->L), v);
	return;
}

// dequeue()
// private function using deleteFront
int dequeue(Queue Q){
	if (Q == NULL) {
		fprintf(stderr, "Graph(Queue) Error: dequeue(Q, v) called on NULL Queue reference\n");
		exit(EXIT_FAILURE);
	}
	int frnt = front(Q->L);
	deleteFront(Q->L);
	return (frnt);
}

// dequeue()
// private function using deleteFront
int isEmpty(Queue Q){
	if (Q == NULL) {
		fprintf(stderr, "Graph(Queue) Error: isEmpty(Q) called on NULL Queue reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(Q->L) >= 1){
		return (0);
	}
	else return (1);
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

