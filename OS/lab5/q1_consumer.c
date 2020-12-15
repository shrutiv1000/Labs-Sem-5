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
	int res,buff;
	int open_mode = O_RDONLY;
	int bytes_sent = 0;
	int buffer;
	printf("Process % d opening fifo\n", getpid());
	pipe_fd = open(FILE_NAME,open_mode);
	printf("Process %d : Result %d\n",getpid(),pipe_fd );
	if(pipe_fd!=-1)
	{
		res = read(pipe_fd,&buff,4);
		printf("Recieved, number of numbers to be sent : %d\n",buff);
	}
	else{
		printf("Error opening the pipe\n");
		exit(1);
	}
	for(int i=0;i<buff;i++){
		res = read(pipe_fd,&buffer,4);
		printf("Recieved : %d",buffer);
	}
	printf("Finished\n");
}