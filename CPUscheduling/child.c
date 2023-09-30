#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<ctype.h>
#include<wait.h>
#include<unistd.h>

struct process {
	int pid,at,bt,ct,tat,wt,rt;
};


void fcfs(struct process *p,int n){

	p[0].ct=p[0].at + p[0].bt;
	p[0].tat = p[0].ct - p[0].at;
	p[0].wt = p[0].tat - p[0].bt;
	
	for(int i=1;i<n;i++){
		if(p[i].at > p[i-1].ct) {
			p[i].ct = p[i].at + p[i].bt;
		}
		else{
			p[i].ct = p[i-1].ct + p[i].bt;
		}
		p[i].tat = p[i].ct - p[i].at;
		p[i].wt = p[i].tat - p[i].bt;
	}		
}

void sjf(struct process *p, int n) {
    int i, j;
    struct process temp;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[j].bt < p[i].bt) {
                temp = p[j];
                p[j] = p[i];
                p[i] = temp;
            }
        }
    }

    fcfs(p, n);
}


void srtf(struct process *p,int n)
{
    int i,j,k,l,m;
    int rem_bt[n];
    for(i=0;i<n;i++)
        rem_bt[i]=p[i].bt;
    int t=0;
    int flag=0;
    while(1)
    {
        flag=0;
        for(i=0;i<n;i++)
        {
            if(rem_bt[i]>0 && p[i].at<=t)
            {
                flag=1;
                if(rem_bt[i]==p[i].bt)
                    p[i].rt=t-p[i].at;
                if(rem_bt[i]>1)
                {
                    rem_bt[i]--;
                    t++;
                }
                else
                {
                    rem_bt[i]=0;
                    p[i].ct=t+1;
                    p[i].tat=p[i].ct-p[i].at;
                    p[i].wt=p[i].tat-p[i].bt;
                }
            }
        }
        if(flag==0)
            break;
    }
}


void print_gantt_chart(struct process *p, int n)
{
    int i, j;
    // print top bar
    printf(" ");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].bt; j++) printf("--");
        printf(" ");
    }
    printf("\n|");
 
    // printing process id in the middle
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].bt - 1; j++) printf(" ");
        printf("P%d", p[i].pid);
        for(j=0; j<p[i].bt - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");
    // printing bottom bar
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].bt; j++) printf("--");
        printf(" ");
    }
    printf("\n");
 
    // printing the time line
    printf("0");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].bt; j++) printf("  ");
        if(p[i].tat > 9) printf("\b"); // backspace : remove 1 space
        printf("%d", p[i].tat);
 
    }
    printf("\n");
 
}

int main(){
	int i,n;
	struct process *p;
	key_t key=3174;
	int shmid = shmget(key,sizeof(struct process *),IPC_CREAT|0666);
	
	p=(struct process *)shmat(shmid,NULL,0);
	printf("Enter number of processes:");
	scanf("%d",&n);
	fcfs(p,n);
    	printf("\nGantt Chart:\n\n");
    	for (i = 0; i < n; i++) {
		printf("P%d(%d-%d)", p[i].pid, p[i].ct-p[i].bt, p[i].ct);
		if (i != n - 1) {
	   		printf(", idle(%d-%d), ", p[i].ct, p[i + 1].at);
		}
  	}	
	printf("\n\n");
	printf("\nProcess Table :\n\n");
    	puts("+-----+--------------+------------+-----------------+--------------+-----------------+");
    	puts("| PID | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time |");
    	puts("+-----+--------------+------------+-----------------+--------------+-----------------+");
 
   	for(i=0; i<n; i++) {
      printf("| %2d  |     %2d       |     %2d      |        %2d      |      %2d      |        %2d      |\n"
		, p[i].pid,p[i].at,  p[i].bt,p[i].ct, p[i].wt, p[i].tat );
	puts("+-----+--------------+------------+-----------------+--------------+-----------------+");
   	}	
   	printf("\n\n");
   	printf("\nGantt Chart:\n\n");
   	print_gantt_chart(p,n);
	return 0;
}	


























	


