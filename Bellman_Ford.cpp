#include <iostream>
#include <limits>

using namespace std;
int n_vertices = 0;

class Graph{

    private:
        double** matrix = NULL;
        int size;
    public:
        
        void creat_graph(int n_vertices)
        {
            int i;

            this->matrix = new double*[n_vertices];
            for (i=0;i<n_vertices;i++)
            {
                this->matrix[i] = new double[n_vertices];
            }
            this->size = n_vertices;
        }

        void add_edge(int v1,int v2,double w){
            this->matrix[v1][v2] = w;
        }

        void show_graph(){
            int i,j;

            for(i=0;i<this->size;i++)
            {
                for(j=0;j < this->size;j++)
                {
                    printf("%.2lf ", this->matrix[i][j]);
                }
                printf("\n");
            }
        }

        void free_graph(){
            free(this->matrix);
        }

        void execute_Bellman_Ford(){
            
        }
};
int main()
{
    int n_vertices, n_edges;
    int i, v1,v2;
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

    graph.show_graph();
    graph.free_graph();


    return 0;
}