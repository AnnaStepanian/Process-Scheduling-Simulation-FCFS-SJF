#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    int completion_time;
} Process;

void fcfs_scheduling(Process processes[], int n);
void sjf_scheduling(Process processes[], int n);
void print_gantt_chart(Process processes[], int n);
void print_gantt_chart_sjf(Process processes[], int execution_order[], int n);
void print_process_table(Process processes[], int n);
void calculate_averages(Process processes[], int n);
void sort_by_arrival_time(Process processes[], int n);
void sort_by_burst_time(Process processes[], int n);
void copy_processes(Process source[], Process destination[], int n);

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    Process *processes = (Process*)malloc(n * sizeof(Process));
    Process *fcfs_processes = (Process*)malloc(n * sizeof(Process));
    Process *sjf_processes = (Process*)malloc(n * sizeof(Process));
    
    printf("\nEnter process details:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("  Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("  Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].pid = i + 1;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
        processes[i].response_time = 0;
        processes[i].completion_time = 0;
    }
    
    copy_processes(processes, fcfs_processes, n);
    copy_processes(processes, sjf_processes, n);
    
    printf("\n");
    fcfs_scheduling(fcfs_processes, n);
    
    printf("\n");
    sjf_scheduling(sjf_processes, n);
    
    free(processes);
    free(fcfs_processes);
    free(sjf_processes);
    
    return 0;
}

void fcfs_scheduling(Process processes[], int n) {
    printf("=== First Come First Served (FCFS) ===\n");
    
    sort_by_arrival_time(processes, n);
    
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        
        processes[i].response_time = processes[i].waiting_time;
        
        processes[i].completion_time = current_time + processes[i].burst_time;
        
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        
        current_time = processes[i].completion_time;
    }
    
    print_gantt_chart(processes, n);
    print_process_table(processes, n);
    calculate_averages(processes, n);
}

void sjf_scheduling(Process processes[], int n) {
    printf("=== Shortest Job First (SJF) ===\n");
    
    int *execution_order = (int*)malloc(n * sizeof(int));
    int *processed = (int*)calloc(n, sizeof(int));
    int current_time = 0;
    int execution_index = 0;
    
    for (int completed = 0; completed < n; completed++) {
        int next_process = -1;
        int min_burst = 999999;
        int earliest_arrival = 999999;
        
        for (int i = 0; i < n; i++) {
            if (!processed[i] && processes[i].arrival_time <= current_time) {
                if (processes[i].burst_time < min_burst || 
                    (processes[i].burst_time == min_burst && processes[i].arrival_time < earliest_arrival)) {
                    min_burst = processes[i].burst_time;
                    earliest_arrival = processes[i].arrival_time;
                    next_process = i;
                }
            }
        }
        
        if (next_process == -1) {
            int earliest_time = 999999;
            for (int i = 0; i < n; i++) {
                if (!processed[i] && processes[i].arrival_time < earliest_time) {
                    earliest_time = processes[i].arrival_time;
                    next_process = i;
                }
            }
        }
        
        execution_order[execution_index++] = next_process;
        
        if (current_time < processes[next_process].arrival_time) {
            current_time = processes[next_process].arrival_time;
        }
        
        processes[next_process].waiting_time = current_time - processes[next_process].arrival_time;
        
        processes[next_process].response_time = processes[next_process].waiting_time;
        
        processes[next_process].completion_time = current_time + processes[next_process].burst_time;
        
        processes[next_process].turnaround_time = processes[next_process].completion_time - processes[next_process].arrival_time;
        
        current_time = processes[next_process].completion_time;
        processed[next_process] = 1;
    }
    
    print_gantt_chart_sjf(processes, execution_order, n);
    print_process_table(processes, n);
    calculate_averages(processes, n);
    
    free(processed);
    free(execution_order);
}

void print_gantt_chart(Process processes[], int n) {
    printf("\nGantt Chart:\n");
    printf("|");
    for (int i = 0; i < n; i++) {
        printf(" P%d |", processes[i].pid);
    }
    printf("\n");
}

void print_gantt_chart_sjf(Process processes[], int execution_order[], int n) {
    printf("\nGantt Chart:\n");
    printf("|");
    for (int i = 0; i < n; i++) {
        printf(" P%d |", processes[execution_order[i]].pid);
    }
    printf("\n");
}

void print_process_table(Process processes[], int n) {
    printf("\nProcess Details:\n");
    printf("PID\tAT\tBT\tWT\tTAT\tRT\n");
    printf("---\t---\t---\t---\t---\t---\n");
    
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", 
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].waiting_time,
               processes[i].turnaround_time,
               processes[i].response_time);
    }
}

void calculate_averages(Process processes[], int n) {
    double avg_waiting = 0, avg_turnaround = 0, avg_response = 0;
    
    for (int i = 0; i < n; i++) {
        avg_waiting += processes[i].waiting_time;
        avg_turnaround += processes[i].turnaround_time;
        avg_response += processes[i].response_time;
    }
    
    avg_waiting /= n;
    avg_turnaround /= n;
    avg_response /= n;
    
    printf("\nAverage Performance Times:\n");
    printf("Average Waiting Time: %.2f\n", avg_waiting);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround);
    printf("Average Response Time: %.2f\n", avg_response);
}

void sort_by_arrival_time(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void sort_by_burst_time(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time ||
                (processes[j].burst_time == processes[j + 1].burst_time && 
                 processes[j].arrival_time > processes[j + 1].arrival_time)) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void copy_processes(Process source[], Process destination[], int n) {
    for (int i = 0; i < n; i++) {
        destination[i] = source[i];
    }
}
