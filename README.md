# Mini OS Simulator (C++)

A menu-driven C++ application that simulates core operating system functionalities such as file management, CPU scheduling, deadlock avoidance, command-line interface, and file compression.

--------------------------------------------------

OVERVIEW

This project demonstrates fundamental operating system concepts through practical implementation. Each module represents a key OS component and can be accessed through a terminal-based menu.

--------------------------------------------------

FEATURES

1. File Explorer
- List files and directories
- Change directory
- Create and delete files

2. Mini Shell
- Supports commands: ls, cd, cat, mkdir, rm
- Basic command-line interface

3. Task Scheduler
- FCFS (First Come First Serve)
- SJF (Non-preemptive)
- Round Robin
- Displays waiting time, turnaround time, and Gantt chart

4. Deadlock Simulation
- Implements Banker’s Algorithm
- Checks system safe state
- Displays safe sequence

5. File Compressor
- Uses Huffman Coding
- Compresses files into .huff format
- Decompresses files using mapping

--------------------------------------------------

CONCEPTS USED

- CPU Scheduling Algorithms
- Deadlock Avoidance
- File System Operations
- Command Line Interface
- Trees and Priority Queues

--------------------------------------------------

HOW TO RUN

Requirements:
- g++ compiler

Steps:
1. Compile:
   g++ main.cpp FileExplorer.cpp MiniShell.cpp TaskScheduler.cpp Deadlock.cpp Compressor.cpp -o miniOS

2. Run:
   ./miniOS

--------------------------------------------------

SAMPLE OUTPUT

MINI OPERATING SYSTEM MAIN MENU:
1. File Explorer
2. Mini Shell
3. Task Scheduler
4. Deadlock Simulation
5. File Compressor
0. Exit

--------------------------------------------------

PURPOSE

To provide hands-on understanding of operating system concepts by implementing them in a modular C++ application.

--------------------------------------------------
