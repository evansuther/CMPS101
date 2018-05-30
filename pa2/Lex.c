/* Evan Suther
 * Cruzid: esuther
 * Assignment: PA2
 * Component: Lex.c
 * Function: takes input file, sorts lines alphabetically then
 * prints them in user specified output file
 */

// stlib for EXIT_FAILURE and heap memory functions
#include <stdlib.h>
// stdio to print to file
#include<stdio.h>
// string for strcmp, strcpy, strtok
#include<string.h>
// list as specified in assignment
#include "List.h"

//Lex.c
int main(int argc, char* argv[]) {
   FILE* in;
   FILE* out;
   if ( argc != 3 ) {
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }
	// open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
	
	int maxLines = 32;
	int maxLen = 256;
	int lineCount = 0;
	// create array of pointers, used calloc so mem would be set to 0
	char **lineptr = calloc(maxLines, sizeof(char*));
	// I used these variables 
	char *linetrim, linebuf[maxLen];
	while( fgets(linebuf, maxLen, in) != NULL){
		// initialize space for the current line 
		lineptr[lineCount] =  calloc(maxLen, sizeof(char));
		linetrim = strtok(linebuf, "\n"); //delete newline from this line
		strcpy(*(lineptr+lineCount), linetrim);
		lineCount++;
		// check if array needs to be increased/realloc'd
		if (lineCount == (maxLines)){
			maxLines *= 2;
			char **temp = realloc(lineptr, maxLines * sizeof(char*));
			if (!temp){
				fprintf(stderr, "realloc error!");
				exit(1);
			}
			else{
				lineptr = temp;
			}
		}
	}
	// done with input file, lines are stored in array
	fclose(in);
	// sorted insert of indices into list 
	List myList = newList();
	append(myList, 0);
	for (int i = 1; i < lineCount; i++ ){
		moveFront(myList);
		int iPlaced = 0;
		// loop through list and check if current index's string belongs before elements in the list
		while((iPlaced == 0) && (index(myList) >= 0)){
			int sortVal = strcmp(lineptr[i], lineptr[get(myList)]);
			if (sortVal < 0){
				insertBefore(myList, i);
				iPlaced = 1;
			}
			moveNext(myList);
		}
		// if the line at the index didn't belong before any element in the list,
		// it goes at the end
		if (iPlaced == 0){
			append(myList, i);
		}
	}
	// print lines in order from the sorted list
	moveFront(myList);
	while (index(myList) >= 0){
		fprintf(out,"%s\n", lineptr[get(myList)]);
		moveNext(myList);
	}
	// free all heap memory then exit program
	freeList(&myList);
	fclose(out);
	for (int i = 0; i < lineCount; i++){free(lineptr[i]);}
	free(lineptr);
	return(0);
}