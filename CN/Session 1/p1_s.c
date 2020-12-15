#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#define PORT 5000
#define MAXLINE 1000
// Server code
int main()
{	int matrix[100][100];
	int row,col;
	int servsockfd, len,n=4;
	struct sockaddr_in servaddr, cliaddr;
	bzero(&servaddr, sizeof(servaddr));
	int tosend[2];
	// Create a UDP Socket
	servsockfd = socket(AF_INET, SOCK_DGRAM, 0);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	// bind server address to socket descriptor
	bind(servsockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	//receive the datagram
	len = sizeof(cliaddr);  
	recvfrom(servsockfd, matrix, sizeof(matrix),0, (struct sockaddr*)&cliaddr,&len);
	//printf("%d\n%d",matrix[0][0],row);
	sendto(servsockfd, "sent", n, 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
	recvfrom(servsockfd, tosend, sizeof(tosend),0, (struct sockaddr*)&cliaddr,&len); 
	row=tosend[0];
	col=tosend[1]; 
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++)
			printf("%d ",matrix[i][j]);
	printf("\n");
	}               
	getchar();
	// close the descriptor
	close(servsockfd);
}
