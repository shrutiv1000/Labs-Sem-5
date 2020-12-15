#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *fa, *fb;
	int ca;
	fa = fopen("in.bin", "r");
	if (fa == NULL){
		printf("Cannot open file \n");
		exit(0); 
	}
	fb = fopen("out.bin", "w");
	ca = getc(fa);
	while (ca != EOF)
	{
		putc(ca,fb);
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	return 0;
}