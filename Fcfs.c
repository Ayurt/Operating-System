#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <limits.h>
#include<math.h>

struct processes{
    int at,bt,ct,tat,wt,rt,st;
};
int compat(const void * a, const void * b){
    int x = ((struct processes*)a)->at;
    int y = ((struct processes*)b)->at;
    if(x<y) return -1;
    else if(x>=y) return 1;
}
int main(){
    int idle_time=0;
    int n;
    printf("enter the size of process");
    scanf("%d",&n);
    struct processes process[n];
    printf("enter the at and bt of processes");
    for(int i=0; i<n; i++){
        printf("\n process[%d]",i);
        scanf("%d",&process[i].at);
        scanf("%d",&process[i].bt);
    }
    int sum_tat = 0, sum_wt =0, sum_rt=0;
    qsort((void*)process, n , sizeof(struct processes), compat );
    int curr =0;
    for(int i=0; i<n; i++){
         process[i].st = (i==0) ? process[i].at : fmax(process[i].at,process[i-1].ct);
         process[i].ct = process[i].st+process[i].bt;
         process[i].tat = process[i].ct-process[i].at;
         process[i].wt = process[i].tat - process[i].bt;
         process[i].rt = process[i].wt;
         
         sum_tat+=process[i].tat;
         sum_wt += process[i].wt;
         sum_rt += process[i].rt;
         idle_time += (i==0) ? 0 : process[i].st-process[i-1].ct;
    }
    int complete_cycle = process[n-1].ct-process[0].st;
    
    float utilization = ((float)(complete_cycle-idle_time)/complete_cycle);
    printf("average turnaround time : %f", (float)sum_tat/n);
    printf("average waiting time : %f", (float)sum_wt/n);
    printf("average response time : %f", (float)sum_rt/n);
    printf("throughput: %f", (n/(float)complete_cycle));
    printf("utilization percentage is : %f", utilization*100);
    return 0;
    
    
}
