#include<stdio.h>
#define MAX_PROCESSES 10

int main() {
    int n, i;
    int burst_time[MAX_PROCESSES], remaining_time[MAX_PROCESSES];
    int process_order[MAX_PROCESSES], waiting_time[MAX_PROCESSES] = {0}, turnaround_time[MAX_PROCESSES] = {0};
    int arrival_time[MAX_PROCESSES];
    int current_time = 0;
    int complete = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        remaining_time[i] = burst_time[i];  // Initialize remaining time with burst time
        process_order[i] = i + 1;
    }

    printf("Enter arrival times for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Arrival time for process %d: ", i + 1);
        scanf("%d", &arrival_time[i]);
    }

    int total_waiting_time = 0, total_turnaround_time = 0;
    
    while (complete < n) {
        int shortest_job = -1;
        int shortest_time = 9999;

        // Find the process with the shortest remaining time that has already arrived
        for (i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && remaining_time[i] > 0 && remaining_time[i] < shortest_time) {
                shortest_job = i;
                shortest_time = remaining_time[i];
            }
        }

        if (shortest_job == -1) {
            // If no process is ready to execute, increment the current time
            current_time++;
        } else {
            // Process the shortest remaining job
            remaining_time[shortest_job]--;
            current_time++;

            // If the process finishes, calculate its waiting and turnaround times
            if (remaining_time[shortest_job] == 0) {
                complete++;  // Increment completed processes

                int finish_time = current_time;
                waiting_time[shortest_job] = finish_time - arrival_time[shortest_job] - burst_time[shortest_job];

                if (waiting_time[shortest_job] < 0) {
                    waiting_time[shortest_job] = 0;  // Avoid negative waiting times
                }

                turnaround_time[shortest_job] = burst_time[shortest_job] + waiting_time[shortest_job];
                
                total_waiting_time += waiting_time[shortest_job];
                total_turnaround_time += turnaround_time[shortest_job];
            }
        }
    }

    // Calculate average waiting time and turnaround time
    double avg_waiting_time = (double) total_waiting_time / n;
    double avg_turnaround_time = (double) total_turnaround_time / n;

    // Print process details
    printf("\n\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", process_order[i], burst_time[i],
               arrival_time[i], waiting_time[i], turnaround_time[i]);
    }

    // Print average times
    printf("\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f", avg_turnaround_time);

    return 0;
}
