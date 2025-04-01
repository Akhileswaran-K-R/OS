#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>

void createShm(key_t key){
  int shmid = shmget(key,1024,0666|IPC_CREAT);
  void *shared_memory = shmat(shmid,NULL,0);
  strcpy(shared_memory,"Hello, from Parent");
}

void childEdit(key_t key){
  int shmid = shmget(key,1024,0666);
  void *shared_memory = shmat(shmid,NULL,0);
  printf("%s\n",(char*)shared_memory);
  strcpy(shared_memory,"Hello, from Child");
}

void parentRead(key_t key){
  int shmid = shmget(key,1024,0666);
  void *shared_memory = shmat(shmid,NULL,0);
  printf("%s\n",(char*)shared_memory);
  shmdt(shared_memory);
  shmctl(shmid,IPC_RMID,NULL);
}

void main(){
  key_t key = ftok(".",65);
  createShm(key);
  
  int p = fork();
  if(p > 0){
    wait(NULL);
    parentRead(key);
  }else if(p == 0){
    childEdit(key);
  }else{
    printf("\nFork error\n");
    exit(0);
  }
}