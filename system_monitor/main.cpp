#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <vector>      
#include <csignal>      
#include <unistd.h>
#include <algorithm>   
#include "system_info.h"
#include "process_info.h"
using namespace std;

enum class SortBy { CPU, Memory };

int main() {

    SortBy sortOption = SortBy::CPU;
    const int refreshInterval = 1;


    while (true) {

        system("clear");
        
        float cpu = getCPUUsage();
        float mem = getMemoryUsage();
         string uptime = getUptime();
       

        // UI Layout
        cout << "==============================\n";
        cout << "       SYSTEM MONITOR\n";
        cout << "==============================\n\n";

        cout << "CPU Usage       : " << cpu << " %\n";
        cout << "Memory Usage    : " << mem << " %\n";
        cout << "System Uptime   : " << uptime << "\n\n";

        cout << "==============================\n";
        vector<Process> processes = getProcessList();         
         if (sortOption == SortBy::CPU) {
             sort(processes.begin(), processes.end(), [](const Process &a, const Process &b){
                return a.cpu > b.cpu;
        });
        } else {
            sort(processes.begin(), processes.end(), [](const Process &a, const Process &b){
                return a.memory > b.memory;
        });
      }
         cout << "PID\tCPU\tMemory(MB)\tName\n";

        // Process list
        for (auto &p : processes) {
            cout << p.pid << "\t"
                 << fixed << setprecision(1) << p.cpu << "\t"
                 << fixed << setprecision(1) << p.memory << "\t\t"
                 << p.name << "\n";
        }   
        cout << "\nSorting by: " << (sortOption == SortBy::CPU ? "CPU" : "Memory") << "\n";
        cout << "Press 'c' to sort by CPU, 'm' to sort by Memory\n";

        // Non-blocking check for input to switch sorting
        if (cin.rdbuf()->in_avail()) {
            char ch;
            cin >> ch;
            if (ch == 'c') sortOption = SortBy::CPU;
            else if (ch == 'm') sortOption = SortBy::Memory;
             else if (ch == 'k') {
                int pidToKill;
                cout << "Enter PID to kill: ";
                cin >> pidToKill;
                if (kill(pidToKill, SIGTERM) == 0)
                    cout << "Process " << pidToKill << " terminated.\n";
                else
                    perror("Failed to kill process");
                this_thread::sleep_for(chrono::seconds(1));
            }

        }
        // Update every 1 second
        this_thread::sleep_for(chrono::seconds(1));
    }
}
