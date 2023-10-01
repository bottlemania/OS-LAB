#include <stdio.h>
struct process
{
int at;
int st;
int status;
int ft;
}ready_list[10];
int n;
int dispatcher(int time)
{
int i,s_bt=9999,index=-1;
for(i=0;i<n;i++)
{
if(ready_list[i].status != 1)
if(ready_list[i].at <= time)
if(ready_list[i].st < s_bt)
{
s_bt = ready_list[i].st;
index=i;
}
}
return index;
}
int main()
{
int i,cur_time,pid;
int rem_procs=0;
printf("Enter number of processes:");
scanf("%d",&n);
// Collect process details -
for(i=0;i<n;i++)
{
printf("Process %d\n",i+1);
printf("***********\n");
printf("Enter Arrival Time:");
scanf("%d",&ready_list[i].at);
printf("Enter Burst Time:");
scanf("%d",&ready_list[i].st);
ready_list[i].status=0;
}
int bd[n];
for(i=0;i<n;i++){
bd[i] = ready_list[i].st;
}
cur_time=0;
while(rem_procs < n)
{
pid=dispatcher(cur_time);
ready_list[pid].ft=cur_time + 1;
cur_time = cur_time + 1;
ready_list[pid].st-=1;
if(ready_list[pid].st==0)
{
ready_list[pid].status=1;
rem_procs+=1;
}
}
printf("Process\t Arrival Time\t Burst Time\t Finish Time");
printf("*******\t **********\t **********\t *********\n");
for(i=0;i<n;i++)
{
printf("%d\t\t%d\t\t%d\t\t\t%d\n",i,ready_list[i].at,bd[i],ready_list[i].ft);
}
}