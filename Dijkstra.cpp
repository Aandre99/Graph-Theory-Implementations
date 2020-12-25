#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <queue>

using namespace std;

//definitions -> pair<vertex,distance>

typedef pair<int,double> vertex;
typedef vector<vertex> Adj;
typedef vector<Adj> Graph;

//customized comparer to order priority queue by sencond element (distance)
//  use -> priority_queue<vertex,vector<vertex>,myComp>

struct myComp { 
	constexpr bool operator()( 
		vertex const& a, 
		vertex const& b) 
		const noexcept 
	{ 
		return a.second > b.second; 
	} 
};

//useful funcition
Graph add_edge(Graph G, int v1,int v2, double weight){
    
    G[v1].push_back(make_pair(v1,weight));
    return G;
}
void show_graph(Graph G){

    int i, j;
    for (i = 0; i < G.size(); i++){
        printf("[%d] -> ", i);
        for (j = 0; j < G[i].size() ; j++){
            printf("(%d,%.2lf) -> ", G[i][j].first, G[i][j].second);
        }
        printf("\n");
    }
}

//dijkstra algorithm function
void Dijkstra(Graph G, int source, int destiny){ 
}

int main(){

    int i,v1,v2;
    int n_vertices,n_edges;
    double w;
    Graph graph;

    scanf("%d", &n_vertices);
    scanf("%d", &n_edges);

    graph.resize(n_vertices);

    for(i=0;i<graph.size();i++){

        scanf("%d", &v1); 
        scanf("%d", &v2);
        scanf("%lf", &w);

        graph = add_edge(graph,v1-1,v2-1,w);
    }

    show_graph(graph);
  
    return 0;
}