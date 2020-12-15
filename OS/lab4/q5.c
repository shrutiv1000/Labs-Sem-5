#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
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
			struct stat sb;
			int n = stat(entry->d_name,&sb);
			if(n)
			{
				perror("stat");
				return 1;
			}
			printf("%*s%s\tInode Number:%d\n",depth,"",entry->d_name,sb.st_ino);
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
