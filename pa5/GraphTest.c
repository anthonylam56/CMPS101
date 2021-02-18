//--------------------------------------------------------------
//Name: Anthony Lam
//CruzID: alam26
//Programing Assignment 5
//
//GraphTest.c
//Graph ADT Tester, with GraphClient uncommented
//--------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
	//int n =  10;
	//Graph G = newGraph(n);
	//Graph H = newGraph(n + 5);

	//should print 0's for both
	//printf(getSize(G));
	//printf(getSize(H));

	//addEdge(G, 1 , 2);
	//addEdge(G, 1 , 3);
	//addEdge(G, 1 , 4);
	//addEdge(G, 1 , 5);
	//addEdge(G, 2 , 3);
	//addEdge(G, 2 , 5);

	//addEdge(H, 1 , 2);
	//addEdge(H, 1 , 3);
	//addEdge(H, 1 , 4);
	//addEdge(H, 1 , 5);
	//addEdge(H, 2 , 3);
	//addEdge(H, 2 , 5);
	//addEdge(H, 2, 16);
	//H should print error for out of bounds.

	//getOrder(G);//10
	//getOrder(H);//15

	//print adjacency list of G & H
	//printGraph(stdout, G);
	//printGraph(stdout, H);

	//freeGraph(G);
	//freeGraph(H);
	

	//return 0;

   int i, n=8;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   return(0);
}