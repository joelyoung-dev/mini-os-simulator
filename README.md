# Mini Operating System Simulator

A command-line operating system simulator written in C++ that demonstrates fundamental operating system concepts including CPU scheduling, memory management, paging, virtual file systems, and shell-based user interaction.

This project was created to explore how operating systems manage processes, allocate memory, and handle file operations through a simulated environment.

---

# Features

## Process Scheduling

The simulator implements three CPU scheduling algorithms:

### FIFO (First In First Out)

Processes execute in the order they are added to the ready queue.

### Round Robin

Processes execute using a fixed time quantum, allowing multiple processes to share CPU time.

### Priority Scheduling

Processes are executed based on priority values from 1-5, with higher priority processes running first.

Commands:

`addproc <name> <burst_time> <priority>`

schedfifo

schedrr

schedprioqueue

showprocs


---

# Memory Management

The memory manager simulates paging using page tables and physical memory frames.

Implemented features:

- Fixed number of physical memory frames
- Page allocation and deallocation per process
- FIFO page replacement
- Page table visualization
- Memory usage reporting
- Memory fragmentation analysis

Commands:

`allocmem <pid> <pages>`

`freemem <pid>`

memstatus

pagetables

fragmentation


---

# Virtual File System

The simulator includes an in-memory file system supporting basic file operations.

Implemented features:

- Creating files
- Reading files
- Writing/modifying files
- Deleting files
- Listing files
- File operation logging

Commands:

`create <filename> <content>`

`read <filename>`

`write <filename> <content>`

`delete <filename>`

ls


---

# Interactive Shell

The project includes a custom command-line shell that allows users to interact with the simulated operating system.

General commands:

help

dashboard

exit


The dashboard displays system information including process status, memory usage, and file system information.

---

# Project Structure

Mini OS Simulator

CustomShell.cpp  
CustomShell.h  

ProcessScheduler.h  
Process.h  

MemoryManager.cpp  
MemoryManager.h  

FileSystem.cpp  
FileSystem.h  

main.cpp  

Makefile  

README.md


---

# Technologies Used

- C++
- Object-Oriented Programming
- Data Structures
- Operating Systems Concepts
- Make Build System


---

# Installation and Usage

## Build

Using Make:

make


## Run

make run


## Clean Build Files

make clean


---

# Future Improvements

Possible future additions:

- Multilevel feedback queue scheduling
- User permissions
- Persistent storage
- Virtual memory simulation
- Additional shell commands
- Process states (running, waiting, terminated)


---

# Concepts Demonstrated

This project demonstrates understanding of:

- CPU scheduling algorithms
- Memory management
- Paging and page tables
- File system design
- Command-line interfaces
- Object-oriented software architecture
- Modular C++ development
