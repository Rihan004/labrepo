//server.c
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *fifo_path = "/tmp/myfifo";  // Path to the FIFO file
    mkfifo(fifo_path, 0666);                // Create the FIFO with read/write permissions

    char received_msg[80];                  // Buffer to store the received message

    while (1) {
        int fifo_fd = open(fifo_path, O_RDONLY);   // Open the FIFO for reading
        read(fifo_fd, received_msg, sizeof(received_msg));  // Read message from FIFO
        printf("Received: %s\n", received_msg);    // Print the message
        close(fifo_fd);                            // Close the FIFO
    }

    return 0;
}


// client.c
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *fifo_path = "/tmp/myfifo";  // Path to the FIFO file

    char send_msg[80];                      // Buffer to store the message to send
    printf("\n Enter Your Messages : ");
    while (1) {
        int fifo_fd = open(fifo_path, O_WRONLY);   // Open the FIFO for writing
        fgets(send_msg, sizeof(send_msg), stdin);  // Get input from the user
        write(fifo_fd, send_msg, strlen(send_msg) + 1);  // Write the message to FIFO
        close(fifo_fd);                            // Close the FIFO
    }

    return 0;
}



/*
gcc server.c -o server
gcc client.c -o client

*/