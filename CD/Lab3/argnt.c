#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

FILE * fa;
struct token{
	char name[50];
	int row,col;
	char type[50];
};
int c,row=1,col=1;

struct token getNextToken(){
	struct token t;
	while(c!=EOF){
		if(c=='\n'){
			row++;
			col=1;
			c=getc(fa);
		}else if(c==' '){
			col++;
			c=getc(fa);
		}else if(c=='+'){
			strcpy(t.name,"+");
			strcpy(t.type,"ADDITION");
			t.row=row;
			t.col=col;
			col++;
			c=getc(fa);
			return t;
		}else if(c=='-'){
			strcpy(t.name,"-");
			strcpy(t.type,"SUBTRACTION");
			t.row=row;
			t.col=col;
			col++;
			c=getc(fa);
			return t;
		}else if(c=='*'){
			strcpy(t.name,"*");
			strcpy(t.type,"MULTIPLICATION");
			t.row=row;
			t.col=col;
			col++;
			c=getc(fa);
			return t;
		}else if(c=='/'){
			strcpy(t.name,"/");
			strcpy(t.type,"DIVISION");
			t.row=row;
			t.col=col;
			col++;
			c=getc(fa);
			return t;
		}else{
			char buff[10];
			int i=0;
			while(isdigit(c)){
				buff[i++]=c;
				c=getc(fa);
				col++;
			}
			buff[i]='\0';
			fseek(fa,-1,SEEK_CUR);
			strcpy(t.name,buff);
			strcpy(t.type,"OPERAND");
			t.row=row;
			t.col=col;
			col+=strlen(buff);
			c=getc(fa);
			return t;
		}
	}t.row=-1;
	return t;
}

int main(){
	fa=fopen("in.txt","r");
	if(fa==NULL){
		printf("Cannot Open File!");
		exit(1);
	}c=getc(fa);
	while(c!=EOF){
		struct token t=getNextToken();
		if(t.row!=-1)
			printf("<%s,%d,%d,%s>\n", t.name,t.row,t.col,t.type);
		else
			break;
		//c=getc(fa);
	}
	exit(0);
}