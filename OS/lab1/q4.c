#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	char c;
	int in, out;
	in = open(argv[1], O_RDONLY);
	out = open(argv[2], O_WRONLY|O_CREAT, S_IRUSR | S_IWUSR);
	while(read(in,&c,1) == 1)
	write(out,&c,1);
	exit(0);
}