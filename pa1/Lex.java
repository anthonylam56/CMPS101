//---------------------------------------------------------------------------------------
//Name   : Anthony Lam
//Course : CMPS101
//Programming Assignment 1
//
//Lex.java
//This file runs the List.java program and output returns the sorted items.
//
//
// 
//---------------------------------------------------------------------------------------

import java.io.*;
import java.util.*;

public class Lex{
	public static void main(String[] args){
		int numberofLines = 0;
		Scanner in = null;
		PrintWriter out = null;

		//checking to see if and only if there are 2 arguments
		if (args.length != 2){
			System.err.println("Usage: Lex infile outfile");
			System.exit(1);
		}

		//open input file and output file
		try{
			//input file
			in = new Scanner(new File(args[0]));
			//output file
			out = new PrintWriter(new FileWriter(args[1]));
		}
		catch(FileNotFoundException exception){
			exception.printStackTrace();
		}
		catch(IOException exception){
			exception.printStackTrace();
		}
		

		//counts how many lines are in the input file
		while(in.hasNextLine()){
			numberofLines++;
			in.nextLine();
		}

		//resetting scanner
		try{
			in = new Scanner(new File(args[0]));
		}
		catch(IOException exception){
			exception.printStackTrace();
		}
		

		//input file converted into array form and stored seperately
		String[] inputLines = new String[numberofLines];
		for(int i = 0; i < numberofLines ; i++){
			inputLines[i] = in.nextLine();
		}

		//create new empty List object
		List list = new List();
		list.append(0); //first element
		//insertion sort
		for(int i = 1 ; i < inputLines.length; i++){
			list.moveFront();
			String s = inputLines[i];
			int j = i ;
			
			while(j > 0 && s.compareTo(inputLines[list.get()]) >= 0){
				list.moveNext();
				j--;
			}
			if(list.index() >= 0){
				list.insertBefore(i);
			}
			else{
				list.append(i);
			}
		}

		//contents being printed to file
		list.moveFront();

		while(list.index() >= 0){
			out.println(inputLines[list.get()]);
			list.moveNext();
		}


		in.close();
		out.close();
	}
}