#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 5

sem_t empty, full, mutex;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void produce(int item) {
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
}

int consume() {
    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    return item;
}

const char* producer() {
    int item = 1;

    while (1) {
        sem_wait(&empty);
        sem_wait(&mutex);

        produce(item);
        printf("Produced item %d\n", item);
        item++;

        sem_post(&mutex);
        sem_post(&full);

        sleep(1); // Simulate some work
    }
}

const char* consumer() {
    while (1) {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = consume();
        printf("Consumed item %d\n", item);

        sem_post(&mutex);
        sem_post(&empty);

        sleep(2); // Simulate some work
    }
}

int main() {
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // Create producer and consumer threads
    sem_open(*producer, O_CREAT, mode_t 2, int value);
    sem_open(*consumer, O_CREAT, mode_t 2, int value);
    //consumer(NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
