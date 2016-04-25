/* Jason Stumbaugh
 * CSE 7343 Operating Systems
 * PCB.cpp
 */

#import <iostream>
#import <string>
#import <ctime>
#import <vector>

using namespace std;

class PCB {
  public:
    PCB();
    PCB(int, int, string, string, int, int);
    PCB(int, int, int, int);
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
    int get_how_long_needed();
    void set_how_long_needed(int);
    int get_duration();
    int get_memory_size();
    string get_created_at();
  private:
    int pid;
    int priority;
    int job_time;
    string state;
    string program_counter;
    int arrival_time;
    int how_long_needed;
    int memory_size;
    int duration;
    time_t created_at;
    struct tm * timeinfo;
};

// Empty constructor
PCB::PCB() {}

// Phase 2 constructor
PCB::PCB(int id, int arr_time, int dur, int mem_size) {
    pid = id;
    arrival_time = arr_time;
    duration = dur;
    memory_size = mem_size;
    created_at = time(0);
}

// Normal constructor
PCB::PCB(int id, int p, string st, string pc, int j=0, int hln=0) {
    pid = id;
    priority = p;
    state = st;
    program_counter = pc;
    j == 0 ? job_time = rand() % 20 + 1 : job_time = j;
    created_at = time(0);
    hln == 0 ? how_long_needed = job_time : how_long_needed = hln;
}

// this method will print the contents of the PCB
void PCB::print() {
  // PHASE 1
    // cout << "  PID:           " << pid << endl;
    // cout << "  Priority:      " << priority << endl;
    // cout << "  State:         " << state << endl;
    // cout << "  PC:            " << program_counter << endl;
    // cout << "  Job Time:      " << job_time << endl;
    // cout << "  Arrival Time:  " << arrival_time << endl;
    // cout << "  Length Needed: " << how_long_needed << endl;
  // PHASE 2
    cout << "  PID:           " << pid << endl;
    cout << "  Arrival Time:  " << arrival_time << endl;
    cout << "  Duration:      " << duration << endl;
    cout << "  Memory Size:   " << memory_size << endl;
    cout << "  Created At:    " << get_created_at();
}

int PCB::get_duration() {
    return duration;
}

int PCB::get_memory_size() {
    return memory_size;
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
    j < 0 ? job_time = 0 : job_time = j;
}

string PCB::get_created_at() {
    timeinfo = localtime(&created_at);
    return asctime(timeinfo);
}

int PCB::get_how_long_needed() {
    return how_long_needed;
}

void PCB::set_how_long_needed(int hln) {
    how_long_needed = hln;
}
