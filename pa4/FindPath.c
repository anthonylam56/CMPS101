//--------------------------------------------------------------
//Name: Anthony Lam
//CruzID: alam26
//Programing Assignment 4
//
//FindPath.c
//Finds shortest path between two points
//--------------------------------------------------------------



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

#define MAX_LEN 200
int main(int argc, char *argv[]){
	int n = 0;
	FILE *in, *out;

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
		addEdge(G, u, v);
	}

	printGraph(out, G);//print adjacency list
	fprintf(out, "\n");

	//start printing out distance and shortest path
	while(fgetc(in) != EOF){
		int dest = 0;
		int source = 0;

		fscanf(in, "%d", &source);//take source from in
		fscanf(in, "%d", &dest);//take destination from in

		if(source == 0 && dest == 0){
			break;
		}
		List L = newList();
		BFS(G, source);
		getPath(L, G, dest);

		int distance = getDist(G, dest);
		if(distance != INF){
			fprintf(out, "The distance from %d to %d is %d\n", source, dest, length(L) - 1);
			fprintf(out, "A shortest %d-%d path is: ", source, dest);
			printList(out, L);
			fprintf(out, "\n\n");
		}
		else{
			fprintf(out, "The distance from %d to %d is infinity\n", source, dest);
			fprintf(out, "No %d-%d path exists\n", source, dest);
		}
		//free list memory
		freeList(&L);
	}
	//free graph memory
	freeGraph(&G);

	fclose(in);
	fclose(out);
	return 0;
}