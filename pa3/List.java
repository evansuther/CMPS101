/* Evan Suther
 * Cruzid: esuther
 * Assignment: PA3
 * Component: List.java
 * Function: implements List adt spec from PA3, doubly linked list of objects with a cursor
 */

@SuppressWarnings("overrides")// annotation for compiler warnings 
public class List {

// private inner Node class required for list class
	@SuppressWarnings("overrides") // annotation for compiler warnings 
   private class Node {
      // Fields
      Object data;
      Node next;
      Node prev;
      // Constructor
      Node(Object o) {
         this.data = o;
         next = null;
         prev = null;
      }

      // toString():  overrides Object's toString() method
      public String toString() {
         return data.toString();
      }

      // equals(): overrides Object's equals() method
      public boolean equals(Object x) {
         boolean eq = false;
			Node that;
			if (x instanceof Node){
				that = (Node) x;
				eq = data.equals(that.data);
			}
         return eq;
      }
   }
   // Fields
   private Node front;
   private Node back;
   private Node cursor;
   private int length;
   private int iCursor;
   // Constructor
   // List()
   // Creates a new empty list.
   List() {
      front = back = cursor = null;
      length = 0;
      iCursor = -1;
   }


// Access functions ------------------------------------------------------------------------------

   // length()
   // Returns the number of elements in this List.
   int length() {
      return this.length;
   }

// index()
// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1.
   int index() {
      if (cursor != null) {
         return this.iCursor;
      } else {
         return -1;
      }
   }

// front()
// Returns front element. Pre: length()>0
   Object front() {
      if (!(this.length() > 0)) {
         throw new RuntimeException(
            "List Error: front() called on empty list");
      }

      return front.data;
   }

// back()
// Returns back element. Pre: length()>0
   Object back() {
      if (!(this.length() > 0)) {
         throw new RuntimeException(
            "List Error: back() called on empty list");
      }

      return back.data;
   }

// get()
// Returns cursor element. Pre: length()>0, index()>=0
   Object get() {
      if (!(this.length() > 0)) {
         throw new RuntimeException(
            "List Error: get() called on empty list");
      }

      if (!(this.index() >= 0)) {
         throw new RuntimeException(
            "List Error: get() called on undefined cursor");
      }
      return cursor.data;
   }

// equals()
// Returns true if and only if this List and L are the same
// integer sequence. The states of the cursors in the two Lists
// are not used in determining equality.
   public boolean equals(Object x) {
   boolean eq  = false;
   // uses two dummy nodes
   Node N, M;
   N = M = null;
   List L;
   if (x instanceof List) {
		L = (List) x;
      eq = (this.length() == L.length());
      // dummy nodes pointed at fronts
      if (eq) {
         N = this.front;
         M = L.front;
      }
      // nodes traverse list until eq evaluates false or a list's end is reached
      while ( eq && (N != null) && (M != null) ) {
         eq = N.equals(M);
         N = N.next;
         M = M.next;
      }
   }

   return eq;
}

// Manipulation procedures ------------------------------------------------------------------------
// clear()
// Resets this List to its original empty state.
   void clear() {
      front = back = cursor = null;
      length = 0;
      iCursor = -1;
      return;
   }

// moveFront()
// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
   void moveFront() {
      if (front != null) {
         cursor = front;
         iCursor = 0;
      }

      return;
   }

// moveBack()
// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
   void moveBack() {
      if (back != null) {
         cursor = back;
         iCursor = this.length() - 1;
      }

      return;
   }

// movePrev()
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
   void movePrev() {
      if (cursor != null) {
         if (cursor != front) {
            cursor = cursor.prev;
            iCursor--;
            // make cursor undefined if at front
         } else {
            cursor = null;
            iCursor = -1;
         }
      }

      return;
   }

// moveNext()
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
   void moveNext() {
      if (cursor != null) {
         if (cursor != back) {
            cursor = cursor.next;
            iCursor++;
            // make cursor undefined if at back
         } else {
            cursor = null;
            iCursor = -1;
         }
      }

      return;
   }

// prepend()
// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
   void prepend(Object data) {
      Node N = new Node(data);

      // empty list case
      if (this.length() == 0) {
         front = back = N;
         length++;

      }

      // non-empty list case
      else {
         front.prev = N;
         N.next = front;
         front = N;
         length++;

         // cursor is defined
         if (iCursor != -1) {
            iCursor++;
         }
      }

      return;
   }

// append()
// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
   void append(Object data) {
      Node N = new Node(data);

      // empty list case
      if (this.length() == 0) {
         front = back = N;
         length++;
      }

      // non-empty list case
      else {
         back.next = N;
         N.prev = back;
         back = N;
         length++;
      }

      return;
   }

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
   void insertBefore(Object data) {
      if (!(this.length() > 0)) {
         throw new RuntimeException(
            "List Error: insertBefore() called on empty list");
      }

      if (!(this.index() >= 0)) {
         throw new RuntimeException(
            "List Error: insertBefore() called on undefined cursor");
      }

      // if cursor is the front, let prepend handle
      if (cursor.prev == null) {
         prepend(data);
      } else {
         Node N = new Node(data);
         // 4 pointers to handle if not at front
         N.prev = cursor.prev;
         N.next = cursor;
         cursor.prev = N;
         N.prev.next = N;
         length++;
         iCursor++;
      }

      return;
   }

// insertAfter()
// Inserts new element after cursor.
// Pre: length()>0, index()>=0
   void insertAfter(Object data) {
      if (!(this.length() > 0)) {
         throw new RuntimeException(
            "List Error: insertAfter() called on empty list");
      }

      if (!(this.index() >= 0)) {
         throw new RuntimeException(
            "List Error: insertAfter() called on undefined cursor");
      }

      // if the cursor is at the end, append can handle it
      if (cursor.next == null) {
         append(data);
      } else {
         Node N = new Node(data);
         // 4 pointers if not at back
         N.next = cursor.next;
         N.prev = cursor;
         cursor.next = N;
         N.next.prev = N;
         length++;
      }

      return;
   }

// deleteFront()
// Deletes the front element. Pre: length()>0
   void deleteFront() {
      if (!(this.length() > 0)) {
         throw new RuntimeException(
            "List Error: deleteFront() called on empty list");
      }

      // special case where cursor is on the front
      if (cursor == front) {
         cursor = null;
         iCursor = -1;

      }

      // special case
      if (this.length() == 1) {
         this.clear();
      }

      // handle pointers and fields
      else {
         front = front.next;
         front.prev = null;
         length--;
         iCursor--;
      }

      return;
   }

// deleteBack()
// Deletes the back element. Pre: length()>0
   void deleteBack() {
      if (!(this.length() > 0)) {
         throw new RuntimeException(
            "List Error: deleteBack() called on empty list");
      }

      // special case where cursor is on the back
      if (cursor == back) {
         cursor = null;
         iCursor = -1;

      }

      // special case
      if (this.length() == 1) {
         this.clear();
      }

      // handle pointers and field
      else {
         back = back.prev;
         back.next = null;
         length--;
      }

      return;
   }

// delete()
// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
   void delete () {
      if (!(this.length() > 0)) {
         throw new RuntimeException(
            "List Error: delete() called on empty list");
      }

      if (!(this.index() >= 0)) {
         throw new RuntimeException(
            "List Error: delete() called on undefined cursor");
      }

      // let other functions handle special cases
      if (cursor == front) {
         deleteFront();
      } else if (cursor == back) {
         deleteBack();
      }

      // handle pointers and fields
      else {
         cursor.prev.next = cursor.next;
         cursor.next.prev = cursor.prev;
         cursor = null;
         iCursor = -1;
         length--;
      }

      return;
   }


// Other methods ----------------------------------------------------------------------------------
// toString()
// Overrides Object's toString method. Returns a String
// representation of this List consisting of a space
// separated sequence of integers, with front on left.
   public String toString() {
      String s = "";
      // dummy node to not disturb cursor
      Node temp = this.front;
		int count = 0;
      if (length > 0) {
         while (temp != null) {
            s = s + temp.data.toString();
				count++;
				if (count != this.length){
					s = s + " ";
				}
            temp = temp.next;
         }
      }

      return s;
   }
/*
// copy()
// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
 List copy() {
      // dummy node to not disturb cursor
      Node temp = this.front;
      List L = new List();

      while (temp != null) {
         L.append(temp.data);
         temp = temp.next;
      }

      return L;
   }

// *** OPTIONAL ***
// List concat(List L)
// Returns a new List which is the concatenation of
// this list followed by L. The cursor in the new List
// is undefined, regardless of the states of the cursors
// in this List and L. The states of this List and L are
// unchanged.
 /*  List concat(List L) {
      // use copy for simplicity
      List both = this.copy();
      // dummy node to not disturb cursor
      Node temp = L.front;

      while (temp != null) {
         both.append(temp.data);
         temp = temp.next;
      }

      return both;
   }*/
}
