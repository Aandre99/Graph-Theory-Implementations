/*

   Implementação: SPT
   
   RECEBE um grafo G direcionado com um vértice s, e
   que existe caminho de s a todos os demais vértices.
   ENCONTRA uma árvore de caminhos curtos (SPT) de G com raiz em S.

*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define vertex int

typedef struct _graph *graph;
typedef struct _queue *queue;
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

struct _queue
{
   int head;
   int tail;
   vertex *items;
   int size;
   int current_size;
};

/* Funções do grafo*/

adj new_node(vertex v, adj next);
graph create_graph(int qnt_vertex);
void create_edge(graph g, vertex v1, vertex v2);
void print_graph(graph g);

/* Funções da fila*/

queue create_queue(int size);
void enqueue(queue q, vertex item);
vertex dequeue(queue q);
int is_empty(queue q);

/* Algoritmo que gera SPT */

void spt(graph g, vertex begin, int *parents, int *distance);


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
   vertex parents[qnt_vertex];
   int begin;

   printf("\nRaiz da SPT: ");
   scanf("%d", &begin);
   spt(g, begin, parents, distance);
   puts("\nImprimindo vetor de pais...\n");
   print(parents, qnt_vertex);
   puts("Imprimindo vetor de distancia a raiz...\n");
   print(distance, qnt_vertex);
 
   return 0;
}


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

queue create_queue(int size)
{
   queue new_queue = malloc(sizeof(struct _queue));
   new_queue->head = 0;
   new_queue->tail = size - 1;
   new_queue->items = malloc(size * sizeof(vertex));
   new_queue->size = size;
   new_queue->current_size = 0;
   return new_queue;
}

void enqueue(queue q, vertex item)
{
   q->tail = (q->tail + 1) % q->size;
   q->items[q->tail] = item;
   q->current_size++;
}

vertex dequeue(queue q)
{
   vertex dequeue = q->items[q->head];
   q->head = (q->head + 1) % q->size;
   q->current_size--;
   return dequeue;
}

int is_empty(queue q)
{
   return !q->current_size;
}

void spt(graph g, vertex begin, int *parents, int *distance)
{
   const int INFINITY = INT_MAX;
   for(vertex v = 0; v< g->qnt_vertex; ++v)
   {
      distance[v] = INFINITY;
      parents[v] = -1;
   }
   distance[begin] = 0;
   parents[begin] = begin;
   queue q = create_queue(g->qnt_vertex);
   enqueue(q, begin);

   while(!is_empty(q))
   {
      vertex v = dequeue(q);
      for(adj aux = g->vertex_list[v]; aux != NULL; aux = aux->next)
      {
         if(distance[aux->v] == INFINITY)
         {
            distance[aux->v] = distance[v] + 1;
            parents[aux->v] = v;
            enqueue(q, aux->v);
         }
      }
   }
}

void print(int *v, int size)
{
   for(int i = 0; i < size; ++i)
   {
      printf("%d ", v[i]);
   }
   puts("\n");
}

