#include<stdio.h>
#include<sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	printf("Before fork, in parent\n");
	pid_t pid =fork();
	printf("After fork\n");
	if(pid<0)
	{
		printf("Some error occured \n");
		exit(0);
	}
	else if(pid ==0 )
	{
		printf("Child process started\nCounting till 10: ");
		for(int i=0;i<10;i++)
		{
			printf("%d ",i);
		}
		printf("\nChild process Exiting");
	}
	else{
		wait(NULL);
		printf("\nChild Completed\n");
		exit(0);
	}
}