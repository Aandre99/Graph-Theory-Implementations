/*
	
	Implementação do algoritmo de Kruskal

	Entrada:
		Um grafo não direcionado e com peso nas arestas.

		Formato da entrada:
		Dois inteiros n, m, representando a quantidade de vértices e arestas do grafo, respectivamente.
		Em seguida m linhas contendo três inteiros v1, v2, c, representando a aresta v1v2 com peso c.


	Saída:
		Gera uma árvore geradora mínima (MST) do grafo recebido.

		Formato da saída:
		n-1 linhas contendo cada aresta da MST:
		v1 			v2 			Peso
		Em seguida o custo mínimo da árvore geradora.

*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Edge
{
private:
	int vertex1;
	int vertex2;
	int cost;
public:
	Edge(int vertex1, int vertex2, int cost);
	~Edge();
	int get_vertex1();
	int get_vertex2();
	int get_cost();
	bool operator < (const Edge &edge2);
};

class Graph
{
private:
	int qnt_vertex;
	int qnt_edges;
	vector<Edge> edges;
public:
	Graph(int qnt_vertex);
	~Graph();
	void create_edge(int vertex1, int vertex2, int cost);
	int search(int subset[], int i);
	void unite(int subset[], int vertex1, int vertex2);
	vector<Edge> kruskal();
};


int main()
{
	int qnt_vertex, qnt_edges, v1, v2, cost;
	cin >> qnt_vertex >> qnt_edges;
	Graph g(qnt_vertex);
	for(int i = 0; i < qnt_edges;++i)
	{
		cin >> v1 >> v2 >> cost;
		g.create_edge(v1, v2, cost);
	}
	vector<Edge> mst = g.kruskal();
	sort(mst.begin(), mst.end());

	int minimum_cost = 0;

	for(int i = 0; i < mst.size(); ++i)
	{
		printf("%d\t%d\t\t%d\n", mst[i].get_vertex1(), mst[i].get_vertex2(), 
				mst[i].get_cost());
		minimum_cost += mst[i].get_cost();
	}
	cout << endl << minimum_cost << endl << endl;

	return 0;
}


Edge::Edge(int vertex1, int vertex2, int cost)
{
	this->vertex1 = vertex1;
	this->vertex2 = vertex2;
	this->cost = cost;
}

Edge::~Edge()
{
}

int Edge::get_vertex1()
{
	return this->vertex1;
}

int Edge::get_vertex2()
{
	return this->vertex2;
}

int Edge::get_cost()
{
	return this->cost;
}

bool Edge::operator < (const Edge &edge2)
{
	return (vertex1 < edge2.vertex1);
}

Graph::Graph(int qnt_vertex)
{
	this->qnt_vertex = qnt_vertex;
	this->qnt_edges = 0;
}

Graph::~Graph()
{
}

void Graph::create_edge(int vertex1, int vertex2, int cost)
{
	Edge edge(vertex1, vertex2, cost);
	edges.push_back(edge);
	this->qnt_edges++;
}

int Graph::search(int subset[], int i)
{
	if(subset[i] == -1)
	{
		return i;
	}
	return search(subset, subset[i]);
}

void Graph::unite(int subset[], int vertex1, int vertex2)
{
	int vertex1_set = search(subset, vertex1);
	int vertex2_set = search(subset, vertex2);
	subset[vertex1_set] = vertex2_set;
}

void sort_edge(vector<Edge> &v)
{
	int size = v.size();
	for(int i = 0; i < size; ++i)
	{
		for(int j = size-1; j > i; --j)
		{
			if(v[i].get_cost() > v[j].get_cost())
			{
				swap(v[i], v[j]);
			}
		}
	}
}

vector<Edge> Graph::kruskal()
{
	vector<Edge> mst;
	int subset[this->qnt_vertex];

	for(int i = 0; i < this->qnt_vertex; ++i)
	{
		subset[i] = -1;
	}
	
	sort_edge(this->edges);

	for(int i = 0; i < this->qnt_edges; i++)
	{
		int vertex1 = search(subset, edges[i].get_vertex1());
		int vertex2 = search(subset, edges[i].get_vertex2());
		if(vertex1 != vertex2)
		{
			mst.push_back(edges[i]);
			unite(subset, vertex1, vertex2);
		}
	}
	return mst;
}

