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

sem_t * producer(int item) {
   // while (1) {
        sem_wait(&empty);
        sem_wait(&mutex);

        produce(item);
        printf("Produced item %d\n", item);
        item++;

        sem_post(&mutex);
        sem_post(&full);

        sleep(1); // Simulate some work
   // }
}

sem_t * consumer() {
    //while (1) {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = consume();
        printf("Consumed item %d\n", item);

        sem_post(&mutex);
        sem_post(&empty);

        sleep(2); // Simulate some work
    //}
}

int main() {
    sem_init(&empty, 0, BUFFER_SIZE);  // Set initial value to 1
    sem_init(&full, 0, 0);             // Set initial value to 0
    sem_init(&mutex, 0, 1);            // Set initial value to 1

    // Create producer process
    pid_t pid = fork();
    while (1) {
        if (pid < 0) {
            perror("Error creating producer process");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            //Process for producer
            int item = 1;
            sem_init(&producer(item),1, 0);
            exit(EXIT_SUCCESS);
        } else {
          //Process for consumer
            sem_init(&consumer,2, 0);
            exit(EXIT_SUCCESS);
        }
    }
    
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
