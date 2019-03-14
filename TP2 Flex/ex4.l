%option noyywrap
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "struct.c"

		FILE* fp;
		char* autor;

		int i=0,j;
		int k = 0;

%}
%%
^.*"author".*$		{ strtok(yytext,"=");
					  yytext = strtok(NULL,"\0");
					 pontoRep(yytext);
					 hifenRep(yytext);
					 rmSubstr(yytext,"{");
					 rmSubstr(yytext,"}");
					 rmSubstr(yytext,"\\");
					 rmSubstr(yytext,"\"");
					 rmSubstr(yytext,"\'");
					 rmSubstr(yytext,"\~");
					 rmSubstr(yytext,"\´");
					 rmSubstr(yytext,"\`");
					 rmSubstr(yytext,"/");
					 rmSubstr(yytext,"?");
					 rmSubstr(yytext,"(");
					 rmSubstr(yytext,")");
					 i=0;
					 j = strlen(yytext);
					 while(yytext[i]!='\0'){
					 	if(yytext[i]==','){
					 		yytext[i-1]='-';
					 		yytext[i]='>';
					 		k=1;
					 	}
					 	if(yytext[i]=='a' && yytext[i+1]=='n' && yytext[i+2]=='d' && yytext[i+3]==' '){
					 		yytext[i]='-';
					 		yytext[i+1]='>';
					 		yytext[i+2]=' ';
					 		i++;
					 		k=1;
					 	}
					 	i++;
					 }
					 RemoveSpaces(yytext);
					 rmSetaFim(yytext);
					 repetidaSeta(yytext);
					 rmHifenRep(yytext);
					 if(k){
					 	fprintf(fp, "%s\n", yytext);
					 	k=0;
					 }
					 i++;
					}


%%



int main() {
	fp = fopen("out.dot", "w");

	fprintf(fp, "digraph { \n");
	yylex();
	fprintf(fp,"}");
	fclose(fp);
	return 0;
}
