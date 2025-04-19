# MiniSysMonitor

## Introduction
MiniSysMonitor is a lightweight C++ desktop application that displays the current time, CPU load, and RAM usage in a transparent always-on-top overlay window using the Windows API.

---

## Prerequisites  
- **Visual Studio 2022** (Desktop development with C++)
- **Windows 10 or higher**
- No external libraries or dependencies required

---

## Building
1. **Clone the repository**
2. **Open** `MiniSysMonitor.sln` in Visual Studio 2022
3. **Select** desired configuration (e.g., `Release` x64)
4. **Build** the solution

---

## Usage
1. Run the compiled `MiniSysMonitor.exe`
2. A small overlay window will appear in the top-right corner showing:
   - Current system time (`HH:MM:SS`)
   - CPU usage (percentage)
   - RAM usage (used/total in GB)
3. **Drag** the window anywhere on screen using the mouse
4. The overlay updates automatically every second
