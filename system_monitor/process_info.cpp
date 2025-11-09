#include "process_info.h"
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unistd.h>

using namespace std;

vector<Process> getProcessList() {
    vector<Process> processes;
    DIR* dir = opendir("/proc");
    struct dirent* entry;

    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            string pidStr = entry->d_name;
            if (all_of(pidStr.begin(), pidStr.end(), ::isdigit)) {
                int pid = stoi(pidStr);
                Process p;
                p.pid = pid;

                // Read process name from /proc/[pid]/comm
                ifstream nameFile("/proc/" + pidStr + "/comm");
                if (nameFile.is_open()) {
                    getline(nameFile, p.name);
                    nameFile.close();
                } else {
                    p.name = "unknown";
                }

                // Read CPU usage from /proc/[pid]/stat
                ifstream statFile("/proc/" + pidStr + "/stat");
                if (statFile.is_open()) {
                    string content;
                    getline(statFile, content);
                    statFile.close();

                    istringstream ss(content);
                    string token;
                    int count = 1;
                    long utime = 0, stime = 0, rss = 0;
                    while (ss >> token) {
                        if (count == 14) utime = stol(token);
                        if (count == 15) stime = stol(token);
                        if (count == 24) rss = stol(token); // resident set size
                        count++;
                    }

                    long page_size_kb = sysconf(_SC_PAGESIZE) / 1024; // in KB
                    p.cpu = (utime + stime) / 100.0; // Simplified CPU usage
                    p.memory = rss * page_size_kb / 1024.0; // Memory in MB
                }

                processes.push_back(p);
            }
        }
    }
    closedir(dir);

    // Sort by CPU descending
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.cpu > b.cpu;
    });

    return processes;
}
