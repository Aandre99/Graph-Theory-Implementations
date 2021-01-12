/*  
Para o algoritmo de Dijkstra, temos:
    Entrada:
        1 - n_vertices e n_edges representando o número de vértices e arestas do grafo
        2 - n_edges linhas seguintes com 3 valores:
            
            v1 v2 w , onde v1 e v2 representam os vértices e w o peso contido na aresta
            que liga estes dois vértices;
        3 - begin e end, vértice inicial e final para os quais deseja-se obter o caminho
            mínimo entre os dois;
    Saída:
        A saída do algoritmo segue como abaixo:
            1 - custo do caminho mínimo
            2 - caminho minimo
*/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef pair<double,int> vertex;
typedef vector<vertex> Adj;


class Graph
{
private:
    vector<Adj> Adj_list;
    int size;
public:
    void creat_graph(int n_v);
    void add_edge(int v1, int v2, double weight);
    void show_path(int v, int prev[]);
    void execute_dijkstra(int s, int d);
};


int main()
{
    int v1, v2, begin, end, n_vertices, n_edges;
    double w;
    Graph graph;

    cin >> n_vertices >> n_edges;
    graph.creat_graph(n_vertices);

    for(int i = 0; i < n_edges; i++)
    {
        cin >> v1 >> v2 >> w;
        graph.add_edge(v1, v2, w);
    }

    cin >> begin >> end;
    graph.execute_dijkstra(begin,end);  

    return 0;
}

void Graph::creat_graph(int n_v)
{
    this->Adj_list.resize(n_v);
    this->size = n_v;
}

void Graph::add_edge(int v1, int v2, double weight)
{
    this->Adj_list[v1].push_back(make_pair(weight, v2));
}

void Graph::show_path(int v, int prev[])
{   
    if (v == -1)
    {
        return;
    }
    show_path(prev[v], prev);
    cout << " -> " << v;
}

void Graph::execute_dijkstra(int s, int d)
{   
    double distance[this->size];
    int previous[this->size], visited[this->size];

    for (int v = 0; v < this->size; v++)
    {
        distance[v] = INT16_MAX / 2;
        previous[v] = -1;
        visited[v] = 0;
    }

    distance[s] = 0;
    priority_queue<vertex, vector<vertex>, greater<vertex>> Q;
    Q.push(make_pair(0, s));

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
    cout << "\nDistancia minima: " << distance[d];
    cout << "\n\nCaminho minimo entre " << s << " e " << d << ": " << endl;
    show_path(d, previous);
    cout << endl << endl;
}
