#ifndef PROCESS_INFO_H
#define PROCESS_INFO_H

#include <string>
#include <vector>

struct Process {
    int pid;
    std::string name;
    float cpu;
    float memory;
};

// Returns a list of all running processes
std::vector<Process> getProcessList();

#endif
