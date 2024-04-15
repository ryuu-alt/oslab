
/*
 * PAGE MANAGEMENT BY FIRST IN FIRST OUT
 *
 * SUBMISSION BY ADITYA KUMAR
 * 2K22/CO/26
 * 
*/

#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

struct Page {
	int id;
	Page(int id) : id(id) {}
};

void fifo_cache(list<Page>& pages, unordered_map<int, list<Page>::iterator>& page_map, int capacity, const Page& page) {
	int page_id = page.id;

	if (page_map.find(page_id) == page_map.end()) {
		if (pages.size() == capacity) {
			Page oldest = pages.front();
			pages.pop_front();
			page_map.erase(oldest.id);
			cout << "Removed page " << oldest.id << " from memory.\n";
		}
	} else cout << "Page " << page.id << " already in memory.\n";

	if (page_map.find(page_id) == page_map.end()) {
		pages.push_back(page);
		page_map[page_id] = --pages.end();
		cout << "Added page " << page_id << " to memory.\n";
	}
}

void display_cache(const list<Page>& pages) {
	cout << "Memory contents: ";
	for (const auto& page : pages)
		cout << "Page " << page.id << ", ";
	cout << "\b\b  " << endl;
}

int main() {
	list<Page> pages;
	unordered_map<int, list<Page>::iterator> page_map;
	int capacity = 4;

	Page pg1(1), pg2(2), pg3(3), pg4(4), pg5(5);

	fifo_cache(pages, page_map, capacity, pg1);
	fifo_cache(pages, page_map, capacity, pg2);
	fifo_cache(pages, page_map, capacity, pg3);
	fifo_cache(pages, page_map, capacity, pg4);
	display_cache(pages);

	fifo_cache(pages, page_map, capacity, pg5);
	display_cache(pages);

	fifo_cache(pages, page_map, capacity, pg2);
	display_cache(pages);

	return 0;
}
