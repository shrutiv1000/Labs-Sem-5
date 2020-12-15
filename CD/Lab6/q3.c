/*
S->aAcBe
A->bAprime
Aprime->bAprime | epsilon
B->d
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int curr = 0;
char str[100];

void S();
void A();
void Aprime();
void B();

void invalid()
{
	printf("-----------------ERROR!----------------\n");
	exit(0);
}
void valid()
{
	printf("----------------SUCCESS!---------------\n");
	exit(0);
}

void B()
{
	if(str[curr]=='d'){
		curr++;
		return;
	}else
		invalid();
}

void Aprime()
{
	if(str[curr] == 'b')
	{
		curr++;		
		Aprime();
	}
}

void A()
{
	if(str[curr] == 'b')
	{
		curr++;		
		Aprime();
	}else
		invalid();
}

void S()
{
	if(str[curr]=='a'){
		curr++;
		A();
		if(str[curr]=='c'){
			curr++;
			B();
			if(str[curr]=='e'){
				curr++;
				return;
			}else
				invalid();
		}else
			invalid();
	}else
		invalid();
}

int main()
{
	printf("Enter String: ");
	scanf("%s", str);
	S();
	if(str[curr] == '$')
		valid();
	else{
		printf("%c\n", str[curr]);
		invalid();
	}
}