#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	FILE *fa, *fb;
	int ca, cb;
	char prep[]={"#include","#define"};
	char buff[100];
	fa = fopen("in.c", "r");
	fb = fopen("out.c", "w");
	if (fa == NULL || fb==NULL){
		printf("Cannot open file \n");
		exit(0); }
	ca = getc(fa);
	while (ca != EOF)
	{
		memset(buff,0,sizeof(buff));
		if(ca=='#')
		{
			int i=0;
			while(ca!=' '){
				buff[i++]=ca;
				ca = getc(fa);
			}
			buff[i]='\0';
			puts(buff);
			for(int j=0; j<2;j++){
				if(strcmp(buff,prep[j])==0)
				{
					while(ca!='\n')
						ca = getc(fa);
					i=0;
					break;
				}
			}if(i==0)
				continue;
			else
			{
				for(int j=0;j<i;j++)
					putc(buff[j],fb);
			}
		}
		else 
			putc(ca,fb);
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	return 0;
}