#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "graph.h"
#include "topological_numbering.h"
#include "spt.h"


void print(int *v, int size);


int main()
{
   int qnt_vertex, qnt_edge, v1, v2;
   printf("Numero de vertices e arestas: ");
   scanf("%d%d", &qnt_vertex,&qnt_edge);
   graph g = create_graph(qnt_vertex);
   puts("\nAdicione as arestas:\n");
   for(int i = 0; i < qnt_edge; ++i)
   {
      scanf("%d%d", &v1, &v2);
      create_edge(g, v1, v2);
   }
   puts("\nImprimindo grafo...\n");
   print_graph(g);

   int distance[qnt_vertex];
   vertex topo[qnt_vertex];
   vertex _permu_topo[qnt_vertex];
   vertex parents[qnt_vertex];
   int begin;

   printf("\nRaiz da SPT: ");
   scanf("%d", &begin);

   topological_numbering(g, topo);
   permu_topo(g, topo, _permu_topo);
   dag_spt(g, begin, parents, _permu_topo, distance);

   puts("\nImprimindo vetor de pais...\n");
   print(parents, qnt_vertex);
   puts("Imprimindo vetor de distancia a raiz...\n");
   print(distance, qnt_vertex);
 
   return 0;
}


void print(int *v, int size)
{
   for(int i = 0; i < size; ++i)
   {
      printf("%d ", v[i]);
   }
   puts("\n");
}

