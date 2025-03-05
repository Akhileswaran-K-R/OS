#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#define N 100

int buffer[N],in=0,out=0;
sem_t full,empty;
pthread_mutex_t mutex;

void* producer(void *args){
  int n = (int)args;

  for(int i=0;i<n;i++){
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    buffer[in] = i;
    printf("Produced item: %d\n",i);
    in = (in+1)%N;
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
    sleep(1);
  }
  return NULL;
}

void* consumer(void *args){
  int n = (int)args;

  for(int i=0;i<n;i++){
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    int item = buffer[out];
    printf("Consumed item: %d\n",item);
    out = (out+1)%N;
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    sleep(1);
  }
  return NULL;
}

void main(){
  int np,nc;
  printf("Enter the no: of producers: ");
  scanf("%d",&np);
  printf("Enter the no: of consumers: ");
  scanf("%d",&nc);

  pthread_t prod,cons;
  sem_init(&full,0,0);
  sem_init(&empty,0,100);
  pthread_mutex_init(&mutex,NULL);
  pthread_create(&prod,NULL,producer,(void*)np);
  pthread_create(&cons,NULL,consumer,(void*)nc);

  pthread_join(prod,NULL);
  pthread_join(cons,NULL);
  sem_destroy(&empty);
  sem_destroy(&full);
}