#include<stdio.h>

struct process{
  int id,at,bt,ct,wt,tt,rt;
};

typedef struct process process;

void enqueue(process p[],int *rear,process p1){
  if(*rear == -1 || p[*rear].at < p1.at){
    p[++(*rear)] = p1;
    return;
  }

  int i = *rear;
  while(i >=0 ){
    if(p[i].at > p1.at || (p[i].at == p1.at && p[i].bt > p1.bt)){
      p[i+1] = p[i];
    }else{
      break;
    }
    i--;
  }
  p[i+1] = p1;
  ++(*rear);
}

void accept(process p[],int n){
  process p1;
  int rear = -1;
  for(int i=0;i<n;i++){
    p1.id = i+1;
    printf("\nEnter the details of process P%d",i+1);
    printf("\nArrival time: ");
    scanf("%d",&p1.at);
    printf("Burst time: ");
    scanf("%d",&p1.bt);
    p1.rt = p1.bt;
    
    enqueue(p,&rear,p1);
  }
}

int findShort(process p[],int n){
  int index = -1;
  int min = 9999;
  for(int i=0;i<n;i++){
    if(p[i].rt != 0 && p[i].rt < min){
      min = p[i].rt;
      index = i;
    }
  }
  return index;
}

void SRTF(process p[],int n,float *avgwt,float *avgtt,int seq[][20],int *k){
  int i=0,j=1,ct=0,finished = 0;
  float wt=0,tt=0;
  if(p[0].at > 0){
    ct = p[0].at;
    seq[0][0] = -1;
    seq[1][0] = ct;
    *k=1;
  }

  while(i!=-1){
    p[i].rt--;
    ct++;
    if(p[i].rt == 0){
      p[i].ct = ct;
      p[i].tt = p[i].ct - p[i].at;
      p[i].wt = p[i].tt - p[i].bt;

      tt += p[i].tt;
      wt += p[i].wt;
      seq[0][*k] = p[i].id;
      seq[1][*k] = ct;
      ++(*k);
      finished++;
    }

    while(j<n){
      if(p[j].at <= ct){
        j++;
      }else{
        break;
      }
    }

    if(finished == j && j < n){
      ct = p[j].at;
      j++;
      seq[0][*k] = -1;
      seq[1][*k] = ct;
      ++(*k);
    }

    int l = i;
    i = findShort(p,j);
    if( i != l && p[l].rt != 0){
      seq[0][(*k)] = p[l].id;
      seq[1][*k] = ct;
      ++(*k);
    }
  }
  *avgwt = wt/n;
  *avgtt = tt/n;
}

void display(process p[],int n,float avgwt,float avgtt){
  printf("\nPid\tAT\tBT\tCT\tTT\tWT\n");
  for(int i=0;i<n;i++){
    printf("P%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].tt,p[i].wt);
  }

  printf("\nAverage TT = %.2f ms",avgtt);
  printf("\nAverage WT = %.2f ms",avgwt);
}

void ganttChart(int k,int seq[][20]){
  printf("\n\nGantt Chart\n\n");

  printf("+");
  for(int i=0;i<k;i++){
    printf("----------------");
  }
  printf("\b+\n");

  printf("|");
  for(int i=0;i<k;i++){
    if(seq[0][i] == -1){
      printf("\t\bIdle\t|");
    }else{
      printf("\tP%d\t|",seq[0][i]);
    }
  }

  printf("\n+");
  for(int i=0;i<k;i++){
    printf("----------------");
  }
  printf("\b+\n");

  printf("0");
  for(int i=0;i<k;i++){
    printf("\t\t%d",seq[1][i]);
  }
}

void main(){
  printf("Enter the no: of process: ");
  int n;
  scanf("%d",&n);
  process p[n];
  accept(p,n);

  float avgwt=0,avgtt=0;
  int k=0,seq[2][20];
  SRTF(p,n,&avgwt,&avgtt,seq,&k);
  display(p,n,avgwt,avgtt);
  ganttChart(k,seq);
}