/* Jason Stumbaugh
 * CSE 7343 Operating Systems
 * MemoryManagement.cpp
 */

#import <iostream>
#import <string>
#import <ctime>
#import <vector>
#import "PCB.cpp"
#import "queue.cpp"

using namespace std;

class MemoryManagement {
  public:
    MemoryManagement();
    MemoryManagement(int, vector<int>, vector<int>, int, vector<PCB>);
    void FirstFit();
    void BestFit();
    void WorstFit();
  private:
    int memory_size;
    vector<int> starting_address;
    vector<int> available_space;
    int number_processes;
    vector<PCB> processes;
};

MemoryManagement::MemoryManagement() {}

MemoryManagement::MemoryManagement(int size, vector<int> addr, vector<int> spaces, int num_pro, vector<PCB> pcbs) {
    memory_size = size;
    starting_address = addr;
    available_space = spaces;
    number_processes = num_pro;
    processes = pcbs;
}

void MemoryManagement::FirstFit() {
    // Allocate the first hole that is big enough
    cout << "\nAlgorithm:              First Fit\n";
    cout << "Assigned Processes:     ";
    vector<int> blocked_processes;
    bool blocked;
    double assigned_memory = 0;
    double processes_assigned = 0;
    for (int i=0; i<number_processes; i++) {
        int mem_size = processes[i].get_memory_size();
        blocked = true;
        for (int j=0; j<starting_address.size(); j++) {
            if (available_space[j] > mem_size) {
                cout << processes[i].get_pid() << ", " << starting_address[j] << ", " << mem_size << ";  ";
                starting_address[j] = starting_address[j] + mem_size;
                available_space[j] = available_space[j] - mem_size;
                blocked = false;
                assigned_memory += mem_size;
                processes_assigned += 1;
                break;
            }
        }
        if (blocked)
            blocked_processes.push_back(processes[i].get_pid());
    }
    cout << "\nBlocked Processes:      ";
    for (int i=0; i<blocked_processes.size(); i++) {
        cout << blocked_processes[i] << ", ";
    }
    if (blocked_processes.size() == 0)
        cout << "None";
        
    cout << "\nMemory Utilization:     " << assigned_memory << "/" << memory_size << " = " << assigned_memory / memory_size * 100 << "\%" << endl;
    cout << "Blocking Probability:   1 - (" << processes_assigned << "/" << number_processes << ") = " << (1 - processes_assigned / number_processes) * 100 << "\%" << endl;
}

void MemoryManagement::BestFit() {
    // allocate the smallest hole that is big enough, must search entire list each time, produces smallest leftover hole
    cout << "Algorithm:              Best Fit\n";
    cout << "Assigned Processes:     ";
    vector<int> blocked_processes;
    bool blocked;
    double assigned_memory = 0;
    double processes_assigned = 0;
    for (int i=0; i<number_processes; i++) {
        int mem_size = processes[i].get_memory_size();
        blocked = true;
        int diff = 1000;
        int temp;
        for (int j=0; j<starting_address.size(); j++) {
            if (available_space[j] >= mem_size && (available_space[j] - mem_size) < diff) {
                diff = available_space[j] - mem_size;
                temp = j;
                blocked = false;
            }
        }
        if (!blocked) {
            cout << processes[i].get_pid() << ", " << starting_address[temp] << ", " << mem_size << ";  ";
            starting_address[temp] += mem_size;
            available_space[temp] -= mem_size;
            assigned_memory += mem_size;
            processes_assigned += 1;
        }
        else
            blocked_processes.push_back(processes[i].get_pid());
    }
    cout << "\nBlocked Processes:      ";
    for (int i=0; i<blocked_processes.size(); i++) {
        cout << blocked_processes[i] << ", ";
    }
    if (blocked_processes.size() == 0)
        cout << "None";
    cout << "\nMemory Utilization:     " << assigned_memory << "/" << memory_size << " = " << assigned_memory / memory_size * 100 << "\%" << endl;
    cout << "Blocking Probability:   1 - (" << processes_assigned << "/" << number_processes << ") = " << (1 - processes_assigned / number_processes) * 100 << "\%" << endl;
}

void MemoryManagement::WorstFit() {
    // allocate the largest hole, must search entire list
    cout << "Algorithm:              Worst Fit\n";
    cout << "Assigned Processes:     ";
    vector<int> blocked_processes;
    bool blocked;
    double assigned_memory = 0;
    double processes_assigned = 0;
    for (int i=0; i<number_processes; i++) {
        int mem_size = processes[i].get_memory_size();
        blocked = true;
        int diff = 0;
        int temp;
        for (int j=0; j<starting_address.size(); j++) {
            if (available_space[j] > mem_size && (available_space[j] - mem_size) > diff) {
                diff = available_space[j] - mem_size;
                temp = j;
                blocked = false;
            }
        }
        if (!blocked) {
            cout << processes[i].get_pid() << ", " << starting_address[temp] << ", " << mem_size << ";  ";
            starting_address[temp] += mem_size;
            available_space[temp] -= mem_size;
            assigned_memory += mem_size;
            processes_assigned += 1;
        }
        else
            blocked_processes.push_back(processes[i].get_pid());
    }
    cout << "\nBlocked Processes:      ";
    for (int i=0; i<blocked_processes.size(); i++) {
        cout << blocked_processes[i] << ", ";
    }
    if (blocked_processes.size() == 0)
        cout << "None";
        cout << "\nMemory Utilization:     " << assigned_memory << "/" << memory_size << " = " << assigned_memory / memory_size * 100 << "\%" << endl;
        cout << "Blocking Probability:   1 - (" << processes_assigned << "/" << number_processes << ") = " << (1 - processes_assigned / number_processes) * 100 << "\%" << endl;
}
