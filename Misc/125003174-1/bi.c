#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>
int main(){
	int p[2],p1[2],p2[2];
	char in[20],out[20],inbuf[20],outbuf[20];
	pipe(p);
	pipe(p1);
	pipe(p2);
	int pid=fork();
	if(pid==-1){
		printf("Fork failed to create");
	}
	if(pid){
		close(p1[0]);
		printf("Initiating Parent process (id=%d)\n",getpid());
		sleep(1);
		printf("Parent: "); scanf("%s",out);	
		write(p1[1],out,sizeof(out));
		close(p1[1]);
		close(p2[1]);
		read(p2[0],inbuf,20);
		close(p2[0]);		
		printf("						 Parent: %s\n",inbuf);		
	}
	else{
		close(p1[1]);
		printf("Initiating Child process (id=%d)\n\n",getpid());
		printf("Sender					Receiver\n\n");
		read(p1[0],in,20);
		close(p1[0]);
		printf("						 Child: %s\n",in);
		close(p2[0]);
		printf("Child: "); scanf("%s",outbuf); 
		write(p2[1],outbuf,sizeof(outbuf));		
		close(p2[1]);
	}
	return 0;
}

