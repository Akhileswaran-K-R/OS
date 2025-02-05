#include<stdio.h>
#include<string.h>

struct process{
  int pid;
  int at;
  int bt;
  int tt;
  int ct;
  int wt;
  char name[5];
};

typedef struct process process;

struct queue{
  process p[20];
  int rear;
  int box;
  float avgtt;
  float avgwt;
};

typedef struct queue queue;

int isEmpty(queue *q){
  if(q->rear == -1){
    return 1;
  }
  return 0;
}

void enqueue(queue *q,process p){
  if(isEmpty(q) || q->p[q->rear].at < p.at){
    q->p[++(q->rear)] = p;
    return;
  }

  if(q->p[q->rear].at >= p.at){
    int i = q->rear;
    while(q->p[i].at >= p.at && i > -1){
      if(q->p[i].at == p.at){
        if(q->p[i].pid > p.pid){
          q->p[i+1] = q->p[i];
        }else{
          break;
        }
      }else{
        q->p[i+1] = q->p[i];
      }
      i--;
    }

    q->p[i+1] = p;
    q->rear++;
  }
}

void accept(queue *q){
  int n;
  process p;
  printf("Enter the no: of process: ");
  scanf("%d",&n);

  for(int i=0;i<n;i++){
    char name[3] = "P";
    char str[3];
    sprintf(str,"%d",i+1);
    strcat(name,str);

    strcpy(p.name,name);
    printf("\nEnter the details of P%d\n",i+1);
    printf("Pid: ");
    scanf("%d",&p.pid);
    printf("Arrival time: ");
    scanf("%d",&p.at);
    printf("Burst time: ");
    scanf("%d",&p.bt);

    enqueue(q,p);
  }

}

void calculate(queue *q){
  int ct = 0;
  float wt = 0,tt = 0;
  q->box = 0;

  for(int i=0;i<=q->rear;i++){
    if(ct < q->p[i].at){
      ct = q->p[i].at;
      i--;
      q->box++;
      continue;
    }
    q->p[i].ct = ct + q->p[i].bt;
    q->p[i].tt = q->p[i].ct - q->p[i].at;
    q->p[i].wt = q->p[i].tt - q->p[i].bt;
    q->box++;

    ct = q->p[i].ct;
    tt += q->p[i].tt;
    wt += q->p[i].wt;
  }

  q->avgtt = tt/(q->rear+1);
  q->avgwt = wt/(q->rear+1);
}

void display(queue q){
  printf("\nPname\tPid\tAT\tBT\tCT\tTT\tWT\n");
  for(int i=0;i<=q.rear;i++){
    printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",q.p[i].name,q.p[i].pid,q.p[i].at,q.p[i].bt,q.p[i].ct,q.p[i].tt,q.p[i].wt);
  }

  printf("\nAverage TT = %.2f ms",q.avgtt);
  printf("\nAverage WT = %.2f ms",q.avgwt);
}

void ganttChart(queue q){
  printf("\n\nGantt Chart\n\n");

  printf("+");
  for(int i=0;i<q.box;i++){
    printf("-----------");
  }
  printf("\b+\n");

  int n = 0;
  printf("|");
  for(int i=0;i<=q.rear;i++){
    if(n < q.p[i].at){
      printf("   Idle   |");
      n = q.p[i].at;
      i--;
    }else{
      printf("    %s    |",q.p[i].name);
      n = q.p[i].ct;
    }
  }

  printf("\n+");
  for(int i=0;i<q.box;i++){
    printf("-----------");
  }
  printf("\b+\n");

  n = 0;
  printf("0");
  for(int i=0;i<=q.rear;i++){
    if(n < q.p[i].at){
      if(q.p[i].at < 10){
        printf("          %d",q.p[i].at);
      }else{
        printf("         %d",q.p[i].at);
      }
      n = q.p[i].at;
      i--;
    }else{
      if(q.p[i].ct < 10){
        printf("          %d",q.p[i].ct);
      }else{
        printf("         %d",q.p[i].ct);
      }
      n = q.p[i].ct;
    }
  }
}

void main(){
  queue q;
  q.rear=-1;

  accept(&q);
  calculate(&q);
  display(q);
  ganttChart(q);
}