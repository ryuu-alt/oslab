
/*
 * ROUND-ROBIN SCHEDULING
 *
 * SUBMISSION BY ADITYA KUMAR
 * 2K22/CO/26
 * 
*/

#include <bits/stdc++.h>
using namespace std;

class Task {
	int arrival, burst, procid,
		completion, turnaround, waiting,
		remaining;

public:
	Task() {
		cout << "Enter arrival and burst time: ";
		cin >> arrival >> burst;
		remaining = burst;
	}

	int at() {return arrival;}
	int bt() {return burst;}
	int pid() {return procid;}
	int ct() {return completion;}
	int tat() {return turnaround;}
	int wt() {return waiting;}
	int rem() {return remaining;}

	void setpid(int x) {procid = x;}
	void setcompl(int x) {completion = x;}
	void setrem(int x) {remaining = x;}

	void calcnprint() {
		turnaround = completion - arrival;
		waiting = turnaround - burst;

		cout << "PID " << procid << ":\n"
			<< " - Waiting time:    " << waiting << "\n"
			<< " - Turnaround time: " << turnaround << "\n" << endl;
	}
};

int main() {
	int n;
	cout << "Enter number of tasks: ";
	cin >> n;

	vector<Task> sorted (n);

	for (int i=0; i<n; i++) {
		Task& x = sorted[i];
		x.setpid(i);
	}

	int quant = 1;
	cout << "Enter time quantum: ";
	cin >> quant;
	quant = max(1, quant);

	cout << "\n\n--------------------\nList of processes\n\n";

	sort (sorted.begin(), sorted.end(), [](Task& a, Task& b) {
		if (a.at() == b.at()) {
			return a.pid() < b.pid();
		}
		else return a.at() < b.at();
	});
	
	for (auto x : sorted)
		cout << x.pid() << ": " << x.at() << ' ' << x.bt() << endl;
	
	cout << "\n\n--------------------\nTickwise schedule:\n\n";

	queue <Task*> q;
	q.push(&sorted[0]);

	// 1. pop process from queue
	// - process starts now?
	//   [y] run it
	//   [n] skip, don't full pop
	// 2. if process ran, reduce rem and push back if needed

	int tick = 0, sortedptr = 1;
	while (q.size()) {
		Task* current = q.front();
		if (current->at() > tick) {
			cout << "Tick " << tick++ << "\t: IDLE\n";
			continue;
		}

		q.pop();
		for (int i=0; i < quant && current->rem() > 0; i++) {
			while (sortedptr < n && sorted[sortedptr].at() == tick) q.push(&sorted[sortedptr++]);
			cout << "Tick " << tick++ << "\t: EXEC PID " << current->pid() << endl;
			while (sortedptr < n && sorted[sortedptr].at() == tick) q.push(&sorted[sortedptr++]);
			current->setrem(current->rem()-1);
		}

		if (current->rem() <= 0)
			current->setcompl(tick);
		else
			q.push(current);
	}

	cout << "\n\n--------------------\nProcess-wise Report:\n\n";

	double avgtat = 0, avgwt = 0;
	for (auto x : sorted) {
		x.calcnprint();
		avgtat += x.tat();
		avgwt += x.wt();
	}

	cout << "\n\n--------------------\nStatistics Report:\n\n";

	cout<< " - Processes executed:      " << n << endl
		<< " - Average turnaround time: " << avgtat/n << endl
		<< " - Average waiting time:    " << avgwt/n << endl;
	
	cout << "\n\n\n";
}