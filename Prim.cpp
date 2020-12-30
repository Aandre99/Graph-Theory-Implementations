#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <queue>
#include <limits>
#include <tuple>
using namespace std;

// Definitions

int* previous;

typedef pair<int,double> vertex;
typedef vector<vertex> Adj;
typedef vector<Adj> Graph;

struct myComp { 
	constexpr bool operator()( 
		vertex const& a, 
		vertex const& b) 
		const noexcept 
	{ 
		return a.second > b.second; 
	} 
};

// userful functions

void show_graph(Graph G){

    int i, j;
    for (i = 0; i < G.size(); i++){
        printf("[%d] -> ", i);
        for(vertex v:G[i]){
            printf("(%d,%.2lf) -> ", v.first, v.second );
        }
        printf("\n");
    }
}
Graph add_edge(Graph G, int v1,int v2, double weight){
    
    G[v1].push_back(make_pair(v2,weight));
    return G;
}

// Prim algorithm

double Prim(Graph G, int v_start){

    int visited[G.size()];
    double cost[G.size()];
    int i,v;

    for (v=0;v < G.size();v++)
    {
        visited[v] = 0;
        *(previous + v) = -1; 
        cost[v] = INT16_MAX;
    }

    cost[v_start] = 0;
    *(previous + v_start) = v_start;

    priority_queue<vertex,Adj,myComp> Q;

    Q.push(make_pair(v_start,cost[v_start]));
    while (!Q.empty())
    {
        vertex u = Q.top();
        Q.pop();
        visited[u.first] = 1;

        for(vertex v:G[u.first])
        {
            if (!visited[v.first])
            {
                if(cost[v.first] > v.second)
                {
                    cost[v.first] = v.second;
                    *(previous + v.first) = u.first;
                    Q.push(make_pair(v.first,cost[v.first]));
                }
            }
        }
    }

     printf("ola2");

    double min_cost = 0.0;
    // compute cost of generator tree
    for (i=0;i<G.size();i++)
    {
        if (cost[i] != INT16_MAX){
        min_cost += cost[i];}
    }
    return min_cost;
}

int main(){

    int n_vertices,n_edges;
    int i,v1,v2,v_start;
    int* generator_tree = NULL;

    double w,min_cost = 0.0;
    Graph graph;

    scanf("%d", &n_vertices);
    scanf("%d", &n_edges);

    graph.resize(n_vertices);
    previous = (int*)malloc(n_vertices * sizeof(int));

    for(i=0;i<n_edges;i++)
    {
        scanf("%d %d %lf", &v1,&v2,&w);
        graph = add_edge(graph,v1,v2,w);
        graph = add_edge(graph,v2,v1,w);
    }
    printf("\n\n");
    show_graph(graph);
    printf("\n\n");
    scanf("%d",&v_start);
    min_cost = Prim(graph,v_start);

    printf("The generator tree is: \n");
    for (i=0;i<n_vertices;i++)
    {
        printf(" %d ", *(previous+i));
    }
    printf("\nThe minimum cost of generator tree is: %.lf\n", min_cost);
    free(previous);
    return 0;
}

