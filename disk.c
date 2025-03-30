#include<stdio.h>
#include<stdlib.h>

void accept(int arr[],int n){
  printf("Enter the disk requests: ");
  for(int i=2;i<n;i++){
    scanf("%d",&arr[i]);
  }
  printf("Enter the head: ");
  scanf("%d",&arr[1]);
}

int FCFS(int arr[],int n){
  int seek = 0;
  printf("\n%d",arr[1]);
  for(int i=2;i<n;i++){
    seek += abs(arr[i] - arr[i-1]);
    printf(" -> %d",arr[i]);
  }
  return seek;
}

int findHead(int arr[],int n,int head){
  for(int i=0;i<n;i++){
    if(arr[i] == head){
      return i;
    }
  }
} 
	
void copy(int arr1[],int arr2[],int n){
  for(int i=0;i<n;i++){
    arr2[i] = arr1[i];
  }
}

void sort(int arr[],int n){
  for(int i=0;i<n-1;i++){
    for(int j=0;j<n-1-i;j++){
      if(arr[j] > arr[j+1]){
        int temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;
      }
    }
  }
}

int SSTF(int arr[],int n){
  int dup[n],count=0,seek=0;
  copy(arr,dup,n);
  sort(dup,n);
  int head = findHead(dup,n,arr[1]);
  int i=head-1,j=head+1,k=head;

  printf("\n%d",dup[head]); 
  while(count < n-2){
    if((dup[j] - dup[k] < dup[k] - dup[i]) || (i == 0 && j != n)){
      seek += dup[j] - dup[k];
      k = j;
      j++;
    }else{
      seek += dup[k] - dup[i];
      k = i;
      i--;
    }
    count++;
    printf(" -> %d",dup[k]);
  }
  return seek;
}

int SCAN(int arr[],int n){
  int dup[n];
  copy(arr,dup,n);
  sort(dup,n);
  int head = findHead(dup,n,arr[1]);

  printf("\nEnter the direction\n");
  printf("1.Right\n");
  printf("2.Left\n");
  int d;
  scanf("%d",&d);

  int seek = 0,i;
  printf("\n%d",arr[1]); 
  if(d == 1){
    i = head + 1;
    while(i > 1){
      seek += dup[i] - dup[i-1];
      printf(" -> %d",dup[i]);
      if(i == n-1){
        i = head - 1;
        seek += dup[n-1] - dup[i];
      }else if(i > head){
        i++;
      }else{
        i--;
      }
    }
  }else{
    i = head - 1;
    while(i < n-2){
      seek += dup[i+1] - dup[i];
      printf(" -> %d",dup[i]);
      if(i == 0){
        i = head + 1;
        seek += dup[i];
      }else if(i < head){
        i--;
      }else{
        i++;
      }
    }
  }
  printf(" -> %d",dup[i]);
    
  return seek;
} 

int CSCAN(int arr[],int n){
  int dup[n];
  copy(arr,dup,n);
  sort(dup,n);
  int head = findHead(dup,n,arr[1]);

  printf("\nEnter the direction\n");
  printf("1.Right\n");
  printf("2.Left\n");
  int d;
  scanf("%d",&d);

  int seek = 0;
  printf("\n%d",arr[1]); 
  if(d == 1){
    int i = head;
    while(i != head -1){
      seek += abs(dup[(i+1)%n] - dup[i]);
      i = (i+1)%n;
      printf(" -> %d",dup[i]);
    }
  }else{
    for(int i=head-1;i!=head;i--){
      seek += abs(dup[(i+1)%n] - dup[i]);
      printf(" -> %d",dup[i]);
      if(i == 0){
        i = n;
      }
    }
  }
   
 return seek;
}

int LOOK(int arr[],int n){
  int dup[n];
  copy(arr,dup,n);
  sort(dup,n);
  int head = findHead(dup,n,arr[1]);

  printf("\nEnter the direction\n");
  printf("1.Right\n");
  printf("2.Left\n");
  int d;
  scanf("%d",&d);

  int seek = 0,i;
  printf("\n%d",arr[1]); 
  if(d == 1){
    i = head + 1;
    while(i > 1){
      seek += dup[i] - dup[i-1];
      printf(" -> %d",dup[i]);
      if(i == n-1){
        i = head - 1;
        seek += dup[n-1] - dup[i];
      }else if(i > head){
        i++;
      }else{
        i--;
      }
    }
  }else{
    i = head - 1;
    while(i < n-1){
      seek += dup[i+1] - dup[i];
      printf(" -> %d",dup[i]);
      if(i == 1){
        i = head + 1;
        seek += dup[i] - dup[1];
      }else if(i < head){
        i--;
      }else{
        i++;
      }
    }
  }
  printf(" -> %d",dup[i]);
    
  return seek;
}

int CLOOK(int arr[],int n){
  int dup[n];
  copy(arr,dup,n);
  sort(dup,n);
  int head = findHead(dup,n,arr[1]);

  printf("\nEnter the direction\n");
  printf("1.Right\n");
  printf("2.Left\n");
  int d;
  scanf("%d",&d);

  int seek = 0;
  printf("\n%d",arr[1]); 
  if(d == 1){
    int i = head;
    while(i != head -1){
      seek += abs(dup[i%(n-1)+1] - dup[i]);
      i = i%(n-1)+1;
      printf(" -> %d",dup[i]);
    }
  }else{
    for(int i=head-1;i!=head;i--){
      seek += abs(dup[i%(n-1)+1] - dup[i]);
      printf(" -> %d",dup[i]);
      if(i == 1){
        i = n;
      }
    }
  }
   
 return seek;
}

void main(){
  printf("Enter the no: of disks: ");
  int n;
  scanf("%d",&n);

  int arr[n+3];
  arr[0] = 0;
  accept(arr,n+2);

  printf("Enter the max request: ");
  int max;
  scanf("%d",&max);
  arr[n+2] = max-1;

  do{
    printf("\nEnter a choice");
    printf("\n1.FCFS");
    printf("\n2.SSTF");
    printf("\n3.SCAN");
    printf("\n4.C-SCAN");
    printf("\n5.LOOK");
    printf("\n6.C-LOOK");
    printf("\n7.Exit\n");

    int c,seek = 0;
    scanf("%d",&c);

    switch(c){
      case 1: seek = FCFS(arr,n+2);
      break;

      case 2: seek = SSTF(arr,n+2);
      break;
      
      case 3: seek = SCAN(arr,n+3);
      break;
      
      case 4: seek = CSCAN(arr,n+3);
      break;

      case 5: seek = LOOK(arr,n+2);
      break;

      case 6: seek = CLOOK(arr,n+2);
      break;

      case 7: exit(0);
      
      default: printf("\nWrong choice entered\n");
      continue;
    }

    printf("\nSeek time: %d\n",seek);
  }while(1);
}