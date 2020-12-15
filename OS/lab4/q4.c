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
		printf("Error!\n");
		exit(1);
	}
	int n= symlink("./q4.c",argv[1]);
	if(n)
	{
		perror("link");
		return 1;
	}
	printf("Soft Link created successfully \n");
	
	printf("Unlinking ...\n");
	n= unlink(argv[1]);
	if(n)
	{
		perror("unlink");
		return 1;
	}
	printf("Unlinking Successful\n");
	
}