// CST-315-WF900
// Author: Isaac Lund
// Group: A5
// Date: 01/20-27/2024

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define stockSize 1000

void put(int p);
int get(int i);
void consume(int i);

pthread_mutex_t lock;

int stock = -1, inp_array[stockSize];
int theProduce;

void *producer(void *ptr)
{
  int i;
  while(1) {
    i = produce();
    put(i);
    sleep(1);
  }
}

void *consumer(void *ptr)
{
  int i;
  while(1) {
    i = rand() % (theProduce + 1);
    get(i);
    sleep(2);
  }
}

int produce() 
{
  return theProduce++;
}

void put(int p) 
{
  pthread_mutex_lock(&lock);
  
  if (stock < stockSize) {
    stock = stock + 1;
    inp_array[stock] = 1;
    printf("They stocked %i produce, now have %i Stocked.\n", p, stock);
  } else {
    printf("Full Stock.\n");
    sleep(10);
  }
  
  pthread_mutex_unlock(&lock);
}

void get(int i)
{
  pthread_mutex_lock(&lock);
  
  if (stock >= i) {
      stock = stock - 1;
      consume(i);
  } else {
    printf("Out of Stock.\n");
    sleep(10);
  }
  
  pthread_mutex_unlock(&lock);
}

void consume(int i)
{
  printf("They wanted %i now there is %i produce left.\n", i, stock);
}

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
  
  sleep(200);
  pthread_cancel(id_1);
  pthread_cancel(id_2);
  
  pthread_mutex_destroy(&lock);
  
  return 0;
}
