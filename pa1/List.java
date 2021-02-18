//---------------------------------------------------------------------------------------
//Name   : Anthony Lam
//Course : CMPS101
//Programming Assignment 1
//
//List.java
//This is a List ADT that incluedes a "cursor" that can be used for iteration. This List
//ADT uses a doubly linked list. Also contains a Node class.
//
// 
//---------------------------------------------------------------------------------------

public class List{

	//Node Class
	private class Node{
		//Fields or instance variables
		private Node next;
		private Node prev;
		private Node cursor;
		int data;

		public Node(int data){
			this.data = data;
			next = null;
			prev = null;
		}

		public String toString(){ //overrides original toString's method
			return String.valueOf(data);
		}

		public boolean equals(Object x){
			boolean equal = false;
			Node that;
			if(x instanceof Node){
				that = (Node) x;
				equal = (this.data == that.data);
			}
			return equal;
		}
	}

	//Beginning of List.java class
	//instance variables
private Node front;
private Node back;
private Node cursor;
private int length;
private int index;

//List Constructor
//Creates a new empty list.
public List() {
	Node front = null;
	Node back = null;
	cursor = null;
	index = -1;
	length = 0;
}

// Access functions----------------------------------------------------------------------

//int length()
//Returns the number of elements in this list.
public int length(){
	return length;
}

//int index()
//If cursor is defined, returns the index of the cursor element.
public int index(){
	if(this.length() <= 0){
		return -1;
	}
	return index;
}

//int front()
//Returns front element. Pre: length()>0
public int front(){
	if(this.length() <= 0){
		throw new RuntimeException(
			"List Error: front() called on an empty List");
	}
	else{
		return front.data;
	}
}

//int back()
//Returns back element. Pre:length()>0
public int back(){
	if (this.length() <= 0){
		throw new RuntimeException(
			"List Error: back() called on empty List");
	}
	else{
		return back.data;
	}
}

//int get()
//Returns cursor element. Pre: length() > 0, index() >= 0
public int get(){
	if(this.length() <= 0){
		throw new RuntimeException(
			"List error: get() called on an empty list.");
	}
	if(cursor == null){
		throw new RuntimeException(
			"List error: get() called with an undefined cursor.");
	}
	return cursor.data;
}

//boolean equals(List L)
//Returns true if and only if this List and L are the same
//integer sequence. The states of the cursors in the two Lists
//are not used in determining equality.
public boolean equals(List L){
	boolean eq = false;
	Node a, b;
	eq = (this.length() == L.length);
	if (eq == true){
		a = this.front;
		b = L.front;
		while(eq && a != null){
			eq = a.equals(b);
			a = a.next;
			b = b.next;
		}
	}
	return eq;
}


// Manipulation procedures---------------------------------------------------------------

//void clear()
//Resets this List to its original empty space.
public void clear() {
	this.front = null;
	this.back = null;
	index = -1;
	cursor = null;
	length = 0;

}

//void moveFront()
//If List is non-empty, places the cursor under the front element,
//otherwise do nothing.
public void moveFront(){
	if(this.length() > 0){
		cursor = this.front;
		index = 0;
	}
}

//void moveBack()
//If List is non-empty, places the cursor under the back element,
//otherwise does nothing.
public void moveBack(){
	if (this.length > 0){
		cursor = this.back;
		index = length - 1;
	}
}

//void movePrev()
//if cursor is defined and not at front, moves cursor one step toward
//undefined, if cursor is undefined does nothing.
public void movePrev(){
	if(cursor == front){
		cursor = null;
		index = -1;
	}
	else{
		cursor = cursor.prev;
		index--;
	}
}

//void moveNext()
//If cursor is defined and not at back, moves cursor one step toward
//undefined, if cursor is undefined does nothing.
public void moveNext(){
	if(cursor == back){
		cursor = null;
		index = -1;
	}
	else{
		cursor = cursor.next;
		index++;
	}
}

//void prepend(int data)
//Insert new element into this List. If List is non-empty,
//insertion takes place before front element.
public void prepend(int data){
	Node newNode = new Node(data);

	if(front == null){
		front = back = newNode;
		cursor = front;
	}
	else{
		this.front.prev = newNode;
		newNode.next = this.front;
		this.front = newNode;
		index++;
	}
	length++;
}


//void append(int data)
//Insert new element into this List. If List is non-empty,
//insertion takes place after back element.
public void append(int data){
	Node newNode = new Node(data);

	if(back == null){
		front = back = newNode;
		cursor = back;
	}
	else{
		this.back.next = newNode;
		newNode.prev = this.back;
		this.back = newNode;
		newNode.next = null;
	}
	length++;
}

//void insertBefore()
//Insert new element before cursor.
//Pre: length() > 0, index() >= 0
public void insertBefore(int data){
	Node newNode = new Node(data);

	if(this.length() <= 0){
		//throw new RuntimeException(
		//	"List Error: insertBefore() called with List empty.");
		prepend(data);
	}
	if(cursor == null){
		throw new RuntimeException(
			"List Error: insertBefore() called with cursor undefined.");
	}
	if(cursor == front){
		prepend(data);
	}
	else{
		newNode.next = cursor;
		newNode.prev = cursor.prev;
		cursor.prev.next = newNode;
		cursor.prev = newNode;
		index++;
		length++;
	}
}

//void insertAfter(int data)
//Inserts new element after cursor.
//Pre: length() > 0, index() > = 0
public void insertAfter(int data){
	Node newNode = new Node(data);

	if (this.length() <= 0){
		throw new RuntimeException(
			"List Error: insertAfter() called with List empty.");
		
	}
	if(this.index() < 0){
		throw new RuntimeException(
			"List Error: insertAfter() called with cursor undefined.");
	}
	if(cursor == back){
		append(data);
	}
	else{
		cursor.next.= newNode;
		newNode.prev = cursor;
		newNode.next = cursor.next; 
		cursor.next = newNode;
		length++;
	}
}

public void deleteFront(){
	if(this.length() <= 0){
		throw new RuntimeException(
			"List Error: deleteFront() called on a empty list.");
	}
	else{
		if(front == cursor){
			index = -1;
			cursor = null;
		}
		if(this.length() > 1){
			front = front.next;
			front.prev = null;
			
			if(cursor != null){
				index--;
			}
		}
		length--;
	}
}

public void deleteBack(){
	if(length() <= 0){
		throw new RuntimeException(
			"List Error: deleteBack() called on empty List.");
	}
	else{
		if(this.back == cursor){
			index = -1;
			cursor = null;
		}
		if(this.length() > 1){
			back = back.prev;
			back.next = null;
		}
		length--;
	}
}

public void delete(){
	if(this.length() <= 0){
		throw new RuntimeException(
			"List Error: delete() called on empty List.");
	}
	if(cursor == null){
		throw new RuntimeException(
			"List Error: delete() called with undefined cursor.");
	}
	if(cursor == front){
		deleteFront();
	}
	else if(cursor == back){
		deleteBack();
	}
	else{
		cursor.prev.next = cursor.next;
		cursor.next.prev = cursor.prev;
		length--;
	}
	index = -1;
}

//public String toString()
//Overides Object's toString method. Returns a String representation
//of this List consisting of a space sperated sequence of integers,
//with front on left.

public String toString(){
	Node newNode = front;
	StringBuffer s = new StringBuffer();

	while(newNode != null){
		s.append(newNode.data);
		if(newNode.next != null){
			s.append(" ");
		}
		newNode = newNode.next;
	}
	return new String(s);
}

//List copy()
//Returns a new List representing the same integer sequence as this
//List. The cursor in the new list is undefined, regardless of the
//state of the cursor in this List. This List is unchanged.

public List copy(){
	List l = new List();
	Node n = front;
	if(this.length() > 0){
		while(n != null){
			l.append(n.data);
			n = n.next;
		}
	}
	l.cursor = null;
	l.index = -1;
	return l;
}
}







