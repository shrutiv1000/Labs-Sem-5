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
		printf("Child process started, Process Id: %d\n",getpid());
		exit(0);
	}else{
		printf("Parent Process Id: %d\n", getpid());
		execlp("/bin/ps","ps",NULL);
		exit(0);
	}
}