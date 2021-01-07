#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <queue>
#include <limits>

using namespace std;

//definitions -> pair<vertex,distance>

typedef pair<double,int> vertex;
typedef vector<vertex> Adj;

//custom comparator for order priority queue by sencond element (distance)
//  use -> priority_queue<vertex,vector<vertex>,myComp>
class Graph{
    private:
    
    vector<Adj> Adj_list;
    int size = 0;

    public:
        void creat_graph(int n_v){
            this->Adj_list.resize(n_v);
            this->size = n_v;
        }

        void add_edge(int v1,int v2, double weight){
            this->Adj_list[v1].push_back(make_pair(weight,v2));
        }

        void show_graph()
        {
            int i, j;
            for (i = 0; i < this->size; i++)
            {
                printf("[%d] -> ", i+1);
                for(vertex v:this->Adj_list[i]){
                    printf("(%d,%.2lf) -> ", v.second, v.first);
                }
                printf("\n");
            }
        }
        
        void show_path(int v, int prev[])
        {   
            if (v == -1){
                return;
            }else{

                show_path(prev[v],prev);
                printf("[%d]->",v);
            }
        }

        void execute_dijkstra(int s, int d)
        {   
            double distance[this->size];
            int previous[this->size], visited[this->size];
            int v,i;

            for (v=0;v<this->size;v++)
            {
                distance[v] = INT16_MAX / 2;
                previous[v] = -1;
                visited[v] = 0;
            }

            distance[s] = 0;

            priority_queue<vertex,vector<vertex>,greater<vertex>> Q;
            Q.push(make_pair(0,s));

            while(!Q.empty())
            {
                vertex u = Q.top();
                Q.pop();
                visited[u.second] = 1;

                for(vertex w: this->Adj_list[u.second])
                {
                    if(visited[w.second] == 0)
                    {
                        if (distance[w.second] > distance[u.second] + w.first)
                        {
                            distance[w.second] = distance[u.second] + w.first;
                            previous[w.second] = u.second;
                            Q.push(make_pair(distance[w.second],w.second));
                        }
                    }
                } 
            }
            printf("Caminho com distancia minima entre %d e %d: \n", s,d);
            this->show_path(d,previous);
        }
};

int main(){

    int i,v1,v2;
    int begin, end;
    int n_vertices,n_edges;
    double w;
    Graph graph;

    scanf("%d", &n_vertices);
    scanf("%d", &n_edges);

    graph.creat_graph(n_vertices);

    for(i=0;i<n_edges;i++){

        scanf("%d", &v1); 
        scanf("%d", &v2);
        scanf("%lf", &w);

        graph.add_edge(v1,v2,w);
    }

    scanf("%d", &begin);
    scanf("%d", &end);
    
    graph.execute_dijkstra(begin,end);  

    //show_graph(graph);
    return 0;
}
