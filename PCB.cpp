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
    PCB(int, int, string, string);
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
  private:
    int pid;
    int priority;
    string state;
    string program_counter;
};

// Empty constructor
PCB::PCB() {}

// Normal constructor
PCB::PCB(int id, int p, string st, string pc) {
    pid = id;
    priority = p;
    state = st;
    program_counter = pc;
    cout << "Process " << id << " Created\n";
}

// this method will print the contents of the PCB
void PCB::print() {
    cout << "  PID:       " << pid << endl;
    cout << "  Priority:  " << priority << endl;
    cout << "  State:     " << state << endl;
    cout << "  PC:        " << program_counter << endl << endl;
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
