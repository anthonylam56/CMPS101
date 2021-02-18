//Matrix.java
//pa3
//Anthony Lam

public class Matrix{
	
	//Entry class
	private class Entry{
		private int column;
		private double data;

		public Entry(int c, double v){
			column = c;
			data = v;
		}

		public String toString(){
			return "(" + column + ", " + data + ")" ;
		}

		public boolean equals(Object e){
			boolean equal = false;
			Entry that;

			if( e instanceof Entry){
				that = (Entry)e;
				equal = (that.data == this.data && this.column == that.column);
			}
			return equal;
		}
	}

List[] row;
int size;
//Constructor------------------------------------------------------------------------------------------------
//Matrix(int n)
//Makes a new n x n zero Matrix
//pre n >= 1
public Matrix(int n){
	if (n < 1){
		throw new RuntimeException("Matrix Error: Matrix can't be called with 0 or negative number.");
	}
	else{
		size = n;
		row = new List[size + 1];
		for(int i = 1 ; i < n + 1 ; i++){
			row[i] = new List();
		}
	}
}

//Access funtions--------------------------------------------------------------------------------------------

//int getSize()
//Returns n, the number of rows and columns of this matrix
public int getSize(){
	return this.size;
}

//int getNNZ()
//Returns the number of non-zero entries in this matrix
public int getNNZ(){
	int NNZ = 0;
	for(int i = 1 ; i <= getSize() ; i++){
		NNZ += row[i].length();
	}
	return NNZ;
}

//boolean equals(Object x)
//overrides Object's equals() method
public boolean equals(Object x){
	Matrix m;
	//boolean eq = false;
	if(x instanceof Matrix){
		m = (Matrix)x;
		if(getSize() != m.getSize() || getNNZ() != m.getNNZ()){
			return false;
		}
		else{
			for(int i = 1; i <= getSize() ; i++){
				if(!row[i].equals(m.row[i])){
					return false;
				}
			}	
		}
	}
	return true;
}

//Manipulation procedures------------------------------------------------------------------------------------

//void makeZero()
//sets this matrix to the zero state
public void makeZero(){
	for(int i = 1 ; i <= getSize() ; i++){
		row[i] = new List();
	}
}
	

//Matrix copy()
//returns a new Matrix having the same entries as this Matrix
public Matrix copy(){
	//create new Matrix m to copy to
	Matrix m = new Matrix(getSize());
	for(int i = 1; i <= getSize() ; i++){
		row[i].moveFront();
		while (row[i].index() != -1) {
			Entry e = (Entry)row[i].get();
			m.changeEntry(i, e.column, e.data);
			row[i].moveNext();
		}
	}
	return m;
}

//void changeEntry(int i, int j, double x)
//chages ith row, jth column of this Matrix to x
//pre: 1 <= i <= getSize, 1 <= j <= getSize()
public void changeEntry(int i , int j, double x){

	if(i < 1 || i > getSize() || j < 1 || j > getSize()){
		throw new RuntimeException("Matrix Error: changeEntry() called with invalid ith,jth position on Matrix.");
	}
	if(row[i].length() == 0){
		if(x != 0){
			Entry e = new Entry(j , x);
			row[i].append(e);
		}
	}
	else{
		boolean found = false;
		row[i].moveFront();
		while(row[i].index() >= 0){
			Entry en =(Entry)row[i].get();
			if(en.column == j){
				found = true;
			}
			else{
				found = false;
			}
			
			if(found){
				if (x == 0){
					row[i].delete();
				}
				else{
					en.data = x;
				}
				break;
			}
			row[i].moveNext();
		}

		if(!found && x != 0){
			if(row[i].index() == -1){
				row[i].append(new Entry(j , x));
			}
			else{
				while(((Entry)row[i].get()).column != j && row[i].index() != -1){
				//might have to change to < for both
					row[i].moveNext();
				}
				if(row[i].index() > j){
					row[i].insertBefore(new Entry(j , x));
				}
				else{
					row[i].append(new Entry(j , x));
				}
			}
		}
		
	}
}


//Matrix scalarMult(double x)
//returns a new Matrix that is the product of this Matrix with x
public Matrix scalarMult(double x){
	Matrix m = copy();
	for(int i = 1 ; i <= getSize() ; i++){
		m.row[i].moveFront();
		while(m.row[i].index() >= 0){
			Entry temp = ((Entry)m.row[i].get());
			temp.data *= x;
			m.row[i].moveNext();
		}
	}
	return m;
}

//Matrix add(Matrix M)
//returns a new Matrix that is the sum of this Matrix with M
//pre: getSize() == M.getSize()
public Matrix add(Matrix M){
	if(getSize() != M.getSize()){
		throw new RuntimeException("Matrix Error: add() called with different Matrix sizes.");
	}
	if(M == this){//multiply by 2 if adding the same thing
		return copy().scalarMult(2);
	}
	Matrix m = new Matrix(getSize());
	for(int i = 1; i <= getSize() ; i++){
		m.row[i] = addAndSub(row [i], M.row[i], 1);
	}
	return m;
}

//Matrix sub(Matrix M)
//returns a new Matrix that is the difference of this Matrix with M
//pre: getSize() == M.getSize()
public Matrix sub(Matrix M){
	if(getSize() != M.getSize()){
		throw new RuntimeException("Matrix Error: add() called with different Matrix sizes.");
	}
	if(this == M){//subtracting itself = 0 for all entries.
		return new Matrix(getSize());
	}
	Matrix m = new Matrix(getSize());
	for(int i = 1; i <= getSize(); i++){
		m.row[i] = addAndSub(row[i], M.row[i], -1);
	}

	return m;
}

//takes in row of this matrix and Matrix M in add() and sub() and return a List with its
//corresponding 
//Pre: P.index() >= 0 || Q.index() >= 0
//addOrSub = -1 if subtracting
//addOrSub = 1 if adding
private List addAndSub(List P, List Q, int addOrSub){
	double val = 0;
	P.moveFront();
	Q.moveFront();
	List l = new List();

	while(P.index() >= 0 || Q.index() >= 0){
		if(P.index() >= 0 && Q.index() >= 0){//both P and Q have not fallen off the list
			Entry temp1 = (Entry)P.get();
			Entry temp2 = (Entry)Q.get();
			if(temp1.column < temp2.column){
				l.append(new Entry(temp1.column , (addOrSub) * temp1.data));
				P.moveNext();
			}
			else if(temp1.column > temp2.column){
				l.append(new Entry(temp2.column, (addOrSub) * temp2.data));
				Q.moveNext();
			}
			else if(temp1.column == temp2.column){
				if((addOrSub == 1 && temp1.data + temp2.data != 0) || (addOrSub == -1 && temp1.data - temp2.data != 0)){
					if(addOrSub == 1){
						l.append(new Entry(temp1.column, (temp1.data + temp2.data)));
					}
					else if(addOrSub == -1){
						l.append(new Entry(temp1.column, (temp1.data - temp2.data)));
					}
					P.moveNext();
					Q.moveNext();
				}
			}
		}
		else if(P.index() >= 0){//if Q has fallen off the list
			Entry temp1 = (Entry)P.get();
			l.append(new Entry(temp1.column, temp1.data));
			P.moveNext();
		}
		else{//if P has fallen off the list
			Entry temp2 = (Entry)Q.get();
			l.append(new Entry(temp2.column, (addOrSub * temp2.data)));
			Q.moveNext();
		}
	}
	return l;
}

//Matrix transpose()
//returns a new Matrix that is the transpose of this Matrix
public Matrix transpose(){
	Matrix m = new Matrix(getSize());

	for(int i = 1 ; i <= getSize() ; i++){
		row[i].moveFront();
		while(row[i].index() >= 0){
			Entry e = (Entry)(row[i].get());
			m.changeEntry(e.column, i, e.data);
			row[i].moveNext();
		}
	}
	return m;
}

//Matrix mult(Matrix M)
//returns a new Matrix that is the product of this Matrix with M
//pre: getSize() == M.getSize()
public Matrix mult(Matrix M){
	if(getSize() != M.getSize()){
		throw new RuntimeException("Matrix Error: mult() called with different Matrix sizes.");
	}
	Matrix m = M.transpose();
	Matrix T = new Matrix(getSize());
	for(int i = 1 ; i < getSize() ; i++){
		if(row[i].length() == 0){
			continue;
		}
		for(int j = 1 ; j < getSize() ; j++){
			if(T.row[j].length() == 0){
				continue;
			}
			else{
				m.changeEntry(i , j , dot(row[i], T.row[j]));
			}
		}
	}
	return m;
	
}

//private static double dot(List P, List Q)
//helper method for mult()
private static double dot(List P, List Q){
	double prod = 0;
	P.moveFront();
	Q.moveFront();

	while(P.index() >= 0 && Q.index() >= 0){
		Entry temp1 = (Entry)P.get();
		Entry temp2 = (Entry)Q.get();
		if(temp1.column == temp2.column){
			prod = (temp1.data * temp2.data);
			P.moveNext();
			Q.moveNext();
		}
		else if(temp1.column > temp2.column){
			Q.moveNext();
		}
		else if(temp2.column > temp1.column){
			P.moveNext();
		}
	}
	return prod;
}

//Other functions--------------------------------------------------------------------------------------------

//public String toString()
//overrides Object's toString() method
public String toString(){
	String str = "";
	for(int i = 1 ; i <= getSize() ; i++){
		if(row[i].length() >= 1){
			str += (i + ": " + row[i] + "\n");
		}
	}
	return str;
}

}