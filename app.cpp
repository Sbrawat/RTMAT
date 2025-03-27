#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <unordered_map>
#include <algorithm>
#include <thread>
#include <chrono>

class MemoryManager {
private:
    // Total memory size
    size_t totalMemory;
    
    // Page size
    size_t pageSize;
    
    // Total number of pages
    size_t totalPages;
    
    // Memory map to track page allocations
    struct Page {
        std::string processId;
        size_t pageIndex;
        bool isFree;
        
        Page() : processId(""), pageIndex(0), isFree(true) {}
    };
    
    std::vector<Page> memoryMap;
    
    // Process tracking
    int processCounter;
    std::unordered_map<std::string, size_t> processAllocations;

    // Random number generation
    std::random_device rd;
    std::mt19937 gen;

public:
    MemoryManager(size_t totalMemory = 1024, size_t pageSize = 64) 
        : totalMemory(totalMemory), 
          pageSize(pageSize), 
          totalPages(totalMemory / pageSize),
          memoryMap(totalPages),
          processCounter(0),
          gen(rd()) {
        // Initialize all pages as free
        for (size_t i = 0; i < totalPages; ++i) {
            memoryMap[i].isFree = true;
        }
    }

    // Allocate memory for a process
    std::string allocateMemory(size_t size) {
        size_t requiredPages = (size + pageSize - 1) / pageSize;
        
        // Find consecutive free pages
        size_t startPage = findConsecutivePages(requiredPages);
        
        if (startPage == -1) {
            std::cout << "Memory allocation failed. Not enough contiguous space.\n";
            return "";
        }

        // Generate process ID
        processCounter++;
        std::string processId = "P" + std::to_string(processCounter);

        // Mark pages as allocated
        for (size_t i = startPage; i < startPage + requiredPages; ++i) {
            memoryMap[i].isFree = false;
            memoryMap[i].processId = processId;
            memoryMap[i].pageIndex = i - startPage;
        }

        // Track process allocation
        processAllocations[processId] = size;

        return processId;
    }

    // Deallocate memory for a specific process
    void deallocateMemory(const std::string& processId) {
        if (processAllocations.find(processId) == processAllocations.end()) {
            std::cout << "Process " << processId << " not found.\n";
            return;
        }

        // Free pages allocated to this process
        for (auto& page : memoryMap) {
            if (page.processId == processId) {
                page.isFree = true;
                page.processId = "";
                page.pageIndex = 0;
            }
        }

        // Remove from process allocations
        processAllocations.erase(processId);
    }

    // Visualize memory allocation
    void displayMemory() {
        std::cout << "\nMemory Allocation Map:\n";
        std::cout << std::string(totalPages * 3, '-') << "\n";
        
        for (size_t i = 0; i < totalPages; ++i) {
            if (memoryMap[i].isFree) {
                std::cout << "[ ]";
            } else {
                std::cout << "[" << memoryMap[i].processId << "]";
            }
        }
        std::cout << "\n" << std::string(totalPages * 3, '-') << "\n";
    }

    // Display active processes
    void displayProcesses() {
        std::cout << "\nActive Processes:\n";
        for (const auto& process : processAllocations) {
            std::cout << process.first << ": " << process.second << " bytes\n";
        }
    }

    // Generate a random process size
    size_t generateRandomProcessSize() {
        std::uniform_int_distribution<> sizeDistribution(50, 200);
        return sizeDistribution(gen);
    }

private:
    // Find consecutive free pages
    size_t findConsecutivePages(size_t requiredPages) {
        size_t consecutiveFound = 0;
        
        for (size_t i = 0; i < totalPages; ++i) {
            if (memoryMap[i].isFree) {
                consecutiveFound++;
                
                if (consecutiveFound == requiredPages) {
                    return i - requiredPages + 1;
                }
            } else {
                consecutiveFound = 0;
            }
        }
        
        return -1; // No consecutive pages found
    }
};

// Interactive Memory Allocation Simulation
class MemorySimulation {
private:
    MemoryManager memoryManager;

public:
    void run() {
        while (true) {
            displayMenu();
            int choice = getChoice();

            switch (choice) {
                case 1: allocateRandomProcess(); break;
                case 2: deallocateProcess(); break;
                case 3: memoryManager.displayMemory(); break;
                case 4: memoryManager.displayProcesses(); break;
                case 5: std::cout << "Exiting...\n"; return;
                default: std::cout << "Invalid choice. Try again.\n";
            }

            // Add a small delay for readability
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

private:
    void displayMenu() {
        std::cout << "\n--- Memory Allocation Simulator ---\n";
        std::cout << "1. Allocate Random Process\n";
        std::cout << "2. Deallocate Process\n";
        std::cout << "3. Display Memory Map\n";
        std::cout << "4. Display Active Processes\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
    }

    int getChoice() {
        int choice;
        std::cin >> choice;
        return choice;
    }

    void allocateRandomProcess() {
        size_t processSize = memoryManager.generateRandomProcessSize();
        std::string processId = memoryManager.allocateMemory(processSize);
        
        if (!processId.empty()) {
            std::cout << "Allocated process " << processId 
                      << " with size " << processSize << " bytes\n";
        }
    }

    void deallocateProcess() {
        memoryManager.displayProcesses();
        std::cout << "Enter process ID to deallocate: ";
        std::string processId;
        
        std::cin >> processId;
        memoryManager.deallocateMemory(processId);
    }
};

int main() {
    MemorySimulation simulation;
    simulation.run();
    return 0;
}