// ============================================================================
// ProcessScheduler.cpp
// Implementation file for the Process Scheduler class
// Contains the code for scheduling algorithms
// ============================================================================

#include "ProcessScheduler.h"
#include <iostream>

using namespace std;

// Constructor: Initialize the scheduler with a time quantum
// Parameters: quantum or the time slice for Round Robin scheduling
// Returns: nothing 
ProcessScheduler::ProcessScheduler(int quantum) {
    timeQuantum = quantum;
    currentTime = 0;
    contextSwitches = 0;  // Initialize context switch counter
}

// Add a new process to the ready queue
// Parameters: proc - the Process object to add
// Returns: nothing
void ProcessScheduler::addProcess(Process proc) {
    readyQueue.push(proc);
    cout << "[SCHEDULER] Added process '" << proc.processName 
         << "' (ID: " << proc.processId << ") to ready queue" << endl;
}

// Execute processes using Round Robin scheduling
// Each process runs for a time quantum then moves to back of queue
// Parameters: none
// Returns: nothing
void ProcessScheduler::scheduleRoundRobin() {
    cout << "\n=== Starting Round Robin Scheduling ===" << endl;
    cout << "Time Quantum: " << timeQuantum << " time units\n" << endl;
    
    contextSwitches = 0;  // Reset context switch counter
    
    // Keep running while there are processes in the queue
    while (!readyQueue.empty()) {
        // Get the process at the front of the queue
        Process currentProc = readyQueue.front();
        readyQueue.pop();
        
        // Check if this is the first time this process is running
        if (currentProc.hasStarted == false) {
            currentProc.startTime = currentTime;
            currentProc.hasStarted = true;
            currentProc.waitingTime = currentTime - currentProc.arrivalTime;
        }
        
        cout << "[TIME " << currentTime << "] Running process: " 
             << currentProc.processName << " (ID: " << currentProc.processId 
             << ", Priority: " << currentProc.priority << ")" << endl;
        
        // Figure out how long this process will run
        // It's either the time quantum or whatever time is left 
        int executionTime;
        if (currentProc.remainingTime > timeQuantum) {
            executionTime = timeQuantum;
        } else {
            executionTime = currentProc.remainingTime;
        }
        
        // Simulate the process running
        cout << "  -> Executing for " << executionTime << " time units" << endl;
        currentProc.remainingTime = currentProc.remainingTime - executionTime;
        currentTime = currentTime + executionTime;
        
        // Check if process is finished
        if (currentProc.remainingTime == 0) {
            cout << "  -> Process COMPLETED!" << endl;
            currentProc.turnaroundTime = currentTime - currentProc.arrivalTime;
            completedProcs.push_back(currentProc);
        } else {
            // Process isn't done so push to back of queue
            cout << "  -> " << currentProc.remainingTime 
                 << " time units remaining, moving to back of queue" << endl;
            readyQueue.push(currentProc);
            contextSwitches = contextSwitches + 1;  // Count the context switch
        }
        cout << endl;
    }
    
    cout << "=== All processes completed ===" << endl;
    cout << "Total time : " << currentTime << " time units" << endl;
    cout << "Context switches: " << contextSwitches << endl << endl;
}

// Execute processes using FIFO scheduling
// Each process runs until it's completely finished before the next one starts
// Parameters: none
// Returns: nothing
void ProcessScheduler::scheduleFIFO() {
    cout << "\n=== Starting FIFO Scheduling ===" << endl;
    
    contextSwitches = 0;  // Reset context switch counter
    
    // Process each item in the queue one at a time
    while (!readyQueue.empty()) {
        Process currentProc = readyQueue.front();
        readyQueue.pop();
        
        // Mark when this process starts
        currentProc.startTime = currentTime;
        currentProc.hasStarted = true;
        currentProc.waitingTime = currentTime - currentProc.arrivalTime;
        
        cout << "[TIME " << currentTime << "] Running process: " 
             << currentProc.processName << " (ID: " << currentProc.processId 
             << ", Priority: " << currentProc.priority << ")" << endl;
        cout << "  -> Burst time: " << currentProc.burstTime << " time units" << endl;
        
        currentTime = currentTime + currentProc.burstTime;
        currentProc.remainingTime = 0;
        currentProc.turnaroundTime = currentTime - currentProc.arrivalTime;
        
        cout << "  -> Process COMPLETED at time " << currentTime << endl;
        completedProcs.push_back(currentProc);
        cout << endl;
    }
    
    cout << "=== All processes completed ===" << endl;
    cout << "Total time elapsed: " << currentTime << " time units" << endl;
    cout << "Context switches: " << contextSwitches << endl << endl;
}

// Display all completed processes
// Parameters: none
// Returns: nothing
void ProcessScheduler::showCompletedProcesses() {
    cout << "\n--- Completed Processes ---" << endl;
    
    // Loop through each completed process and display its info
    for (int i = 0; i < (int)completedProcs.size(); i = i + 1) {
        cout << "Process " << completedProcs[i].processId << ": " 
             << completedProcs[i].processName 
             << " (Burst: " << completedProcs[i].burstTime 
             << ", Priority: " << completedProcs[i].priority << ")" << endl;
    }
}

// Execute processes using Priority scheduling
// Higher priority processes run before lower priority processes
// If priorities are equal use FIFO order
// Parameters: none
// Returns: nothing
void ProcessScheduler::schedulePriority() {
    cout << "\n=== Starting Priority Scheduling ===" << endl;
    cout << "Priority levels: 1 (lowest) to 5 (highest)\n" << endl;
    
    contextSwitches = 0;  // Reset context switch counter
    
    // Convert queue to vector so we can sort by priority
    vector<Process> processList;
    while (!readyQueue.empty()) {
        processList.push_back(readyQueue.front());
        readyQueue.pop();
    }
    
    // Sort processes by priority highest first
    // If priorities are equal, keep original order 
    for (int i = 0; i < (int)processList.size(); i = i + 1) {
        for (int j = i + 1; j < (int)processList.size(); j = j + 1) {
            // If process j has higher priority than process i, swap them
            if (processList[j].priority > processList[i].priority) {
                Process temp = processList[i];
                processList[i] = processList[j];
                processList[j] = temp;
            }
        }
    }
    
    // Now execute processes in priority order
    for (int i = 0; i < (int)processList.size(); i = i + 1) {
        Process currentProc = processList[i];
        
        // Mark when this process starts
        currentProc.startTime = currentTime;
        currentProc.hasStarted = true;
        currentProc.waitingTime = currentTime - currentProc.arrivalTime;
        
        cout << "[TIME " << currentTime << "] Running process: " 
             << currentProc.processName << " (ID: " << currentProc.processId 
             << ", Priority: " << currentProc.priority << ")" << endl;
        cout << "  -> Burst time: " << currentProc.burstTime << " time units" << endl;
        
        // Process runs to completion
        currentTime = currentTime + currentProc.burstTime;
        currentProc.remainingTime = 0;
        currentProc.turnaroundTime = currentTime - currentProc.arrivalTime;
        
        cout << "  -> Process COMPLETED at time " << currentTime << endl;
        completedProcs.push_back(currentProc);
        cout << endl;
    }
    
    cout << "=== All processes completed ===" << endl;
    cout << "Total time elapsed: " << currentTime << " time units" << endl;
    cout << "Context switches: " << contextSwitches << endl << endl;
}

// Calculate and return scheduling performance metrics
// This analyzes how well the scheduling algorithm performed
// Parameters: none
// Returns: SchedulingMetrics structure with all calculated values
SchedulingMetrics ProcessScheduler::calculateMetrics() {
    SchedulingMetrics metrics;
    
    // Initialize totals
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    
    // If no processes completed then return zeros
    if (completedProcs.size() == 0) {
        metrics.avgWaitingTime = 0;
        metrics.avgTurnaroundTime = 0;
        metrics.cpuUtilization = 0;
        metrics.contextSwitches = 0;
        metrics.throughput = 0;
        metrics.totalProcesses = 0;
        return metrics;
    }
    
    // Calculate totals by looping through all completed processes
    for (int i = 0; i < (int)completedProcs.size(); i = i + 1) {
        totalWaitingTime = totalWaitingTime + completedProcs[i].waitingTime;
        totalTurnaroundTime = totalTurnaroundTime + completedProcs[i].turnaroundTime;
    }
    
    // Calculate averages
    metrics.totalProcesses = completedProcs.size();
    metrics.avgWaitingTime = (float)totalWaitingTime / (float)metrics.totalProcesses;
    metrics.avgTurnaroundTime = (float)totalTurnaroundTime / (float)metrics.totalProcesses;
    
    // Calculate CPU utilization
    // Eqn: (time spent executing) / (total time elapsed) * 100
    int totalBurstTime = 0;
    for (int i = 0; i < (int)completedProcs.size(); i = i + 1) {
        totalBurstTime = totalBurstTime + completedProcs[i].burstTime;
    }
    if (currentTime > 0) {
        metrics.cpuUtilization = ((float)totalBurstTime / (float)currentTime) * 100.0;
    } else {
        metrics.cpuUtilization = 0;
    }
    
    // Store context switches
    metrics.contextSwitches = contextSwitches;
    
    // Calculate throughput (processes per time unit)
    if (currentTime > 0) {
        metrics.throughput = (float)metrics.totalProcesses / (float)currentTime;
    } else {
        metrics.throughput = 0;
    }
    
    return metrics;
}

// Display performance metrics in a nice formatted way
// Parameters: none
// Returns: nothing
void ProcessScheduler::displayMetrics() {
    cout << "\n";
    cout << "============================================" << endl;
    cout << "    SCHEDULING PERFORMANCE METRICS         " << endl;
    cout << "============================================" << endl;
    
    SchedulingMetrics metrics = calculateMetrics();
    
    cout << " Total Processes:        " << metrics.totalProcesses << "              " << endl;
    cout << " Avg Waiting Time:       " << metrics.avgWaitingTime << " time units  " << endl;
    cout << " Avg Turnaround Time:    " << metrics.avgTurnaroundTime << " time units  " << endl;
    cout << " CPU Utilization:        " << metrics.cpuUtilization << "%           " << endl;
    cout << " Context Switches:       " << metrics.contextSwitches << "              " << endl;
    cout << " Throughput:             " << metrics.throughput << " proc/unit   " << endl;
    
    cout << "============================================" << endl;
    cout << endl;
}

// Visualize the scheduling timeline as a Gantt chart
// Shows when each process was executing
// Parameters: none
// Returns: nothing
void ProcessScheduler::visualizeScheduling() {
    cout << "\n";
    cout << "+----------------------------------------+" << endl;
    cout << "|        SCHEDULING GANTT CHART          |" << endl;
    cout << "+----------------------------------------+" << endl;
    cout << endl;
    
    if (completedProcs.size() == 0) {
        cout << "No processes to visualize." << endl;
        return;
    }
    
    // Find the maximum time to know how long our timeline is
    int maxTime = 0;
    for (int i = 0; i < (int)completedProcs.size(); i = i + 1) {
        int endTime = completedProcs[i].startTime + completedProcs[i].burstTime;
        if (endTime > maxTime) {
            maxTime = endTime;
        }
    }
    
    // Print time scale at the top
    cout << "Time: ";
    for (int t = 0; t <= maxTime; t = t + 5) {
        cout << t;
        if (t < 10) {
            cout << "    ";
        } else {
            cout << "   ";
        }
    }
    cout << endl;
    
    cout << "      ";
    for (int t = 0; t <= maxTime; t = t + 1) {
        if (t % 5 == 0) {
            cout << "|";
        } else {
            cout << "-";
        }
    }
    cout << endl << endl;
    
    // Print each process as a row
    for (int i = 0; i < (int)completedProcs.size(); i = i + 1) {
        Process proc = completedProcs[i];
        
        // Print process name
        cout << "P" << proc.processId;
        if (proc.processId < 10) {
            cout << "  : ";
        } else {
            cout << " : ";
        }
        
        // Print spaces before the process starts
        for (int t = 0; t < proc.startTime; t = t + 1) {
            cout << " ";
        }
        
  /*      // Print the process execution block
        for (int t = 0; t < proc.burstTime; t = t + 1) {
            cout << "#";
        }
    */
   // Add spaces before the process to match start time
        for (int i = 0; i < proc.startTime; i++) {
            cout << " ";
        }

        // Then print '#' for burst
        for (int i = 0; i < proc.burstTime; i++) {
            cout << "#";
        }    
        // Print process name at the end
        cout << " " << proc.processName;
        cout << " (Priority: " << proc.priority << ")";
        
        cout << endl;
    }
    
    cout << endl;
}