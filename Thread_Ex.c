#include<stdio.h>
#include<pthread.h>
//int pthread_create(pthread_t *thread, const pthread_attr_1 *atrr, void *(*start_routine)(void *), void *arg);
void *busy(void *ptr)
{
//ptr will point to "Hi"
puts("Hello World");
return NULL;
}
int main()
{
pthread_t id;
pthread_create(&id, NULL, busy, "Hi");
while (1) {} // Loop forever
}
