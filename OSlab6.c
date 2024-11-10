#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

sem_t emptySlots, filledSlots, mutex;
int buffer[5];
int insertIndex = 0, removeIndex = 0;

void* producer(void* arg) {
   sem_wait(&emptySlots);         // Wait for empty slot
   sem_wait(&mutex);               // Enter critical section
   int product = rand();           // Generate product
   buffer[insertIndex] = product;  // Insert product into buffer
   printf("\nProduct %d produced by thread %lu\n", product, pthread_self());
   insertIndex = (insertIndex + 1) % 5;
   sem_post(&mutex);               // Exit critical section
   sem_post(&filledSlots);         // Signal filled slot
   sleep(1);
   return NULL;
}

void* consumer(void* arg) {
  for (int i = 0; i < 5; i++) {    // Consume exactly 5 products
     sem_wait(&filledSlots);       // Wait for filled slot
     sem_wait(&mutex);             // Enter critical section
     int product = buffer[removeIndex];  // Remove product from buffer
     printf("\nProduct %d consumed by thread %lu\n", product, pthread_self());
     removeIndex = (removeIndex + 1) % 5;
     sem_post(&mutex);             // Exit critical section
     sem_post(&emptySlots);        // Signal empty slot
     sleep(1);
  }
  return NULL;
}

int main() {
   pthread_t producerThreads[5], consumerThread;

   sem_init(&filledSlots, 0, 0);   // Initialize filled slots to 0
   sem_init(&emptySlots, 0, 5);    // Initialize empty slots to buffer size
   sem_init(&mutex, 0, 1);         // Initialize mutex

   for (int i = 0; i < 5; i++) {
      pthread_create(&producerThreads[i], NULL, producer, NULL);
   }

   pthread_create(&consumerThread, NULL, consumer, NULL);

   for (int i = 0; i < 5; i++) {
      pthread_join(producerThreads[i], NULL);
   }
   pthread_join(consumerThread, NULL);

   sem_destroy(&filledSlots);
   sem_destroy(&emptySlots);
   sem_destroy(&mutex);

   return 0;
}
