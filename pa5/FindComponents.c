//--------------------------------------------------------------
//Name: Anthony Lam
//CruzID: alam26
//Programing Assignment 5
//
//FindComponents.c
//Finds strongly connected components
//--------------------------------------------------------------



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char *argv[]){
	int n = 0;
	FILE *in, *out;

	List L = newList();

	if(argc != 3){
		printf("FindPath error: wrong # of arguments.");
		exit(1);
	}

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	if(in == NULL){
		printf("Unable to open file %s for reading.\n", argv[1]);
		exit(1);
	}
	if(out == NULL){
		printf("Unable to open %s for writing.\n", argv[2]);
		exit(1);
	}

	fscanf(in , "%d" , &n);
	Graph G = newGraph(n);

	//adding edges to graph
	while(fgetc(in) != EOF){
		int u = 0 , v = 0;
		fscanf(in, "%d", &u);
		fscanf(in, "%d", &v);
		if(u == 0 && v == 0){
			break;
		}
		addArc(G, u, v);
	}

	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);//print adjacency list
	fprintf(out, "\n");


	//adding vertice numbers to list
	for(int i = 1; i <= n; i++){
		append(L, i);
	}

	//perform DFS
	DFS(G, L);

	//perform DFS on G transpose
	Graph graphT = transpose(G);
	DFS(graphT, L);

	//printList(out, L); test statement

	int scc = 0;
	for(int i = 1; i <= getOrder(graphT); i++){
		if(getParent(graphT, i) == NIL){
			scc++;
		}
	}
	fprintf(out, "G contains %d strongly connected components:\n", scc);

	List *sccList = calloc(scc + 1, sizeof(List));
	//creating list of sccs
	for(int i = 1; i <= scc; i++){
		sccList[i] = newList();
	}

	//start doing operations to group SCCs
	int sccCount = 1;
	int temp = front(L);
	int listlength = length(L);//initialize list length as popping occurs 
	for(int i = 1 ; i <= listlength - 1; i++){
		int pop = back(L); //pop function
		deleteBack(L);//pop function
		prepend(sccList[sccCount], pop);
		if(getParent(graphT, pop) == NIL){
			sccCount++;
		}
	}
	prepend(sccList[sccCount], temp);
	

	int i = 1;
	while(i <= scc){
		fprintf(out, "Component %d: ", i);
		printList(out, sccList[i]);
		fprintf(out, "\n");
		i++;
	}

	//freeing memory
	freeGraph(&G);
	freeGraph(&graphT);
	for(int i = 0; i <= scc; i++){
		freeList(&sccList[i]);
	}
	free(sccList);
	freeList(&L);

	fclose(in);
	fclose(out);
	return 0;
}