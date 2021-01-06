#ifndef _TOPOLOGICAL_NUMBERING_H_
#define _TOPOLOGICAL_NUMBERING_H_

#include "queue.h"


void graph_in_degree(graph g, int *in_degree);
void permu_topo(graph g, vertex *topo, vertex *permu_topo);



bool topological_numbering(graph g, vertex *topo)
{
   int in_degree[g->qnt_vertex];
   graph_in_degree(g, in_degree);
   queue q = create_queue(g->qnt_vertex);
   for(vertex v = 0; v < g->qnt_vertex; ++v)
   {
      if(in_degree[v] == 0)
      {
         enqueue(q, v);
      }
   }

   int cnt = 0;
   while(!is_empty(q))
   {
      vertex v = dequeue(q);
      topo[v] = cnt++;
      for(adj aux = g->vertex_list[v]; aux != NULL; aux = aux->next)
      {
         in_degree[aux->v] -= 1;
         if(in_degree[aux->v] == 0)
         {
            enqueue(q, aux->v);
         }
      }
   }
   return cnt >= g->qnt_vertex;
}

void graph_in_degree(graph g, int *in_degree)
{
   for(vertex v = 0; v < g->qnt_vertex; ++v)
   {
      in_degree[v] = 0;
   }
   for(vertex v = 0; v < g->qnt_vertex; ++v)
   {
      for(adj aux = g->vertex_list[v]; aux != NULL; aux = aux->next)
      {
         in_degree[aux->v] += 1;
      }
   }
}

void permu_topo(graph g, vertex *topo, vertex *permu_topo)
{
   for(int i = 0; i < g->qnt_vertex; ++i)
   {
      permu_topo[topo[i]] = i;
   }
}

#endif

