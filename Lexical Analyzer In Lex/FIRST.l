%{
	#include "Tokens.h"
%}

/* REGULAR DEFINITIONS	*/

delim	[ \t\n]
digit	[0-9]
ws		{delim}+
id		[_a-zA-Z][_a-zA-Z0-9]*
number	{digit}+(\.{digit}+)?([eE][+-]?{digit}+)?
strltr	\"(\\.|[^"\\])*\"

%%

"auto"		{return(AUTO);}
"do"		{return(DO);}
"goto"		{return(GOTO);}
"signed"	{return(SIGNED);}
"unsigned"	{return(UNSIGNED);}
"break"		{return(BREAK);}
"double"	{return(DOUBLE);}
"if"		{return(IF);}
"sizeof"	{return(SIZEOF);}
"void"		{return(VOID);}
"case"		{return(CASE);}
"else"		{return(ELSE);}
"int"		{return(INT);}
"static"	{return(STATIC);}
"volatile"	{return(VOLATILE);}
"char"		{return(CHAR);}
"enum"		{return(ENUM);}
"long"		{return(LONG);}
"struct"	{return(STRUCT);}
"while"		{return(WHILE);}
"const"		{return(CONST);}
"extern"	{return(EXTERN);}
"register"	{return(REGISTER);}
"switch"	{return(SWITCH);}
"continue"	{return(CONTINUE);}
"float"		{return(FLOAT);}
"return"	{return(RETURN);}
"typedef"	{return(TYPEDEF);}
"default"	{return(DEFAULT);}
"for"		{return(FOR);}
"short"		{return(SHORT);}
"union"		{return(UNION);}
"endl"		{return(ENDL);}
"include"	{return(INCLUDE);}
"define"	{return(DEFINE);}


{ws}		{/*NO ACTION IS NEEDED*/}
{number}	{return(NUMBER);}
{id}		{return(IDENTIFIER);}
{strltr}	{return(STRLTR);}

"<<"	{return(STRINS);}
">>"	{return(STREXT);}

"<" 	{return(LT);}
">"		{return(GT);}
"="		{return(EQ);}
">="	{return(GE);}
"<="	{return(LE);}
"!="	{return(NE);}
"<>"	{return(NE);}

"+"		{return(ADD);}
"-"		{return(SUB);}
"/"		{return(DIV);}
"*"		{return(MUL);}
"%"		{return(MOD);}

"!"		{return(NOT);}
"||"	{return(OR);}
"&&"	{return(AND);}

"#"		{return(HASH);}
":"		{return(COLON);}
";"		{return(SEMICOLON);}
"&"		{return(AMPERCENT);}
","		{return(COMMA);}

"("		{return(OPA);}
")"		{return(CPA);}
"{"		{return(OCB);}
"}"		{return(CCB);}
"["		{return(OBR);}
"]"		{return(CBR);}

%%

int yywrap()
{
	return 1;
}