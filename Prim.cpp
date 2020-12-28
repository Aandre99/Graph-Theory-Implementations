#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <queue>
#include <limits>

using namespace std;

//definitions -> pair<vertex,distance>

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

void Prim(Graph G, int v_start){

    int visited[G.size()],previous[G.size()];
    double coust[G.size()];
    int i,v;

    for (v=0;v < G.size();v++)
    {
        visited[v] = 0;
        previous[v] = -1; 
        coust[v] = INT16_MAX / 2;
    }


    priority_queue<vertex,Adj,myComp> Q;
    Q.push(make_pair(v_start,0));

    while (!Q.empty())
    {
        vertex u = Q.top();
        Q.pop();

        for(vertex v:G[u.first])
        {
            if (!visited[v.first])
            {
                if(coust[v.first] > v.second)
                {
                    coust[v.first] = v.second;
                    previous[v.first] = u.first;
                }
            }
        }
    }


    for(v=0;v < G.size();v++)
    {
        printf(" %d ", previous[v]);
    }
}

int main(){

    int n_vertices,n_edges;
    int i,v1,v2,v_start;
    double w;
    Graph graph;

    scanf("%d", &n_vertices);
    scanf("%d", &n_edges);

    graph.resize(n_vertices);

    for(i=0;i<n_edges;i++)
    {
        scanf("%d %d %lf", &v1,&v2,&w);
        graph = add_edge(graph,v1,v2,w);
        graph = add_edge(graph,v2,v1,w);
    }

    scanf("%d",&v_start);
    
    show_graph(graph);
    Prim(graph,v_start);
    return 0;
}

