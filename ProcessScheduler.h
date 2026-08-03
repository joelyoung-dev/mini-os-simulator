// ============================================================================
// ProcessScheduler.h
// Header file for the Process Scheduler class
// Handles scheduling processes using RR, FIFO, Priority scheduling
// ============================================================================

#ifndef PROCESS_SCHEDULER_H
#define PROCESS_SCHEDULER_H

#include <queue>
#include <vector>
#include "Process.h"

using namespace std;

// ============================================================================
// SCHEDULING METRICS STRUCTURE
// Stores performance metrics calculated after scheduling
// ============================================================================
struct SchedulingMetrics {
    float avgWaitingTime;      // Average time processes spend waiting
    float avgTurnaroundTime;   // Average time from arrival to completion
    float cpuUtilization;      // Percentage of time CPU was busy
    int contextSwitches;       // Number of times we switched processes
    float throughput;          // Processes completed per time unit
    int totalProcesses;        // Total number of processes scheduled
};

// ============================================================================
// PROCESS SCHEDULER CLASS
// This class handles scheduling processes using different algorithms
// It can use Round Robin (each process gets a time quantum), 
// FIFO (Processes run to completion in order),
// or Priority scheduling (higher priority processes run first)
// ============================================================================
class ProcessScheduler {
private:
    queue<Process> readyQueue;     // Queue of processes ready to run
    vector<Process> completedProcs; // List of finished processes
    int timeQuantum;               // Time slice for Round Robin
    int currentTime;               // Current system time
    int contextSwitches;           // Counter for context switches
    
public:
    // Constructor: Initialize the scheduler with a time quantum
    // Parameters: quantum - the time slice for Round Robin scheduling
    ProcessScheduler(int quantum);
    
    // Add a new process to the ready queue
    // Parameters: proc - the Process object to add
    // Returns: nothing
    void addProcess(Process proc);
    
    // Execute processes using Round Robin scheduling
    // Each process runs for a time quantum, then moves to back of queue
    // Parameters: none
    // Returns: nothing
    void scheduleRoundRobin();
    
    // Execute processes using FIFO 
    // Each process runs until it's completely finished before the next one starts
    // Parameters: none
    // Returns: nothing
    void scheduleFIFO();
    
    // Execute processes using Priority scheduling
    // Higher priority processes, 5, run before lower priority of 1
    // Parameters: none
    // Returns: nothing
    void schedulePriority();
    
    // Display all completed processes
    // Parameters: none
    // Returns: nothing
    void showCompletedProcesses();
    
    // Calculate and return scheduling performance metrics
    // Parameters: none
    // Returns: SchedulingMetrics structure with calculated values
    SchedulingMetrics calculateMetrics();
    
    // Display performance metrics in a formatted way
    // Parameters: none
    // Returns: nothing
    void displayMetrics();
    
    // Visualize the scheduling timeline as a Gantt chart
    // Parameters: none
    // Returns: nothing
    void visualizeScheduling();

    void addCompletedProcess(const Process& p) {
    completedProcs.push_back(p);}

    void setCurrentTime(int t) {
    currentTime = t;
}
};

#endif // PROCESS_SCHEDULER_H