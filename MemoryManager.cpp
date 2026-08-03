// ============================================================================
// MemoryManager.cpp
// Implementation file for Memory Manager class
// Contains the code for memory allocation and page table management
// ============================================================================

#include "MemoryManager.h"
#include <iostream>

using namespace std;

// Default constructor for PageTableEntry
PageTableEntry::PageTableEntry() {
    pageNumber = -1;
    frameNumber = -1;
    isValid = false;
}

// Constructor: Set up memory with a specific number of frames
// Parameters: frames - number of physical memory frames
// Returns: nothing 
MemoryManager::MemoryManager(int frames) {
    totalFrames = frames;
    
    // Initialize all frames as free 
    for (int i = 0; i < totalFrames; i = i + 1) {
        frameAllocation.push_back(false);
    }
    
    cout << "[MEMORY] Initialized memory manager with " 
         << totalFrames << " frames" << endl;
}

// Allocate memory pages for a process
// Parameters: processId - which process needs memory
//            numPages - how many pages to allocate
// Returns: true if successful and false if not enough memory
bool MemoryManager::allocateMemory(int processId, int numPages) {
    cout << "\n[MEMORY] Allocating " << numPages 
         << " pages for Process " << processId << endl;
    
    // Check if we have enough free frames
    int freeFrames = 0;
    for (int i = 0; i < totalFrames; i = i + 1) {
        if (frameAllocation[i] == false) {
            freeFrames = freeFrames + 1;
        }
    }
    
    if (freeFrames < numPages) {
        while(freeFrames < numPages)
        {
            evictPageFIFO();
            freeFrames = freeFrames + 1;
        }
    }
    
    // Allocate pages to frames
    vector<PageTableEntry> pageTable;
    int pagesAllocated = 0;
    
    // Go through frames and allocate them to pages
    for (int frameNum = 0; frameNum < totalFrames; frameNum = frameNum + 1) {
        if (pagesAllocated >= numPages) {
            break;  // Once done allocating
        }
        
        if (frameAllocation[frameNum] == false) {
            // This frame is free 
            PageTableEntry entry;
            entry.pageNumber = pagesAllocated;
            entry.frameNumber = frameNum;
            entry.isValid = true;
            
            pageTable.push_back(entry);
            frameAllocation[frameNum] = true;  // Mark frame as used
            fifoQueue.push({processId, pagesAllocated, frameNum});
            
            cout << "  -> Page " << pagesAllocated 
                 << " mapped to Frame " << frameNum << endl;
            
            pagesAllocated = pagesAllocated + 1;
        }
    }
    
    // Save this process page table
    pageTables[processId] = pageTable;
    cout << "  -> Memory allocation successful!" << endl;
    return true;
}

// Free all memory allocated to a process
// Parameters: processId - which process to deallocate
// Returns: nothing
void MemoryManager::deallocateMemory(int processId) {
    cout << "\n[MEMORY] Deallocating memory for Process " << processId << endl;
    
    // Check if this process has a page table
    if (pageTables.find(processId) == pageTables.end()) {
        cout << "  -> No memory allocated for this process" << endl;
        return;
    }
    
    // Get the page table for this process
    vector<PageTableEntry> pageTable = pageTables[processId];
    
    // Free each frame used by this process
    for (int i = 0; i < (int)pageTable.size(); i = i + 1) {
        int frameNum = pageTable[i].frameNumber;
        frameAllocation[frameNum] = false;  // Mark frame as free
        cout << "  -> Freed Frame " << frameNum << endl;
    }
    
    // Remove the page table
    pageTables.erase(processId);
    removeProcessFromFIFO(processId);
    cout << "  -> Deallocation complete" << endl;
}

// Display current memory status
// Parameters: none
// Returns: nothing
void MemoryManager::displayMemoryStatus() {
    cout << "\n--- Memory Status ---" << endl;
    cout << "Total Frames: " << totalFrames << endl;
    
    // Count free frames
    int freeCount = 0;
    for (int i = 0; i < totalFrames; i = i + 1) {
        if (frameAllocation[i] == false) {
            freeCount = freeCount + 1;
        }
    }
    
    cout << "Free Frames: " << freeCount << endl;
    cout << "Used Frames: " << (totalFrames - freeCount) << endl;
    
    // Show which frames are allocated
    cout << "\nFrame Allocation Map: " << endl;
    for (int i = 0; i < totalFrames; i = i + 1) {
        cout << "Frame " << i << ": ";
        if (frameAllocation[i] == true) {
            cout << "[USED]" << endl;
        } else {
            cout << "[FREE]" << endl;
        }
    }
}

// Display page tables for all processes
// Parameters: none
// Returns: nothing
void MemoryManager::displayPageTables() {
    cout << "\n--- Page Tables ---" << endl;
    
    if (pageTables.empty()) {
        cout << "No active page tables" << endl;
        return;
    }
    
    // Loop through each process' page table
    for (map<int, vector<PageTableEntry>>::iterator it = pageTables.begin(); 
         it != pageTables.end(); it = std::next(it, 1)) {
        
        int procId = it->first;
        vector<PageTableEntry> table = it->second;
        
        cout << "\nProcess " << procId << " Page Table:" << endl;
        
        // Display each entry in this page table
        for (int i = 0; i < (int)table.size(); i = i + 1) {
            cout << "  Page " << table[i].pageNumber 
                 << " -> Frame " << table[i].frameNumber;
            if (table[i].isValid == true) {
                cout << " [VALID]" << endl;
            } else {
                cout << " [INVALID]" << endl;
            }
        }
    }
}

// Analyze and display memory fragmentation
// Shows holes in the allocations
// and memory efficiency statistics
// Parameters: none
// Returns: nothing
void MemoryManager::analyzeFragmentation() {
    cout << "\n";
    cout << "============================================" << endl;
    cout << "    MEMORY FRAGMENTATION ANALYSIS          " << endl;
    cout << "============================================" << endl;
    
    // Count used and free frames
    int usedFrames = 0;
    int freeFrames = 0;
    for (int i = 0; i < totalFrames; i = i + 1) {
        if (frameAllocation[i] == true) {
            usedFrames = usedFrames + 1;
        } else {
            freeFrames = freeFrames + 1;
        }
    }
    
    // Find holes
    vector<int> holesSizes;  // Store the size of each hole
    int currentHoleSize = 0;
    int largestHole = 0;
    
    for (int i = 0; i < totalFrames; i = i + 1) {
        if (frameAllocation[i] == false) {
            // This frame is free so add to current hole
            currentHoleSize = currentHoleSize + 1;
        } else {
            // This frame is used so the hole ended
            if (currentHoleSize > 0) {
                holesSizes.push_back(currentHoleSize);
                if (currentHoleSize > largestHole) {
                    largestHole = currentHoleSize;
                }
                currentHoleSize = 0;
            }
        }
    }
    
    // Check the last possible hole if memory ends with free frames
    if (currentHoleSize > 0) {
        holesSizes.push_back(currentHoleSize);
        if (currentHoleSize > largestHole) {
            largestHole = currentHoleSize;
        }
    }
    
    // Calculate memory efficiency
    float efficiency = 0.0;
    if (totalFrames > 0) {
        efficiency = ((float)usedFrames / (float)totalFrames) * 100.0;
    }
    
    // Display statistics
    cout << " Total Memory Frames:    " << totalFrames << "              " << endl;
    cout << " Used Frames:            " << usedFrames << "               " << endl;
    cout << " Free Frames:            " << freeFrames << "               " << endl;
    cout << "                                         " << endl;
    cout << " External Fragmentation:                 " << endl;
    cout << "   Number of Holes:      " << holesSizes.size() << "               " << endl;
    cout << "   Largest Hole:         " << largestHole << " frames        " << endl;
    
    // Show total free space in holes
    int totalHoleSpace = 0;
    for (int i = 0; i < (int)holesSizes.size(); i = i + 1) {
        totalHoleSpace = totalHoleSpace + holesSizes[i];
    }
    cout << "   Total Hole Space:     " << totalHoleSpace << " frames        " << endl;
    cout << "                                         " << endl;
    cout << " Memory Efficiency:      " << efficiency << "%           " << endl;
    
    cout << "============================================" << endl;
    
    // Visual representation of memory
    cout << "\nMemory Layout Visualization:" << endl;
    cout << "[";
    for (int i = 0; i < totalFrames; i = i + 1) {
        if (frameAllocation[i] == true) {
            cout << "#";  // Used frame
        } else {
            cout << "-";  // Free frame
        }
    }
    cout << "]" << endl;
    cout << "Key: # = Used, - = Free\n" << endl;
    
    // Provide recommendations if fragmentation is bad
    if (holesSizes.size() > 3 && efficiency < 70) {
        cout << "WARNING: HIGH FRAGMENTATION DETECTED!" << endl;
        cout << endl;
    }
}

//Getter functions for visualization
// Parameters: none
// Returns: total number of page frames
int MemoryManager::getTotalFrames() const{
    return totalFrames;
}

//Getter functions for visualization
// Parameters: none
// returns: number of page frames in use
int MemoryManager::getUsedFrames() const {
    int used = 0;
    for (int i = 0; i < totalFrames; i++) {
        if (frameAllocation[i] == true) {
            used++;
        }
    }
    return used;
}

// Calculates percentage of used frames
//Parameters: none
// Returns: percentage of frames being used
float MemoryManager::getUsagePercent() const {
    if (totalFrames == 0) {
        return 0.0f;
    }
    return ((float)getUsedFrames() / (float)totalFrames) * 100.0f;
}

// Evicts a single page from FIFO queue if no pages left and trying to allocate
// Parameters: none
// returns: nothing
void MemoryManager::evictPageFIFO(){
    if(fifoQueue.empty())
    {
        return;
    }
    FrameInfo victim = fifoQueue.front(); //take oldest member(whats in front of queue)
    fifoQueue.pop(); //delete it

    cout << "[MEM] No free frames - evicting a Page "
         << victim.page << " of Process "
         << victim.pid << " from Frame "
         << victim.frame << endl;

    // Invalidate page table entry
    pageTables[victim.pid][victim.page].isValid = false;

    // Free the frame
    frameAllocation[victim.frame] = false;

}
// This removes the PF's that a process that's been removed is taking up
// Parameters: the PID of the process that's being removed
// Returns: nothing
void MemoryManager::removeProcessFromFIFO(int processId) {
    queue<FrameInfo> temp;

    while (!fifoQueue.empty()) {
        FrameInfo f = fifoQueue.front();
        fifoQueue.pop();

        if (f.pid != processId) {
            temp.push(f);
        }
    }

    fifoQueue = temp;
}