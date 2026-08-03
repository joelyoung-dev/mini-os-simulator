// ============================================================================
// CustomShell.cpp
// Implementation file for Custom Shell class
// Contains the code for the CLI
// ============================================================================

#include "CustomShell.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <queue>

using namespace std;

// Constructor: Initialize the shell and create OS components
// Parameters: none
// Returns: nothing 
CustomShell::CustomShell() {
    // Init the OS 
    scheduler = new ProcessScheduler(3);  // Time quantum of 3
    memoryMgr = new MemoryManager(20);    // 20 memory frames
    fileSys = new FileSystem();
    isRunning = true;
    nextProcessId = 1;
    
    cout << "\n";
    cout << "========================================" << endl;
    cout << "  OPERATING SYSTEM SIMULATOR v1.0" << endl;
    cout << "========================================" << endl;
    cout << "\nType 'help' for available commands\n" << endl;
}

// Destructor
CustomShell::~CustomShell() {
    delete scheduler;
    delete memoryMgr;
    delete fileSys;
}

// Display help information showing all available commands
// Parameters: none
// Returns: nothing
void CustomShell::displayHelp() {
    cout << "\n=== Available Commands ===" << endl;
    cout << "\nProcess Scheduling:" << endl;
    cout << "  addproc <name> <burst_time>  - Add a new process" << endl;
    cout << "  schedrr                      - Run Round Robin scheduling" << endl;
    cout << "  schedfifo                    - Run FIFO scheduling" << endl;
    cout << "  schedprioqueue               - Run priority scheduling" << endl;
    cout << "  showprocs                    - Show completed processes" << endl;
    cout << "  displaymetrics               - Displays process metrics" << endl;
    
    cout << "\nMemory Management:" << endl;
    cout << "  allocmem <process_id> <pages> - Allocate memory for a process" << endl;
    cout << "  freemem <process_id>          - Free process memory" << endl;
    cout << "  memstatus                     - Show memory status" << endl;
    cout << "  pagetables                    - Show all page tables" << endl;
    cout << "  fragmentation                 - Show holes in page tables" << endl;  

    cout << "\nFile System:" << endl;
    cout << "  create <filename> <content>   - Create a new file" << endl;
    cout << "  read <filename>               - Read a file" << endl;
    cout << "  write <filename> <content>    - Write to a file" << endl;
    cout << "  delete <filename>             - Delete a file" << endl;
    cout << "  ls                            - List all files" << endl;
    
    cout << "\nSystem:" << endl;
    cout << "  dashboard                     - Displays dashboard with metrics" << endl;
    cout << "  help                          - Show this help message" << endl;
    cout << "  exit                          - Exit the simulator" << endl;
    cout << endl;
}

// Main loop that continuously keeps accepting and processing commands
// Parameters: none
// Returns: nothing
void CustomShell::run() {
    string command;
    
    while (isRunning == true) {
        cout << "OS> ";
        getline(cin, command);
        
        // Process the command
        processCommand(command);
    }
}

// Execute a user command
// Parameters: command - the full command string entered by user
// Returns: nothing
void CustomShell::processCommand(string command) {
    // If empty, skip
    if (command.empty() == true) {
        return;
    }
    
    // Split command into parts
    vector<string> parts;
    stringstream ss(command);
    string part;
    
    while (ss >> part) {
        parts.push_back(part);
    }
    
    if (parts.size() == 0) {
        return;
    }
    
    string cmd = parts[0];
    
    // Process scheduling commands
    //If addproc cmd entered
    if (cmd == "addproc") {
        if (parts.size() < 3) {
            cout << "Usage: addproc <name> <burst_time>" << endl;
            return;
        }
        string procName = parts[1];
        int burstTime = stoi(parts[2]);
        Process newProc(nextProcessId, procName, burstTime, 0);
        scheduler->addProcess(newProc);
        nextProcessId = nextProcessId + 1;
    }
    // If schedrr cmd entered
    else if (cmd == "schedrr") {
        scheduler->scheduleRoundRobin();
    }
    // If schedfifo cmd entered
    else if (cmd == "schedfifo") {
        scheduler->scheduleFIFO();
    }
    else if(cmd == "schedprioqueue")
    {
        runPriorityQueue();
    }
    // If showprocs cmd entered
    else if (cmd == "showprocs") {
        scheduler->showCompletedProcesses();
        scheduler-> visualizeScheduling();
    }
    // If displaymetrics entered
    else if(cmd == "displaymetrics")
    {
        scheduler->displayMetrics();
    }
    
    // Memory management commands
    else if (cmd == "allocmem") {
        if (parts.size() < 3) {
            cout << "Usage: allocmem <process_id> <pages>" << endl;
            return;
        }
        int procId = stoi(parts[1]);
        int pages = stoi(parts[2]);
        memoryMgr->allocateMemory(procId, pages);
    }
    else if (cmd == "freemem") {
        if (parts.size() < 2) {
            cout << "Usage: freemem <process_id>" << endl;
            return;
        }
        int procId = stoi(parts[1]);
        memoryMgr->deallocateMemory(procId);
    }
    else if (cmd == "memstatus") {
        memoryMgr->displayMemoryStatus();
    }
    else if (cmd == "pagetables") {
        memoryMgr->displayPageTables();
    }
    else if (cmd == "fragmentation") {
        memoryMgr->analyzeFragmentation();
    }
    
    // File system commands
    else if (cmd == "create") {
        if (parts.size() < 3) {
            cout << "Usage: create <filename> <content>" << endl;
            return;
        }
        string fileName = parts[1];
        string content = "";
        // Combine all remaining parts as content
        for (int i = 2; i < (int)parts.size(); i = i + 1) {
            content = content + parts[i];
            if (i < (int)parts.size() - 1) {
                content = content + " ";
            }
        }
        fileSys->createFile(fileName, content);
    }
    else if (cmd == "read") {
        if (parts.size() < 2) {
            cout << "Usage: read <filename>" << endl;
            return;
        }
        fileSys->readFile(parts[1]);
    }
    else if (cmd == "write") {
        if (parts.size() < 3) {
            cout << "Usage: write <filename> <content>" << endl;
            return;
        }
        string fileName = parts[1];
        string content = "";
        for (int i = 2; i < (int)parts.size(); i = i + 1) {
            content = content + parts[i];
            if (i < (int)parts.size() - 1) {
                content = content + " ";
            }
        }
        fileSys->writeFile(fileName, content);
    }
    else if (cmd == "delete") {
        if (parts.size() < 2) {
            cout << "Usage: delete <filename>" << endl;
            return;
        }
        fileSys->deleteFile(parts[1]);
    }
    else if (cmd == "ls") {
        fileSys->listFiles();
    }
    
    // System commands
    else if (cmd == "dashboard") {
        displayDashboard();
    }
    else if (cmd == "help") {
        displayHelp();
    }

    else if (cmd == "exit") {
        cout << "\nShutting down OS Simulator..." << endl;
        cout << "Thank you for using the simulator!" << endl;
        isRunning = false;
    }
    else {
        cout << "Unknown command: " << cmd << endl;
        cout << "Type 'help' for available commands" << endl;
    }
}

// Display a real-time system dashboard
// Shows an overview of the entire system status
// Parameters: none
// Returns: nothing
void CustomShell::displayDashboard() {
    cout << "\n";
    cout << "============================================================" << endl;
    cout << "            OPERATING SYSTEM DASHBOARD                     " << endl;
    cout << "============================================================" << endl;
    cout << "                                                            " << endl;
    
    // Get scheduler metrics if available
    SchedulingMetrics metrics = scheduler->calculateMetrics();
    
    // CPU Section
    cout << "  CPU STATUS                                                " << endl;
    cout << "  -----------------------------------------------------------" << endl;
    
    if (metrics.totalProcesses > 0) {
        cout << "    Completed Processes:     " << metrics.totalProcesses << "                            " << endl;
        cout << "    CPU Utilization:         ";
        
        // Draw CPU utilization bar
        int barLength = 20;
        int filledBars = (int)((metrics.cpuUtilization / 100.0) * barLength);
        cout << "[";
        for (int i = 0; i < barLength; i = i + 1) {
            if (i < filledBars) {
                cout << "#";
            } else {
                cout << "-";
            }
        }
        cout << "] " << (int)metrics.cpuUtilization << "%   " << endl;
        
        cout << "    Context Switches:        " << metrics.contextSwitches << "                            " << endl;
    } else {
        cout << "    Status: IDLE - No processes scheduled yet             " << endl;
    }
    
    cout << "                                                            " << endl;
    
    // Memory Section
    cout << "  MEMORY STATUS                                             " << endl;
    cout << "  -----------------------------------------------------------" << endl;
    
    // Calculate memory statistics
    // Count used frames by checking if any page tables exist
    cout << "    Total Frames:            20                            " << endl;
    
    // Create a  memory usage bar
    int totalFrames = memoryMgr->getTotalFrames();
    int usedFrames = memoryMgr->getUsedFrames();
    float usagePercent = memoryMgr->getUsagePercent();

    cout << "    Memory Usage:            ";

    int barLength = 20;
    int filledBars = (int)((usagePercent / 100.0f) * barLength);

    cout << "[";
    for (int i = 0; i < barLength; i++) {
        if (i < filledBars) {
            cout << "#";
        } else {
            cout << "-";
        }
    }
    cout << "] " << (int)usagePercent << "%   " << endl;

    cout << "    Used Frames:             " << usedFrames << endl;
    cout << "    Free Frames:             " << (totalFrames - usedFrames) << endl;
    cout << "                                                            " << endl;
    
    // File System Section
    cout << "  FILE SYSTEM STATUS                                        " << endl;
    cout << "  -----------------------------------------------------------" << endl;
    cout << "    Active Files:            (use 'ls' to view)            " << endl;
    cout << "    Log File:                filesystem_log.txt            " << endl;
    cout << "                                                            " << endl;
    
    // System Info
    cout << "  SYSTEM INFO                                               " << endl;
    cout << "  -----------------------------------------------------------" << endl;
    cout << "    OS Simulator Version:    1.0                           " << endl;
    cout << "    Scheduling Algorithms:   RR, FIFO, Priority            " << endl;
    cout << "    Memory Management:       Page-based                    " << endl;
    cout << "                                                            " << endl;
    
    cout << "============================================================" << endl;
    cout << "\nType 'help' to see all available commands" << endl;
    cout << endl;
}

void CustomShell::runPriorityQueue()
{
    cout << "\nPriority Queue Scheduling\n";
    cout << "Enter processes like this:\n";
    cout << "name burst priority(1-5)\n";
    cout << "Type 'done' when finished\n\n";

    // Higher priority should run first
    // If priority is the same, earlier PID goes first
    auto cmp = [](Process a, Process b) {
        if (a.priority == b.priority) {
            return a.processId > b.processId;
        }
        return a.priority < b.priority;
    };

    priority_queue<Process, vector<Process>, decltype(cmp)> pq(cmp);

    string line;
    int pid = 1;

    // Read input
    while (true) {
        cout << "proc> ";
        getline(cin, line);

        if (line == "done") {
            break;
        }

        string name;
        int burst;
        int priority;

        stringstream ss(line);
        ss >> name >> burst >> priority;

        if (priority < 1 || priority > 5) {
            cout << "Invalid priority, using 3\n";
            priority = 3;
        }

        Process p(pid, name, burst, 0, priority);
        pq.push(p);

        cout << "Added " << name
             << " (burst=" << burst
             << ", priority=" << priority << ")\n";

        pid++;
    }

    int time = 0;

    cout << "\nExecution order:\n";

    // Run processes
    while (!pq.empty()) {
        Process p = pq.top();
        pq.pop();

        // set metrics
        p.startTime = time;
        p.waitingTime = p.startTime;    // assuming arrivalTime = 0
        time += p.burstTime;
        p.turnaroundTime = time;
        scheduler->addCompletedProcess(p);  // push to main scheduler

        cout << "[TIME " << p.startTime << "] Running "
             << p.processName
             << " (priority " << p.priority << ")\n";

        cout << "  Finished at time " << time << endl;
    }

    scheduler->setCurrentTime(time);

    cout << "\nAll processes finished\n";
    cout << "Total time: " << time << "\n\n";
}