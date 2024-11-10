// server.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// Define a shared memory structure
struct shared_data {
    char message[100];   // Buffer to store the message
    int ready_flag;      // Flag to indicate the status of the message
};

int main() {
    key_t key = ftok("abc.txt", 'A');  // Generate unique key for shared memory
    int shmid = shmget(key, sizeof(struct shared_data), 0666 | IPC_CREAT);  // Create shared memory segment
    struct shared_data *shared_mem = (struct shared_data *)shmat(shmid, NULL, 0);  // Attach shared memory

    printf("Enter a message: ");
    fgets(shared_mem->message, sizeof(shared_mem->message), stdin);  // Read message into shared memory
    shared_mem->ready_flag = 1;  // Set flag to indicate message is ready

    while (shared_mem->ready_flag != -1) {  // Wait for client to acknowledge the message
        sleep(1);
    }

    // Detach and delete the shared memory segment
    shmdt(shared_mem);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

// client.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// Define a shared memory structure
struct shared_data {
    char message[100];  // Buffer to store the message
    int ready_flag;     // Flag to indicate the status of the message
};

int main() {
    key_t key = ftok("abc.txt", 'A');  // Generate unique key for shared memory
    int shmid = shmget(key, sizeof(struct shared_data), 0666 | IPC_CREAT);  // Access shared memory segment
    struct shared_data *shared_mem = (struct shared_data *)shmat(shmid, NULL, 0);  // Attach shared memory

    while (shared_mem->ready_flag != 1) {  // Wait until server sets the flag
        sleep(1);
    }

    printf("Received message: %s", shared_mem->message);  //  Print received message
    shared_mem->ready_flag = -1;  // Set flag to indicate message has been read

    // Detach shared memory
    shmdt(shared_mem);

    return 0;
}
