## CSE 7343 Operating Systems Project
##### Jason Stumbaugh
##### Spring 2016

To download source code: `git clone https://github.com/jstumbaugh/OS_project.git`


To compile operating system:
```
cd OS_project/
make
```


To run operating system: `./os.exe`


To delete the executable: `make clean`


### Basic information

This is a project for my Operating Systems class. It is currently in Phase 1.

The UI is basic, revolving around the command line. Upon starting the OS, the user is prompted with the following options:

```
===========================================================
|           CSE 7343: Operating Systems Project           |
|                     Jason Stumbaugh                     |
===========================================================

Please select an option:
   1  -  Manually Enter Processes.
   2  -  Read Processes in from text file.
   0  -  Exit Operating System.
>
```

After selecting an option, the user is then prompted for the associated input. Once processes are created either manually or from a text file, the user can interact with the queues that are created. The following options are presented to the user:

```
Please select an option:
   1  -  Print contents of Ready Queue.
   2  -  Print contents of Waiting Queue.
   3  -  Run the Shortest Job First Scheduler on the Ready queue.
   4  -  Run the Priority Scheduler on the Ready queue.
   5  -  Run the Round Robin Scheduler on the Ready queue.
   6  -  Run all of the schedulers on the Ready queue.
   7  -  Add PCB to a given queue.
   8  -  Delete PCB from given queue.
   0  -  Exit Operating System.
>
```

Each option is self explanatory and has the same basic interface.

#### Process Control Blocks
Process Control Blocks are represented as follows:
```
PID              - process identifier
Priority         - priority of the process (1, 2, 3, or 4)
State            - current state of the process (ready or waiting)
Program Counter  - address of the program counter register
Job Time         - time it takes to complete the process
```

#### Scheduler Information
Three schedulers are implemented in this operating system: Shortest Job First, Priority, and Round-Robin. They are all implemented in their own methods in `scheduler.cpp` The Shortest Job First scheduler takes the ready queue, orders the PCBs from shortest job time to longest, processes each PCB in that order, and returns the average wait time of each process. The Priority scheduler takes the ready queue, orders the PCBs from highest priority (1) to lowest (4), processes each PCB in that order, and returns the average wait time of each process. The Round Robin scheduler takes the ready queue and a time quantum Q. The scheduler goes down the ready queue allowing each process a time period Q to perform its computations. Each time, the PCB's job time is decremented the length of the time quantum Q. Once a PCB's job time reaches 0, it is removed from the ready queue. Once the scheduler is completed, it returns the average wait time of each process.

### Phase 1 Information
##### PCB File Expected Format
Upon selecting the mode where you read in the process information from a text file, the OS is set up to receive a specific format. It is as follows:
```
# ID, Priority, State, ProgramCounter, Job Time
1, 1, ready, 0x1234, 20
2, 4, waiting, 0x4321, 10
```
Lines beginning with a pound sign `#` will be ignored as comments. Each attribute of the PCB can be separated by either a comma or a space. Each line is expected to be a different PCB. See the `test.txt` file as an example.

### Phase 2 Information
##### Input File Expected Format
```
Size_of_memory
Number_of_available spaces
starting_address_1, available_space_1
starting_address_2,  available_space_2
…….
starting_address_N, available_space_N
number_of_processes
pid, arrival_time, duration, size_of_memory
pid, arrival_time, duration, size_of_memory
…………
…………
pid, arrival_time, duration, size_of_memory


EX.
input.txt
4000
 6 /* number available spaces */
200, 300
600, 600
1400, 350
2000, 200
2500, 750
3500, 125
5 /* number of processes */
1, 0, 10, 115
2, 0, 10, 500
3, 0, 10, 358
4, 0, 10, 200
5, 0, 10, 375

```


#### Dependencies
g++

C++11
