#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *fa, *fb;
	int ca, cb;
	fa = fopen("in.c", "r");
	if (fa == NULL){
		printf("Cannot open file \n");
		exit(0); }
	fb = fopen("out.c", "w");
	ca = getc(fa);
	while (ca != EOF)
	{
		if(ca==' ')
		{
			putc(ca,fb);
			while(ca==' ')
			ca = getc(fa);
		}
		if (ca=='/t')
		{
			putc(' ',fb);
		}
		else 
			putc(ca,fb);
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	return 0;
}