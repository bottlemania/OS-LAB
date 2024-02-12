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

int main(){
	int i,n;
	struct process *p;
	key_t key=7888;
	
	printf("Enter number of Processes:");
	scanf("%d",&n);
	
	//long unsigned int shareSize=sizeof(struct process *)*4000000000;
	int shmid = shmget(key,10000,IPC_CREAT|0666);
	
	p=shmat(shmid,NULL,0);
	
	for(i=0;i<n;i++){
		printf("\nEnter details of process %d:\n",i+1);
		printf("PID: ");
		scanf("%d",&p[i].pid);
		printf("Arrival Time: ");
		scanf("%d",&p[i].at);
		printf("Burst Time: ");
		scanf("%d",&p[i].bt);
		p[i].ct=p[i].tat=p[i].wt=0;
		p[i].rt=0;
	}
	shmdt(p);
	return 0;
}
	











































