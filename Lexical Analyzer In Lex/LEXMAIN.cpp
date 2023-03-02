#include<iostream>
#include "Tokens.h"

using namespace std;

extern int yylex();
extern char* yytext;

int main()
{
	cout<<"\n\t\t[TOKENS FOR YOUR INPUT ARE]\t\t\n\n";
	int Token = yylex();
	while(Token != 0)
	{
		cout<< Token << " , " << yytext << " \n";
		Token = yylex();
	}
}
