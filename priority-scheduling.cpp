
/*
 * PRIORITY-BASED SCHEDULING (NON-PREEMPTIVE)
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
		remaining, priority;

public:
	Task() {
		cout << "Enter arrival time, burst time and priority: ";
		cin >> arrival >> burst >> priority;
		remaining = burst;
	}

	int at() 	{return arrival;}
	int bt() 	{return burst;}
	int pid() 	{return procid;}
	int ct() 	{return completion;}
	int tat() 	{return turnaround;}
	int wt() 	{return waiting;}
	int rem() 	{return remaining;}
	int pty() 	{return priority;}

	void setpid(int x) 		{procid = x;}
	void setcompl(int x) 	{completion = x;}
	void setrem(int x) 		{remaining = x;}
	void setpty(int x) 		{priority = x;}

	void calcnprint() {
		turnaround = completion - arrival;
		waiting = turnaround - burst;

		cout << "PID " << procid << ":\n"
			<< " - Priority:        " << priority << "\n"
			<< " - Waiting time:    " << waiting << "\n"
			<< " - Turnaround time: " << turnaround << "\n" << endl;
	}
};

class Compare {
public:
	bool operator() (Task* a, Task* b) {
		if (a->pty() == b->pty()) {
			if (a->at() == b->at())
				return a->pid() < b->pid();
			else return a->at() < b->at();
		}
		else return a->pty() > b->pty();
	}
};

int main() {
	cout << "Please note tasks with lower \'priority\' value have higher priority." << endl;

	cout << "Enter number of tasks: ";
	int n; cin >> n;

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

	int sortedptr = 0;
	priority_queue<Task*, vector<Task*>, Compare> q;

	int tick = 0;
	while (sortedptr != n || q.size()) {
		if (sorted[sortedptr].at() == tick) q.push(&(sorted[sortedptr++]));

		if (q.size() == 0) {
			cout << "Tick " << tick++ << "\t: IDLE\n";
			continue;
		}

		Task* current = q.top();
		if (current->at() > tick) {
			cout << "Tick " << tick++ << "\t: IDLE\n";
			continue;
		}

		while (current->rem() > 0) {
			current->setrem(current->rem()-1);
			cout << "Tick " << tick++ << "\t: EXEC PID " << current->pid() << endl;
		}

		q.pop();
		current->setcompl(tick);
		while (sortedptr < n && sorted[sortedptr].at() <= tick) q.push(&(sorted[sortedptr++]));
	}

	cout << "\n\n--------------------\nProcess-wise Report:\n\n";

	sort (sorted.begin(), sorted.end(), [](Task& a, Task& b) {
		return a.pid() < b.pid();
	});

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