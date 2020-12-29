#include <iostream>
#include <vector>
#include <utility>

using namespace std;

typedef pair<int,double> vertex;
typedef vector<vertex> Adj;

class Graph{
    private:
        vector<Adj> Adj_matrix;
        int size;
    public:
        
        void creat_graph(int n_vertices){
            this->Adj_matrix.resize(n_vertices);
            this->size = n_vertices;
        }
        void add_edge(int v1,int v2,double w){
            this->Adj_matrix[v1].push_back(make_pair(v2,w));
        }
        void show_graph(){

            int i;

            for(i = 0; i < this->size ; i++)
            {
                printf("[%d]-> ", i);
                for( vertex v:this->Adj_matrix[i])
                {
                    printf("(%d , %.2lf)-> ", v.first,v.second);
                }
                printf("\n");
            }
        }
        void Bellman_Ford();
};

void Graph::Bellman_Ford(){
    cout << "ola";
}

int main()
{
    Graph graph;

    graph.creat_graph(5);

    graph.add_edge(0,1,10);
    graph.add_edge(1,4,70);
    graph.add_edge(3,2,13);
    graph.add_edge(3,4,130);
    graph.add_edge(2,0,150);
    graph.add_edge(4,1,1);

    graph.show_graph(); 

    graph.Bellman_Ford();
    return 0;
}