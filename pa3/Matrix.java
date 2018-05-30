/* Evan Suther
 * Cruzid: esuther
 * Assignment: PA3
 * Component: Matrix.java
 * Function: Implements Matrix ADT spec from assignment
 */
 
@SuppressWarnings("overrides") // annotation for compiler warnings 
public class Matrix {

   //Private inner class Entry-------------------
   private class Entry {
      //fields
      int col;
      double val;
      // constructor
      Entry (int i, double v) {
         col = i;
         val = v;
      }
      public String toString() {
         String s = "(" + col + ", " + val + ")";
         return s;
      }
		@SuppressWarnings("overrides") // annotation for compiler warnings 
      public boolean equals(Object x) {
         boolean eq = false;
         Entry that;
         if (x instanceof Entry) {
            that = (Entry) x;
            eq = (this.col == that.col);
            eq = (this.val == that.val);
         }
         return eq;
      }
   }
   // fields of Matrix---------------------------
   int size, NNZ;
   List[] row;
   // Constructor
   // Makes a new n x n zero Matrix. pre: n>=1
   Matrix(int n) {
      if (!(n >= 1)) {
         throw new RuntimeException(
            "Matrix Error: Matrix() constructor called with n !>= 1");
      }
      size = n;
      NNZ = 0;
      // array will not use 0 index, index in array will correspond to row
      row = new List[n+1];
      for (int i = 1; i <= n; i++) {
         row[i] = new List();
      }
   }
// Access functions--------------------------------------------------------------------------------

	// getSize()
	// Returns n, the number of rows and columns of this Matrix
   int getSize() {
      return size;
   }
	
   // getNNZ()
   // Returns the number of non-zero entries in this Matrix
   int getNNZ() {
      return NNZ;
   }
	
   // equals()
   // overrides Object's equals() method
   public boolean equals(Object x) {
		boolean eq = false;
		Matrix that;
		if (x instanceof Matrix) {
			that = (Matrix) x;
			if (this == that){
				that = this.copy();
			}
			// both matrices must be nxn
			eq = (this.getSize() == that.getSize());
			if (eq) {
				// checking same NNZ should make this slightly faster
				eq = (this.getNNZ() == that.getNNZ());
				int i = 1;
				// use list equals to compare objects in lists
				while (eq && (i <= that.getSize())) {
					eq = this.row[i].equals(that.row[i]);
					i++;
				}
			}
		}
		return eq;
	}

// Manipulation procedures-------------------------------------------------------------------------

   // makeZero()
   // sets this Matrix to the zero state
   void makeZero() {
	  // resets each list to default state
      for (int i = 1; i <= this.getSize(); i++) {
         this.row[i].clear();
      }
      NNZ = 0;
      return;
   }
	
   // copy()
   // returns a new Matrix having the same entries as this Matrix
   Matrix copy() {
      Matrix cpy = new Matrix(this.getSize());
      Entry tmp;
		if (this.getNNZ() >= 1){
			// loop through rows and copy the entries
			for (int i = 1; i <= this.getSize(); i++) {
				this.row[i].moveFront();
				while (this.row[i].index() != -1) {
					tmp = (Entry) this.row[i].get();
					cpy.changeEntry(i, tmp.col, tmp.val);
					this.row[i].moveNext();
				}
			}
		}
      return cpy;
   }
	
   // changeEntry
   // changes ith row, jth column of this Matrix to x
   // pre: 1<=i<=getSize(), 1<=j<=getSize()
   void changeEntry(int i, int j, double x) {
      if (!(1 <= i && i <= getSize()) || !(1 <= j && j <= getSize())) {
         throw new RuntimeException(
            "Matrix Error: changeEntry() called with 1 or more indices out of bounds");
      }
      Entry found, test;
      found = test = null;
		// look through matrix to see if entry at i, j exists
      row[i].moveFront();
      while ((row[i].index() != -1) && (found == null)) {
         test = (Entry) row[i].get();
         if ( test.col == j) {
            found = (Entry) row[i].get();
         }
         if (found == null) {
            row[i].moveNext();
         }

      }
      // if there is an entry at index given, and value to be changed to is 0, delete
      if ((found != null) && (x == 0)) {
         row[i].delete();
         NNZ--;
      }
      // there is an entry at given index, given value is non-zero - change value
      else if ((found != null) && (x != 0)) {
         found.val = x;
      }
      // if no entry at index, and given value is zero - dont insert a 0 value, waste of space
      else if ((found == null) && (x == 0)) {
         return;
      }
      // if no entry at index, and given value is non-zero - insert
      else if ((found == null) && (x != 0)) {
         Entry tmp = new Entry(j, x);
         // Entry test;
         row[i].moveFront();
         boolean placed = false;
         // sorted insert
         while ((row[i].index() != -1) && !placed) {
            test = (Entry) row[i].get();
            if (tmp.col <= test.col) {
               row[i].insertBefore(tmp);
               placed = true;
               break;
            }
            row[i].moveNext();
         }
         if (!placed) {
            row[i].append(tmp);
         }
         NNZ++;
      }
      return;
   }
   // scalarMult()
   // returns a new Matrix that is the scalar product of this Matrix with x
   Matrix scalarMult(double x) {
      Matrix result = new Matrix (getSize());
      Entry tmp;
      double tmpResult;
		if (x != 0){
			for (int i = 1; i <= this.getSize(); i++) {
				this.row[i].moveFront();
				while (this.row[i].index() != -1) {
					tmp = (Entry) this.row[i].get();
					tmpResult = tmp.val * x;
					result.changeEntry(i, tmp.col, tmpResult);
					this.row[i].moveNext();
				}
			}
		}
      return result;
   }

   // add()
   // returns a new Matrix that is the sum of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix add(Matrix M) {
      if (!(getSize() == M.getSize())) {
         throw new RuntimeException(
            "Matrix Error: add() called on matrices of different sizes");
      }
      Matrix result = new Matrix(getSize());
		// if the references are the same, multiply by 2
      if (this == M) {
         result = this.scalarMult(2);
         return result;
      }
      double sum;
      List A, B;
      Entry tmpA, tmpB;
      for (int i = 1; i <= getSize(); i++) {
         A = this.row[i];
         B = M.row[i];
         A.moveFront();
         B.moveFront();
			// loop through current row
         while ((A.index() != -1) || (B.index() != -1)) {
            // cursor is still defined on both lists
            if ((A.index() != -1) && (B.index() != -1)) {
               tmpA = (Entry) A.get();
               tmpB = (Entry) B.get();
					// both rows have an entry at the same row, add then insert into result
               if (tmpA.col == tmpB.col) {
                  sum = tmpA.val + tmpB.val;
                  result.changeEntry(i, tmpA.col, sum);
                  A.moveNext();
                  B.moveNext();
               }
					// A is behind
               else if (tmpA.col < tmpB.col) {
                  result.changeEntry(i, tmpA.col, tmpA.val);
                  A.moveNext();
               }
					// B is behind
               else if (tmpA.col > tmpB.col) {
                  result.changeEntry(i, tmpB.col, tmpB.val);
                  B.moveNext();
               }
            }
				// cursor only defined on A
            else if (A.index() != -1) {
               tmpA = (Entry) A.get();
               result.changeEntry(i, tmpA.col, tmpA.val);
               A.moveNext();
            }
				// cursor only defined on B
            else if (B.index() != -1) {
               tmpB = (Entry) B.get();
               result.changeEntry(i, tmpB.col, tmpB.val);
               B.moveNext();
            }
         }
      }
      return result;

   }
   // sub()
   // returns a new Matrix that is the difference of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix sub(Matrix M) {
      if (!(getSize() == M.getSize())) {
         throw new RuntimeException(
            "Matrix Error: sub() called on matrices of different sizes");
      }
      Matrix result = new Matrix(getSize());
      // if references are the same, return 0 matrix
      if (this == M) {
         return result;
      }
      double diff;
      List A, B;
      Entry tmpA, tmpB;
      for (int i = 1; i <= getSize(); i++) {
         A = this.row[i];
         B = M.row[i];
         A.moveFront();
         B.moveFront();
			// loop through current row
         while ((A.index() != -1) || (B.index() != -1)) {
            // cursor is still defined on both lists
            if ((A.index() != -1) && (B.index() != -1)) {
               tmpA = (Entry) A.get();
               tmpB = (Entry) B.get();
               // both rows have an entry at the same row, subtract then insert into result
               if (tmpA.col == tmpB.col) {
                  diff = tmpA.val - tmpB.val;
                  result.changeEntry(i, tmpA.col, diff);
                  A.moveNext();
                  B.moveNext();
               }
					// A is behind
               else if (tmpA.col < tmpB.col) {
                  result.changeEntry(i, tmpA.col, tmpA.val);
                  A.moveNext();
               }
					// B is behind
               else if (tmpA.col > tmpB.col) {
                  result.changeEntry(i, tmpB.col, 0 - tmpB.val);
                  B.moveNext();
               }
            }
				// cursor only defined on A
            else if (A.index() != -1) {
               tmpA = (Entry) A.get();
               result.changeEntry(i, tmpA.col, tmpA.val);
               A.moveNext();
            }
				// cursor only defined on B
            else if (B.index() != -1) {
               tmpB = (Entry) B.get();
               result.changeEntry(i, tmpB.col, 0 - tmpB.val);
               B.moveNext();
            }
         }
      }
      return result;
   }

   // transpose()
   // returns a new Matrix that is the transpose of this Matrix
   Matrix transpose() {
      Matrix transpose = new Matrix(this.size);
      Entry tmp;
		if (getNNZ() != 0){
			for (int i = 1; i <= getSize(); i++) {
				this.row[i].moveFront();
				while (this.row[i].index() != -1) {
					tmp = (Entry) this.row[i].get();
					// here the entry is inserted into the transpose with its current row and col switched in the i, j format of changeEntry
					transpose.changeEntry(tmp.col, i, tmp.val);
					this.row[i].moveNext();
				}
			}
		}
      return transpose;
   }

   // mult()
   // returns a new Matrix that is the product of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix mult(Matrix M) {
      if (!(getSize() == M.getSize())) {
         throw new RuntimeException(
            "Matrix Error: Mult() called on matrices of different sizes");
      }
		// had to check if mult was passed itself, copy so function will work
      if (this == M) {
         M = this.copy();
      }
      Matrix result = new Matrix(getSize());
      Matrix transM = M.transpose();
      double dot;
      for (int i = 1; i <= getSize(); i++) {
         if (this.row[i].length() != 0) {
            for (int j = 1; j <= getSize(); j++) {
               if (transM.row[j].length() != 0) {
                  dot = dotProduct(this.row[i], transM.row[j]);
                  result.changeEntry(i, j, dot);
               }
            }
         }
      }
      return result;
   }
// Other functions---------------------------------------------------------------------------------

   // overrides Object's toString() method
   public String toString() {
      String s = "";
      String listStr;
      int count = 0;
      for (int i = 1; i <= getSize(); i++) {
         if (row[i].length() > 0) {
            listStr = row[i].toString();
            count = count + row[i].length();
            s = s + i + ": " + listStr;
            // don't print extra newline
            if (count != getNNZ()) {
               s = s + "\n";
            }
         }
      }
      return s;
   }

// Helper functions--------------------------------------------------------------------------------
	// dotProduct
	// takes two lists as inputs and computes the scalar dot product of the vectos
   private double dotProduct(List A, List B) {
      double prodSum = 0;
      A.moveFront();
      B.moveFront();
      Entry tmpA, tmpB;
      while ((A.index() != -1) && (B.index() != -1)) {
         tmpA = (Entry) A.get();
         tmpB = (Entry) B.get();
         if (tmpA.col == tmpB.col) {
            prodSum = prodSum + (tmpA.val * tmpB.val);
            A.moveNext();
            B.moveNext();
         }
         else if (tmpA.col < tmpB.col) {
            A.moveNext();
         }
         else if (tmpA.col > tmpB.col) {
            B.moveNext();
         }
      }
      return prodSum;
   }
}
