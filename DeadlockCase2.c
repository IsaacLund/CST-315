// Second deadlock scenario. Two mutexes are used, read_mutex and write_mutex. 
// To gain access to the file both these mutexes have to be locked. In the code, 
// the write thread locks write_mutex and then after a little delay tries to locks read_mutex. 
// The read thread on the other hand locks read_mutex first and then tries to 
// lock write_mutex. Thus by the time the write tries to access read_mutex, it has already 
// been locked by read thread and by the time read thread tries to lock write_mutex, it has already 
// been locked by the write thread. Both the threads end up waiting infinitely for each other to 
// unlock the mutexes and process ends up in a deadlock. 

#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include<unistd.h>

pthread_mutex_t read_mutex;
pthread_mutex_t write_mutex;

void *write_th(void *ptr) 
{
  char *ret;
  FILE *file1;
  char *str;
  pthread_mutex_lock(&write_mutex);
  sleep(5);
  pthread_mutex_lock(&read_mutex);
  printf("\nFile locked, please enter the message \n");
  str=(char *)malloc(10*sizeof(char));
  file1=fopen("temp","w");
  scanf("%s",str);
  fprintf(file1,"%s",str);
  fclose(file1);
  pthread_mutex_unlock(&read_mutex);
  pthread_mutex_unlock(&write_mutex);
  printf("\nUnlocked the file you can read it now \n");
  //return ret;
}


void *read_th(void *ptr) 
{
  char *ret;
  FILE *file1;
  char *str;
  pthread_mutex_lock(&read_mutex);
  sleep(5);
  pthread_mutex_lock(&write_mutex);
  printf("\n Opening file \n");
  file1=fopen("temp","r");
  str=(char *)malloc(10*sizeof(char));
  fscanf(file1,"%s",str);
  printf("\n Message from file is %s \n",str);

  fclose(file1);

  pthread_mutex_unlock(&write_mutex);
  pthread_mutex_unlock(&read_mutex);
  //return ret;
}

int main() 
{
  pthread_t thread_id,thread_id1;
  //pthread_attr_t attr;
  //int ret;
  //void *res;
  pthread_create(&thread_id,NULL,&write_th,NULL);
  pthread_create(&thread_id1,NULL,&read_th,NULL);
  printf("\n Created thread");
  pthread_join(thread_id,NULL);
  pthread_join(thread_id1,NULL);
  
  sleep(10);
  pthread_cancel(thread_id);
  pthread_cancel(thread_id1);
  
  pthread_mutex_destroy(&write_mutex);
  pthread_mutex_destroy(&read_mutex);
  
  return 0;
}
