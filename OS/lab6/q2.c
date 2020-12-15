#include <unistd.h>
#include <stdlib.h>
#include<string.h>
#include<sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/shm.h>
#include "shared_conn.h"

int main()
{
	void *shared_memory = (void *)0;
	struct shared_mem *shared_stuff;
	char c[1];
	int shmid;
	shmid = shmget((key_t)1234,sizeof(struct shared_mem),0666|IPC_CREAT);
	if(shmid == -1)
	{
		printf("shmget failed \n");
		exit(1);
	}
	shared_memory = shmat(shmid,(void *)0,0);
	if(shared_memory == (void *)-1)
	{
		printf("shmat failed\n");
		exit(1);
	}
	printf("Shared memory attached at %X\n",(int)shared_memory );
	shared_stuff = (struct shared_mem*)shared_memory;
	pid_t cpid=fork();
	if(cpid==-1){
		perror("fork");
		exit(EXIT_FAILURE);
	}if(cpid==0){
		while(1)
		{
			if(shared_stuff->written_by_you==1)
			{
				printf("Recieved from parent : %s\n",shared_stuff->text);
				strcpy(c,shared_stuff->text);
				c[0] = c[0] + 1;
				strcpy(shared_stuff->text,c);
				printf("Sent to parent : %s\n",shared_stuff->text );
				shared_stuff->written_by_you = 0;
				break;
			}
		}
	}else{
		while(shared_stuff->written_by_you==1)
		{
			sleep(1);
		}
		printf("Enter the character \n");
		scanf("%s",c);
		strcpy(shared_stuff->text,c);
		shared_stuff->written_by_you = 1;
		while(shared_stuff->written_by_you==1)
			sleep(1);
		printf("The character recieved from child is %s\n", shared_stuff->text);
	}
	if(shmdt(shared_memory)==-1)
	{
		printf("Shmdt failed\n");
		exit(1);
	}
}