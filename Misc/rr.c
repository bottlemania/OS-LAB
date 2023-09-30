
#include<stdio.h>
struct process
{
int at;
int st;
int ft;
int status;
}ready[10];
int n,t,com=0;
int Dispatch(int ct)
{
int i,index=-1,high_at=0,high_status=0; //high_status - 0 - Not yet execsted once
, 1- already executed atleast once
int m;
m=n;
for(i=0;i<n;i++)
{
if(ready[i].at> high_at)
{
high_at=ready[i].at;
}
}
for(i=0;i<n;i++)
{
if(ready[i].status > high_status)
{
high_status=ready[i].status;
}
}
for(i=0;i<n;i++)
{
if(ready[i].status!=2) //Status = 2 means process already completed
{
if(ready[i].at<=ct)
{
if(ready[i].at<high_at)
{
index=i;
high_at=ready[i].at;
}
if(ready[i].at==high_at)
{
if(ready[i].status<high_status)
{
index=i;
high_status=ready[i].status;
}
else if(ready[i].status==high_status)
{
if(i<m)
{
index=i;
m=i;
}
}
}
}
}
}
return index;
}
int main()
{
int i;
printf("Enter number of processes:");
scanf("%d",&n);
printf("Enter the time slice:");
scanf("%d",&t);
for(i=0;i<n;i++)
{
printf("Process:%d\n",i+1);
printf("****************\n");
printf("Enter the arrival time:");
scanf("%d",&ready[i].at);
printf("Enter the service time:");
scanf("%d",&ready[i].st);
ready[i].status=0;
}
i=0;
int at[10],st[10];
for(i=0;i<n;i++)
{
at[i]=ready[i].at;
st[i]=ready[i].st;
}
int pid,cur_time=0;
while(com<n)
{
pid=Dispatch(cur_time);
if(ready[pid].st<=t)
{
cur_time+=ready[pid].st;
ready[pid].ft=cur_time;
ready[pid].status=2;
com++;
}
else
{
cur_time+=t;
ready[pid].at=cur_time;
ready[pid].st=ready[pid].st-t;
ready[pid].status=1;
}
}
printf("process-id\t arrival time\t service time\t finish time\t turnaround time
\twaitingtime\n");
printf("*************************************************************************************
***************\n");
for(i=0;i<n;i++)
{
printf("%d\t\t %d\t\t\t %d\t\t %d\t\t %d\t\t\t
%d\n",i+1,at[i],st[i],ready[i].ft,ready[i].ft-at[i],ready[i].ft-at[i]-st[i]);
}
}