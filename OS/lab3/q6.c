#include<stdio.h>
#include<sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	pid_t pid =fork();
	if(pid<0)
	{
		printf("Some error occured \n");
		exit(0);
	}
	else if(pid ==0 )
	{
		printf("Child process started, Process Id: %d, Parent Process Id: %d\nGoing to Sleep\n",getpid(),getppid());
		sleep(10);
		printf("Child Woke Up, Process Id: %d, Parent Process Id: %d\n",getpid(),getppid());
		exit(0);
	}else{
		printf("Parent Process Id: %d, Parent's Parent Process Id: %d\n", getpid(),getppid());
		pid_t status;
		wait(&status);
		printf("%d",status);
		exit(0);
	}
}