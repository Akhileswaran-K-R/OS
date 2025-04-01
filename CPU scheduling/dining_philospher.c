#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

pthread_mutex_t chopsticks[5];

void* dine(void *args){
  int n = (int)args;
  printf("Philospoher %d is thinking\n",n+1);

  pthread_mutex_lock(&chopsticks[n]);
  pthread_mutex_lock(&chopsticks[(n + 1) % 5]);
  printf("Philospher %d is eating\n",n+1);
  sleep(3);

  pthread_mutex_unlock(&chopsticks[n]);
  pthread_mutex_unlock(&chopsticks[(n + 1) % 5]);
  printf("Philosopher %d finished eating\n",n);

  return NULL;
}

void main(){
  pthread_t phil[5];
  for(int i=0;i<5;i++){
    pthread_mutex_init(&chopsticks[i],NULL);
  }

  for(int i=0;i<5;i++){
    pthread_create(&phil[i],NULL,dine,(void*)i);
  }

  for(int i=0;i<5;i++){
    pthread_join(phil[i],NULL);
  }
}