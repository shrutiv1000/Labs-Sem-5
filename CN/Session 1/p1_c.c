#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

#define PORT 5000
#define MAXLINE 1000
// Driver code

int main()
{	int matrix[100][100];
	int row,col;
	printf("Enter number of rows and colums: ");
	scanf("%d %d",&row,&col);
	printf("Enter matrix");
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++)
			scanf("%d",&matrix[i][j]);
	}  
	int sockfd, n,len;
	int tosend[2]={row,col};
	struct sockaddr_in servaddr, cliaddr;
	// clear servaddr
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;
	// create datagram socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	sendto(sockfd, matrix, MAXLINE, 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
	len=sizeof(cliaddr);
	char buffer[20];
	n=recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr,&len );        
	buffer[n]='\0';
	printf("%s \n",buffer); 
	getchar();
	sendto(sockfd, tosend, MAXLINE, 0, (struct sockaddr*)&servaddr, sizeof(servaddr));       
	getchar();    
	// close the descriptor
	close(sockfd);
}
