
#include <stdio.h>
struct process
{
    int at;
    int st;
    int cpu;
    int status;
    int ft;
} ready_list[10];
int n;
int dispatcher(int time)
{
    int i, index = -1;
    for (i = 0; i < n; i++)
    {
        if (ready_list[i].status != 1)
            if (ready_list[i].at <= time)
            {
                index = i;
                return index;
            }
    }
    return index;
}
int main()
{
    int i, j, cur_time, pid, h;
    printf("Enter number of processes:");
    scanf("%d", &n);
    printf("Enter no of cpu");
    scanf("%d", &h);
    // Collect process details -
    for (i = 0; i < n; i++)
    {
        printf("Process %d\n", i + 1);
        printf("***********\n");
        printf("Enter Arrival Time:");
        scanf("%d", &ready_list[i].at);
        printf("Enter Service Time:");
        scanf("%d", &ready_list[i].st);
        ready_list[i].status = 0;
    }
    i = 0, cur_time = 0;
    while (i < n)
    {
        for (j = 0; j < h; j++)
        {
            pid = dispatcher(cur_time);
            ready_list[pid].ft = ready_list[i].at + ready_list[pid].st;
            ready_list[pid].status = 1;
            ready_list[pid].cpu = j + 1;
            cur_time += ready_list[pid].st;
            i++;
        }
    }
    printf("Process\t Arrival Time\t Burst Time\t Finish Time \t CPU \tTT \t WT\n");
    printf("*******\t ************\t ************\t ***********\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t\t%d\t%d\t%d\t%d\n", i, ready_list[i].at, ready_list[i].st,
               ready_list[i].ft, ready_list[i].cpu,
               (ready_list[i].ft - ready_list[i].at), (ready_list[i].ft - ready_list[i].at) - ready_list[i].st);
    }
}