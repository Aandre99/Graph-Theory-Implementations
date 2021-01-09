#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int* previous;
double* cost;

typedef pair<double, int> vertex;
typedef vector<vertex> Adj;

class Graph
{
private:
    int size;
    vector<Adj> Adj_list;
public:
    Graph(int n_v);
    ~Graph();
    void add_edge(int v1, int v2, double weight);
    void show_graph();
    void execute_prim(int v_start);
};


int main()
{
    int n_vertices, n_edges, v1, v2, v_start;
    double w, min_cost = 0;

    cin >> n_vertices >> n_edges;
    Graph graph(n_vertices);

    previous = (int*)calloc(n_vertices, sizeof(int));
    cost = (double*)calloc(n_vertices, sizeof(double));

    for(int i = 0; i < n_edges; i++)
    {
        cin >> v1 >> v2 >> w;
        graph.add_edge(v1, v2, w);
    }

    cin >> v_start;
    graph.execute_prim(v_start);
    cout << "\nThe generator tree is:\n\n";

    for(int i = 0; i < n_vertices; i++)
    {
        printf("%d\t%d\t\t%.2lf\n", i , previous[i], cost[i]);
        min_cost += cost[i];
    }

    printf("\nThe minimum cost of generator tree is: %.lf\n\n", min_cost);
    free(previous);
    free(cost);
    
    return 0;
}


Graph::Graph(int n_v)
{
    this->Adj_list.resize(n_v);
    this->size = n_v;
}

Graph::~Graph()
{
}

void Graph::add_edge(int v1,int v2, double weight)
{
    this->Adj_list[v1].push_back(make_pair(weight,v2));
    this->Adj_list[v2].push_back(make_pair(weight,v1));
}

void Graph::show_graph()
{
    for(int i = 0; i < this->size; i++)
    {
        printf("[%d]", i);
        for(vertex v: this->Adj_list[i])
        {
            printf(" -> (%d, %.2lf)", v.second, v.first);
        }
        printf("\n\n");
    }
}

void Graph::execute_prim(int v_start)
{
    int visited[this->size];

    for (int v = 0; v < this->size; v++)
    {
        visited[v] = 0;
        previous[v] = -1; 
        cost[v] = INT_MAX;
    }
    cost[v_start] = 0;
    previous[v_start] = v_start;
    priority_queue<vertex, Adj, greater<vertex>> Q;

    Q.push(make_pair(cost[v_start], v_start));

    while (!Q.empty())
    {
        vertex u = Q.top();
        Q.pop();
        visited[u.second] = 1;

        for(vertex v: this->Adj_list[u.second])
        {
            if (!visited[v.second])
            {
                if(cost[v.second] > v.first)
                {
                    cost[v.second] = v.first;
                    previous[v.second] = u.second;
                    Q.push(make_pair(cost[v.second], v.second));
                }
            }
        }
    }
}


