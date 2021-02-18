//---------------------------------------------------------------------------------------
//Name  : Anthony Lam
//Course: CMPS101
//
//Lex.c
//This file runs the List.c program and returns sorted items
//
//---------------------------------------------------------------------------------------



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 160

int main(int argc, char* argv[]){

	int count = 0;
	FILE *in, *out;

	char line[MAX_LEN];
	char** token;

	//check if argc equals 3
	if(argc != 3){
		printf("Usage: %s <input file> <output file>.\n", argv[0]);
	}

	//open input and output files
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if(in == NULL){
		printf("Unable to open file %s for reading.\n", argv[1]);
		exit(1);
	}
	if(out == NULL){
		printf("Unable to open %s for writing.\n", argv[2]);
	}

	//counting lines
	while(fgets(line, MAX_LEN, in) != NULL){
		count++;
	}

	rewind(in);

	//allocate amount of spaces for array
	token = malloc(count * sizeof(char*));
	//allocate space for each array space
	for(int i = 0 ; i < count ; i++){
		token[i] = malloc(MAX_LEN * sizeof(char));
	}

	//get lines into array
	int k = 0;
	while(fgets(line, MAX_LEN, in) != NULL){
		strcpy(token[k], line);
		k++;
	}

	//create new list for storage
	List l = newList();
	append(l, 0); //first element
	//insertion sort on indices
	for(int i = 1; i < count; i++){
		moveFront(l);
		char* c = token[i];
		int j = i;
		while(j > 0 && strcmp(c , token[get(l)]) >= 0){
			moveNext(l);
			j--;
		}
		if(index(l) >= 0){
			insertBefore(l, i);
		}
		else{
			append(l, i);
		}
	}

	moveFront(l);

	//contents being printed to file
	while(index(l) >=0 && index(l) != -1 ){
		fprintf(out, "%s\n", token[get(l)]);
		moveNext(l);
	}

	fclose(in);
	fclose(out);

	//clearing memory
	freeList(&l);
	//freeing data within array
	int i = 0;
	while(token[i] != NULL){
		free(token[i]);
		i++;
	}
	//freeing array object
	free(token);

	return (0);
}