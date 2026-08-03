// ============================================================================
// MemoryManager.h
// Header file for Memory Manager class
// Simulates memory management using page tables
// ============================================================================

#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <vector>
#include <map>
#include <queue>
using namespace std;

// ============================================================================
// PAGE TABLE ENTRY
// This structure represents one entry in a page table which maps
// VA to PA
// ============================================================================
struct PageTableEntry {
    int pageNumber;         // Virtual page number
    int frameNumber;        // Physical frame number 
    bool isValid;          // Is this page currently in memory
    
    // Default constructor
    PageTableEntry();
};

// ============================================================================
// FRAME INFO
// This structure represents the PF info that will be stored in a FIFO
// queue to implement FIFO page replacement
// ============================================================================

struct FrameInfo {
    int pid;
    int page;
    int frame;
};

// ============================================================================
// MEMORY MANAGER CLASS
// Simulates memory management using page tables
// In real systems this maps VA to PA
// ============================================================================
class MemoryManager {
private:
    int totalFrames;                           // Total physical memory frames available
    vector<bool> frameAllocation;              // Track which frames are in use
    map<int, vector<PageTableEntry>> pageTables; // Page table for each process
    queue<FrameInfo> fifoQueue;                 //FIFO quueue for PF replacement
public:
    // Constructor: Set up memory with a specific number of frames
    // Parameters: frames - number of PM frames
    MemoryManager(int frames);
    
    // Allocate memory pages for a process
    // Parameters: processId - which process needs memory
    //            numPages - how many pages to allocate
    // Returns: true if successful and false if not enough memory
    bool allocateMemory(int processId, int numPages);
    
    // Free all memory allocated to a process
    // Parameters: processId - which process to deallocate
    // Returns: nothing
    void deallocateMemory(int processId);
    
    // Display current memory status
    // Parameters: none
    // Returns: nothing
    void displayMemoryStatus();
    
    // Display page tables for all processes
    // Parameters: none
    // Returns: nothing
    void displayPageTables();
    
    // Analyze and display memory fragmentation statistics
    // Shows internal and external fragmentation
    // Parameters: none
    // Returns: nothing
    void analyzeFragmentation();

    //Getter functions for memory visualization
    int getTotalFrames() const;
    int getUsedFrames() const;
    float getUsagePercent() const;

    // Function to evict a page from FIFO queue
    void evictPageFIFO();
    
    // Function to remove a process's PF from the queue if process is deleted
    void removeProcessFromFIFO(int processId);

};
//Adding in

#endif // MEMORY_MANAGER_H