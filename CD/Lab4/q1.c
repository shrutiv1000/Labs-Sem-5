#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct token
{
	char name[20];
	int row,col;
};

struct symbolTableEntry
{
	int id;
	char lexemeName[20];
	char type[20];
	int size;
};

struct localSymbolTable
{
	int i;
	char name[50];
	struct symbolTableEntry entry[50];
};

char buffer[20],currType[20];
char keywords[][20] = {"int","char","float","bool","double","if","else","break","continue","for","while","do","printf","scanf","void","true","false","return"};
char specialchars[] = {',','.','?',':',';','(',')','{','}'};
char arithmaticsymbols[] = {'+','-','*','/'};
int row = 1,col=0,ca,t=-1;
FILE *fa;
struct localSymbolTable table[50];

int isArray(){
	int res=1,i=0;
	int pos = ftell(fa);
	char b[20];
	if(ca =='['){
		ca=getc(fa);
		while(ca!=']'&&isdigit(ca)){
			b[i++]=ca;
			ca=getc(fa);
		}if(i>0){
			b[i]='\0';
			res=atoi(b);
		}
	}
	fseek (fa, 0, SEEK_END);
  	fseek (fa, pos, SEEK_SET);
	return res;
}

int getSize(){
	int n=isArray();
	if(strcmp(currType,"int")==0)
		return 4*n;
	if(strcmp(currType,"char")==0)
		return 1*n;
	if(strcmp(currType,"float")==0)
		return 4*n;
	if(strcmp(currType,"bool")==0)
		return 1*n;
	if(strcmp(currType,"double")==0)
		return 8*n;
	return -1;
}

int isFunction(){
	int res=0;
	int pos = ftell(fa);
	if(ca =='('){
		while(ca!=')'){
			ca=getc(fa);
		}
		ca=getc(fa);
		if(ca=='\n'||ca=='{')
			return 2;
		else return 1;
	}
	fseek (fa, 0, SEEK_END);
  	fseek (fa, pos, SEEK_SET);
	return res;
}

void createSymbolTableEntry(){
	int res=isFunction();
	if(res==2){
		t++;
		table[t].i=-1;
		strcpy(table[t].name,buffer);
	}else if(res==0){
		for(int j=0;j<=table[t].i;j++){
			if(strcmp(table[t].entry[j].lexemeName, buffer)==0)
				return;
		}
		table[t].i++;
		strcpy(table[t].entry[table[t].i].lexemeName, buffer);
		strcpy(table[t].entry[table[t].i].type, currType);
		table[t].entry[table[t].i].id=table[t].i+1;
		table[t].entry[table[t].i].size=getSize();
	}
	else if(res==1)
	{
		for(int j=0;j<=table[t].i;j++){
			if(strcmp(table[t].entry[j].lexemeName, buffer)==0)
				return;
		}
		table[t].i++;
		strcpy(table[t].entry[table[t].i].lexemeName, buffer);
		strcpy(table[t].entry[table[t].i].type, "Func");
		table[t].entry[table[t].i].id=table[t].i+1;
		table[t].entry[table[t].i].size=-1;
	}
}

void printSymbolTable(){
	for(int k=0;k<=t;k++){
		puts(table[k].name);
		for(int j=0;j<=table[k].i;j++){
			printf("%d  %s  %s  %d\n", table[k].entry[j].id, table[k].entry[j].lexemeName, table[k].entry[j].type, table[k].entry[j].size);
		}
		printf("---------------------------------------------------------\n");
	}
}

struct token getNextToken()
{
	while(ca!=EOF)
	{
		//PreProcessors
		if(ca=='#'){
			while(ca!='\n'){
				col++;
				ca=getc(fa);
			}
		}
		//Comments
		if(ca == '/')
		{
			col++;
			ca = getc(fa);
			if(ca == '/')
			{
				while(ca!='\n')
				{
					col++;
					ca = getc(fa);
				}
			}
			else if(ca == '*')
			{
				do{
					while(ca!='*')
					{
						col++;
						if(ca=='\n'){
							col=1;
							row++;
						}
						ca = getc(fa);
					}
					ca = getc(fa);
				}while(ca !='/');
			}
		}
		//Literal
		if(ca=='"')
		{
			int i=0;
			ca = getc(fa);
			col++;
			while(ca!='"')
			{
				buffer[i++] = ca;
				ca = getc(fa);
			}
			buffer[i] = '\0';
			struct token t;
			int j=0;
			while(buffer[j]!='\0')
			{
				t.name[j] = buffer[j];
				j++;
			}
			t.name[j] = '\0';
			t.row = row;
			t.col = col;
			col = col + strlen(buffer);
			ca = getc(fa);
			return t;
		}
		//blank space
		if(ca ==' ')
		{
			col++;
			ca = getc(fa);
		}
		//new line
		if(ca == '\n')
		{
			row++;
			col=1;
			ca = getc(fa);
		}
		//Special Character
		for(int i=0;i<9;i++)
		{
			if(ca==specialchars[i])
			{
				struct token t;
				t.name[0] = ca;
				t.name[1] = '\0';
				t.row = row;
				t.col = col;
				ca = getc(fa);
				col++;
				return t;
			}
		}
		//Arithmatic Operators
		for(int i=0;i<4;i++)
		{
			if(ca == arithmaticsymbols[i])
			{
				struct token t;
				t.name[0] = ca;
				t.name[1] = '\0';
				t.row = row;
				t.col = col;
				ca = getc(fa);
				col++;
				return t;
			}
		}
		//Assignment or equals op
		if(ca == '=')
		{
			ca = getc(fa);
			
			if(ca == '=')
			{
				struct token t;
				t.name[0] = '=';
				t.name[1] = '=';
				t.name[2] = '\0';
				t.row = row;
				t.col = col;
				ca = getc(fa);
				col+=2;
				return t;
			}
			else{
				struct token t;
				t.name[0] = '=';
				t.name[1] = '\0';
				t.row = row;
				t.col = col;
				col++;
				return t;
			}
		}
		//RelOps
		if(ca == '<')
		{
			ca = getc(fa);
			
			if(ca == '=')
			{
				struct token t;
				t.name[0] = '<';
				t.name[1] = '=';
				t.name[2] = '\0';
				t.row = row;
				t.col = col;
				ca = getc(fa);
				col+=2;
				return t;
			}
			else{
				struct token t;
				t.name[0] = '<';
				
				t.name[1] = '\0';
				t.row = row;
				t.col = col;
				col++;
				return t;
			}
		}
		else if(ca == '>')
		{
			ca = getc(fa);
			
			if(ca == '=')
			{
				struct token t;
				t.name[0] = '>';
				t.name[1] = '=';
				t.name[2] = '\0';
				t.row = row;
				t.col = col;
				ca = getc(fa);
				col+=2;
				return t;
			}
			else{
				struct token t;
				t.name[0] = '>';
				
				t.name[1] = '\0';
				t.row = row;
				t.col = col;
				col++;
				return t;
			}
		}
		//logical ops
		if(ca == '&')
		{
			ca = getc(fa);
			
			if(ca == '&')
			{
				struct token t;
				t.name[0] = '&';
				t.name[1] = '&';
				t.name[2] = '\0';
				t.row = row;
				t.col = col;
				ca = getc(fa);
				col+=2;
				return t;
			}
			else{
				struct token t;
				t.name[0] = '&';
				
				t.name[1] = '\0';
				t.row = row;
				t.col = col;
				col++;
				return t;
			}
		}
		if(ca == '|')
		{
			ca = getc(fa);
			
			if(ca == '|')
			{
				struct token t;
				t.name[0] = '|';
				t.name[1] = '|';
				t.name[2] = '\0';
				t.row = row;
				t.col = col;
				ca = getc(fa);
				col+=2;
				return t;
			}
			else{
				struct token t;
				t.name[0] = '|';
				t.name[1] = '\0';
				t.row = row;
				t.col = col;
				col++;
				return t;
			}
		}
		if(ca == '^')
		{
			struct token t;
			t.name[0] = '^';
			t.name[1] = '\0';
			t.row = row;
			t.col = col;
			col++;
			return t;
		}
		//Numeric
		int i=0;
		if(isdigit(ca)){
			while(isdigit(ca)){
				buffer[i++] = ca;
				ca = getc(fa);
			}
			buffer[i] = '\0';
			struct token t;
			strcpy(t.name,buffer);
			t.row = row;
			t.col = col;
			col+=strlen(buffer);
			return t;
		}
		//Keywords
		i=0;
		while(isalpha(ca)){
			buffer[i++] = ca;
			ca = getc(fa);

		}
		buffer[i] = '\0';
		for(int j=0;j<18;j++)
		{
			if(strcmp(buffer,keywords[j])==0)
			{
				struct token t;
				strcpy(t.name,buffer);
				t.row = row;
				t.col = col;
				col = col + strlen(buffer);
				if(j<5){
					strcpy(currType,buffer);
				}
				return t;
			}
		}
		if(buffer[0]!='\0')
		{
			struct token t;
			strcpy(t.name,"id");
			t.row = row;
			t.col = col;
			col+=strlen(buffer);
			createSymbolTableEntry();
			return t;
		}
		ca = getc(fa);
		col++;
	}
	struct token t;
	t.row = -1;
}

int main()
{
	fa = fopen("in.c","r");
	if(fa == NULL)
	{
		printf("Cannot open file \n");
		return 0;
	}
	ca = getc(fa);
	col = 1;

	printf("Tokens: \n");
	while(ca!=EOF)
	{
		struct token t = getNextToken();
		if(t.row == -1)
			break;
		printf("<%s , %d , %d>\n",t.name,t.row,t.col );
	}
	printf("\n-----------------------SYMBOL TABLE-----------------------\n");
	printSymbolTable();
}
