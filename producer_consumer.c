#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10
#define NUM_ITEMS 20

int buffer[BUFFER_SIZE];
int fill = 0; // Index to add data by producer
int use = 0; // Index to consume data by consumer
int count = 0; // Number of items in the buffer

sem_t empty; // Semaphore to track empty slots in the buffer
sem_t full; // Semaphore to track the number of items available for consumption

void put(int value) {
    buffer[fill] = value;
    fill = (fill + 1) % BUFFER_SIZE;
    count++;
}

int get() {
    int tmp = buffer[use];
    use = (use + 1) % BUFFER_SIZE;
    count--;
    return tmp;
}

void *producer(void *arg) {
    int i;
    for (i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&empty); // Wait for an empty slot
        put(i);
        printf("Produced: %d\n", i);
        sem_post(&full); // Signal that an item is produced
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int i;
    for (i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full); // Wait for an item to be produced
        int value = get();
        printf("Consumed: %d\n", value);
        sem_post(&empty); // Signal that an empty slot is available
    }
    pthread_exit(NULL);
}

int main() {
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // Set empty slots to BUFFER_SIZE
    sem_init(&full, 0, 0); // No items available initially

    pthread_t producer_thread, consumer_thread;

    // Create threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

