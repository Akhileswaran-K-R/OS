#include<stdio.h>

struct process{
  int id,at,bt,pri,ct,wt,tt,rt;
};

typedef struct process process;

void enqueue(process p[],int *rear,process p1){
  if(*rear == -1 || p[*rear].at < p1.at){
    p[++(*rear)] = p1;
    return;
  }

  int i = *rear;
  while(i >= 0){
    if(p[i].at > p1.at || (p[i].at == p1.at && p[i].pri > p1.pri)){
      p[i+1] = p[i];
      i--;
    }else{
      break;
    }
  }
  p[i+1] = p1;
  ++(*rear);
}

void accept(process p[],int n){
  int rear = -1;
  process p1;
  for(int i=0;i<n;i++){
    printf("\nEnter the details of process P%d\n",i+1);
    p1.id = i+1;
    printf("Arrival time: ");
    scanf("%d",&p1.at);
    printf("Burst time: ");
    scanf("%d",&p1.bt);
    printf("Priority: ");
    scanf("%d",&p1.pri);

    p1.rt = p1.bt;
    enqueue(p,&rear,p1);
  }
}

int findPriority(process p[],int n){
  int index=-1,min=9999;
  for(int i=0;i<n;i++){
    if(p[i].rt != 0 && p[i].pri < min){
      min = p[i].pri;
      index = i;
    }
  }
  return index;
}

void calculate(process p[],int n,int seq[][20],float *wt,float *tt,int *k){
  int i=0,j=1,ct=0,finished = 0;

  if(p[0].at > ct){
    ct = p[0].at;
    seq[0][0] = -1;
    seq[1][0] = ct;
    *k = 1;
  }

  while(i != -1){
    p[i].rt--;
    ct++;

    if(p[i].rt == 0){
      p[i].ct = ct;
      p[i].tt = p[i].ct - p[i].at;
      p[i].wt = p[i].tt - p[i].bt;

      *wt += p[i].wt;
      *tt += p[i].tt;
      seq[0][*k] = p[i].id;
      seq[1][(*k)++] = ct;
      finished++;
    }

    while(j < n && p[j].at <= ct){
      j++;
    }

    if(j == finished && j < n){
      ct = p[j].at;
      i = j;
      j++;
      seq[0][*k] = -1;
      seq[1][(*k)++] = ct;
    }else{
      int l = i;
      i = findPriority(p,j);
      if(l != i && p[l].rt != 0){
        seq[0][*k] = p[l].id;
        seq[1][(*k)++] = ct;
      }
    }
  }
}

void display(process p[],int n,float wt,float tt){
  printf("\nPid\tAT\tBT\tP\tCT\tTT\tWT\n");
  for(int i=0;i<n;i++){
    printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].pri,p[i].ct,p[i].tt,p[i].wt);
  }

  printf("\nAverage WT = %.2f",wt/n);
  printf("\nAverafe TT = %.2f",tt/n);
}

void ganttChart(int k, int seq[][20]){
  printf("\n\nGantt Chart\n\n");
  printf("+");
  for(int i=0;i<k;i++){
    printf("----------------");
  }
  printf("\b+");

  printf("\n|");
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
  printf("Enter the no: of processes: ");
  int n;
  scanf("%d",&n);
  process p[n];
  accept(p,n);

  int seq[2][20],k=0;
  float wt=0,tt=0;
  calculate(p,n,seq,&wt,&tt,&k);
  display(p,n,wt,tt);
  ganttChart(k,seq);
}