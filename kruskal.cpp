
/*
 * KRUSKAL'S ALGORITHM USING DSU
 *
 * SUBMISSION BY ADITYA KUMAR
 * 2K22/CO/26
 * 
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Edge {
	int src, dest, weight;
};

struct Graph {
	int V, E;
	vector<Edge> edges;
	
	Graph(int V, int E) : V(V), E(E) {}

	void addEdge(int src, int dest, int weight) {
		edges.push_back({src, dest, weight});
	}
};

struct DSU {
	vector<int> parent, rank;
	
	DSU(int n) : parent(n), rank(n, 0) {
		for (int i = 0; i < n; i++) {
			parent[i] = i;
		}
	}
	
	int find(int i) {
		if (parent[i] != i)
			parent[i] = find(parent[i]);
		return parent[i];
	}
	
	void union_set(int x, int y) {
		int rootX = find(x);
		int rootY = find(y);
		
		if (rootX != rootY) {
			if (rank[rootX] > rank[rootY])
				parent[rootY] = rootX;
			else if (rank[rootX] < rank[rootY])
				parent[rootX] = rootY;
			else {
				parent[rootY] = rootX;
				rank[rootX]++;
			}
		}
	}
};

bool compareEdges(Edge a, Edge b) {
	return a.weight < b.weight;
}

vector<Edge> kruskalMST(Graph& graph) {
	vector<Edge> result;
	sort(graph.edges.begin(), graph.edges.end(), compareEdges);
	
	DSU dsu(graph.V);
	
	for (Edge e : graph.edges) {
		if (dsu.find(e.src) != dsu.find(e.dest)) {
			result.push_back(e);
			dsu.union_set(e.src, e.dest);
		}
	}
	return result;
}

int main() {
	int v, e;
	
	cout << "Number of vertices: "; cin >> v;
	cout << "Number of edges: "; cin >> e;

	Graph g(v, e);

	for (int i=0; i<e; i++) {
		int vf, vs, vl;
		cout << "Enter first vertex, second vertex and edge length: ";
		cin >> vf >> vs >> vl;
		g.addEdge(vf, vs, vl);
	}

	vector<Edge> mst = kruskalMST(g);
	cout << "Edges in MST:" << endl;
	for (Edge e : mst) {
		cout << e.src << " <---" << e.weight << "---> " << e.dest << endl;
	}

	return 0;
}
