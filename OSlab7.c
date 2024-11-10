#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>

sem_t readerMutex;  // Controls access to readerCount
sem_t resourceMutex;  // Controls access to the resource for writing
int readerCount = 0;  // Number of active readers

void* reader(void* arg) {
    sem_wait(&readerMutex);  // Lock readerMutex to update readerCount safely
    readerCount++;
    
    if (readerCount == 1) {  // First reader locks the resource for reading
        sem_wait(&resourceMutex);
    }
    
    sem_post(&readerMutex);  // Release readerMutex after updating readerCount

    printf("\nReading operation performed");

    sem_wait(&readerMutex);  // Lock readerMutex to safely update readerCount
    readerCount--;
    
    if (readerCount == 0) {  // Last reader unlocks the resource for writing
        sem_post(&resourceMutex);
    }
    
    sem_post(&readerMutex);  // Release readerMutex after updating readerCount
    return NULL;
}

void* writer(void* arg) {
    sem_wait(&resourceMutex);  // Lock resource for exclusive writing
    printf("\nWriting operation performed");
    sem_post(&resourceMutex);  // Release resource after writing
    return NULL;
}

int main() {
    pthread_t readerThreads[5];
    pthread_t writerThreads[5];
    
    sem_init(&readerMutex, 0, 1);
    sem_init(&resourceMutex, 0, 1);
    
    for (int i = 0; i < 5; i++) {
        pthread_create(&writerThreads[i], NULL, writer, NULL);
        pthread_create(&readerThreads[i], NULL, reader, NULL);
    }
    
    for (int i = 0; i < 5; i++) {
        pthread_join(readerThreads[i], NULL);
        pthread_join(writerThreads[i], NULL);
    }

    sem_destroy(&readerMutex);
    sem_destroy(&resourceMutex);

    return 0;
}
