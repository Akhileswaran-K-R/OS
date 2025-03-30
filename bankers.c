#include<stdio.h>

void accept(int m,int n,int alloc[][n],int max[][n],int need[][n],int available[][n]){
  printf("Enter the total no: of resource: ");
  for(int i=0;i<n;i++){
    scanf("%d",&available[0][i]);
  }

  for(int i=0;i<m;i++){
    printf("\nEnter the details of P%d\n",i+1);
    printf("Allocation: ");
    for(int j=0;j<n;j++){
      scanf("%d",&alloc[i][j]);
      available[0][j] -= alloc[i][j];
    }

    printf("Max: ");
    for(int j=0;j<n;j++){
      scanf("%d",&max[i][j]);
      need[i][j] = max[i][j] - alloc[i][j];
    }
  }
}

int isSafe(int m,int n,int alloc[][n],int max[][n],int need[][n],int available[][n],int safeseq[]){
  int finish[10] = {0};
  int work[n];
  for(int i=0;i<n;i++){
    work[i] = available[0][i];
  }

  int k = 1,count;
  do{
    count = 0;
    for(int i=0;i<m;i++){
      if(finish[i]){
        continue;
      }

      int canAllocate = 1;
      for(int j=0;j<n;j++){
        if(need[i][j] > work[j]){
          canAllocate = 0;
          break;
        }
      }
      
      if(canAllocate){
        for(int j=0;j<n;j++){
          work[j] += alloc[i][j];
          available[k][j] = work[j];
        }
        safeseq[k-1] = i+1;
        finish[i] = 1;
        k++;
        count++;
      }
    }
  }while(count > 0);

  for(int i=0;i<m;i++){
    if(!finish[i]){
      return 0;
    }
  }
  return 1;
}

void display(int m,int n,int alloc[][n],int max[][n],int need[][n],int available[][n]){
  printf("\nProcess\t\tAllocation\tMax\t\tNeed\t\tAvailable");
  for(int i=0;i<m;i++){
    printf("\n  P%d\t\t",i+1);
    for(int j=0;j<n;j++){
      printf("%d ",alloc[i][j]);
    }
    printf("\t");
    for(int j=0;j<n;j++){
      printf("%d ",max[i][j]);
    }
    printf("\t");
    for(int j=0;j<n;j++){
      printf("%d ",need[i][j]);
    }
    printf("\t");
    for(int j=0;j<n;j++){
      printf("%d ",available[i][j]);
    }
  }
}

void result(int m,int n,int alloc[][n],int max[][n],int need[][n],int available[][n],int safeseq[]){
  if(isSafe(m,n,alloc,max,need,available,safeseq)){
    display(m,n,alloc,max,need,available);

    printf("\n\nSystem is in safe state");
    printf("\nSafe sequence: ");
    for(int i=0;i<m;i++){
      printf("P%d ",safeseq[i]);
    }
  }else{
    printf("\nSystem is in unsafe state");
  }
}

int request(int id,int n,int available[][n],int need[][n],int alloc[][n],int req[]){
  for(int i=0;i<n;i++){
    if(req[i] > available[0][i] || req[i] > need[id][i]){
      return 0;
    }

    alloc[id][i] += req[i];
    available[0][i] -= req[i];
    need[id][i] -= req[i];
  }
  return 1;
}

void main(){
  int m,n;
  printf("Enter the no: of processes: ");
  scanf("%d",&m);
  printf("Enter the no: of resources: ");
  scanf("%d",&n);
  
  int alloc[m][n],max[m][n],need[m][n],available[m+1][n],safeseq[m];
  accept(m,n,alloc,max,need,available);
  result(m,n,alloc,max,need,available,safeseq);

  int id,req[n];
  printf("\n\nEnter the id of the proccess requesting: ");
  scanf("%d",&id);
  printf("Enter the request: ");
  for(int i=0;i<n;i++){
    scanf("%d",&req[i]);
  }

  if(request(id-1,n,available,need,alloc,req)){
    printf("\nThe request can be granted\n");
    result(m,n,alloc,max,need,available,safeseq);
  }else{
    printf("\nThe request cannot be granted\n");
  }
}