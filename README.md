# RTMAT
Real Time Memory Allocation Tracker
Memory Allocation Simulation System
Overview
A sophisticated C++ application that simulates memory allocation mechanisms, demonstrating key operating system memory management principles through an interactive console interface.
Features

Dynamic memory allocation
Process tracking and management
Real-time memory visualization
Multiple sorting capabilities
Paging and segmentation simulation

Prerequisites

C++ Compiler (GCC, Clang, or MSVC)
C++17 Standard Support
Minimal system resources

Compilation Instructions
bashCopy# Compile the program
g++ -std=c++17 memory_allocation.cpp -o memory_allocation

# Run the executable
./memory_allocation
Program Workflow

Launch the simulation
Choose from menu options:

Allocate random processes
Manually allocate processes
Deallocate processes
View memory map
Sort active processes



Memory Management Concepts

Fixed page size (64 bytes)
Total memory: 1024 bytes
Process size range: 50-200 bytes
Contiguous memory allocation
Page-based memory tracking

Sorting Capabilities

Sort processes by:

Memory size
Allocation time
Pages used



Technical Details

Language: C++17
Paradigm: Object-Oriented Programming
Allocation Complexity: O(n)

Sample Use Cases

Operating system design education
Memory management training
Algorithm visualization
Performance analysis

Learning Objectives

Understand memory allocation strategies
Visualize memory segmentation
Learn process tracking techniques

Potential Improvements

Graphical user interface
Advanced allocation algorithms
Detailed memory fragmentation analysis
Performance metrics

Contribution
Contributions are welcome! Please fork the repository and submit pull requests.
License
Open-source MIT License
Contact
For questions or suggestions, please open an issue in the repository.
