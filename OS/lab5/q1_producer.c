#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<limits.h>
#include<sys/types.h>
#include<sys/stat.h>
 
#define FILE_NAME "/tmp/my_fifo"


int main()
{
	int pipe_fd;
	int res,buff,buf;
	int open_mode = O_WRONLY;
	int bytes_sent = 0;
	char buffer[4];
	if(access(FILE_NAME,F_OK)==-1)
	{
		res = mkfifo(FILE_NAME,0777);
		if(res!=0)
		{
			printf("Cannot create fifo\n");
			exit(1);
		}
	}
	printf("Process % d opening fifo\n", getpid());
	pipe_fd = open(FILE_NAME,open_mode);
	printf("Process %d : Result %d\n",getpid(),pipe_fd );
	printf("Enter Number: ");
	scanf("%d",&buff);
	if(pipe_fd!=-1)
	{
		res = write(pipe_fd,&buff,4);
		if(res==-1)
		{
			printf("Error writing on pipe\n");
			exit(1);
		}	
	}else{
		printf("Error opening the pipe\n");
		exit(1);
	}
	for(int i=0;i<buff;i++){
		printf("Enter the Number: ");
		scanf("%d",&buf);
		res = write(pipe_fd,&buf,4);
		if(res==-1)
		{
			printf("Error writing on pipe\n");
			exit(1);
		}
	}
	(void)close(pipe_fd);
	printf("Finished\n");
}