/* Evan Suther
 * Cruzid: esuther
 * Assignment: PA3
 * Component: MatrixTest.java
 * Function: Tests every Matrix Operation 
 */
 
class MatrixTest {
	public static void main(String[] args){
		Matrix A, B, C;
		String result;
		// basic constructor test
		A = new Matrix(10);
		result = (A.getSize() != 10 || A.getNNZ() != 0) ? "FAIL" : "PASS";
		System.out.println("Constructor test: " + result);
		
		// changeEntry entry DNE and 0 val test
		A.changeEntry(1, 1, 0);
		result = (A.getNNZ() != 0) ? "FAIL" : "PASS";
		System.out.println("insert 0 test: " + result);
		
		// 10x10 unit matrix getNNZ test 
		// also tests entryDNE and val != 0 case with changeEntry
		for (int i = 1; i <= A.getSize(); i++){
			for (int j = 1; j <= A.getSize(); j++){
				A.changeEntry(i, j, 1.0);
			}
		}
		result = (A.getNNZ() != 100) ? "FAIL" : "PASS";
		System.out.println("10x10 unit matrix NNZ test: " + result);
		
		// changeEntry entry exists and val != 0 
		A.changeEntry(1, 1, 2.0);
		result = (A.getNNZ() != 100) ? "FAIL" : "PASS";
		System.out.println("change existing entry test: " + result);
		
		// changeEntry entry exists and 0 val test
		A.changeEntry(1, 1, 0);
		result = (A.getNNZ() != 99) ? "FAIL" : "PASS";
		System.out.println("change entry to 0 test: " + result);
		
		// calling toString
		System.out.println(A);
		
		// equals test
		result = (!A.equals(A)) ? "FAIL" : "PASS";
		System.out.println("equals self test: " + result);
		
		// Copy tests
		B = A.copy();
		result = (A.equals(B)) ? "PASS" : "FAIL";
		System.out.println("copy equals test: " + result);
		
		// MakeZero test
		B.makeZero();
		result = (B.getNNZ() != 0) ? "FAIL" : "PASS";
		System.out.println("makeZero test: " + result);
		
		// Add empty matrix test
		C = new Matrix(10);
		B = A.add(C);
		result = (!B.equals(A)) ? "FAIL" : "PASS";
		System.out.println("Add empty matrix test: " + result);
		
		// Add non-empty matrix test
		C = new Matrix(10);
		C.changeEntry(1, 1, 1);
		A = A.add(C);
		result = (A.getNNZ() != 100) ? "FAIL" : "PASS";
		System.out.println("Add non-empty matrix test: " + result);
		
		// Add to self test
		B = A.add(A);
		result = (A.getNNZ() != B.getNNZ()) ? "FAIL" : "PASS";
		System.out.println("add to self test: " + result);
		
		// scalarMult test
		C = A.scalarMult(2);
		result = (A.getNNZ() != C.getNNZ()) ? "FAIL" : "PASS";
		System.out.println("scalarMult test: " + result);
		
		// scalarMult(2) and add to self equals test
		result = (B.equals(C)) ? "PASS" : "FAIL";
		System.out.println("scalarMult(2) and add to self equals test: " + result);
		
		// scalarMult(0) test
		C = A.scalarMult(0);
		result = (C.getNNZ() == 0) ? "PASS" : "FAIL";
		System.out.println("scalarMult(0) test: " + result);
		
		// B sub A where B = A+A test
		// B-A=(A+A)-A = A
		C = B.sub(A);
		result = (!C.equals(A)) ? "FAIL" : "PASS";
		System.out.println("Sub test: " + result);
		
		// Sub from self test
		B = A.sub(A);
		result = (B.getNNZ() != 0) ? "FAIL" : "PASS";
		System.out.println("Sub from self test: " + result);
		
		// Sub empty matrix test
		C.makeZero();
		B = A.sub(C);
		result = (C.getNNZ() == A.getNNZ()) ? "FAIL" : "PASS";
		System.out.println("Sub empty matrix test: " + result);
		
		// transpose test
		C = new Matrix (100);
		C.changeEntry(1, 100, 2.0);
		B = C.transpose();
		result = (C.equals(B)) ? "FAIL" : "PASS";
		System.out.println("transpose test: " + result);
		//System.out.println(A);
		
		// mult test
		B = A.copy();
		B = B.scalarMult(2);
		C = A.mult(B);
		//System.out.println(C);
		result = (C.getNNZ() != 100) ? "FAIL" : "PASS";
		System.out.println("mult test: " + result);
		
		// mult by empty matrix test
		B = new Matrix(10);
		C = A.mult(B);
		//System.out.println(C);
		result = (C.getNNZ() != 0) ? "FAIL" : "PASS";
		System.out.println("mult by empty matrix test: " + result);
		
		// mult by self test
		B = A.mult(A);
		//System.out.println(B);
		result = (B.getNNZ() != 100) ? "FAIL" : "PASS";
		System.out.println("mult by self test: " + result);
		
	}
}
