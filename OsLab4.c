// Parent Program

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void bubbleSort(int *array, int size) {
    int temp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main() {
    int numElements;
    printf("Enter the number of elements: ");
    scanf("%d", &numElements);

    int array[numElements];
    printf("Enter the elements:\n");
    for (int i = 0; i < numElements; i++) {
        scanf("%d", &array[i]);
    }

    bubbleSort(array, numElements);

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork Failed\n");
        return 1;
    } else if (pid == 0) {
        char *args[numElements + 2];
        args[0] = "./childProgram"; // Path to child program

        for (int i = 0; i < numElements; i++) {
            args[i + 1] = malloc(10);  // Allocate memory for each argument
            sprintf(args[i + 1], "%d", array[i]);
        }

        args[numElements + 1] = NULL;

        execve(args[0], args, NULL);

        perror("execve failed");  // Handle execve failure
        return 1;
    } else { 
        wait(NULL);
        printf("Child process completed.\n");
    }

    return 0;
}



// Child Program

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("Array in reverse order:\n");
    for (int i = argc - 1; i > 0; i--) {
        printf("%s ", argv[i]);
    }
    printf("\n");
    return 0;
}


/*
gcc -o parentProgram parent.c
gcc -o childProgram child.c

*/