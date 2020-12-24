#include <iostream>
#include <vector>
#include <utility>

using namespace std;

typedef pair<int,double> vertex;
typedef vector<vertex> Adj;
typedef vector<Adj> Graph;


void add_edge(Graph* G, int v1,int v2, double weight);
void show_graph(Graph* G);


int main(){

    int i,v1,v2;
    int n_vertices,n_edges;
    double w;

    cin >> n_vertices;
    cin >> n_edges;

    Graph graph(n_vertices);

    for(i=0;i<graph.size();i++){

        scanf("%d", &v1); 
        scanf("%d", &v2);
        scanf("%lf", &w);
    }

    return 0;
}