/* Jason Stumbaugh
 * CSE 7343 Operating Systems
 * PCB.cpp
 */

#import <iostream>
#import <string>

using namespace std;

class PCB {
  public:
    PCB();
    PCB(int, int, string, string, int);
    void print();
    // getters and setters
    int get_pid ();
    void set_pid (int);
    int get_priority ();
    void set_priority (int);
    string get_state ();
    void set_state (string);
    string get_PC ();
    void set_PC (string);
    int get_job_time();
    void set_job_time(int);
  private:
    int pid;
    int priority;
    int job_time;
    string state;
    string program_counter;
};

// Empty constructor
PCB::PCB() {}

// Normal constructor
PCB::PCB(int id, int p, string st, string pc, int j=0) {
    pid = id;
    priority = p;
    state = st;
    program_counter = pc;
    j == 0 ? job_time = rand() % 20 + 1 : job_time = j;
    cout << "Process " << id << " Created\n";
}

// this method will print the contents of the PCB
void PCB::print() {
    cout << "  PID:       " << pid << endl;
    cout << "  Priority:  " << priority << endl;
    cout << "  State:     " << state << endl;
    cout << "  PC:        " << program_counter << endl;
    cout << "  Job Time:  " << job_time << endl;
}

// Basic getters and setters for the attributes
int PCB::get_pid() {
    return pid;
}

void PCB::set_pid(int id) {
    pid = id;
}

int PCB::get_priority() {
    return priority;
}

void PCB::set_priority(int p) {
    priority = p;
}

string PCB::get_state() {
    return state;
}

void PCB::set_state(string s) {
    state = s;
}

string PCB::get_PC() {
    return program_counter;
}

void PCB::set_PC(string pc) {
    program_counter = pc;
}

int PCB::get_job_time() {
    return job_time;
}

void PCB::set_job_time(int j) {
    job_time = j;
}
