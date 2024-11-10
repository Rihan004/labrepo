#include <stdio.h>
#include <stdlib.h>

int main() {
    int RQ[100], i, n, totalMovement = 0, initial, size, direction;
    
    // Input number of requests
    printf("Enter number of requests: ");
    scanf("%d", &n);
    
    // Input the requests sequence
    printf("Enter the request sequence: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &RQ[i]);
    }
    
    // Input the initial head position
    printf("Enter initial head position: ");
    scanf("%d", &initial);
    
    // Input the disk size
    printf("Enter total disk size: ");
    scanf("%d", &size);
    
    // Input the head movement direction (1 for high, 0 for low)
    printf("Enter head movement direction (1 for high, 0 for low): ");
    scanf("%d", &direction);

    // Sort the request array in ascending order
    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (RQ[j] > RQ[j + 1]) {
                int temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }
    
    // Find the index where the request is greater than the initial position
    int startIndex = 0;
    for (i = 0; i < n; i++) {
        if (RQ[i] > initial) {
            startIndex = i;
            break;
        }
    }

    // Move the head according to the chosen direction
    if (direction == 1) {  // Moving towards high
        for (i = startIndex; i < n; i++) {  // Move right (high direction)
            totalMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        totalMovement += abs(size - 1 - initial);  // Move to the end of the disk
        initial = size - 1; 
        for (i = startIndex - 1; i >= 0; i--) {  // Move left (low direction)
            totalMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    } else {  // Moving towards low
        for (i = startIndex - 1; i >= 0; i--) {  // Move left (low direction)
            totalMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        totalMovement += abs(initial);  // Move to the start of the disk
        initial = 0;
        for (i = startIndex; i < n; i++) {  // Move right (high direction)
            totalMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }
    
    // Output the total head movement
    printf("Total head movement is %d\n", totalMovement);
    
    return 0;
}
