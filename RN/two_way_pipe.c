#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

void main(){
	int p1[2],p2[2];
	pipe(p1);
	pipe(p2);
	int pid;
	char Pin[15],Pout[15],Cin[15],Cout[15];
	int rtck = 0;
	pid = fork();
	if(pid){
l1 :
		if(rtck==0){
			printf("Enter message(from parent to child) : ");
			scanf("%s",Pin);
			write(p1[1],Pin,sizeof(Pin));
			sleep(3);
		}
		if(rtck==1){
			sleep(3);
			read(p2[0],Cout,sizeof(Cout));
			printf("Child said %s",Cout);
			rtck = -1;
		}
	}
	else{
		if(rtck==0){
			sleep(3);
			read(p1[0],Pout,sizeof(Pout));
			printf("Parent said %s",Pout);
			rtck = 1;
		}
		if(rtck==1){
			printf("Enter message(from child to parent) : ");
			scanf("%s",Cin);
			write(p2[1],Cin,sizeof(Cin));
			sleep(3);
			goto l1;
		}
	}
}