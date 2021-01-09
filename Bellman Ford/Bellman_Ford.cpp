/*
    Para o algoritmo de Bellman-Ford, temos:

    Entrada:

        1 - n_vertices e n_edges representando o número de vértices e arestas do grafo
        2 - n_edges linhas seguintes com 3 valores:
            
            v1 v2 w , onde v1 e v2 representam os vértices e w o peso contido na aresta
            que liga estes dois vértices;

        3 - v0 representando o vértice inicial de onde o algoritmo partirá para encontrar
            todos os caminhos mínimos entre v0 e os n_vertices - 1 vértices restantes,
            caso exista caminho entre v0 e outro vértice dado;

    Saída:

        A saída do algoritmo segue como abaixo:

            [1] Minimum Path v0 to vx:
            [2] caminho entre v0 e vx, onde vx ⊂ V e vx ≠ v0 (com o formato v0 -> vx -> vy -> ....)

        Obs:
            Quando não existe caminho entre v0 e um vx dado a saída será:
            v0 -> 
*/

#include <iostream>
#include <vector> 
#include <utility>
#include <climits>
#include <math.h>

using namespace std;

typedef pair<int,double> vertex;
typedef vector<vertex> Adj;

class Graph{

    private:
        vector<Adj> Adj_list;
        int size;
    public:
        
        void creat_graph(int n_vertices)
        {
            this->Adj_list.resize(n_vertices);
            this->size = n_vertices;
        }

        void add_edge(int v1,int v2,double w){
            this->Adj_list[v1].push_back(make_pair(v2,w));
        }

        void show_graph(){
            int i,j;

            for(i=0;i<this->size;i++)
            {
                printf("[%d] ->", i);
                for(j=0;j < this->Adj_list[i].size();j++)
                {
                    printf("(%d,%.2lf)->", this->Adj_list[i][j].first, this->Adj_list[i][j].second);
                }
                printf("\n");
            }
        }

        void show_path(int v,int previous [])
        {
            if (v == -1){
                return;
            }else{
                show_path(previous[v],previous);
                printf(" %d ->", v);
            }
        }
        void show_all_paths(int v0,int previous[],double distance[]){
            
            int i, n = this->size;

            for (i = 0; i< n; i++)
            {
               printf("Caminho Minimo entre %d e %d,", v0,i);
               
               if (distance[i] == 2147483647.00){printf("com custo INF\n");}
               else{printf("com custo %.2lf\n",distance[i]);}
               
               if(i == v0){
                   printf(" %d -> ",v0);
               }else{
                show_path(i,previous);
               }
               printf("\n");
            }
        }

        void execute_Bellman_Ford(int v0){

            double dist[this->size];
            int path[this->size];

            int i,j,k, n = this->size;
            
            for(i=0;i<this->size;i++)
            {
                dist[i] = INT_MAX;
                path[i] = -1;
            }

            dist[v0] = 0;
            path[v0] = -1;

            for(i=0;i < n - 1;i++)
            {
                for(j=0;j < n ;j++)
                {
                    for(k=0;k < this->Adj_list[j].size();k++)
                    {
                        vertex v = this->Adj_list[j][k];

                        if(dist[v.first] > dist[j] + v.second)
                        {
                            dist[v.first] = dist[j] + v.second;
                            path[v.first] = j;
                        }
                    }
                }
            }   

            this->show_all_paths(v0,path,dist);
        }
};

int main()
{
    int n_vertices, n_edges;
    int i, v0,v1,v2;
    double w;

    
    scanf("%d", &n_vertices);
    scanf("%d", &n_edges);

    Graph graph;
    graph.creat_graph(n_vertices);

    for(i=0;i<n_edges;i++)
    {
        scanf("%d %d %lf", &v1,&v2,&w);
        graph.add_edge(v1,v2,w);
    }

    scanf("%d",&v0);

    graph.execute_Bellman_Ford(v0);

    return 0;
}
