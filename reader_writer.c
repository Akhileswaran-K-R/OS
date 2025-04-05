#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

pthread_mutex_t rw_mutex,mutex;
int read_count = 0;

void* writer(void *args){
  int *n = args;
  
  printf("Writer %d is trying to enter\n",*n);
  pthread_mutex_lock(&rw_mutex);
  printf("Writer %d is writing\n",*n);
  sleep(2);
  pthread_mutex_unlock(&rw_mutex);
  printf("Writer %d is leaving\n",*n);

  return NULL;
}

void* reader(void *args){
  int *n = args;

  printf("Reader %d is trying to enter\n",*n);
  pthread_mutex_lock(&mutex);
  read_count++;
  if(read_count == 1){
    pthread_mutex_lock(&rw_mutex);
  }
  pthread_mutex_unlock(&mutex);

  printf("Reader %d is reading\n",*n);
  sleep(2);

  pthread_mutex_lock(&mutex);
  read_count--;
  printf("Reader %d is leaving\n",*n);
  if(read_count == 0){
    pthread_mutex_unlock(&rw_mutex);
  }
  pthread_mutex_unlock(&mutex);
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
  int pidw[w],pidr[r];
  pthread_mutex_init(&rw_mutex,NULL);
  pthread_mutex_init(&mutex,NULL);

  for(int i=0;i<w||i<r;i++){
    if(i < w){
      pidw[i] = i+1;
      pthread_create(&writers[i],NULL,writer,&pidw[i]);
    }
    
    if(i < r){
      pidr[i] = i+1;
      pthread_create(&readers[i],NULL,reader,&pidr[i]);
    }
  }

  for(int i=0;i<w;i++){
    pthread_join(writers[i],NULL);
  }

  for(int i=0;i<r;i++){
    pthread_join(readers[i],NULL);
  }

  pthread_mutex_destroy(&rw_mutex);
  pthread_mutex_destroy(&mutex);
}