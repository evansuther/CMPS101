/* Evan Suther
 * Cruzid: esuther
 * Assignment: PA4
 * Component: FindPath.c
 * Function: takes formatted input file, builds a graph from the input,
 * determines shortest paths between vertices, if they exist specified in the input
 * using BFS, then produces a formatted output in the output file
 * USAGE: ./FindPath <input file> <output file>
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
   // ints s, x - both vertices, used for inputting into graph and finding shortest path using BFS
   // int d - distance after BFS is run
   // int part - used to keep track of which part of input file while loop is in
   int s, x, d, part;
   part = 1;
   Graph G;
   List L;
	// initialize graph
   if (fgets(str, 128, in) != NULL) {
      G = newGraph(atoi(str));
   }
	// loop through input file, convert tokens to ints, process ints depending on part of input file
   while (fgets(str, 128, in) != NULL) {
      s = atoi(strtok(str, " "));
      x = atoi(strtok(0, "\n"));
		// 0 0 is a dummy line signalling end of part 1 or 2
      if (s == 0 && x == 0) {
         if (part == 1) {
            printGraph(out, G);
            part = 2;
         }
         else if (part == 2) break;
      }
      else if (part == 1) addEdge(G, s, x);
      else {
			// part 2 of input file, produce formatted output according to ints on line
			BFS(G, s);
         L = newList();
         d = getDist(G, x);
         // convert distance int to string
         snprintf(str,128, "%d", d);
         // formatted print, prints "infinity" or distance as a string
         fprintf(out,"\nThe distance from %d to %d is %s\n", s, x, d == INF? "infinity" : str);
         // 2 formatted string based on if a path exists or not
         if (d != INF) {
            fprintf(out,"A shortest %d-%d path is: ", s, x);
            getPath(L, G, x);
            printList(out, L);
         } else {fprintf(out,"No %d-%d path exists", s, x);}
         fprintf(out, "\n");
         freeList(&L);
      }
   }
	// free all heap memory and exit
   fclose(in);
   fclose(out);
   freeGraph(&G);
   exit(EXIT_SUCCESS);
}

