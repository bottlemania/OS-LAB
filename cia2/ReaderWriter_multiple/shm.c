#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<unistd.h>
#define SHMSZ 1024

int main()
{
  key_t key;
  
  int shmid;

  char *shm , *k , *s;
 
  key = 3415;
  
  if((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666))<0)
  {
    perror("shmget");
	
    exit(1);
  }

  if((shm = shmat(shmid,NULL,0)) == (char *)-1)
  {
	perror("shmat");
	
    exit(1);
  }

  s = shm;
  
  char pattern[10];

  printf("\nEnter the pattern: ");

  fgets(pattern,10, stdin); //Will accept till ENTER key is hit...

  int len = sizeof(pattern);
  
  for(int i = 0; i < len; i++)
  {
	  printf("%c",pattern[i]);
  }	  
  
  int choice;

  printf("1. READER PRIORITY \n2. WRITER PRIORITY\n");
  
  printf("\nEnter your choice (1/2): ");

  scanf("%d",&choice);

  if(choice == 1)//Reader Priority
  { 
	char first = pattern[0];

        printf("\nThe first character is: %c",first);

        if(first == 'R')
        {
		int rcount = 0;

		int wcount = 0;

		for (int i = 0; i < len; i++)
		{
			if(pattern[i] == 'R')
				rcount = rcount + 1;
			else if(pattern[i] == 'W')
				wcount = wcount + 1;
   		}
		printf("\nThe no. of readers is: %d",rcount);

		printf("\nThe no. of writer is: %d\n",wcount);

    		for(int i = 0; i < rcount; i++)
		{
			system("gnome-terminal -- ./r.out");

			sleep(2);

   		}

		for(int i = 0; i < wcount; i++)
		{
			system("gnome-terminal -- ./w.out");

			sleep(10);

   		}
        }
	else
	{
		int count = 0;
		do
		{
			system("gnome-terminal -- ./w.out");

			sleep(10);

			count = count + 1;
			
		}while(pattern[count] != 'R');

		int rcount = 0;

		int wcount = 0;

		for (int i = count; i < len; i++)
		{
			if(pattern[i] == 'R')
				rcount = rcount + 1;
			else if(pattern[i] == 'W')
				wcount = wcount + 1;
   		}
		printf("\nThe no. of readers is: %d",rcount);

		printf("\nThe no. of writer is: %d\n",wcount);

    		for(int i = 0; i < rcount; i++)
		{
			system("gnome-terminal -- ./r.out");

			sleep(2);

   		}

		for(int i = 0; i < wcount; i++)
		{
			system("gnome-terminal -- ./w.out");

			sleep(10);

   		}
	}	
  }
  else if(choice == 2)
  { 
	char first = pattern[0];

        printf("\nThe first character is: %c",first);

        if(first == 'W')
        {
		int rcount = 0;

		int wcount = 0;

		for (int i = 0; i < len; i++)
		{
			if(pattern[i] == 'R')
				rcount = rcount + 1;
			else if(pattern[i] == 'W')
				wcount = wcount + 1;
   		}
		printf("\nThe no. of readers is: %d",rcount);

		printf("\nThe no. of writer is: %d\n",wcount);

    		for(int i = 0; i < wcount; i++)
		{
			system("gnome-terminal -- ./w.out");

			sleep(10);

   		}

		for(int i = 0; i < rcount; i++)
		{
			system("gnome-terminal -- ./r.out");

			sleep(2);

   		}
        }
	else
	{
		int count = 0;
		do
		{
			system("gnome-terminal -- ./r.out");

			sleep(2);

			count = count + 1;
			
		}while(pattern[count] != 'W');

		int rcount = 0;

		int wcount = 0;

		for (int i = count; i < len; i++)
		{
			if(pattern[i] == 'R')
				rcount = rcount + 1;
			else if(pattern[i] == 'W')
				wcount = wcount + 1;
   		}
		printf("\nThe no. of readers is: %d",rcount);

		printf("\nThe no. of writer is: %d\n",wcount);

		sleep(3);

    		for(int i = 0; i < wcount; i++)
		{
			system("gnome-terminal -- ./w.out");

			sleep(10);

   		}

		for(int i = 0; i < rcount; i++)
		{
			system("gnome-terminal -- ./r.out");

			sleep(2);

   		}
	}	
  }

  return 0;

}






