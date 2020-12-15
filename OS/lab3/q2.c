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
		printf("Child process started");
		execlp("./q1",(char *)0,NULL);
	}
	else{
		wait(NULL);
		printf("\nChild Completed\n");
		exit(0);
	}
}