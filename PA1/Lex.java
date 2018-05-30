/* Evan Suther
 * Cruzid: esuther
 * Assignment: PA1
 * Component: Lex.java
 * Function: takes input file, sorts lines alphabetically then prints them in specified output file
 */
import java.io.*;
import java.util.Scanner;

public class Lex {
   public static void main(String[] args) throws IOException {

      if (args.length != 2) {
         System.err.println("Usage: ./Lex.jar <input file> <output file>");
         System.exit(1);
      }

      Scanner inputFile = new Scanner(new File(args[0]));

      // I learned of the scanner delimiter and \\A on a blog, I've included a link in the readme
      String inputString = inputFile.useDelimiter("\\A").next();
      inputFile.close();
      // After reading the whole file as a single string, split on newline produces an array of the lines
      String[] inputArray = inputString.split("\\n");
      List myList = new List();
      myList.append(0);
      // outer loop moves through array
      for (int i = 1; i < inputArray.length; i++) {
         myList.moveFront();
         boolean iPlaced = false;
         // inner loop moves through the list and inserts the index if it's string belongs before the cursor
         while (!iPlaced && (myList.index() >= 0)) {
            if (inputArray[i].compareTo(inputArray[myList.get()]) < 0 ) {
               myList.insertBefore(i);
               iPlaced = true;
            }
            myList.moveNext();
         }
         // if the index was not placed in inner loop
         if (!iPlaced) {
            myList.append(i);
         }
      }

      PrintWriter outputFile = new PrintWriter(new FileWriter(args[1]));
      myList.moveFront();
      // walk through list and print indexs of array from sorted list
      while (myList.index() >= 0) {
         outputFile.println(inputArray[myList.get()]);
         myList.moveNext();
      }

      outputFile.close();
   }
}