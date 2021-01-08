/*

	Algoritmo de Kruskal
	
	RECEBE um grafo não direcionado com peso nas arestas.
	ENCONTRA uma árvore geradora mínima (MST).

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

	Edge(int vertex1, int vertex2, int cost)
	{
		this->vertex1 = vertex1;
		this->vertex2 = vertex2;
		this->cost = cost;
	}

	int get_vertex1()
	{
		return this->vertex1;
	}

	int get_vertex2()
	{
		return this->vertex2;
	}

	int get_cost()
	{
		return this->cost;
	}

	bool operator < (const Edge &edge2)
	{
		return (cost < edge2.cost);
	}
};


class Graph
{
private:

	int qnt_vertex;
	int qnt_edges;
	vector<Edge> edges;

public:

	Graph(int qnt_vertex)
	{
		this->qnt_vertex = qnt_vertex;
		this->qnt_edges = 0;
	}

	void create_edge(int vertex1, int vertex2, int cost)
	{
		Edge edge(vertex1, vertex2, cost);
		edges.push_back(edge);
		this->qnt_edges++;
	}

	int search(int subset[], int i)
	{
		if(subset[i] == -1)
		{
			return i;
		}
		return search(subset, subset[i]);
	}

	void unite(int subset[], int vertex1, int vertex2)
	{
		int vertex1_set = search(subset, vertex1);
		int vertex2_set = search(subset, vertex2);
		subset[vertex1_set] = vertex2_set;
	}

	vector<Edge> kruskal()
	{
		vector<Edge> mst;
		int subset[this->qnt_vertex];

		sort(this->edges.begin(), this->edges.end());
		
		for(int i = 0; i < this->qnt_vertex; ++i)
		{
			subset[i] = -1;
		}
		for(int i = 0; i < edges.size(); i++)
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
};

int main()
{
	int qnt_vertex, qnt_edges, v1, v2, cost;
	cout << "Numero de vertices e arestas: ";
	cin >> qnt_vertex >> qnt_edges;
	Graph g(qnt_vertex);
	cout << "\nAdicione as arestas (vertice1 vertice2 peso):\n\n";
	for(int i = 0; i < qnt_edges;++i)
	{
		cin >> v1 >> v2 >> cost;
		g.create_edge(v1, v2, cost);
	}
	vector<Edge> mst = g.kruskal();
	cout << "\nImprimindo MST...\n\n";
	cout << "ARESTA \t PESO\n";
	int minimum_cost = 0;
	for(int i = 0; i < qnt_vertex-1; ++i)
	{
		cout << mst[i].get_vertex1() << " "
			<< mst[i].get_vertex2() << " "
			<< mst[i].get_cost() << endl;
		minimum_cost += mst[i]. get_cost();
	}

	cout << "\nCusto minimo: " << minimum_cost << endl;

	return 0;
}

