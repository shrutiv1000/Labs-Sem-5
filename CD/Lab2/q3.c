#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main()
{
	FILE *fa;
	char c,keyw[100][100]={"void","main","while","break","if","else"};
	int n=6;
	fa = fopen("in.c", "r");
	if (fa == NULL)
	{	
		printf("Cannot open file \n");
		exit(0);
	}
	c=getc(fa);
	while(c!=EOF)
	{
		if(isalpha(c))
		{
			char buf[100];
			int x=0;
			while(isalpha(c))
			{
				buf[x++]=c;
				c=getc(fa);
			}
			if(c==' '||c=='\t'||c=='\n'||c=='('||c=='{'||c==';')
			{
				buf[x]='\0';
				int i;
				for(i=0;i<n;i++)
				{
					if(strcmp(buf,keyw[i])==0)
					{
						for(int j=0;j<x;j++)
							printf("%c",toupper(buf[j]));
						printf("\n");
						break;
					}
				}
			}
			else
			{
			while(c!=' ' && c!='\t' && c!='\n' && c!='{' && c!=';' && c!=EOF)
				c=getc(fa);
			}
		}
		else
		{
		while(c!=' ' && c!='\t' && c!='\n' && c!=';' && c!='{' && c!=EOF)
			c=getc(fa);
		}
		if(c!=EOF)
			c=fgetc(fa);
	}
	fclose(fa);
}