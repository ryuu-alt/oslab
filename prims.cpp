
/*
 * PRIM'S ALGORITHM
 *
 * SUBMISSION BY ADITYA KUMAR
 * 2K22/CO/26
 * 
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>
using namespace std;

typedef pair<int, int> pii; // First element: weight, Second element: vertex

struct Graph {
	int V;
	vector<vector<pii>> adj;

	Graph(int V) : V(V), adj(V) {}

	void addEdge(int src, int dest, int weight) {
		adj[src].push_back({weight, dest});
		adj[dest].push_back({weight, src});
	}
};

vector<pii> primsMST(Graph& graph) {
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	int src = 0;
	vector<int> key(graph.V, INT_MAX);
	vector<bool> inMST(graph.V, false);
	vector<int> parent(graph.V, -1);

	pq.push({0, src});
	key[src] = 0;

	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();

		if (inMST[u]) continue;

		inMST[u] = true;
		for (auto& i : graph.adj[u]) {
			int v = i.second;
			int weight = i.first;

			if (!inMST[v] && key[v] > weight) {
				key[v] = weight;
				pq.push({key[v], v});
				parent[v] = u;
			}
		}
	}

	vector<pii> mst;
	for (int i = 1; i < graph.V; i++) {
		mst.push_back({parent[i], i});
	}
	return mst;
}

int main() {
	int v, e;
	cout << "Number of vertices: "; cin >> v;
	cout << "Number of edges: "; cin >> e;

	Graph g(v);

	for (int i = 0; i < e; i++) {
		int vf, vs, vl;
		cout << "Enter first vertex, second vertex and edge length: ";
		cin >> vf >> vs >> vl;
		g.addEdge(vf, vs, vl);
	}

	vector<pii> mst = primsMST(g);
	cout << "Edges in MST:" << endl;
	for (auto e : mst) cout << e.first << " -- " << e.second << endl;

	return 0;
}
