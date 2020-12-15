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
	printf("The ID of device containing file %s is %ld\n",argv[1],sb.st_dev );
	printf("The inode number is %ld\n",sb.st_ino );
	printf("The permissions is %d\n",sb.st_mode );
	printf("The number of hard links is %ld\n",sb.st_nlink );
	printf("The user ID of owner is %d\n",sb.st_uid);
	printf("The grew ID of owner is %d\n",sb.st_gid);
	printf("The device ID (if special file) is %ld\n",sb.st_rdev);
	printf("The total size in bytes is %ld\n",sb.st_size );
	printf("The blocksize for filesystem I/O is %ld\n",sb.st_blksize );
	printf("The number of blocks allocated is %ld\n",sb.st_blocks );
	printf("The last acess time is %ld\n",sb.st_atime );
	printf("The last modification time is %ld\n",sb.st_mtime );
	printf("The last status change time  is %ld\n",sb.st_ctime );
}

