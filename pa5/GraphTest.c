/* Evan Suther
 * Cruzid: esuther
 * Assignment: PA5
 * Component: GraphTest.c
 * Function: runs a series of tests on Graph ADT implementation
 * and prints pass/fail based on what the functions should be returning/modifying
 * USAGE: ./GraphTest
 */

#include "Graph.h"
// stdlib for EXIT_FAILURE and others
#include <stdlib.h>
int main(int argc, char* argv[]){
	char* result;
	
	// newGraph() test
	// 40 chosen arbitrarily, G will be used for testing functions of Graph ADT implementation
	int n = 40;
	Graph G = newGraph(n);
	result = (getOrder(G) != n || getSize(G) != 0) ? "FAIL" : "PASS";
	fprintf(stdout, "newGraph() test: %s\n", result);
	
	// addEdge() test
	for (int i = 1; i <= 10; i++) 
		addEdge(G, i, i+1);
	result = (getOrder(G) != n || getSize(G) != 10) ? "FAIL" : "PASS";
	fprintf(stdout, "addEdge() test: %s\n", result);
	freeGraph(&G);
	G = newGraph(n);
	
	// addArc() test
	for (int i = 1; i <= 10; i++)
		addArc(G, i, i+1);
	result = (getOrder(G) != n || getSize(G) != 10) ? "FAIL" : "PASS";
	fprintf(stdout, "addArc() test: %s\n", result);
	
	// printGraph() test
	printGraph(stdout, G);
	
	// copyGraph() test
	Graph C = copyGraph(G);
	result = (getOrder(G) != getOrder(C) || C == G) ? "FAIL" : "PASS";
	fprintf(stdout, "copyGraph() test: %s\n", result);
	freeGraph(&C);
	
	// transpose() test
	Graph T = transpose(G);
	result = (getOrder(G) != getOrder(T) || T == G) ? "FAIL" : "PASS";
	fprintf(stdout, "transpose() test: %s\n", result);
	freeGraph(&T);
		
	// getParent() no DFS test
	result = (getParent(G, 10) != NIL) ? "FAIL" : "PASS";
	fprintf(stdout, "getParent() no DFS test: %s\n", result);
	
	// getDiscover() no DFS test
	result = (getDiscover(G, 10) != UNDEF) ? "FAIL" : "PASS";
	fprintf(stdout, "getDiscover() no DFS test: %s\n", result);
	
	// getFinish() no DFS test
	result = (getFinish(G, 10) != UNDEF) ? "FAIL" : "PASS";
	fprintf(stdout, "getFinish() no DFS test: %s\n", result);
	
	// DFS() test
	List S = newList();
	for (int i = 1; i <= n; i++) 
		append(S, i);
	DFS(G, S);
	
	// getParent() post BFS test
	result = (getParent(G, 1) != NIL) ? "FAIL" : "PASS";
	fprintf(stdout, "getParent() post BFS test: %s\n", result);
	
	// getDiscover() post BFS test
	result = (getDiscover(G, 37) != 73) ? "FAIL" : "PASS";
	fprintf(stdout, "getDiscover() post BFS test: %s\n", result);
	
	// getFinish() post BFS test
	result = (getFinish(G, 37) != 74) ? "FAIL" : "PASS";
	fprintf(stdout, "getFinish() post BFS test: %s\n", result);
	
	// free heap memory and exit
	freeList(&S);
	freeGraph(&G);
	exit(EXIT_SUCCESS);
}