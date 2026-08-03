// ============================================================================
// Process.h
// Header defining the Process structure
// This represents a single process in the OS
// ============================================================================

#ifndef PROCESS_H
#define PROCESS_H

#include <string>
using namespace std;

// ============================================================================
// PROCESS STRUCT- This represents a single process in the operating system
// Each process has an PID, name, burst time (aka how long it needs to run),
// arrival time, remaining time left to execute, and priority level
// ============================================================================
struct Process {
    int processId;           // Unique identifier for the process
    string processName;      // Humanish name
    int burstTime;          // Total time needed to complete
    int arrivalTime;        // When the process was created
    int remainingTime;      // Time left to finish execution
    int priority;           // Priority level (1-5, where 5 is highest)
    int waitingTime;        // How long process has waited
    int turnaroundTime;     // Total time from arrival to completion
    int startTime;          // When process first started executing
    bool hasStarted;        // Has this process started executing yet?
    
    // Constructor
    // Parameters: id - process's PID number
    //            name - name of the process
    //            burst - how long it needs to run
    //            arrival - when it was created
    //            prio - priority level (default 3 for medium priority range 1-5 with 1 lowest, 5 highest)
    Process(int id, string name, int burst, int arrival, int prio = 3) {
        processId = id;
        processName = name;
        burstTime = burst;
        arrivalTime = arrival;
        remainingTime = burst;  // Initially, remaining time = total burst time
        priority = prio;        // Set priority (1=lowest, 5=highest)
        waitingTime = 0;
        turnaroundTime = 0;
        startTime = -1;
        hasStarted = false;
    }
};

#endif // PROCESS_H