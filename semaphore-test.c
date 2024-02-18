#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 10 // Change this to the desired number of iterations

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

void producer(int item) {
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

    // Cleanup: Destroy semaphores before exiting
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    exit(EXIT_SUCCESS);
}

void consumer() {
    while (1) {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = consume();
        printf("Consumed item %d\n", item);

        sem_post(&mutex);
        sem_post(&empty);

        sleep(2); // Simulate some work
    }

    // Cleanup: Destroy semaphores before exiting
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    exit(EXIT_SUCCESS);
}

int main() {
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pid_t producer_pid = fork();
    if (producer_pid < 0) {
        perror("Error creating producer process");
        exit(EXIT_FAILURE);
    } else if (producer_pid == 0) {
        // Child process for producer
        int item = 1;
        producer(item);
    } else {
        // Parent process for consumer
        pid_t consumer_pid = fork();
        if (consumer_pid < 0) {
            perror("Error creating consumer process");
            exit(EXIT_FAILURE);
        } else if (consumer_pid == 0) {
            // Child process for consumer
            consumer();
        } else {
            // Parent process waiting for both producer and consumer to finish
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}
