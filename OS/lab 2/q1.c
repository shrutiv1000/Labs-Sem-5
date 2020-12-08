#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if(argc<2){
        printf("Error!");
        exit(0);
    }
    DIR * dp;
    struct dirent * entry;
    struct stat statbuf;
    if((dp = opendir(argv[1])) == NULL) {
        printf("Cannot open directory \n");
        return 0;
    }
    chdir(argv[1]);
    while((entry = readdir(dp)) != NULL)
    {
        lstat(entry->d_name,&statbuf);
        if(!S_ISDIR(statbuf.st_mode)){
            printf("%s \t",entry->d_name);
            printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
            printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
            printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
            printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
            printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
            printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
            printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
            printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
            printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
            printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
            printf("\n\n");
        }
    }
}