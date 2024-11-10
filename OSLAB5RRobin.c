#include <stdio.h>
#define MAX_PROCESSES 10

int main() {
    int n, i, time_quantum;
    int burst_time[MAX_PROCESSES], remaining_time[MAX_PROCESSES];
    int arrival_time[MAX_PROCESSES], waiting_time[MAX_PROCESSES] = {0}, turnaround_time[MAX_PROCESSES] = {0};
    int current_time = 0, complete = 0;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Arrival time for process %d: ", i + 1);
        scanf("%d", &arrival_time[i]);
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        remaining_time[i] = burst_time[i];  // Initialize remaining time with burst time
    }

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    int total_waiting_time = 0, total_turnaround_time = 0;
    
    while (complete < n) {
        int all_done = 1;
        
        // Iterate through all processes in a round-robin fashion
        for (i = 0; i < n; i++) {
            if (remaining_time[i] > 0 && arrival_time[i] <= current_time) {
                all_done = 0;

                if (remaining_time[i] > time_quantum) {
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                } else {
                    current_time += remaining_time[i];
                    waiting_time[i] = current_time - arrival_time[i] - burst_time[i];
                    turnaround_time[i] = current_time - arrival_time[i];
                    
                    total_waiting_time += waiting_time[i];
                    total_turnaround_time += turnaround_time[i];
                    
                    remaining_time[i] = 0;
                    complete++;
                }
            }
        }

        if (all_done) {
            current_time++;
        }
    }

    // Calculate average waiting time and turnaround time
    double avg_waiting_time = (double)total_waiting_time / n;
    double avg_turnaround_time = (double)total_turnaround_time / n;

    // Print process details
    printf("\n\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i],
               arrival_time[i], waiting_time[i], turnaround_time[i]);
    }

    // Print average times
    printf("\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f", avg_turnaround_time);

    return 0;
}
