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
#include <climits>

using namespace std;

typedef pair<int,double> vertex;
typedef vector<vertex> Adj;


class Graph
{
private:
    vector<Adj> Adj_list;
    int size;
public:       
    void creat_graph(int n_vertices);
    void add_edge(int v1, int v2, double w);
    void show_path(int v, int previous[]);
    void show_all_paths(int v0, int previous[], double distance[]);
    void execute_Bellman_Ford(int v0);
};


int main()
{
    int n_vertices, n_edges;
    int v0, v1, v2;
    double w;
    Graph graph;

    cin >> n_vertices >> n_edges;
    graph.creat_graph(n_vertices);

    for(int i = 0; i < n_edges; i++)
    {
        cin >> v1 >> v2 >> w;
        graph.add_edge(v1, v2, w);
    }
    
    cin >> v0;
    graph.execute_Bellman_Ford(v0);

    return 0;
}


void Graph::creat_graph(int n_vertices)
{
    this->Adj_list.resize(n_vertices);
    this->size = n_vertices;
}

void Graph::add_edge(int v1, int v2, double w)
{
    this->Adj_list[v1].push_back(make_pair(v2, w));
}

void Graph::show_path(int v, int previous[])
{
    if (v == -1){
        return;
    }
    show_path(previous[v], previous);
    cout << " -> " << v;
}

void Graph::show_all_paths(int v0, int previous[], double distance[])
{    
    for(int i = 0; i < this->size; i++)
    {
        cout << "Caminho minimo entre " << v0 << " e " << i;
        if (distance[i] == 2147483647.00)
        {
            cout << " com custo INF\n";
        }
        else
        {
            cout << " com custo " << distance[i] << endl;
        }
        if(i == v0)
        {
            show_path(i, previous);
        }
        else
        {
            show_path(i, previous);
        }
        cout << endl;
    }
}

void Graph::execute_Bellman_Ford(int v0)
{
    double dist[this->size];
    int path[this->size];
    bool negative_cycle = false;

    for(int i = 0; i < this->size; i++)
    {
        dist[i] = INT_MAX;
        path[i] = -1;
    }

    dist[v0] = 0;
    path[v0] = -1;

    for(int i = 0; i < this->size - 1; i++)
    {
        for(int j = 0; j < this->size; j++)
        {
            for(int k = 0; k < this->Adj_list[j].size(); k++)
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

    for(int j = 0; j < this->size; j++)
        {
            for(int k = 0; k < this->Adj_list[j].size(); k++)
            {
                vertex v = this->Adj_list[j][k];
                if(dist[v.first] > dist[j] + v.second)
                {
                    negative_cycle = true;
                    printf("Negative Cycle found!");
                    break;
                }
            }
        }
    if (!negative_cycle){
        show_all_paths(v0, path,dist);
    }
}

