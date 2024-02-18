#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 5

sem_t* empty;
sem_t* full;
sem_t* mutex;
int* buffer;
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
        sem_wait(empty);
        sem_wait(mutex);

        produce(item);
        printf("Produced item %d\n", item);
        item++;

        sem_post(mutex);
        sem_post(full);

        sleep(1); // Simulate some work
    }
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
}

int main() {
    empty = sem_open("/empty", O_CREAT, 0666, BUFFER_SIZE);
    full = sem_open("/full", O_CREAT, 0666, 0);
    mutex = sem_open("/mutex", O_CREAT, 0666, 1);

    // Create shared memory for buffer
    int shm_id = shmget(IPC_PRIVATE, BUFFER_SIZE * sizeof(int), IPC_CREAT | 0666);
    buffer = (int*)shmat(shm_id, NULL, 0);

    pid_t producer_pid = fork();

    if (producer_pid == 0) {
        // Child process (producer)
        producer();
    } else if (producer_pid > 0) {
        // Parent process (consumer)
        consumer();
        wait(NULL); // Wait for the producer to finish
    } else {
        perror("Fork failed");
        return 1;
    }

    // Cleanup
    sem_unlink("/empty");
    sem_unlink("/full");
    sem_unlink("/mutex");
    sem_close(empty);
    sem_close(full);
    sem_close(mutex);
    shmdt(buffer);
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}
