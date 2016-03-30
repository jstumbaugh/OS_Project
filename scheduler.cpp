/* Jason Stumbaugh
 * CSE 7343 Operating Systems
 * scheduler.cpp
 */

#import <utility>
#import "PCB.cpp"
#import "queue.cpp"
using namespace std;

// Shortest Job First
double sjf_scheduler(Queue ready, Queue waiting, bool display=false) {
    double wait_time = 0;
    double len = ready.length();
    while (ready.length() > 0) {
        PCB shortest = ready[0];
        // find shortest wait time
        for (int i=0; i<ready.length(); i++) {
            if (ready[i].get_job_time() < shortest.get_job_time())
                shortest = ready[i];
        }
        if (display) {
            cout << "Processing PCB\n";
            shortest.print();
        }
        if (ready.length() > 1) // the last process's job_time doesn't matter for wait time
            wait_time += shortest.get_job_time();
        // remove the shortest job
        ready.delete_PCB(shortest.get_pid());
    }
    return wait_time / len;
}

// Non-preemptive Priority
// use 1,2,3,4 for priorities, assume 1 is highest priority
// Non-preemptive: switches from running to waiting state; terminates.
double priority_scheduler(Queue ready, Queue waiting, bool display=false) {
    int wait_time = 0;
    double len = ready.length();
    while (ready.length() > 0) {
        PCB highest = ready[0];
        // find the highest priority PCB
        for (int i=0; i<ready.length(); i++) {
            if (ready[i].get_priority() < highest.get_priority())
                highest = ready[i];
        }
        if (display) {
            cout << "Procesing PCB\n";
            highest.print();
        }
        if (ready.length() > 1) // the last process's job_time doesn't matter for wait time
            wait_time += highest.get_job_time();
        // remove the highest priority job
        ready.delete_PCB(highest.get_pid());
    }
    return wait_time / len;
}

// Round-Robin with a give n Q parameter
double rr_scheduler(Queue ready, Queue waiting, int q, bool display=false) {
    int wait_time = 0;
    double len = 0;
    while (ready.length() > 0) {
        for (int i=0; i<ready.length(); i++) {
            if (display) {
                cout << "Processing PCB\n";
                ready[i].print();
            }
            if (ready[i].get_job_time() <= q)
                wait_time += ready[i].get_job_time();
            else
                wait_time += q;
            len += 1;
            // update the job time
            ready[i].set_job_time(ready[i].get_job_time() - q);
            // remove finished jobs from ready queue
            if (ready[i].get_job_time() == 0)
                ready.delete_PCB(ready[i].get_pid());
        }
    }
    return wait_time / len;
}


// Compare these scheduling algorithms in terms of average waiting time on a
// given sample of processes.
