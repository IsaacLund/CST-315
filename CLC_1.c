// CST-315-WF900
// Author: Isaac Lund
// Group: A5
// Date: 01/20-27/2024

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

# define stockSize 1000

int stock = -1, inp_array[stockSize];
int theProduce;
int produce() 
{
  return theProduce++;
}
void *producer(void *ptr)
{
  int i;
  while(1) {
    i = produce();
    put(i);
  }
}

void consume(int i)
{
  printf("They wanted %i now there is %i produce left.\n", i, stock);
}
void *consumer(void *ptr)
{
  int i;
  while(1) {
    i = get(i);
  }
}

void put(int p) 
{
  if (stock < stockSize) {
    for (int i = 0; i < stock; i++) {
      stock = stock + 1;
      inp_array[stock] = 1;
    }
    printf("They stocked %i produce, now have %i Stocked.\n", p, stock);
  } else {
    printf("Full Stock.\n");
    pthread_join(producer, NULL);
    sleep(100);
  }
}

int get(int i)
{
  if (stock >= i){
      for (int i = 0; i < stock; i++) {
        stock = stock - 1;
      }
      consume(i);
  } else {
    printf("Out of Stock.\n");
    pthread_join(consumer, NULL);
    sleep(150);
  }
  return stock;
}

int main()
{
  pthread_t id_1;
  pthread_t id_2;
  pthread_create(&id_1, NULL, producer, "pro");
  pthread_create(&id_2, NULL, consumer, "con");
  return 0;
}
