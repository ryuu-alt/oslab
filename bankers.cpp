
/*
 * DEMONSTRATION OF BANKER'S ALGORITHM
 *
 * SUBMISSION BY ADITYA KUMAR
 * 2K22/CO/26
 * 
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Process {
public:
    vector<int> allocation;
    vector<int> max_demand;
    vector<int> need;

    Process(int resource_count) : allocation(resource_count), max_demand(resource_count), need(resource_count) {}
};

void calculateNeed(vector<Process>& processes) {
    for (auto& process : processes) {
        for (size_t i = 0; i < process.need.size(); i++) {
            process.need[i] = process.max_demand[i] - process.allocation[i];
        }
    }
}

bool isSafe(const vector<Process>& processes, const vector<int>& available, vector<int>& safeSequence) {
    vector<bool> finished(processes.size(), false);
    vector<int> work = available;
    bool safe = false;

    while (true) {
        safe = false;
        for (size_t i = 0; i < processes.size(); i++) {
            if (!finished[i]) {
                bool possible = true;
                for (size_t j = 0; j < processes[i].need.size(); j++) {
                    if (processes[i].need[j] > work[j]) {
                        possible = false;
                        break;
                    }
                }
                if (possible) {
                    for (size_t k = 0; k < work.size(); k++) {
                        work[k] += processes[i].allocation[k];
                    }
                    finished[i] = true;
                    safeSequence.push_back(i);
                    safe = true;
                }
            }
        }
        if (!safe) {
            break;
        }
    }

    for (bool f : finished) {
        if (!f) return false;
    }
    return true;
}

int main() {
    int num_processes, num_resources;
    cout << "Enter number of processes: ";
    cin >> num_processes;
    cout << "Enter number of resources: ";
    cin >> num_resources;

    vector<Process> processes(num_processes, Process(num_resources));
    vector<int> available(num_resources);

    cout << "Enter available resources: ";
    for (int& a : available) {
        cin >> a;
    }

    for (int i = 0; i < num_processes; i++) {
        cout << "Enter allocation and max demand for Process " << i << ":\n";
        cout << "Allocation: ";
        for (int& alloc : processes[i].allocation) {
            cin >> alloc;
        }
        cout << "Max Demand: ";
        for (int& max : processes[i].max_demand) {
            cin >> max;
        }
    }

    calculateNeed(processes);

    vector<int> safeSequence;
    if (isSafe(processes, available, safeSequence)) {
        cout << "The system is in a safe state.\n";
        cout << "Safe sequence is: ";
        for (int id : safeSequence) {
            cout << "P" << id << " ";
        }
        cout << endl;
    } else {
        cout << "No safe sequence found. The system is not in a safe state.\n";
    }

    return 0;
}
