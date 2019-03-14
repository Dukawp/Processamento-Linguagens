%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "struct.c"

char* autores[600];

char* autor;

int i = 0;

FILE *fp, *fr;

char* lowerCASE(char * str){
	int i;
	for(i = 0; str[i]!='\0'; i++){
  		str[i] = tolower(str[i]);
	}
	return str;
}


%}

%x COD
%x INI
%x AUT
%x TIT

%%



<INITIAL>{													

[\ |	]*(author|AUTHOR)[ |	]*=[ |	]*				 {BEGIN AUT;}
									
}			




<AUT>.*												{rmSubstr(yytext,"{");
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
														 autor = strdup(yytext);
														 i = strlen(autor);
														 autor[i-2] = '\0';
														 autor[i-1] = '\0';
													 	 fprintf(fr, "author = %s\n", autor);
													 	 fprintf (fp, "<a href=lp.bib ><li>%s</li></a>", autor);
													 	 BEGIN INITIAL;
														}



<*>.|[\n]                                                  {;} //para nao imprimir o resto


%%

int yywrap(){
	return 1;
}

int main(){

    fr = fopen("indiceAutores.txt", "w");
    fp = fopen("indiceAutores.html", "w");
    fprintf(fp,"<center><!DOCTYPE html>\n<html>\n<body>\n\n<h1>Indice Autores</h1></center>\n\n");
	yylex();

	i=0;


	fclose(fr);
	fclose(fp);

	return 0;
}