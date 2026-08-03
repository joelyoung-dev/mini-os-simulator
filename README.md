Mini OS Simulator

Overview
This project is a simple operating system simulator written in C++. It demonstrates basic operating system concepts such as process scheduling, memory management, and file system operations through a CLI.


Features

Process Scheduling
The simulator supports the following scheduling algorithms:

FIFO (First In First Out)
Processes run in the order they are added.

Round Robin
Each process runs for a fixed time quantum before being placed back in the queue.

Priority Scheduling
Processes with higher priority values run before lower priority ones.



Memory Management
The memory manager simulates paging with page tables.

Features include:

Fixed number of physical memory frames

Page allocation and deallocation per process

FIFO page replacement

Memory usage display

Memory fragmentation analysis


File System
A simple in memory file system that supports:

Creating files

Reading files

Writing to files

Deleting files

Listing files


# Installation and Usage

## Build

Using Make:

```bash
make
```

## Run
```bash
make run
```


Process Scheduling Commands

addproc <name> <burst_time> <priority (1-5)>
schedfifo
schedrr
schedprioqueue
showprocs

addproc adds a new process. Priority is optional and ranges from 1 to 5.
schedprioqueue runs the standalone priority queue scheduler.

Memory Commands

allocmem <pid> <pages>
freemem <pid>
memstatus
pagetables
fragmentation

File System Commands

create <filename> <content>
read <filename>
write <filename> <content>
delete <filename>
ls

General Commands

help
dashboard
exit

Priority Queue Scheduling Example

OS> schedprioqueue
proc> A 5 1
proc> B 3 5
proc> C 4 3
proc> done

Execution order:

[TIME 0] Running B (priority 5)
[TIME 3] Running C (priority 3)
[TIME 7] Running A (priority 1)

Higher priority processes run first. If two processes have the same priority, they run in the order they were added.

The other scheduling types require using addproc <name> <burst time> and then running the command (schedfifo or schedrr)

Project Structure

CustomShell.cpp
CustomShell.h
ProcessScheduler.cpp
ProcessScheduler.h
MemoryManager.cpp
MemoryManager.h
FileSystem.cpp
FileSystem.h
Process.h
README.md