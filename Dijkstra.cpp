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

//custom comparator for order priority queue by sencond element (distance)
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
    
    G[v1].push_back(make_pair(v2,weight));
    return G;
}
void show_graph(Graph G){

    int i, j;
    for (i = 0; i < G.size(); i++){
        printf("[%d] -> ", i+1);
        for(vertex v:G[i]){
            printf("(%d,%.2lf) -> ", v.first+1, v.second );
        }
        printf("\n");
    }
}

//dijkstra algorithm function
void Dijkstra(Graph G, int s, int d)
{   
    double distance[G.size()];
    int previous[G.size()], visited[G.size()];
    int v,i;

    for (v=0;v<G.size();v++)
    {
        distance[v] = INT16_MAX / 2;
        previous[v] = -1;
        visited[v] = 0;
    }

    distance[s] = 0;

    priority_queue<vertex,vector<vertex>,myComp> Q;
    Q.push(make_pair(s,0));

    while(!Q.empty())
    {
        vertex u = Q.top();
        Q.pop();
        visited[u.first] = 1;

        for(vertex w: G[u.first])
        {
            if(visited[w.first] == 0)
            {
                if (distance[w.first] > distance[u.first] + w.second)
                {
                    distance[w.first] = distance[u.first] + w.second;
                    previous[w.first] = u.first;
                    Q.push(make_pair(w.first,distance[w.first]));
                }
            }
        } 
    }
    
    printf("Caminho com distancia minima entre %d e %d: \n", s,d);
    
    for (v=d;v != -1;v = previous[v])
    {
        printf("[%d] ->",v);
    }

}

int main(){

    int i,v1,v2;
    int begin, end;
    int n_vertices,n_edges;
    double w;
    Graph graph;

    scanf("%d", &n_vertices);
    scanf("%d", &n_edges);

    graph.resize(n_vertices);

    for(i=0;i<n_edges;i++){

        scanf("%d", &v1); 
        scanf("%d", &v2);
        scanf("%lf", &w);

        graph = add_edge(graph,v1,v2,w);
    }

    scanf("%d", &begin);
    scanf("%d", &end);
    
    Dijkstra(graph,begin,end);

    show_graph(graph);
    return 0;
}
