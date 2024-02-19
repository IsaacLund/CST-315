#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define BUFFER_SIZE 5

sem_t *empty, *full, *mutex;
int *buffer, in = 0, out = 0;

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
        sem_wait(empty);
        sem_wait(mutex);

        produce(item);
        printf("Produced item %d\n", item);
        item++;

        sem_post(mutex);
        sem_post(full);

        sleep(1); // Simulate some work
    }

    // Cleanup: Destroy semaphores and unmap memory before exiting
    sem_close(empty);
    sem_close(full);
    sem_close(mutex);
    munmap(buffer, BUFFER_SIZE * sizeof(int));
    exit(EXIT_SUCCESS);
}

void consumer() {
    while (1) {
        sem_wait(full);
        sem_wait(mutex);

        int item = consume();
        printf("Consumed item %d\n", item);

        sem_post(mutex);
        sem_post(empty);

        sleep(2); // Simulate some work
    }

    // Cleanup: Destroy semaphores and unmap memory before exiting
    sem_close(empty);
    sem_close(full);
    sem_close(mutex);
    munmap(buffer, BUFFER_SIZE * sizeof(int));
    exit(EXIT_SUCCESS);
}

int main() {
    // Create shared memory for buffer
    buffer = mmap(NULL, BUFFER_SIZE * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (buffer == MAP_FAILED) {
        perror("Error creating shared memory");
        exit(EXIT_FAILURE);
    }

    // Initialize semaphores in shared memory
    empty = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    full = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    mutex = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    sem_init(empty, 1, BUFFER_SIZE);
    sem_init(full, 1, 0);
    sem_init(mutex, 1, 1);

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
