#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/ipc.h>
#include<sys/msg.h>

struct my_msg {
	long int msg_type;
	char number[10];
};

int main()
{
	struct my_msg msg;
	int msgid;
	char buffer[10];
	printf("Enter the  number \n");
	scanf("%s",buffer);
	msgid = msgget((key_t)1234,0666|IPC_CREAT);
	if(msgid == -1)
	{
		printf("Msgget falied.\n");
		exit(1);
	}
	msg.msg_type = 1;
	strcpy(msg.number,buffer);
	if(msgsnd(msgid,(void *)&msg,10,0)==-1)
	{
		printf("Msgsnd falied\n");
		exit(1);
	}

}