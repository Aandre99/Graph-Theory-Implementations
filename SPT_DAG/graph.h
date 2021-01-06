#ifndef _GRAPH_H_
#define _GRAPH_H_

#define vertex int

typedef struct _graph *graph;
typedef struct node *adj;


struct _graph
{
   int qnt_vertex;
   int qnt_edge;
   adj *vertex_list;
};

struct node
{ 
   vertex v; 
   adj next; 
};


adj new_node(vertex v, adj next);
graph create_graph(int qnt_vertex);
void create_edge(graph g, vertex v1, vertex v2);
void print_graph(graph g);


adj new_node(vertex v, adj next)
{ 
   adj new_node = malloc(sizeof(struct node));
   new_node->v = v;
   new_node->next = next;
   return new_node;
}

graph create_graph(int qnt_vertex)
{ 
   graph g = malloc(sizeof *g);
   g->qnt_vertex = qnt_vertex;
   g->qnt_edge = 0;
   g->vertex_list = malloc(qnt_vertex * sizeof (adj));
   for (vertex i = 0; i < qnt_vertex; ++i)
   {
      g->vertex_list[i] = NULL;
   }
   return g;
}

void create_edge(graph g, vertex v1, vertex v2)
{ 
   for (adj aux = g->vertex_list[v1]; aux != NULL; aux = aux->next)
   {
      if (aux->v == v2)
      {
         return;
      }
   }
   g->vertex_list[v1] = new_node(v2, g->vertex_list[v1]);
   g->qnt_edge++;
}

void print_graph(graph g)
{
   for(vertex i = 0; i < g->qnt_vertex; ++i)
   {
      printf("%d:", i);
      for(adj aux = g->vertex_list[i]; aux != NULL; aux = aux->next)
      {
         printf(" %d", aux->v);
      }
      puts("");
   }
}


#endif

