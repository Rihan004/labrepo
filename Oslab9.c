#include <stdio.h>

int n, nf;             // 'n' for sequence length, 'nf' for number of frames
int in[100];           // Page reference sequence
int frames[50];        // Page frames
int pageFaults = 0;    // Page fault counter

// Function to get data from user
void getData() {
    printf("\nEnter length of page reference sequence: ");
    scanf("%d", &n);
    printf("Enter the page reference sequence: ");
    for (int i = 0; i < n; i++) 
        scanf("%d", &in[i]);
    
    printf("Enter number of frames: ");
    scanf("%d", &nf);
}

// Initialize frames to an empty state
void initialize() {
    pageFaults = 0;
    for (int i = 0; i < nf; i++) 
        frames[i] = -1; // -1 represents an empty frame
}

// Check if a page is in frames and return its index if found
int findPage(int page) {
    for (int i = 0; i < nf; i++) {
        if (frames[i] == page)
            return i;
    }
    return -1;
}

// Display current pages in frames
void displayFrames() {
    for (int i = 0; i < nf; i++) {
        if (frames[i] != -1) 
            printf(" %d", frames[i]);
    }
    printf("\n");
}

// FIFO page replacement algorithm
void fifo() {
    initialize();
    int nextReplace = 0; // Pointer to the next frame to replace

    for (int i = 0; i < n; i++) {
        printf("\nFor %d: ", in[i]);
        if (findPage(in[i]) == -1) { // Page not found (page fault)
            frames[nextReplace] = in[i];
            nextReplace = (nextReplace + 1) % nf; // Move pointer to next frame
            pageFaults++;
            displayFrames();
        } else {
            printf("No page fault. It is Hit \n");
        }
    }
    printf("Total page faults: %d\n", pageFaults);
}

// Optimal page replacement algorithm
void optimal()
{
    initialize();
    for(int i=0; i<n; i++){
        printf("\n for %d " , in[i]);
        if(findPage(in[i]) == -1){
            int replaceindex = -1 , farthest = -1;
            for(int j=0; j<nf; j++){
                int page = frames[j] , distance = 0;
                // Check if the frame is empty
                if (page == -1) {
                    replaceindex = j;
                    break;  // Empty frame found, no need to check further
                } 
                for(int k =i+1; k<n; k++){
                    if(page == in[k]) break;
                    distance++;
                }
                if(distance > farthest){
                    distance = farthest;
                    replaceindex = j;
                }
            }

            frames[replaceindex] = in[i];
            pagefaults++;
            displayFrame();


        }else{
             printf("\nNo page fault. It is page hit\n");
        }
    }

    printf("Total page faults: %d\n", pagefaults);
}

// LRU page replacement algorithm
void lru() {
    initialize();  // Assumes this function sets up frames, in[], nf, n, etc.
    
    for (int i = 0; i < n; i++) {
        printf("\nFor %d: ", in[i]);

        if (findPage(in[i]) == -1) {  // Page not found, so it's a page fault
            int leastRecent = n, replaceIndex = -1;

            // Find the least recently used page or an empty frame
            for (int j = 0; j < nf; j++) {
                int page = frames[j];
                
                // Check if the frame is empty
                if (page == -1) {
                    replaceIndex = j;
                    break;  // Empty frame found, no need to check further
                } 

                // Find the least recent page if all frames are occupied
                for (int k = i - 1; k >= 0; k--) {
                    if (page == in[k]) {
                        if (k < leastRecent) {
                            leastRecent = k;
                            replaceIndex = j;
                        }
                        break;
                    }
                }
            }

            // Replace the page in the identified frame
            if (replaceIndex != -1) {
                frames[replaceIndex] = in[i];
                pageFaults++;
                printf("Page fault occurred. ");
                displayFrames();
            } else {
                printf("Error: No replacement frame found.\n");
            }
        } else {
            // Page is already in memory, no page fault
            printf("No page fault\n");
        }
    }
    printf("Total page faults: %d\n", pageFaults);
}


// Main function with menu for different algorithms
int main() {
    int choice;
    while (1) {
        printf("\nPage Replacement Algorithms\n1. Enter data\n2. FIFO\n3. Optimal\n4. LRU\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            getData();
            break;
        case 2:
            fifo();
            break;
        case 3:
            optimal();
            break;
        case 4:
            lru();
            break;
        case 5:
            return 0;
        default:
            printf("Invalid choice\n");
        }
    }
}
