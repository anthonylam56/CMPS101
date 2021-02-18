//--------------------------------------------------------------
//Name: Anthony Lam
//CruzID: alam26
//Programing Assignment 4
//
//Graph.c
//Graph ADT using List files from PA2
//--------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
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
	int *distance;
	int order;
	int size;
	int source;
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
	graph -> distance = calloc(n+1 , sizeof(int));

	graph -> order = n;
	graph -> size = 0;
	graph -> source = NIL;

	for(int i = 1; i <= n ; i++){
		graph -> neighbors[i] = newList();
		graph -> color[i] = WHITE;
		graph -> parent[i] = NIL;
		graph -> distance[i] = INF;
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
		free(g -> distance);

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

//getSource(Graph G)
//Returns source of Graph G
int getSource(Graph G){
	if(G == NULL){
		printf("getSource() called with null Graph.\n");
		exit(1);
	}
	return G -> source;
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

//getDist()
//returns the distance between (most recent) source to the vertex u
int getDist(Graph G, int u){
	if(G == NULL){
		printf("getDist() called with null Graph.\n");
		exit(1);
	}
	if(u < 1 || (u > getOrder(G))){
		printf("getDist() called with out of bounds integer");
		exit(1);
	}
	if(getSource(G) == NIL){
		return INF;
	}

	return G -> distance[u];
}

//getPath()
//finds the path from the source of graph G to the vertice u
void getPath(List L, Graph G, int u){
	if(G == NULL){
		printf("getPath() called with null Graph.\n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)){
		printf("getPath() called with out of bounds integer.");
		exit(1);
	}
	if(getSource(G) == NIL){
		printf("getPath() called with NIL source.");
		exit(1);
	}
	if(u == getSource(G)){
		append(L, getSource(G));
	}
	else if(G-> parent[u] == NIL){
		append(L, NIL);
	}
	else{
		getPath(L, G, G -> parent[u]);
		append(L, u);
	}
}

//Manipulation procedures---------------------------------------

//makeNull()
//deletes all edges of graph G
void makeNull(Graph G){
	if(G == NULL){
		printf("makeNull() called with null Graph.\n");
		exit(1);
	}
	for(int i = 1; i <= getOrder(G); i++){
		clear(G -> neighbors[i]);
	}
	G -> size = 0;
}

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

void BFS(Graph G, int s){
	for(int i = 1; i <= getOrder(G); i++){
		G -> color[i] = WHITE;
		G -> distance[i] = INF;
		G -> parent[i] = NIL;
	}

	List Q = newList();
	G -> source = s;
	G -> color[s] = GRAY;
	G -> distance[s] = 0;
	G -> parent[s] = NIL;
	append(Q , s);
	while(length(Q) > 0){
		int u = front(Q);
		deleteFront(Q);
		moveFront(G -> neighbors[u]);

		while(index(G -> neighbors[u]) != -1){
			int i = get(G -> neighbors[u]);
			if(G->color[i] == WHITE){
				G -> color[i] = GRAY;
				G -> distance[i] = (G -> distance[u]) + 1;
				G -> parent[i] = u;
				append(Q, i);
			}
			moveNext(G -> neighbors[u]);
		}
		G -> color[u] = BLACK;
	}
	freeList(&Q);
}

//Other procedures----------------------------------------------

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