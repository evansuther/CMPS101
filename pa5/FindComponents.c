/* Evan Suther
 * Cruzid: esuther
 * Assignment: PA5
 * Component: FindComponents.c
 * Function: takes formatted input file, builds a digraph from the input,
 * prints the adjacency list representation to the output file, determines
 * the strongly connected components of the graph and prints them to the output file
 * USAGE: ./FindComponents <input file> <output file>
 */

// Graph as specified in assignment
#include "Graph.h"
// stlib for EXIT_FAILURE and heap memory functions
#include <stdlib.h>
// stdio to print to file
#include<stdio.h>
// string for strcmp, strcpy, strtok
#include<string.h>

int main(int argc, char* argv[]) {
   FILE* in;
   FILE* out;
   if ( argc != 3 ) {
      printf("Usage: ./%s <input file> <output file>\n", argv[0]);
      exit(EXIT_FAILURE);
   }
   // open files for reading and writing
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if ( in==NULL ) {
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(EXIT_FAILURE);
   }
   if ( out==NULL ) {
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(EXIT_FAILURE);
   }
   char* str = malloc(128*sizeof(char));
   // int naming conventions:
   // ints s, x - both vertices, used for building graph
   int s, x;
   Graph G;
   List L = newList();
	// initialize graph from first line of input file
   if (fgets(str, 128, in) != NULL) {
		s = atoi(str);
      G = newGraph(s);
		// initialize list for use in 1st call to DFS
		for (int i = 1; i <= s; i++)
			append(L, i);
   }
	// loop through input file, convert tokens to ints, build graph G
   while (fgets(str, 128, in) != NULL) {
      s = atoi(strtok(str, " "));
      x = atoi(strtok(0, "\n"));
		// 0 0 signals end of input
      if (s == 0 && x == 0) 
			break;
      else 
			addArc(G, s, x);
   }
	// the first part of the output file is the Adj list representation of the input graph
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out, "\n");
	// to find SCC of G, run dfs, compute transpose of G, run dfs on transpose in dec finish times from the first call 
	// here L is used as an input-output parameter that directs the main loop of DFS and, as vertices finish, they are added to L
	DFS(G, L);
	Graph T = transpose(G);
	DFS(T, L);
	// the output requires a count of SCC's, so count vertices with null parents in L
	s = 0;
	moveFront(L);
	while (index(L) >= 0) {
		x = get(L);
		if (getParent(T, x) == NIL){
			s++;
		}
		moveNext(L);
	}
	fprintf(out, "G contains %d strongly connected components:\n", s);
	List K = newList();
	// build and print lists of Vertices of the different SCC's
	s = 0;
	while (length(L) >= 1) {
		x = back(L);
		prepend(K, x);
		if (getParent(T, x) == NIL) {
			fprintf(out, "Component %d: ", ++s);
			printList(out, K);
			fprintf(out, "\n");
			clear(K);
		}
		deleteBack(L);
	}
	// free all heap memory and exit
   fclose(in);
   fclose(out);
   freeGraph(&G);
   freeGraph(&T);
	freeList(&L);
	freeList(&K);
	free(str);
   exit(EXIT_SUCCESS);
}

