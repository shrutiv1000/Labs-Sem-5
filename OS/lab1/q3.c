#include<stdio.h>
#include<errno.h>

void main()
{
	printf("Conversion specifiers\n");
	printf("For integers: %d\n",25);
	printf("For characters: %c\n",'s');
	printf("For string: %s\n","string");
	printf("For floating point numbers: %f\n",1.2);
	errno = EPERM;
	printf("For error: %m");
}
