#include<stdio.h>
#include<stdlib.h>

void initialise(int frames[],int f){
  for(int i=0;i<f;i++){
    frames[i] = -1;
  }
}

int isFound(int frames[],int f,int pg){
  for(int i=0;i<f;i++){
    if(frames[i] == pg){
      return i;
    }
  }
  return -1;
}

void displayFrames(int frames[],int f){
  for(int i=0;i<f;i++){
    if(frames[i] == -1){
      printf(" - ");
    }else{
      printf(" %d ",frames[i]);
    }
  }
}

void FIFO(int frames[],int f,int pages[],int n,float *fault){
  int rear = -1;

  for(int i=0;i<n;i++){
    if(isFound(frames,f,pages[i]) == -1){
      rear = (rear + 1) % f;
      frames[rear] = pages[i];
      *fault = *fault + 1;
    }
    printf("Stage %d: ",i+1);
    displayFrames(frames,f);
    printf("\n");
  }
}

int findMin(int arr[],int n){
  int min = 0;
  for(int i=1;i<n;i++){
    if(arr[i] < arr[min]){
      min = i;
    }
  }
  return min;
}

void LRU(int frames[],int f,int pages[],int n,float *fault){
  int recent[f],index;
  initialise(recent,f);

  for(int i=0;i<n;i++){
    index = isFound(frames,f,pages[i]);

    if(index == -1){
      index = findMin(recent,f);
      frames[index] = pages[i];
      *fault = *fault + 1;
    }
    recent[index] = i;

    printf("Stage %d: ",i+1);
    displayFrames(frames,f);
    printf("\n");
  }
}

void LFU(int frames[],int f,int pages[],int n,float *fault){
  int freq[f],index;
  initialise(freq,f);

  for(int i=0;i<n;i++){
    index = isFound(frames,f,pages[i]);

    if(index == -1){
      index = findMin(freq,f);
      frames[index] = pages[i];
      *fault = *fault + 1;
      freq[index] = i;
    }else{
      freq[index] += n;
    }

    printf("Stage %d: ",i+1);
    displayFrames(frames,f);
    printf("\n");
  }
}

int findMax(int arr[],int recent[],int n){
  int index = 0;
  for(int i=1;i<n;i++){
    if(arr[i] > arr[index] || (arr[i] == arr[index] && recent[i] < recent[index])){
      index = i;
    }
  }
  return index;
}

void optimal(int frames[],int f,int pages[],int n,float *fault){
  int future[f],recent[f],j=0;
  for(int i=0;i<f;i++){
    future[i] = 500;
  }
  initialise(recent,f);

  for(int i=0;i<n;i++){
    j = isFound(frames,f,pages[i]);

    if(j == -1){
      j = findMax(future,recent,f);
      frames[j] = pages[i];
      *fault = *fault + 1;
    }

    int futIndex = 500;
    for(int k=i+1;k<n;k++){
      if(pages[i] == pages[k]){
        futIndex = k;
        break;
      }
    }

    future[j] = futIndex;
    recent[j] = i;

    printf("Stage %d: ",i+1);
    displayFrames(frames,f);
    printf("\n");
  }
}

void displayRatio(float fault,int n){
  printf("\nPage Fault: %d",(int)fault);
  printf("\nPage Hit: %d",(int)(n - fault));
  printf("\nFault ratio: %.2f",fault / n);
  printf("\nHit ratio: %.2f",(n - fault) / n);
}

void main(){
  int f;
  printf("Enter the no: of frames: ");
  scanf("%d",&f);
  int frames[f];

  int n;
  printf("Enter the no: of pages: ");
  scanf("%d",&n);
  int pages[n];

  printf("Enter the pages: ");
  for(int i=0;i<n;i++){
    scanf("%d",&pages[i]);
  }

  float fault;
  int c;
  do{
    printf("\nEnter a choice\n");
    printf("1.FIFO\n");
    printf("2.LRU\n");
    printf("3.LFU\n");
    printf("4.Optimal\n");
    printf("5.Exit\n");

    scanf("%d",&c);
    initialise(frames,f);
    fault = 0;

    switch(c){
      case 1: printf("\nFIFO\n\n");
              FIFO(frames,f,pages,n,&fault);
      break;

      case 2: printf("\nLRU\n\n");
              LRU(frames,f,pages,n,&fault);
      break;

      case 3: printf("\nLFU\n\n");
              LFU(frames,f,pages,n,&fault);
      break;

      case 4: printf("\nOptimal\n\n");
              optimal(frames,f,pages,n,&fault);
      break;

      case 5: exit(0);

      default: printf("\nWrong choice entered\n");
      continue;
    }

    displayRatio(fault,n);
    printf("\n");
  }while(1);
}