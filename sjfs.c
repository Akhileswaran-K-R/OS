#include<stdio.h>
#include<string.h>

struct process{
  int pid, at, bt, tt, ct, wt;
  char name[5];
};

typedef struct process process;

process p[20];
int rear = -1, box = 0;
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
        if(p[i].bt > p1.bt || (p[i].bt == p1.bt && p[i].pid > p1.pid)){
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

    enqueue(p1);
  }
}

void findShort(int start,int end){
  process temp = p[start+1];
  int j = start+1;
  for(int i=start+2;i<end;i++){
    if(p[i].bt < temp.bt || (p[i].bt == temp.bt && (p[i].at < temp.at || (p[i].at == temp.at && p[i].pid < temp.pid)))){
      temp = p[i];
      j = i;
    }
  }

  temp = p[start+1];
  p[start+1] = p[j];
  p[j] = temp;
}

void calculate(){
  int ct = 0;
  float wt = 0,tt = 0;

  for(int i=0;i<=rear;i++){
    if(ct < p[i].at){
      ct = p[i].at;
      box++;
    }
    p[i].ct = ct + p[i].bt;
    p[i].tt = p[i].ct - p[i].at;
    p[i].wt = p[i].tt - p[i].bt;
    box++;

    ct = p[i].ct;
    tt += p[i].tt;
    wt += p[i].wt;

    int j = i+1;
    while(j <= rear && p[j].at <= ct){
      j++;
    }
    findShort(i,j);
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

void ganttChart(){
  printf("\n\nGantt Chart\n\n");

  printf("+");
  for(int i=0;i<box;i++){
    printf("----------------");
  }
  printf("\b+\n");

  int n = 0;
  printf("|");
  for(int i=0;i<=rear;i++){
    if(n < p[i].at){
      printf("\t\bIdle\t|");
      n = p[i].at;
      i--;
    }else{
      printf("\t%s\t|",p[i].name);
      n = p[i].ct;
    }
  }

  printf("\n+");
  for(int i=0;i<box;i++){
    printf("----------------");
  }
  printf("\b+\n");

  n = 0;
  printf("0");
  for(int i=0;i<=rear;i++){
    if(n < p[i].at){
      printf("\t\t%d",p[i].at);
      n = p[i].at;
      i--;
    }else{
      printf("\t\t%d",p[i].ct);
      n = p[i].ct;
    }
  }
}

void main(){
  accept();
  calculate();
  display();
  ganttChart();
}