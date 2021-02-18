//--------------------------------------------------------------
//Name: Anthony Lam
//CruzID: alam26
//Programing Assignment 5
//
//Graph.c
//Graph ADT using List files from PA2(with DFS)
//--------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"
//colors
#define WHITE 0
#define GRAY 1
#define BLACK 2

//Structs-------------------------------------------------------

typedef struct GraphObj{
	List *neighbors;
	int *color;
	int *parent;
	int *discover;
	int *finish;

	int order;
	int size;
}GraphObj;

typedef struct GraphObj* Graph;

//Constructors - Destructors------------------------------------

//newGraph(int n)
//Creates new Graph object with n vertices
Graph newGraph(int n){
	Graph graph = malloc(sizeof(GraphObj));
	graph -> neighbors = calloc(n+1, sizeof(List));
	graph -> color = calloc(n+1, sizeof(int));
	graph -> parent = calloc(n+1, sizeof(int));
	graph -> discover = calloc(n+1, sizeof(int));
	graph -> finish = calloc(n+1, sizeof(int));

	graph -> order = n;
	graph -> size = 0;

	for(int i = 1; i <= n ; i++){

		graph -> neighbors[i] = newList();
		graph -> color[i] = WHITE;
		graph -> parent[i] = NIL;
		graph -> discover[i] = UNDEF;
		graph -> finish[i] = UNDEF;
	}

	return graph;
}


//freeGraph()
//Frees all heap memory associated with Graph *pG, and sets *pG to NULL
void freeGraph(Graph* pG){
	Graph g = *pG;
	if(pG != NULL || *pG != NULL){
		for(int i = 1 ; i <= getOrder(g); i++){
			freeList(&(g -> neighbors[i]));
		}

		free(g -> neighbors);
		free(g -> color);
		free(g -> parent);
		free(g -> discover);
		free(g -> finish);

		free(*pG);
		*pG = NULL;
	}
}

//Access functions----------------------------------------------

//getOrder(Graph G)
//Returns order of Graph G.
int getOrder(Graph G){
	if(G == NULL){
		printf("getOrder() called with null Graph.\n");
		exit(1);
	}
	return G->order;
}

//getSize(Graph G)
//Returns size of Graph G
int getSize(Graph G){
	if(G == NULL){
		printf("getSize() called with null Graph.\n");
		exit(1);
	}
	return G -> size;
}

//getParent()
//return parent of vertice u in Graph G
int getParent(Graph G, int u){
	if(G == NULL){
		printf("getParent() called with null Graph.\n");
		exit(1);
	}
	if(u < 1 || (u > getOrder(G))){
		printf("getParent() called with out of bounds integer u.");
		exit(1);
	}
	return G -> parent[u];
}

//getDiscover()
//gets discover time
int getDiscover(Graph G, int u){
	if(G == NULL){
		printf("getDiscover() called with null graph.\n");
		exit(1);
	}
	if(u < 1 || (u > getOrder(G))){
		printf("getDiscover() called with out of bounds integer u.\n");
		exit(1);
	}
	return G -> discover[u];
}


//getFinish()
//gets finish time
int getFinish(Graph G, int u){
	if(G == NULL){
		printf("getFinish() called with null graph.\n");
		exit(1);
	}
	if(u < 1 || (u > getOrder(G))){
		printf("getFinish() called with out of bounds integer u.\n");
		exit(1);
	}
	return G -> finish[u];
}

//Manipulation procedures---------------------------------------

//addEdge()
//adds edge between u to v
void addEdge(Graph G, int u, int v){
	if(G == NULL){
		printf("addEdge() called with null Graph.\n");
		exit(1);
	}
	if(u < 0 || u > getOrder(G)){
		printf("addEdge() called with integer u out of bounds.");
		exit(1);
	}
	if(v < 0 || v > getOrder(G)){
		printf("addEdge() called with integer v out of bounds.");
		exit(1);
	}

	addArc(G, u, v);
	addArc(G, v, u);
	G -> size--;
}

void addArc(Graph G, int u, int v){
	if(G == NULL){
		printf("addArc() called with null Graph.\n");
		exit(1);
	}
	if(u < 0 || u > getOrder(G)){
		printf("addArc() called with integer u out of bounds.");
		exit(1);
	}
	if(v < 0 || v > getOrder(G)){
		printf("addArc() called with integer v out of bounds.");
		exit(1);
	}

	moveFront(G -> neighbors[u]);
	
	while(index(G -> neighbors[u]) > -1 && v > get(G->neighbors[u])){
		moveNext(G -> neighbors[u]);
	}
	if(index(G -> neighbors[u]) == -1){
		append(G -> neighbors[u], v);
	}
	else{
		insertBefore(G -> neighbors[u], v);
	}
	

	G->size++;
}
	
void DFS(Graph G, List S){

	if(G == NULL || S == NULL){
		printf("DFS() called on null graph or list.\n");
		exit(1);
	}
	if(length(S) != getOrder(G)){
		printf("DFS called with length(S) != getOrder(G).\n");
		exit(1);
	}
	//initializer
	for(int i = 1; i <= getOrder(G) ; i++){
		G -> color[i] = WHITE;
		G -> parent[i] = NIL;
	}

	int time = 0;
	moveFront(S);

	while(index(S) >= 0){
		int u = get(S);
		if(G -> color[u] == WHITE){
			visit(G, S, u, &time);
		}
		moveNext(S);
	}
	for(int i = 0; i < getOrder(G); i++){
		deleteBack(S);//delete stack ends as they are not needed
	}
}

void visit(Graph G, List S, int u, int *time){
	if(G == NULL){
		printf("visit() called with a null graph.");
		exit(1);
	}
	if(S == NULL){
		printf("visit() called with null list.");
		exit(1);
	}
	//time = time + 1;
	G -> discover[u] = ++(*time);
	G -> color[u] = GRAY;
	moveFront(G -> neighbors[u]);
	while(index(G -> neighbors[u]) >= 0){
		int v = get(G -> neighbors[u]);
		if(G -> color[v] == WHITE){
			G -> parent[v] = u;
			visit(G, S, v, time);
		}
		moveNext(G -> neighbors[u]);
	}
	G -> color[u] = BLACK;
	G -> finish[u] = ++(*time);
	prepend(S,u);//add on to stack
}

//Other procedures----------------------------------------------

//transpose(Graph G)
//returns transpose of Graph G
Graph transpose(Graph G){
	Graph graphT = newGraph(getOrder(G));
	for(int i = 1 ; i <= getOrder(G); i++){
		moveFront(G -> neighbors[i]);
		if(G -> neighbors[i] > 0){
			while(index(G -> neighbors[i]) != -1){
				addArc(graphT, get(G -> neighbors[i]), i);
				moveNext(G -> neighbors[i]);
			}
		}
	}
	return graphT;
}

//Graph copyGraph(Graph G)
//returns copy of graph G
Graph copyGraph(Graph G){
	Graph copy = newGraph(getOrder(G));
	for(int i = 1; i <= getOrder(G); i++){
		moveFront(G -> neighbors[i]);
		if(G -> neighbors[i] > 0){
			while(index(G -> neighbors[i]) >= 0){
				addArc(copy, i, get(G -> neighbors[i]));
				moveNext(G -> neighbors[i]);
			}
		}
	}
	return copy;
}

//printGraph
//prints adjacency list to Graph G
void printGraph(FILE* out, Graph G){
	if(G == NULL){
		printf("printGraph() called with null Graph.");
		exit(1);
	}

	for(int i = 1; i <= getOrder(G); i++){
		fprintf(out, "%d: ", i);
		printList(out, G -> neighbors[i]);
		fprintf(out, "\n");
	}
	
}