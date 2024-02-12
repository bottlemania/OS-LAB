#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<stdlib.h>
#define SHMSZ 50
void main()
{
int shmid;
key_t key;
char *shm, *s;
key = 5678;
shmid = shmget(key, SHMSZ, 0666);
shm = (char*)shmat(shmid, NULL, 0);

for (s = shm; *s != '\0'; s++)
putchar(*s);

*shm = '*';
exit(0);
}
