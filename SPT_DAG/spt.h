/*

   Implementação: SPT
   
   RECEBE um grafo G direcionado acíclico com um vértice s, de modo
   que exista caminho de s a todos os demais vértices.
   ENCONTRA uma árvore de caminhos curtos (SPT) de G com raiz em S.

*/


#ifndef _SPT_H_
#define _SPT_H_


void dag_spt(graph g, vertex begin, vertex *parents, vertex *permu_topo, int *distance)
{
   const int INFINITY = INT_MAX;
   for(vertex v = 0; v < g->qnt_vertex; ++v)
   {
      parents[v] = -1;
      distance[v] = INFINITY;
   }
   parents[begin] = begin;
   distance[begin] = 0;

   for(int i = 0; i < g->qnt_vertex; ++i)
   {
      vertex v = permu_topo[i];
      for(adj aux = g->vertex_list[v]; aux != NULL; aux = aux->next)
      {
         if(distance[v] + 1 < distance[aux->v])
         {
            distance[aux->v] = distance[v] + 1;
            parents[aux->v] = v;
         }
      }
   }
}


#endif

