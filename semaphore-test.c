#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>

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

void producer() {
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
}

int main() {
    sem_init(&empty, 1, BUFFER_SIZE);  // Set initial value to 1
    sem_init(&full, 1, 0);             // Set initial value to 0
    sem_init(&mutex, 1, 1);            // Set initial value to 1

    // Create producer process
    pid_t producer_pid = fork();

    if (producer_pid < 0) {
        perror("Error creating producer process");
        exit(EXIT_FAILURE);
    } else if (producer_pid == 0) {
        // Child process (producer)
        producer();
        exit(EXIT_SUCCESS);
    }

    // Create consumer process
    pid_t consumer_pid = fork();

    if (consumer_pid < 0) {
        perror("Error creating consumer process");
        exit(EXIT_FAILURE);
    } else if (consumer_pid == 0) {
        // Child process (consumer)
        consumer();
        exit(EXIT_SUCCESS);
    }

    // Wait for both processes to finish
    waitpid(producer_pid, NULL, 0);
    waitpid(consumer_pid, NULL, 0);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
