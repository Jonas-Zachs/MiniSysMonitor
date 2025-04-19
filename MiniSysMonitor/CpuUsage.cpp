#include "pch.h"
#include "CpuUsage.h"

// Global variables to store previous system times for CPU usage calculation
static ULONGLONG previousIdle = 0;
static ULONGLONG previousKernel = 0;
static ULONGLONG previousUser = 0;
static bool firstCall = true;

// Calculates the CPU usage percentage based on system times.
double CalculateCpuUsage() {
    FILETIME idleTime, kernelTime, userTime;
    GetSystemTimes(&idleTime, &kernelTime, &userTime);

    ULARGE_INTEGER idle = { {idleTime.dwLowDateTime, idleTime.dwHighDateTime} };
    ULARGE_INTEGER kernel = { {kernelTime.dwLowDateTime, kernelTime.dwHighDateTime} };
    ULARGE_INTEGER user = { {userTime.dwLowDateTime, userTime.dwHighDateTime} };

    if (firstCall) {
        previousIdle = idle.QuadPart;
        previousKernel = kernel.QuadPart;
        previousUser = user.QuadPart;
        firstCall = false;
        return 0.0;
    }

    // Calculate the delta for idle, kernel, and user times since the last measurement
    ULONGLONG idleDelta = idle.QuadPart - previousIdle;
    ULONGLONG kernelDelta = kernel.QuadPart - previousKernel;
    ULONGLONG userDelta = user.QuadPart - previousUser;

    // Total system time is the sum of kernel and user deltas
    ULONGLONG systemDelta = kernelDelta + userDelta;
    double cpuUsage = 0.0;

    // Avoid division by zero and calculate CPU usage percentage
    if (systemDelta > 0) {
        cpuUsage = ((double)(systemDelta - idleDelta) / systemDelta) * 100.0;
    }

    // Update the previous times for the next calculation
    previousIdle = idle.QuadPart;
    previousKernel = kernel.QuadPart;
    previousUser = user.QuadPart;

    // Ensure CPU usage does not exceed 100%
    return cpuUsage > 100.0 ? 100.0 : cpuUsage;
}