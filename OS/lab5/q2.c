#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<assert.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc, char const *argv[])
{
	int pfd[2];
	pid_t cpid;
	char buff;
	assert(argc==2);
	if(pipe(pfd)==-1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}printf("Pipe Created!\n");
	cpid=fork();
	if(cpid==-1){
		perror("fork");
		exit(EXIT_FAILURE);
	}if(cpid==0){
		close(pfd[1]);
		printf("Inside Child Process, Reading!\n");
		while(read(pfd[0],&buff,1))
			printf("%c",buff);
		printf("\n");
		close(pfd[0]);
		exit(EXIT_SUCCESS);
	}else{
		close(pfd[0]);
		printf("Inside Parent Process, Writing!\n");
		write(pfd[1],argv[1],strlen(argv[1]));
		close(pfd[1]);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
	return 0;
}