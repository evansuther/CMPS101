/* Evan Suther
 * Cruzid: esuther
 * Assignment: PA3
 * Component: Sparse.java
 * Function: takes two command line arguments for input and output files,
 * produces formatted output to provided out file
 */
 
import java.io.*;
import java.util.Scanner;
public class Sparse {
	public static void main(String[] args) throws IOException{
		if (args.length != 2) {
         System.err.println("Usage: ./Matrix <input file> <output file>");
         System.exit(1);
      }
		Scanner in = new Scanner(new File(args[0]));
		String inputString = in.useDelimiter("\\A").next().trim();
		in.close();
		
		String[] line = inputString.split("\\n");
		String[] specs = line[0].split("\\s+");
		String[] entry;
		int size = Integer.parseInt(specs[0]);
		int a = Integer.parseInt(specs[1]);
		int b = Integer.parseInt(specs[2]);
		Matrix A = new Matrix(size);
		Matrix B = new Matrix(size);
		int index = 2;
		int i, j;
		double x;
		while ((index-2)<= (a+b)){
			//System.out.println("index = " + index);
			entry = line[index].split("\\s+");
			i = Integer.parseInt(entry[0]);
			j = Integer.parseInt(entry[1]);
			x =  Double.parseDouble(entry[2]);
			if ((index-2)<a){
				A.changeEntry(i, j, x);
				index++;
				//System.out.println("((index-2)<a) => " + index);
				if ((index -2) == (a)){
					//System.out.println("(index -2) == (a) => " + index);
					index++;
				}
			}
			else if ((a<(index-2)) && ((index-2)<=(a+b))){
				//System.out.println("((a<(index-2)) && ((index-2)<b)) => " + index);
				B.changeEntry(i, j, x);
				index++;
			}
		}
		PrintWriter outputFile = new PrintWriter(new FileWriter(args[1]));
		outputFile.println("A has " + A.getNNZ() + " non-zero entries:");
		outputFile.println(A + "\n");
		
		outputFile.println("B has " + B.getNNZ() + " non-zero entries:");
		outputFile.println(B + "\n");
		// A * 1.5
		Matrix C = A.scalarMult(1.5);
		outputFile.println("(1.5)*A =");
		outputFile.println(C + "\n");
		// A + B
		C = A.add(B);
		outputFile.println("A+B =");
		outputFile.println(C + "\n");
		// A + A
		C = A.add(A);
		outputFile.println("A+A =");
		outputFile.println(C + "\n");
		// B - A
		C = B.sub(A);
		outputFile.println("B-A =");
		outputFile.println(C + "\n");
		// A - A
		C = A.sub(A);
		outputFile.println("A-A =");
		outputFile.println(C + "\n");
		// Transpose(A) =
		C = A.transpose();
		outputFile.println("Transpose(A) =");
		outputFile.println(C + "\n");
		// A*B =
		C = A.mult(B);
		outputFile.println("A*B =");
		outputFile.println(C + "\n");
		// B*B =
		C = B.mult(B);
		outputFile.println("B*B =");
		outputFile.println(C + "\n");
		outputFile.close();
		
	}
	
}
