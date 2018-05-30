/* Evan Suther
 * Cruzid: esuther
 * Assignment: PA4
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
	
	// addArc() test
	for (int i = 1; i <= 10; i++){
		addArc(G, i, i+1);
	}
	result = (getOrder(G) != n || getSize(G) != 10) ? "FAIL" : "PASS";
	fprintf(stdout, "addArc() test: %s\n", result);
	
	// makeNull() test
	makeNull(G);
	result = (getOrder(G) != n || getSize(G) != 0) ? "FAIL" : "PASS";
	fprintf(stdout, "makeNull() test: %s\n", result);
	
	// addEdge() test
	// first 12 prime numbers : 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37
	addEdge(G, 2, 3);
	addEdge(G, 3, 5);
	addEdge(G, 5, 7);
	addEdge(G, 7, 11);
	addEdge(G, 11, 13);
	addEdge(G, 13, 17);
	addEdge(G, 17, 19);
	addEdge(G, 19, 23);
	addEdge(G, 23, 29);
	addEdge(G, 29, 31);
	addEdge(G, 31, 37);
	result = (getOrder(G) != n || getSize(G) != 11) ? "FAIL" : "PASS";
	fprintf(stdout, "addEdge() test: %s\n", result);
	
	// printGraph() test
	printGraph(stdout, G);
	
	// getSource() no BFS test
	result = (getSource(G) != NIL) ? "FAIL" : "PASS";
	fprintf(stdout, "getSource() no BFS test: %s\n", result);
	
	// getParent() no BFS test
	result = (getParent(G, 37) != NIL) ? "FAIL" : "PASS";
	fprintf(stdout, "getParent() no BFS test: %s\n", result);
	
	// getDist() no BFS test
	result = (getDist(G, 37) != INF) ? "FAIL" : "PASS";
	fprintf(stdout, "getDist() no BFS test: %s\n", result);
	
	// BFS() test
	BFS(G, 2);
	
	// getSource() post BFS test
	result = (getSource(G) != 2) ? "FAIL" : "PASS";
	fprintf(stdout, "getSource() post BFS test: %s\n", result);
	
	// getParent() post BFS test
	result = (getParent(G, 37) != 31) ? "FAIL" : "PASS";
	fprintf(stdout, "getParent() post BFS test: %s\n", result);
	
	// getDist() post BFS test
	result = (getDist(G, 37) != 11) ? "FAIL" : "PASS";
	fprintf(stdout, "getDist() post BFS test: %s\n", result);
	
	// getPath() test
	List L = newList();
	getPath(L, G, 37);
	printList(stdout, L);
	fprintf(stdout, "\n");
	
	// free heap memory and exit
	freeList(&L);
	freeGraph(&G);
	exit(EXIT_SUCCESS);
}