#include <stdio.h>
#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int n, m; // Number of processes and resources
    int i, j, k;

    // Input the number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int max[MAX_PROCESSES][MAX_RESOURCES];     // Maximum demand of each process
    int allocation[MAX_PROCESSES][MAX_RESOURCES]; // Amount currently allocated
    int need[MAX_PROCESSES][MAX_RESOURCES];    // Remaining need of each process
    int available[MAX_RESOURCES];              // Available amount of each resource

    // Input the Allocation Matrix
    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    // Input the Maximum Matrix
    printf("Enter the Maximum Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    // Input the Available resources
    printf("Enter the Available resources:\n");
    for (j = 0; j < m; j++)
        scanf("%d", &available[j]);

    // Calculate the Need matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // Banker's Algorithm
    int finish[MAX_PROCESSES] = {0}; // To track completed processes
    int safeSequence[MAX_PROCESSES]; // To store the safe sequence
    int work[MAX_RESOURCES];
    
    // Initialize work = available
    for (i = 0; i < m; i++)
        work[i] = available[i];

    int count = 0;
    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) { // Process not yet completed
                int canAllocate = 1;
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j]) {
                        canAllocate = 0;
                        break;
                    }

                if (canAllocate) {
                    // Allocate resources to this process
                    for (k = 0; k < m; k++)
                        work[k] += allocation[i][k];

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) { // No process can proceed safely
            printf("The system is in an unsafe state.\n");
            return 1;
        }
    }

    // If safe sequence is found
    printf("The system is in a safe state.\nSafe sequence is: ");
    for (i = 0; i < n; i++)
        printf("P%d ", safeSequence[i]);
    printf("\n");

    return 0;
}
