#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct memory{
  int occupied,size;
};
typedef struct memory memory;

struct process{
  int allocated,size;
};
typedef struct process process;

void clear(process p[],int n,memory blocks[],int m){
  for(int i=0;i<n;i++){
    p[i].allocated = -1;
  }

  for(int i=0;i<m;i++){
    blocks[i].occupied = -1;
  }
}

void acceptMemory(memory blocks[],int m){
  printf("\nEnter the size of each memory block\n");
  for(int i=0;i<m;i++){
    printf("%d: ",i+1);
    scanf("%d",&blocks[i].size);
  }
}

void acceptProcess(process p[],int n){
  printf("\nEnter the size of each process\n");
  for(int i=0;i<n;i++){
    printf("P%d: ",i+1);
    scanf("%d",&p[i].size);
  }
}

void firstFit(process p[],int n,memory blocks[],int m){
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      if(blocks[j].occupied == -1 && p[i].size <= blocks[j].size){
        p[i].allocated = j+1;
        blocks[j].occupied = 1;
        break;
      }
    }
  }
}

void bestFit(process p[],int n,memory blocks[],int m){
  int best,index;
  for(int i=0;i<n;i++){
    best = INT_MAX;
    index = -1;
    for(int j=0;j<m;j++){
      if(blocks[j].occupied == -1 && blocks[j].size < best && p[i].size <= blocks[j].size){
        best = blocks[j].size;
        index = j;
      }
    }

    if(index != -1){
      p[i].allocated = index + 1;
      blocks[index].occupied = 1;
    }
  }
}

void worstFit(process p[],int n,memory blocks[],int m){
  int worst,index;
  for(int i=0;i<n;i++){
    worst = 0;
    index = -1;
    for(int j=0;j<m;j++){
      if(blocks[j].occupied == -1 && blocks[j].size > worst){
        worst = blocks[j].size;
        index = j;
      }
    }

    if(index != -1 && p[i].size <= worst){
      p[i].allocated = index + 1;
      blocks[index].occupied = 1;
    }
  }
}

void display(process p[],int n){
  for(int i=0;i<n;i++){
    printf("\nP%d: ",i+1);
    if(p[i].allocated == -1){
      printf("Not allocated");
    }else{
      printf("Block %d",p[i].allocated);
    }
  }
}

void main(){
  int n,m;
  printf("Enter the no: of partitions: ");
  scanf("%d",&m);
  memory blocks[m];
  acceptMemory(blocks,m);

  printf("\nEnter the no: of processes: ");
  scanf("%d",&n);
  process p[n];
  acceptProcess(p,n);

  int c;
  do{
    printf("\nEnter a choice\n");
    printf("1.First Fit\n");
    printf("2.Best Fit\n");
    printf("3.Worst Fit\n");
    printf("4.Exit\n");

    scanf("%d",&c);
    clear(p,n,blocks,m);

    switch(c){
      case 1: firstFit(p,n,blocks,m);
      break;
      case 2: bestFit(p,n,blocks,m);
      break;
      case 3: worstFit(p,n,blocks,m);
      break;
      case 4: exit(0);
      default: printf("\nWrong choice entered\n");
      continue;
    }

    display(p,n);
    printf("\n");
  }while(1);
}