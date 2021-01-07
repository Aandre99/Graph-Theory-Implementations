#include <iostream>
#include <vector>
#include <utility>
#include <limits>
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

        void show_all_paths(int v0,int path[]){
            
            int i,j, n = this->size;

            for (i = n-1 ; i >= 0; i--)
            {
                printf("Minimum Path %d to %d vertex", i,v0);
                printf("\n%d ->", i);
                j = i;

                while(1)
                {
                    if(path[j] != -1)
                    {
                        j = path[j];
                        printf(" %d ->", j);
                    }else{
                        break;
                    }
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
                dist[i] = INT16_MAX;
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

            this->show_all_paths(v0,path);
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

    //graph.show_graph();
    graph.execute_Bellman_Ford(v0);

    return 0;
}