#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include <string>

float getCPUUsage();      // Returns CPU usage in %
float getMemoryUsage();   // Returns Memory usage in %
std::string getUptime();  // Returns formatted uptime

#endif
