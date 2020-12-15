#include<stdio.h>
#include <sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	struct stat sb;
	if(argc<2)
	{
		printf("Error! \n");
		exit(1);
	}
	stat("./q3.c",&sb);
	printf("Initial number of links : %ld \n",sb.st_nlink);

	printf("Linking ...\n");
	int n= link("./q3.c",argv[1]);
	if(n)
	{
		perror("link");
		return 1;
	}
	printf("Hard Link created successfully \n");
	stat("./q3.c",&sb);
	printf("Number of links after creation of hard link : %ld\n",sb.st_nlink );

	printf("Unlinking ...\n");
	n= unlink(argv[1]);
	if(n)
	{
		perror("unlink");
		return 1;
	}
	printf("Unlinking Successful\n");
	stat("./q3.c",&sb);
	printf("Number of links after unlinking of hard link : %ld\n",sb.st_nlink );
}