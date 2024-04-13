
/*
 * FIRST-COME-FIRST-SERVE SCHEDULING
 *
 * SUBMISSION BY ADITYA KUMAR
 * 2K22/CO/26
 * 
*/

#include <bits/stdc++.h>
using namespace std;

class Task {
	int arrival, burst, procid,
		completion, turnaround, waiting;

public:
	Task() {
		cout << "Enter arrival and burst time: ";
		cin >> arrival >> burst;
	}

	int at() {return arrival;}
	int bt() {return burst;}
	int pid() {return procid;}
	int ct() {return completion;}
	int tat() {return turnaround;}
	int wt() {return waiting;}

	void setpid(int x) {procid = x;}
	void setcompl(int x) {completion = x;}

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

	cout << "\n\n--------------------\nList of processes\n\n";
	for (auto x : sorted)
		cout << x.pid() << ": " << x.at() << ' ' << x.bt() << endl;

	sort (sorted.begin(), sorted.end(), [](Task& a, Task& b) {
		if (a.at() == b.at()) {
			return a.pid() < b.pid();
		}
		else return a.at() < b.at();
	});
	
	cout << "\n\n--------------------\nTickwise schedule:\n\n";

	queue <Task*> q;
	for (int i=0; i<n; i++) q.push(&sorted[i]);

	int tick = 0;
	while (q.size()) {
		Task* current = q.front(); q.pop();
		while (tick < current->at()) cout << "Tick " << tick++ << "\t: IDLE\n";

		for (int i=0; i < current->bt(); i++) {
			cout << "Tick " << tick++ << "\t: EXEC PID " << current->pid() << endl;
		}

		current->setcompl(tick);
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