#include "pch.h"
#include "MemoryUsage.h"

// Retrieves the current memory usage in gigabytes
void GetMemoryUsage(double& usedGB, double& totalGB) {
    MEMORYSTATUSEX memInfo = { sizeof(memInfo) };
    if (GlobalMemoryStatusEx(&memInfo)) {
        // Convert bytes to gigabytes
        totalGB = memInfo.ullTotalPhys / (1024.0 * 1024.0 * 1024.0);
        usedGB = (memInfo.ullTotalPhys - memInfo.ullAvailPhys) / (1024.0 * 1024.0 * 1024.0);
    }
    else {
        // In case of failure, set both values to 0.0
        usedGB = totalGB = 0.0;
    }
}