#include <iostream>
#include <vector>
#include <string>

class Process {
public:
    std::vector<int> allocation;
    std::vector<int> max_demand;
    std::vector<int> need;

    Process(int resource_count) : allocation(resource_count), max_demand(resource_count), need(resource_count) {}
};

void calculateNeed(std::vector<Process>& processes) {
    for (auto& process : processes) {
        for (size_t i = 0; i < process.need.size(); i++) {
            process.need[i] = process.max_demand[i] - process.allocation[i];
        }
    }
}

bool isSafe(const std::vector<Process>& processes, const std::vector<int>& available, std::vector<int>& safeSequence) {
    std::vector<bool> finished(processes.size(), false);
    std::vector<int> work = available;
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
    std::cout << "Enter number of processes: ";
    std::cin >> num_processes;
    std::cout << "Enter number of resources: ";
    std::cin >> num_resources;

    std::vector<Process> processes(num_processes, Process(num_resources));
    std::vector<int> available(num_resources);

    std::cout << "Enter available resources: ";
    for (int& a : available) {
        std::cin >> a;
    }

    for (int i = 0; i < num_processes; i++) {
        std::cout << "Enter allocation and max demand for Process " << i << ":\n";
        std::cout << "Allocation: ";
        for (int& alloc : processes[i].allocation) {
            std::cin >> alloc;
        }
        std::cout << "Max Demand: ";
        for (int& max : processes[i].max_demand) {
            std::cin >> max;
        }
    }

    calculateNeed(processes);

    std::vector<int> safeSequence;
    if (isSafe(processes, available, safeSequence)) {
        std::cout << "The system is in a safe state.\n";
        std::cout << "Safe sequence is: ";
        for (int id : safeSequence) {
            std::cout << "P" << id << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No safe sequence found. The system is not in a safe state.\n";
    }

    return 0;
}
