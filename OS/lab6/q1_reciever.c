#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/ipc.h>
#include<sys/msg.h>

struct my_msg {
	long int msg_type;
	char number[10];
};

int isPalin(char number[10]){
	int n=strlen(number);
	for(int i=0;i<n/2;i++){
		if(number[i]!=number[n-i-1])
			return 0;
	}return 1;
}

int main(){
	int msgid;
	struct my_msg data;
	long int msg_to_recieve=0;
	msgid=msgget((key_t)1234,0666|IPC_CREAT);
	if(msgid==-1){
		fprintf(stderr,"msgget failed with error: %d\n",errno);
		exit(EXIT_FAILURE);
	}
	if(msgrcv(msgid,(void*)&data,BUFSIZ,msg_to_recieve,0)==-1)
	{
		fprintf(stderr,"msgrcv failed with error: %d\n",errno);
		exit(EXIT_FAILURE);
	}printf("Number Recieved: %s\n", data.number);
	if(isPalin(data.number)){
		printf("Number is a Palindrome!");
	}else
		printf("Number is not a Palindrome!");
	if(msgctl(msgid,IPC_RMID,0)==-1){
		fprintf(stderr,"msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}exit(EXIT_SUCCESS);
}