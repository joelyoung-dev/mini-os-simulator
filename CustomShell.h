// ============================================================================
// CustomShell.h
// Header file for Custom Shell class
// Provides a CLI for using the OS
// ============================================================================

#ifndef CUSTOM_SHELL_H
#define CUSTOM_SHELL_H

#include <string>
#include "ProcessScheduler.h"
#include "MemoryManager.h"
#include "FileSystem.h"

using namespace std;

// ============================================================================
// CUSTOM SHELL CLASS
// Provides a CLI for interacting with the OS simulator
// Users can type commands to test scheduling, memory, and file system
// ============================================================================
class CustomShell {
private:
    ProcessScheduler* scheduler;   // Pointer to the process scheduler
    MemoryManager* memoryMgr;     // Pointer to the memory manager
    FileSystem* fileSys;          // Pointer to the file system
    bool isRunning;               // Is the shell currently running
    int nextProcessId;            // ID to assign to next process
    
public:
    // Constructor: Initialize the shell and create OS components
    // Parameters: none
    CustomShell();
    
    // Destructor: Clean up allocated memory
    ~CustomShell();
    
    // Display help information showing all available commands
    // Parameters: none
    // Returns: nothing
    void displayHelp();
    
    // Main loop - keeps accepting and processing commands
    // Parameters: none
    // Returns: nothing
    void run();
    
    // Parse and execute a user command
    // Parameters: command - the full command string entered by user
    // Returns: nothing
    void processCommand(string command);
    
    // Display a real time system dashboard
    // Shows overview of CPU, memory, and file system
    // Parameters: none
    // Returns: nothing
    void displayDashboard();
    
    // Runs priority queue 
    void runPriorityQueue();

};

#endif // CUSTOM_SHELL_H