#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t mutex;
pthread_mutex_t rw_mutex;
int read_count = 0;

void* writer(void *args){
  int n = (int)args;
  n++;
  printf("Writer %d is trying to enter\n",n);
  pthread_mutex_lock(&rw_mutex);
  printf("Writer %d is writing\n",n);
  pthread_mutex_unlock(&rw_mutex);
  printf("Writer %d is leaving\n",n);
  sleep(2);

  return NULL;
}

void* reader(void *args){
  int n = (int)args;
  n++;

  printf("Reader %d is trying to enter\n",n);
  sem_wait(&mutex);
  read_count++;
  if(read_count == 1){
    pthread_mutex_lock(&rw_mutex);
  }
  sem_post(&mutex);

  printf("Reader %d is reading\n",n);
  sleep(2);

  sem_wait(&mutex);
  read_count--;
  if(read_count == 0){
    pthread_mutex_unlock(&rw_mutex);
  }
  sem_post(&mutex);
  printf("Reader %d is leaving\n",n);

  return NULL;
}

void main(){
  int r,w;
  printf("Enter the no: of readers: ");
  scanf("%d",&r);
  printf("Enter the no: of writers: ");
  scanf("%d",&w);
  printf("\n");

  pthread_t writers[w],readers[r];
  pthread_mutex_init(&rw_mutex,NULL);
  sem_init(&mutex,0,1);

  for(int i=0;i<w||i<r;i++){
    if(i < w){
      pthread_create(&writers[i],NULL,writer,(void*)i);
    }
    
    if(i < r){
      pthread_create(&readers[i],NULL,reader,(void*)i);
    }
  }

  for(int i=0;i<w;i++){
    pthread_join(writers[i],NULL);
  }

  for(int i=0;i<r;i++){
    pthread_join(readers[i],NULL);
  }

  pthread_mutex_destroy(&rw_mutex);
  sem_destroy(&mutex);
}