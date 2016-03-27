/* Jason Stumbaugh
 * CSE 7343 Operating Systems
 * main.cpp
 */

#import <iostream>
#import <vector>
#import <fstream>
#import <sstream>
#import "PCB.cpp"
#import "queue.cpp"

using namespace std;

int main() {
    cout << "CSE 7343: Operating Systems Project\nJason Stumbaugh\n";
    int mode = 0;
    while (mode != 1 && mode != 2) {
        cout << "\nManually Enter Processes:          1\nRead Processes in from text file:  2\nPlease pick a mode: ";
        cin >> mode;
    }
    vector<PCB> ready;
    vector<PCB> waiting;
    vector<PCB> running;
    vector<PCB> terminated;

    if (mode == 1) { // Manually Enter Processes
        cout << "\nManual Mode selected. Please enter in the processes:\n";
        int pid, priority, job_time;
        string state, program_counter;
        char entering_processes = 'y';
        while (entering_processes == 'y') {
            state = "";
            // read in information about Process
            cout << "Process ID: ";
            cin >> pid;
            cout << "Priority: ";
            cin >> priority;
            while (state != "ready" && state != "waiting" && state != "running" && state != "terminated") {
                cout << "State (ready, waiting, running, terminated): ";
                cin >> state;
            }
            cout << "Program Counter: ";
            cin >> program_counter;
            cout << "Job Time: ";
            cin >> job_time;
            PCB pcb(pid, priority, state, program_counter, job_time);

            // move PCB into correct queue
            if (pcb.get_state() == "ready") {
                ready.push_back(pcb);
            } else if (pcb.get_state() == "waiting") {
                waiting.push_back(pcb);
            } else if (pcb.get_state() == "running") {
                running.push_back(pcb);
            } else if (pcb.get_state() == "terminated") {
                terminated.push_back(pcb);
            }
            // prompt user for another process to input
            cout << "\nEnter another process? (y/n): ";
            cin >> entering_processes;
        }
    } else if (mode == 2) { // Read processes from text file
        cout << "Please enter the name of .txt file to read processes from: ";
        // string file_name;
        // cin >> file_name;
        string file_name = "test.txt";
        cout << endl;

        fstream file;
        file.open(file_name);
        if (file.is_open()){
            string line;
            while (getline(file, line)) {
                if (line.at(0) == '/') { // ignore comments
                    continue;
                } else {
                    stringstream ss(line);
                    int pid, priority;
                    string state, program_counter;
                    ss >> pid;
                    ss >> priority;
                    ss >> state;
                    ss >> program_counter;
                    PCB pcb(pid, priority, state, program_counter);
                    // move PCB into correct queue
                    if (pcb.get_state() == "ready") {
                        ready.push_back(pcb);
                    } else if (pcb.get_state() == "waiting") {
                        waiting.push_back(pcb);
                    } else if (pcb.get_state() == "running") {
                        running.push_back(pcb);
                    } else if (pcb.get_state() == "terminated") {
                        terminated.push_back(pcb);
                    }
                }
            }
        }
    }

    // create queues based on processes
    Queue ready_queue("Ready", ready);
    Queue waiting_queue("Waiting", waiting);
    Queue running_queue("Running", running);
    Queue terminated_queue("terminated", terminated);
    // Print contents of queues
    ready_queue.print();
    waiting_queue.print();
    // running_queue.print();
    // terminated_queue.print();



    return 0;
}
