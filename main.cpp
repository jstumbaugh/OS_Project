/* Jason Stumbaugh
 * CSE 7343 Operating Systems
 * main.cpp
 */

#import <iostream>
#import <vector>
#import "PCB.cpp"
#import "queue.cpp"

using namespace std;

int main() {
    vector<PCB> vec;
    PCB pcb(63,1,"ready", "PC");
    vec.push_back(pcb);
    PCB pcb1(22,1,"ready", "PC");
    vec.push_back(pcb1);
    PCB pcb2(32,1,"ready", "PC");
    vec.push_back(pcb2);

    Queue ready_queue("Ready", vec);
    ready_queue.print();

    // PCB p = ready_queue.pop();
    // p.print();

    ready_queue.print();

    return 0;
}
