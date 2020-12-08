#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char buf[500];
	char c;
	int i=0,in;
	if(argc<2){
		printf("Error!");
		exit(0);
	}
	in = open(argv[1],O_RDONLY);
	if(in==-1){
		printf("\nFile Not found!");
		exit(0);
	}
	int linecounter = 0;
	while(read(in,&c,sizeof(char))>0)
	{
		if(c=='\n')
		{
			i=0;
			linecounter++;
			printf("%s \n",buf);
			memset(buf, 0, sizeof(buf));
			if(linecounter==20){
				printf("\nPress any key to continue\n" );
				getchar();
				linecounter=0;
			}
		}
		buf[i] = c;
		i++;
	}
}