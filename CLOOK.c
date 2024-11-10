#include <stdio.h>
#include <stdlib.h>

void c_look(int requests[], int n, int head) {
    int total_movement = 0;
    int i, j;

    // Sort the requests to organize them in ascending order
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    // Find the index where the head is initially positioned or closest
    int start_index = 0;
    for (i = 0; i < n; i++) {
        if (requests[i] >= head) {
            start_index = i;
            break;
        }
    }

    printf("Seek sequence: ");

    // Move right from the head's position to the end of the queue
    for (i = start_index; i < n; i++) {
        printf("%d ", requests[i]);
        total_movement += abs(requests[i] - head);
        head = requests[i];
    }

    // Jump back to the beginning of the queue
    for (i = 0; i < start_index; i++) {
        printf("%d ", requests[i]);
        total_movement += abs(requests[i] - head);
        head = requests[i];
    }

    printf("\nTotal head movement: %d\n", total_movement);
}

int main() {
    int n, head;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    c_look(requests, n, head);

    return 0;
}
