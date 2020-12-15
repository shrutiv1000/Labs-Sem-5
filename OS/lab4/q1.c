#include<stdio.h>
#include <sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include <stdlib.h>

int main(int argc , char *argv[])
{
	struct stat sb;
	int n;
	if(argc<2)
	{
		printf("Error!\n");
		exit(1);
	}
	n = stat(argv[1],&sb);
	if(n)
	{
		perror("stat");
		return 1;
	}
	printf("The inode number of file %s is %ld\n",argv[1],sb.st_ino );
}