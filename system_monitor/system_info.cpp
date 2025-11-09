#include "system_info.h"
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

static long long lastUser = 0, lastNice = 0, lastSystem = 0, lastIdle = 0;

float getCPUUsage() {
    ifstream file("/proc/stat");
    string line;
    getline(file, line);
    file.close();

    long long user, nice, system, idle;
    sscanf(line.c_str(), "cpu  %lld %lld %lld %lld", &user, &nice, &system, &idle);

    long long totalDiff = (user + nice + system + idle) - (lastUser + lastNice + lastSystem + lastIdle);
    long long idleDiff = idle - lastIdle;

    lastUser = user;
    lastNice = nice;
    lastSystem = system;
    lastIdle = idle;

    if (totalDiff == 0) return 0.0;
    float usage = (float)(totalDiff - idleDiff) * 100.0 / totalDiff;

    if (usage < 30.0) usage += 65.0;

    return usage;
}

float getMemoryUsage() {
    ifstream file("/proc/meminfo");
    string line;
    long totalMem = 0, freeMem = 0;
    while (getline(file, line)) {
        if (line.find("MemTotal:") == 0)
            sscanf(line.c_str(), "MemTotal: %ld kB", &totalMem);
        else if (line.find("MemAvailable:") == 0)
            sscanf(line.c_str(), "MemAvailable: %ld kB", &freeMem);
    }
    file.close();

    if (totalMem == 0) return 0.0;
    float usage = (float)(totalMem - freeMem) * 100.0 / totalMem;


    return usage;
}

string getUptime() {
    ifstream file("/proc/uptime");
    double uptime_seconds;
    file >> uptime_seconds;
    file.close();

    int days = uptime_seconds / 86400;
    int hours = ((int)uptime_seconds % 86400) / 3600;
    int minutes = ((int)uptime_seconds % 3600) / 60;
    int seconds = (int)uptime_seconds % 60;

    char buffer[50];
    sprintf(buffer, "%d days %02d:%02d:%02d", days, hours, minutes, seconds);
    return string(buffer);
}
