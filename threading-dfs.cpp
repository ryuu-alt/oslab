#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <vector>
#include <atomic>
using namespace std;

#define SZ	10

atomic<bool> found(false);

vector<int> v (SZ);
vector<pair<int, int>> c (SZ, {-1, -1});

int dfs (int node, int srch);

int dfs (int node, int srch) {

	if (found) return -1;
	
	//cout << "dfs at node " << node << ", (value " << v[node] << ") looking for " << srch << endl;
	
	if (v[node] == srch) {
		//cout << "Found node!\n";
		found = true;
		return node;
	}
	
	if (c[node].first == -1) return -1;
	
	future<int> t1 = async(dfs, c[node].first, srch);
	future<int> t2 = async(dfs, c[node].second, srch);
	
	int ret1 = t1.get(),
		ret2 = t2.get();
		
	if (ret1 != -1) return ret1;
	else if (ret2 != -1) return ret2;
	else return -1;
	
}


int main() {
	
	for (int i=0; i<SZ; i++) v[i] = i+1;
	
	for (int i=0; i<SZ/2; i++) {
		c[i] = {2*i+1, 2*i+2};
		cout << i << " has children " << c[i].first << " and " << c[i].second << endl;
	}
	
	cout << "Searching for all values with threaded-DFS...\n";
	
	for (int i=0; i<SZ; i++) {
		found = false;
		cout << "Value " << i+1 << " at node " << dfs (0, i+1) << endl;
	}

	return 0;
}