
/*This is a multiline comment
sbhfhjbvfkehkhg
efbwukygfuy3*/
int main()
{              
	FILE *fa, *fb;
	int ca, cb;
	fa = fopen("in.c", "r");
	if (fa == NULL){
		printf("#include Cannot open file \n");
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
		if (ca=='/')
		{
			cb = getc(fa);
			if (cb == '/')
			{
				while(ca != '\n')
					ca = getc(fa);//Comment 1
			}                                 
			else if (cb == '*')
			{                                             
				do{
					while(ca != '*')
					ca = getc(fa);
					ca = getc(fa);
				}while (ca != '/');
			}
			else
			{
				putc(ca,fb);
				putc(cb,fb);
			}//Comment 2
		}
		else putc(ca,fb);
			ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	return 0;
	}
}
