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
	int pfd[2],writing=1;
	char buff_in[20],buff_out;
	if(pipe(pfd)==-1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	printf("Pipe Created!\n");
	while(1){
		if(writing==0){
			close(pfd[1]);
			printf("\nReading. Message: ");
			while(read(pfd[0],&buff_out,1))
				printf("%c",buff_out);
			printf("\n");
			close(pfd[0]);
			writing =1;
			break;
		}else if(writing==1){
			memset(buff_in,0,sizeof(buff_in));
			printf("\nWriting. Enter String to Write: ");
			scanf(" %s", buff_in);
			write(pfd[1],buff_in,strlen(buff_in));
			close(pfd[1]);
			writing=0;
		}if(strcmp(buff_in,"exit")==0){
			break;
		}
	}
	return 0;
}