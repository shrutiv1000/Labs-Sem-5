#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printStatStuct(char fname[]){
	struct stat sb;
	int n;
	n = stat(fname,&sb);
	if(n)
	{
		perror("stat");
		return;
	}
	printf("The ID of device containing file %s is %ld\n",fname,sb.st_dev );
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

void printdir(char *dir, int depth)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(dir)) == NULL) 
	{
		fprintf(stderr," cannot open directory: %s\n", dir);
		return;
	}
	chdir(dir);
	while((entry = readdir(dp)) != NULL) 
	{
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)) 
		{
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
				continue;
			printf("%*s%s/\n",depth,"",entry->d_name);
			printdir(entry->d_name,depth+4);
		}
		else{
			printf("%*s%s\n\n",depth,"",entry->d_name);
			printStatStuct(entry->d_name);
			printf("\n");
		}
	}
	chdir("..");
	closedir(dp);
}
int main(int argc, char ** argv)
{
	 if(argc<2){
        printf("Error!");
        exit(0);
    }
	printf("Directory scan of %s\n",argv[1]);
	printdir(argv[1],0);
	printf("\nDone.\n");
	exit(0);
}
