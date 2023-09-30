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
    int i,lat = time,index=-1;
    for(i=0;i<n;i++)
    {
        if(ready_list[i].status != 1){
            if(ready_list[i].at <= lat)
            {
                lat = ready_list[i].at;
                index=i;
            }
            }
    }
    return index;
}

int main()
{
    int i,cur_time,pid;
    printf("Enter number of processes:");
    scanf("%d",&n);
    // Collect process details -
    for(i=0;i<n;i++)
    {
    printf("Process %d\n",i+1);
    printf("***********\n");
    printf("Enter Arrival Time:");
    scanf("%d",&ready_list[i].at);
    printf("Enter Service Time:");
    scanf("%d",&ready_list[i].st);
    ready_list[i].status=0;
    }
    i=0; cur_time=0;
    while(i < n)
    {
    pid=dispatcher(cur_time);
    while(pid==-1){
    cur_time++;
    pid = dispatcher(cur_time);
    }
    ready_list[pid].ft=cur_time + ready_list[pid].st;
    ready_list[pid].status=1;
    cur_time+= ready_list[pid].st;
    i++;
    }
    printf("Process\t Arrival Time\t Burst Time\tFinish Time \t TT \t\t WT\n");
    printf("*******\t ************\t ************\t ***********\t********\t********\n");
    for(i=0;i<n;i++)
    {
    printf("%d\t\t%d\t\t%d\t\t%d\t%d\t\t%d\n",i+1,ready_list[i].at,ready_list[i].st,ready_l
    ist[i].ft, (ready_list[i].ft-ready_list[i].at),(ready_list[i].ft-ready_list[i].at)
    -ready_list[i].st);
    }
}
