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

typedef pair<double,int> vertex;
typedef vector<vertex> Adj;

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

        double execute_prim(int v_start){

            int visited[this->size];
            double cost[this->size];
            int i,v;

            for (v=0;v < this->size;v++)
            {
                visited[v] = 0;
                *(previous + v) = -1; 
                cost[v] = INT16_MAX;
            }

            cost[v_start] = 0;
            *(previous + v_start) = v_start;

            priority_queue<vertex,Adj,greater<vertex>> Q;

            Q.push(make_pair(cost[v_start],v_start));

            while (!Q.empty())
            {
                vertex u = Q.top();
                Q.pop();
                visited[u.second] = 1;

                for(vertex v:this->Adj_list[u.second])
                {
                    if (!visited[v.second])
                    {
                        if(cost[v.second] > v.first)
                        {
                            cost[v.second] = v.first;
                            *(previous + v.second) = u.second;
                            Q.push(make_pair(cost[v.second],v.second));
                        }
                    }
                }
            }
            double min_cost = 0.0;
            // compute cost of generator tree
            for (i=0;i<this->size;i++)
            {
                if(cost[i] != INT16_MAX){min_cost += cost[i];}
            }
            return min_cost;
        }
};

int main(){


    int n_vertices,n_edges;
    int i,v1,v2,v_start;

    double w,min_cost = 0.0;
    Graph graph;

    scanf("%d", &n_vertices);
    scanf("%d", &n_edges);

    graph.creat_graph(n_vertices);

    previous = (int*)calloc(n_vertices,sizeof(int));

    for(i=0;i<n_edges;i++)
    {
        scanf("%d %d %lf", &v1,&v2,&w);
        graph.add_edge(v1,v2,w);
        graph.add_edge(v2,v1,w);
    }

    scanf("%d",&v_start);
    min_cost = graph.execute_prim(v_start);
 
    printf("The generator tree is: \n");
    for (i=0;i<n_vertices;i++)
    {
        printf(" %d ", previous[i]);
    }
    printf("\nThe minimum cost of generator tree is: %.lf\n", min_cost);
    free(previous);
    
    printf("ola");
    return 0;
}

