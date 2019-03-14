%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "struct.c"

int i=0;

struct ll *l;

struct ll *aux;

int a1 = 0;
int t1 = 0;

char* categoria;
char* chave;
char* autor;
char* title;

FILE *fp;

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



<INITIAL>@[A-Za-z]*[\ ]*\{								{
														 i=0;
			                                             while (yytext[i]!='{'){i++;} 
														 yytext[i] = '\0';
														 char* aux = lowerCASE(yytext);
														 categoria = strdup(aux);
														 BEGIN COD;
														}

<COD>.*	 												{i=0;
														 while(yytext[i]!=','){i++;}
														 yytext[i]='\0';
														 chave = strdup(yytext);
														 BEGIN INI;
														}

<INI>{													

[\ |	]*(author|AUTHOR)[ |	]*=[ |	]*				 {BEGIN AUT;}
[\ |	|\n]title[ |	]*=[ |	]*						 {BEGIN TIT;}
														 
([A-Za-z])												{
															if(a1 && t1){
																a1=0;
																t1=0;
																if(strcmp(categoria,"@string")!=0)
																	l=insertInfo(l,categoria,chave,autor,title);
																BEGIN INITIAL;
															}	
															else{BEGIN INI;}									
														 }
}			




<AUT>.*													{
													 	 autor = strdup(yytext); 
													 	 a1=1;
													 	 BEGIN INI;
														}

<TIT>.* 												{
														 title = strdup(yytext);
														 t1 = 1;
													 	 BEGIN INI;
														}



<*>.|[\n]                                                  {;} //para nao imprimir o resto


%%

int yywrap(){
	return 1;
}

int main(){
	l=NULL;
	char * file = read_from_file("indice.html");
	fp = fopen("indice.html", "w");
    fprintf(fp,file);

	yylex();
    fprintf(fp,"<center><!DOCTYPE html>\n<html>\n<body>\n\n<h1>Indice BibText</h1></center>\n\n");

	i=0;

    while(l!=NULL){
    	fprintf(fp, "<p>Categoria: %s\n</p>", l->categoria);
    	
    	while(l->chaves!=NULL){
    		i++;
    		fprintf(fp,"<p>Chave: %s\n</p>", l->chaves->valor);
     		fprintf(fp,"<p>Autor: %s\n</p>", l->autores->valor);
    		fprintf(fp,"<p>Titulo: %s\n</p>", l->titulos->valor);
    		fprintf(fp,"<p>*********************</p>");
    		l->chaves = l->chaves->next;
    		l->autores = l->autores->next;
    		l->titulos = l->titulos->next;

    	}

    	l=l->next;
    }
	fclose(fp);
	

	return 0;
}