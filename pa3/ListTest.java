//---------------------------------------------------------------------------------------
//Name   : Anthony Lam
//Course : CMPS101
//Programming Assignment 3
//
//ListTest.java
//This is used to test List.java.
//
//---------------------------------------------------------------------------------------


public class ListTest{
	public static void main(String[] args){
		List A = new List();
      	List B = new List();
      	List C = new List();
	    List D = new List();
      	
      	for(int i = 1 ; i <= 10 ; i++){
      		A.append(i);
      		C.append(i);
      	}

	    for(int i = 10; i <= 1; i--){
	    	B.prepend(i);
	    	D.prepend(i);
	    }
	    System.out.println(A);
	    System.out.println(B);

	    System.out.println(A.equals(B));

	    D.moveFront();
		D.insertBefore(21);
		D.insertBefore(22);
		D.insertBefore(23);
		D.insertBefore(24);
		D.insertBefore(25);

		C.insertBefore(0);
		C.insertBefore(1);
		C.insertBefore(2);
		C.insertBefore(3);
		C.insertBefore(4);

	    System.out.println(C);
	    System.out.println(D);
	    D.clear();
	    System.out.println("D:\n" + D);

	    System.out.println(C.length());
	    System.out.println(D.length());
	}
}

//0 1 2 3 4 1 2 3 4 5 6 7 8 9 10
//21 22 23 24 25 21
//D:
//
//15
//0