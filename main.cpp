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
#import "scheduler.cpp"

using namespace std;

// Prompt user for process information
PCB enter_process_info(string state="0") {
    int pid, priority, job_time;
    string program_counter;
    cout << "Process ID: ";
    cin >> pid;
    cout << "Priority: ";
    cin >> priority;
    if (state == "0") {
        cout << "State (ready, waiting, running, terminated): ";
        cin >> state;
    }
    cout << "Program Counter Address: ";
    cin >> program_counter;
    cout << "Job Time: ";
    cin >> job_time;
    PCB pcb(pid, priority, state, program_counter, job_time);
    return pcb;
}

// The main worked method of the operating system
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

        char entering_processes = 'y';
        while (entering_processes == 'y') {
            PCB pcb = enter_process_info();
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
                    int pid, priority, job_time;
                    string state, program_counter;
                    ss >> pid;
                    ss >> priority;
                    ss >> state;
                    ss >> program_counter;
                    if (ss >> job_time)
                        cout << "";
                    else
                        job_time = 0;
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
                }
            }
        } else {
            cerr << "Error opening " << file_name << endl;
            exit(1);
        }
    }

    // create queues based on processes
    Queue ready_queue("Ready", ready);
    Queue waiting_queue("Waiting", waiting);
    Queue running_queue("Running", running);
    Queue terminated_queue("terminated", terminated);

    bool using_os = true;
    while (using_os) {
        cout << "\nPlease select an option:\n";
        cout << "   1  - Print contents of Ready Queue.\n";
        cout << "   2  - Print contents of Waiting Queue.\n";
        // cout << "   3  - Print contents of Running Queue.\n";
        // cout << "   4  - Print contents of Terminated Queue.\n";
        cout << "   3  - Run the Shortest Job First Scheduler on the Ready queue.\n";
        cout << "   4  - Run the Priority Scheduler on the Ready queue.\n";
        cout << "   5  - Run the Round Robin Scheduler on the Ready queue.\n";
        cout << "   6  - Run all of the schedulers on the Ready queue.\n";
        cout << "   7  - Add PCB to a given queue.\n";
        cout << "   8  - Delete PCB from given queue.\n";
        cout << "   0  - Exit Operating System.\n";

        int input;
        cout << "> ";
        cin >> input;
        cout << endl;
        int q;
        string queue_selected;
        PCB pcb;
        switch(input) {
            case 1 :    ready_queue.print();
                        break;
            case 2 :    waiting_queue.print();
                        break;
            case 3 :    cout << "Shortest Job First Scheduler average wait time: " << sjf_scheduler(ready_queue,waiting_queue) << endl;
                        break;
            case 4 :    cout << "Priority Scheduler average wait time: " << priority_scheduler(ready_queue, waiting_queue) << endl;
                        break;
            case 5 :    cout << "Please enter the Time Quantum to use: ";
                        cin >> q;
                        cout << "\nRound Robin Scheduler average wait time: " << rr_scheduler(ready_queue, waiting_queue, q) << endl;
                        break;
            case 6 :    cout << "Please enter the Time Quantum to use: ";
                        cin >> q;
                        cout << "\nShortest Job First Scheduler average wait time:    " << sjf_scheduler(ready_queue,waiting_queue) << endl;
                        cout << "Priority Scheduler average wait time:              " << priority_scheduler(ready_queue, waiting_queue) << endl;
                        cout << "Round Robin Scheduler average wait time:           " << rr_scheduler(ready_queue, waiting_queue, q) << endl;
                        break;
            case 7 :    cout << "Add PCB to which queue? (ready, waiting): ";
                        cin >> queue_selected;
                        if (queue_selected == "ready") {
                            pcb = enter_process_info("ready");
                            cout << "Please enter the position you would like to add the PCB in the ready queue: ";
                            cin >> q;
                            ready_queue.push(pcb,q);
                            cout << "PCB added to the Ready queue.\n";
                            break;
                        } else if (queue_selected == "waiting") {
                            pcb = enter_process_info("waiting");
                            cout << "Please enter the position you would like to add the PCB in the waiting queue: ";
                            cin >> q;
                            waiting_queue.push(pcb,q);
                            cout << "PCB added to the Waiting queue.\n";
                            break;
                        } else {
                            cout << "Invalid queue name\n";
                            break;
                        }
                        break;
            case 8 :    cout << "Delete PCB from which queue? (ready, waiting): ";
                        cin >> queue_selected;
                        if (queue_selected == "ready") {
                            ready_queue.print();
                            cout << "\nPlease enter the PID of the process you wish to delete: ";
                            cin >> q;
                            ready_queue.delete_PCB(q);
                            cout << "PCB " << q << " deleted.\n";
                            break;
                        } else if (queue_selected == "waiting") {
                            waiting_queue.print();
                            cout << "\nPlease enter the PID of the process you wish to delete: ";
                            cin >> q;
                            waiting_queue.delete_PCB(q);
                            cout << "PCB " << q << " deleted.\n";
                            break;
                        } else {
                            cout << "Invaild queue name.\n";
                            break;
                        }
                        break;
            case 0 :    using_os = false;
                        break;
            default :   cout << "Please enter in a valid command.\n\n";
                        break;
        }
    }

    return 0;
}
