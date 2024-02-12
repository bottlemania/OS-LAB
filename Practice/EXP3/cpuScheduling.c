#include<stdio.h>
#include<stdlib.h>

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




int main(){

	int n,i;
	printf("Enter number of Processes:");
	scanf("%d",&n);
    struct process *p = malloc(n * sizeof(struct process));

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

    fcfs(p,n);

    printf("\nGantt Chart:\n\n");
 
    for (i = 0; i < n; i++) {
        printf("P%d(%d-%d)", p[i].pid, p[i].ct - p[i].bt, p[i].ct);
        if (i != n - 1 && p[i].ct < p[i + 1].at) {
            printf(", idle(%d-%d), ", p[i].ct, p[i + 1].at);
        }
    }

	return 0;    
}