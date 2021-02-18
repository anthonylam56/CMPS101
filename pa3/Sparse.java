//---------------------------------------------------------------------------------------
//Name   : Anthony Lam
//Course : CMPS101
//Programming Assignment 3
//
//Sparse.java
//Main program that runs the Matrix ADT.
// 
//---------------------------------------------------------------------------------------

import java.io.*;
import java.util.*;

public class Sparse{
	public static void main(String [] args)throws IOException{
		Scanner in = null;
		PrintWriter out = null;

		if(args.length != 2){
			System.err.println("Usage: Sparse infile outfile");
			System.exit(1);
		}

		try{
			//input file
			in = new Scanner(new File(args[0]));
			//output file
			out = new PrintWriter(new FileWriter(args[1]));
		}
		catch(FileNotFoundException exception){
			exception.printStackTrace();
			System.exit(1);
		}
		catch(IOException exception){
			exception.printStackTrace();
			System.exit(1);
		}

		//reading n,a,b from input file
		int n = Integer.parseInt(in.next())+1;
		int a = Integer.parseInt(in.next());
		int b = Integer.parseInt(in.next());

		//creating Matrix object
		Matrix A = new Matrix(n);
		Matrix B = new Matrix(n);

		//filling in matrix A
		for(int i = 1 ; i <= a; i++){
			int rows = Integer.parseInt(in.next());
			int cols = Integer.parseInt(in.next());
			double data = Double.parseDouble(in.next());

			A.changeEntry(rows, cols, data);
		}

		//filling in matrix B
		for(int j = 1 ; j <= b; j++){
			int rows = Integer.parseInt(in.next());
			int cols = Integer.parseInt(in.next());
			double data = Double.parseDouble(in.next());

			B.changeEntry(rows, cols, data);
		}


		//results to output file
		//lists non-zero entries for matrix A
		out.println("A has " + A.getNNZ() + " non-zero entries:");
		out.println(A);

		//lists non-zero entries for matrix B
		out.println("B has " + B.getNNZ() + " non-zero entries:");
		out.println(B);

		//scalarMult(1.5) on A
		out.println("(1.5)*A =");
		out.println(A.scalarMult(1.5));

		//Addtion from Matrix A onto B
		out.println("A+B =");
		out.println(A.add(B));

		//Addition from Matrix A onto itself
		out.println("A+A =");
		out.println(A.add(A));

		//Subtraction from Matrix B to A
		out.println("B-A =");
		out.println(B.sub(A));

		//Subtraction from Matrix A to itself
		out.println("A-A =");
		out.println(A.sub(A));

		//A Transpose
		out.println("Transpose(A) =");
		out.println(A.transpose());

		//Multiplication from Matrix A onto B
		out.println("A*B =");
		out.println(A.mult(B));

		//Multiplication from Matrix B to itself
		out.println("B*B =");
		out.println(B.mult(B));

		//closing streams
		in.close();
		out.close();
	}
}