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
	int sd,nd,n,len,reult;
	struct sockaddr_in seraddress, cliaddr;
	int op1,op2,ans;
	char op;
	sd=socket(AF_INET, SOCK_STREAM,0);
	if (sd == -1) 
	{
		printf("socket creation failed...\n");
		exit(0);
	}else
		printf("Socket successfully created..\n");
	seraddress.sin_family=AF_INET;
	seraddress.sin_addr.s_addr=INADDR_ANY;
	seraddress.sin_port=htons(10200);
	if (bind(sd,(struct sockaddr*)&seraddress,sizeof(seraddress)) != 0) 
	{
		printf("socket bind failed...\n");
		exit(0);
	}else
		printf("Socket successfully binded..\n");
	if ((listen(sd, 5)) != 0) 
	{
		printf("Listen failed...\n");
		exit(0);
	}else
		printf("Server listening..\n");
	len=sizeof(cliaddr);
	while(1)
	{
		nd=accept(sd,(struct sockaddr*)&cliaddr,&len);
		if (nd < 0)
		{
			printf("server acccept failed...\n");
			exit(0);
		}else
			printf("server acccept the client...\n");
		if (fork()!=0){
			wait(NULL);
			break;
		}{
		// read the op1 from client
		read(nd, &op1, sizeof(op1));
		//printf("%d\n", op1);
		// read the op2 from client
		read(nd, &op2, sizeof(op2));
		// read the op from client
		read(nd, &op, sizeof(op));
		// perform operation
		switch(op){
			case '+' : ans=op1+op2; break;
			case '/' : ans=op1/op2; break;
			case '*' : ans=op1*op2; break;
			case '-' : ans=op1-op2; break;
		}
		//printf("%d\n", ans);
		// and send that buffer to client
		write(nd, &ans, sizeof(ans));
		close(nd);
		//exit(0);
		}
		//getchar();
	}
	close(sd);
}
