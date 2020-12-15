#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
	int sd,nd,n,len,reult,n1;
	struct sockaddr_in seraddress, cliaddr;
	int op1,op2,ans;
	char op;
	sd=socket(AF_INET, SOCK_STREAM,0);
	if (sd == -1) 
	{
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	seraddress.sin_family=AF_INET;
	seraddress.sin_addr.s_addr=INADDR_ANY;
	seraddress.sin_port=htons(10200);
	len=sizeof(seraddress);
	
	if (connect(sd,(struct sockaddr*)&seraddress,len) != 0) 
	{
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

		printf("Enter op1 : ");
		scanf("%d",&op1);
		write(sd, &op1, sizeof(op1));

		printf("Enter op2 : ");
		scanf("%d", &op2);
		write(sd, &op2, sizeof(op2));

		printf("Enter op : ");
		scanf(" %c",&op);
		write(sd, &op, sizeof(op));

		read(sd, &ans, sizeof(ans));
		printf("From Server : %d", ans);

	getchar();
}
