
/*
 * PAGE MANAGEMENT BY OPTIMAL PAGE REPLACEMENT (DEMONSTRATION)
 *
 * SUBMISSION BY ADITYA KUMAR
 * 2K22/CO/26
 * 
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

struct Page {
	int id;
	Page(int id) : id(id) {}
};

int find_farthest_page_index(const vector<Page>& future_requests, const unordered_set<int>& pages_in_memory, int start_index) {
	unordered_map<int, int> last_occurrence;
	for (int i = start_index; i < future_requests.size(); i++) {
		int page_id = future_requests[i].id;
		if (pages_in_memory.find(page_id) != pages_in_memory.end()) {
			last_occurrence[page_id] = i;
		}
	}

	int max_index = -1, chosen_page_id = -1;
	for (int page_id : pages_in_memory) {
		if (last_occurrence.find(page_id) == last_occurrence.end()) {
			return page_id;
		}
		if (last_occurrence[page_id] > max_index) {
			max_index = last_occurrence[page_id];
			chosen_page_id = page_id;
		}
	}

	return chosen_page_id;
}

void optimal_page_replacement(const vector<Page>& page_requests, int capacity) {
	unordered_set<int> pages_in_memory;
	int page_faults = 0;

	for (int i = 0; i < page_requests.size(); i++) {
		int current_page_id = page_requests[i].id;

		if (pages_in_memory.find(current_page_id) == pages_in_memory.end()) {
			if (pages_in_memory.size() == capacity) {
				int to_remove = find_farthest_page_index(page_requests, pages_in_memory, i + 1);
				pages_in_memory.erase(to_remove);
				cout << "Removed page " << to_remove << " from memory.\n";
			}

			pages_in_memory.insert(current_page_id);
			cout << "Added page " << current_page_id << " to memory.\n";
			page_faults++;
		}

		cout << "Accessed page " << current_page_id << ".\n";
	}

	cout << "Total page faults: " << page_faults << endl;
}

int main() {
	vector<Page> page_requests = {Page(1), Page(2), Page(3), Page(4), Page(1), Page(2), Page(5), Page(1), Page(2), Page(3), Page(4), Page(5)};
	int capacity = 3;
	optimal_page_replacement(page_requests, capacity);
	return 0;
}
