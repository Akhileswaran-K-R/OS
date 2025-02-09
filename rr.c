#include<stdio.h>
#include<string.h>

struct process{
  int pid, at, bt, tt, ct, wt, rt;
  char name[5];
};

typedef struct process process;

process p[20];
int rear = -1, box = 0, tq,nrq;
float avgtt, avgwt;

void enqueue(process p1){
  if(rear == -1 || p[rear].at < p1.at){
    p[++(rear)] = p1;
    return;
  }

  if(p[rear].at >= p1.at){
    int i = rear;
    while(p[i].at >= p1.at && i > -1){
      if(p[i].at == p1.at){
        if(p[i].pid > p1.pid){
          p[i+1] = p[i];
        }else{
          break;
        }
      }else{
        p[i+1] = p[i];
      }
      i--;
    }

    p[i+1] = p1;
    rear++;
  }
}

void accept(){
  int n;
  process p1;
  box = 0;
  printf("Enter the no: of process: ");
  scanf("%d",&n);

  for(int i=0;i<n;i++){
    char name[3] = "P";
    char str[3];
    sprintf(str,"%d",i+1);
    strcat(name,str);

    strcpy(p1.name,name);
    printf("\nEnter the details of P%d\n",i+1);
    printf("Pid: ");
    scanf("%d",&p1.pid);
    printf("Arrival time: ");
    scanf("%d",&p1.at);
    printf("Burst time: ");
    scanf("%d",&p1.bt);

    p1.rt = p1.bt;
    box += p1.bt;

    enqueue(p1);
  }

  printf("\nEnter the time quantum: ");
  scanf("%d",&tq);
}

void calculate(process *rq[]){
  int ct = 0,nop = rear+1,i =0,j = 0;
  float wt = 0,tt = 0;
  box = 0;

  rq[i] = &p[j];
  if(p[j].at > 0){
    box++;
    ct = p[j].at;
  }
  j++;

  nrq = 0;
  while(nop > 0){
    if(rq[i]->rt <= tq){
      ct += rq[i]->rt;
      rq[i]->rt = 0;
      rq[i]->ct = ct;
      nop--;

      rq[i]->tt = rq[i]->ct - rq[i]->at;
      rq[i]->wt = rq[i]->tt - rq[i]->bt;
      wt += rq[i]->wt;
      tt += rq[i]->tt;
    }else{
      rq[i]->rt -= tq;
      ct += tq;
    }

    while(j <= rear && p[j].at <= ct){
      rq[++nrq] = &p[j];
      j++;
    }

    if(rq[i]->rt != 0){
      rq[++nrq] = rq[i];
    }
    
    if(i == nrq){
      rq[++nrq] = &p[j];
      ct = p[j].at;
      box++;
      j++;
    }
    i++;
  }

  avgtt = tt/(rear+1);
  avgwt = wt/(rear+1);
}

void display(){
  printf("\nPname\tPid\tAT\tBT\tCT\tTT\tWT\n");
  for(int i=0;i<=rear;i++){
    printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].name,p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tt,p[i].wt);
  }

  printf("\nAverage TT = %.2f ms",avgtt);
  printf("\nAverage WT = %.2f ms",avgwt);
}

void ganttChart(process *rq[]){
  printf("\n\nGantt Chart\n\n");

  printf("+");
  for(int i=0;i<box+nrq-1;i++){
    printf("----------------");
  }
  printf("\b+\n");

  int n = 0;
  printf("|");
  for(int i=0;i<nrq;i++){
    if(n < rq[i]->at){
      printf("\t\bIdle\t|");
      n = rq[i]->at;
      i--;
    }else{
      printf("\t%s\t|",rq[i]->name);
      if(n + tq > rq[i]->ct){
        n = rq[i]->ct;
      }else{
        n = n + tq;
      }
    }
  }

  printf("\n+");
  for(int i=0;i<box+nrq-1;i++){
    printf("----------------");
  }
  printf("\b+\n");

  n = 0;
  printf("0");
  for(int i=0;i<nrq;i++){
    if(n < rq[i]->at){
      printf("\t\t%d",rq[i]->at);
      n = rq[i]->at;
      i--;
    }else{
      if(n + tq > rq[i]->ct){
        n = rq[i]->ct;
      }else{
        n = n + tq;
      }
      printf("\t\t%d",n);
    }
  }
}

void main(){
  accept();
  process *rq[box/tq + 2];
  calculate(rq);
  display();
  ganttChart(rq);
}