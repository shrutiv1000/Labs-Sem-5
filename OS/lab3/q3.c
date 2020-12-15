#include<stdio.h>
#include<sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	printf("In Parent\n");
	printf("pid: %d\n",getpid());
	printf("ppid: %d\n",getppid());
	pid_t pid =fork();
	if(pid<0)
	{
		printf("Some error occured \n");
		exit(0);
	}
	else if(pid ==0 )
	{
		printf("\nIn Child\n");
		printf("pid: %d\n",getpid());
		printf("ppid: %d\n",getppid());
	}
	else{
		wait(NULL);
		printf("\nChild Completed\n");
		exit(0);
	}
}