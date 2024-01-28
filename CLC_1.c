// CST-315-WF900
// Author: Isaac Lund
// Group: A5
// Date: 01/20-27/2024

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

// defines the stack size.
#define stockSize 100

// initializes the functions that push and pop from the stack, and a print function and increment of produce function.
void put(int p);
void get(int i);
void consume(int i);
int produce(void);

// creates a global lock for the threads to share protection.
pthread_mutex_t lock;

// initializes the stack at 0 to 100 because of definition  and set theProduce variable to 1.
int stock = 0, inp_array[stockSize];
int theProduce = 1;

// creates the thread function for adding to the stack with the value of produce function at 1 second intervals.
void *producer(void *ptr)
{
  int i;
  while(1) {
    i = produce();
    put(i);
    sleep(1);
  }
}

// creates the thread function for removing from the stack with a rand number from 0 up to what was added to the stack plus 5 at 1 second intervals.
void *consumer(void *ptr)
{
  int i;
  while(1) {
    i = rand() % (theProduce + 5);
    get(i);
    sleep(1);
  }
}

// This increments the value of theProduce variable and returns it to be used 
int produce() 
{
  return theProduce++;
}

// This takes the given produce amount and adds to the stack the number of produce amount, if does not exceed max stack size, then sets the theProduce variable value randomly between current 0 to add produce amount plus 5.
// Prints a message depending on if it produce add to stacks or not.
void put(int p) 
{
  pthread_mutex_lock(&lock);
  
  if ((stock+p) < stockSize) {
    for (int i = 0; i < p; i++) {
      stock = stock + 1;
      inp_array[stock] = 1;
    }
    theProduce = rand() % (p+5);
    printf("They stocked %i produce, now have %i Stocked.\n", p, stock);
  } else {
    printf("Full Stock.\n");
    //sleep(10);
  }
  
  pthread_mutex_unlock(&lock);
}

// This removes from the stack as many as the consumer amount unless it put the stack into the negative.
// Prints or calls a function with a message depending on if it consume removed from stack or not.
void get(int i)
{
  pthread_mutex_lock(&lock);
  
  if (stock >= i) {
    for (int c = 0; c < i; c++) {
    stock = stock - 1;
    }
    consume(i);
  } else {
    printf("Out of Stock.\n");
    //sleep(10);
  }
  
  pthread_mutex_unlock(&lock);
}

// Prints how many were consumed and how many are left in stack.
void consume(int i)
{
  printf("They wanted %i now there is %i produce left.\n", i, stock);
}

// This sets up the threads and their locks, random number generator, breaks out of the infinite loop after 200 second by canceling the threads and then destroys the lock of the leads.
int main()
{
  pthread_mutex_init(&lock, NULL);
  
  srand(time(NULL));
  
  pthread_t id_1;
  pthread_t id_2;
  pthread_create(&id_1, NULL, producer, NULL);
  pthread_create(&id_2, NULL, consumer, NULL);
  
  pthread_join(id_1, NULL);
  pthread_join(id_2, NULL);
  
  // this as of the moment does not work at all. So you will have to use crtl+C to end the program on terminal.
  sleep(200);
  pthread_cancel(id_1);
  pthread_cancel(id_2);
  
  pthread_mutex_destroy(&lock);
  
  return 0;
}
