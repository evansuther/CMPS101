/* Evan Suther
 * Cruzid: esuther
 * Assignment: PA3
 * Component: ListTest.java
 * Function: Tests every List operation using ints
 */
 
class ListTest {
	public static void main(String[] args){
		List A = new List();
		String result;
		int x;
		// length() - empty list test
		result = (A.length() != 0) ? "FAIL" : "PASS";
		System.out.println("length() - empty list test: " + result);
		
		// index() - empty list test
		result = (A.index() != -1) ? "FAIL" : "PASS";
		System.out.println("index() - empty list test: " + result);
		
		// append() - Length test
		A.append(1); // List = 1
		result = (A.length() != 1) ? "FAIL" : "PASS";
		System.out.println("append() - Length test: " + result);
		
		// append() - index test
		A.moveFront();
		A.append(2); // List = 1 2
		result = (A.index() != 0) ? "FAIL" : "PASS";
		System.out.println("Append() - index test: " + result);
		
		// prepend() - length test
		A.prepend(3); // List = 3 1 2
		result = (A.length() != 3) ? "FAIL" : "PASS";
		System.out.println("prepend() - length test: " + result);
		
		// prepend() - index test
		A.moveFront();
		A.prepend(4); // List = 4 3 1 2
		result = (A.index() != 1) ? "FAIL" : "PASS";
		System.out.println("prepend() test - index test: " + result);
		
		// moveFront() - index test
		A.moveFront();
		result = (A.index() != 0) ? "FAIL" : "PASS";
		System.out.println("moveFront() - index test: " + result);
		
		// moveBack() - index test
		A.moveBack();
		result = (A.index() != 3) ? "FAIL" : "PASS";
		System.out.println("moveBack() - index test: " + result);
		
		// insertBefore() - index test
		A.insertBefore(5); // List = 4 3 1 5 2
		result = (A.index() != 4) ? "FAIL" : "PASS";
		System.out.println("insertBefore() - index test: " + result);		
		
		// insertAfter() - index test
		A.insertAfter(6); // List = 4 3 1 5 2 6
		result = (A.index() != 4) ? "FAIL" : "PASS";
		System.out.println("insertAfter() - index test: " + result);	
		
		// front() test
		x = (int) A.front();
		result = (x != 4) ? "FAIL" : "PASS";
		System.out.println("front() test: " + result);
		
		// back() test
		A.append(7); // List = 4 3 1 5 2 6 7
		x = (int) A.back();
		result = (x != 7) ? "FAIL" : "PASS";
		System.out.println("back() test: " + result);
		
		// moveNext() - index test
		A.moveFront();
		A.moveNext();
		result = (A.index() != 1) ? "FAIL" : "PASS";
		System.out.println("moveNext() - index test: " + result);
		
		// movePrev() - index test
		A.moveBack();
		A.movePrev();
		result = (A.index() != A.length()-2) ? "FAIL" : "PASS";
		System.out.println("movePrev() - index test: " + result);
		
		// get() test
		A.moveFront();
		A.moveNext();
		x = (int) A.get();
		result = (x != 3) ? "FAIL" : "PASS";
		System.out.println("get() test: " + result);
		
		// equals() - empty list test
		List B = new List();
		result = (A.equals(B)) ? "FAIL" : "PASS";
		System.out.println("equals() - empty list test: " + result);
		
		// equals() - non-empty list test
		B.append(1);
		result = (A.equals(B)) ? "FAIL" : "PASS";
		System.out.println("equals() - non-empty list test: " + result);
		
		// clear() - length test
		B.clear();
		result = (A.length() != 0) ? "FAIL" : "PASS";
		System.out.println("clear() - length test: " + result);
		
		// clear() - index test
		result = (A.index() != 0) ? "FAIL" : "PASS";
		System.out.println("clear() - index test: " + result);
		
		// deleteFront() - length test
		A.moveFront();
		A.moveNext();
		A.deleteFront(); // List = 3 1 5 2 6 7
		result = (A.length() != 6) ? "FAIL" : "PASS";
		System.out.println("deleteFront() - length test: " + result);
		
		// deleteFront() - index test
		result = (A.index() != 0) ? "FAIL" : "PASS";
		System.out.println("deleteFront() - index test: " + result);
		
		// deleteFront() - cursor on front test
		A.moveFront();
		A.deleteFront(); // List = 1 5 2 6 7
		result = (A.index() != -1) ? "FAIL" : "PASS";
		System.out.println("deleteFront() - cursor on front test: " + result);
		
		// deleteBack() - length test
		A.deleteBack(); // List = 1 5 2 6 
		result = (A.length() != 4) ? "FAIL" : "PASS";
		System.out.println("deleteBack() - length test: " + result);
		
		// deleteBack() - cursor on back test
		A.moveBack();
		A.deleteBack(); // List = 1 5 2
		result = (A.index() != -1) ? "FAIL" : "PASS";
		System.out.println("deleteBack() - cursor on back test: " + result);
		
		// delete() test
		A.moveBack();
		A.delete(); // List = 1 5
		result = (A.length() != 2) ? "FAIL" : "PASS";
		System.out.println("delete() test: " + result);
		// toString() test
		result = (!A.toString().trim().equals("1 5")) ? "FAIL" : "PASS";
		System.out.println("toString() test: " + result);
		
	}
}

