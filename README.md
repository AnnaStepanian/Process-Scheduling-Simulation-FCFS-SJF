# Process Scheduling Simulator

A C program that simulates two CPU scheduling algorithms: First Come First Served (FCFS) and Shortest Job First (SJF).

## Features

- **Process Structure**: Implements a comprehensive process data structure with PID, arrival time, burst time, turnaround time, waiting time, and response time.
- **FCFS Algorithm**: Schedules processes in the order they arrive.
- **SJF Algorithm**: Schedules processes based on shortest burst time (non-preemptive).
- **Gantt Charts**: Visual representation of process execution order.
- **Performance Metrics**: Calculates and displays waiting time, turnaround time, and response time for each process.
- **Average Statistics**: Computes average waiting time, turnaround time, and response time.

## Compilation

```bash
make
```

Or manually:
```bash
gcc -Wall -Wextra -std=c99 -g -o process_scheduler process_scheduler.c
```

## Usage

```bash
./process_scheduler
```

The program will prompt you to enter:
1. Number of processes
2. For each process: arrival time and burst time

## Example

Input:
```
4
0 8
1 4
2 9
3 5
```

This creates 4 processes:
- Process 1: Arrives at time 0, needs 8 time units
- Process 2: Arrives at time 1, needs 4 time units  
- Process 3: Arrives at time 2, needs 9 time units
- Process 4: Arrives at time 3, needs 5 time units

## Output

The program displays:
- Gantt chart showing execution order
- Process details table with all metrics
- Average performance statistics

For both FCFS and SJF algorithms.

## Algorithm Details

### FCFS (First Come First Served)
- Processes are executed in the order they arrive
- No preemption
- Simple but may not be optimal for average waiting time

### SJF (Shortest Job First) - Non-preemptive
- Processes are executed in order of shortest burst time
- Among processes with same burst time, earlier arrival time is chosen
- Generally provides better average waiting time than FCFS
- Non-preemptive: once a process starts, it runs to completion

## Quick Start

### Option 1: Automated Installation
```bash
chmod +x install.sh
./install.sh
```

### Option 2: Manual Setup
```bash
make
./process_scheduler
```

### Option 3: Run Tests
```bash
chmod +x run_tests.sh
./run_tests.sh
```

## Testing

The project includes comprehensive testing scripts:

### Automated Test Suite
```bash
./run_tests.sh
```
Runs multiple test cases including:
- Basic test case with 4 processes
- All processes arriving at the same time
- Processes arriving at different times

### Individual Test
```bash
chmod +x test.sh
./test.sh
```
Runs a single test case with sample input.

### Using Input File
```bash
make
./process_scheduler < input.txt
```
The `input.txt` file contains a sample test case.

## File Structure

- `process_scheduler.c` - Main program source code
- `Makefile` - Build configuration
- `install.sh` - Automated installation script
- `run_tests.sh` - Comprehensive test suite
- `test.sh` - Simple test script
- `input.txt` - Sample input file
- `README.md` - This documentation

## Requirements

- C compiler (gcc recommended)
- Linux/Unix/macOS environment
- Make (optional, for easy compilation)
- Bash (for running test scripts)


