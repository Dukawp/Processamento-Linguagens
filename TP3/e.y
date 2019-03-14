%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>
#include <gmodule.h> 
//#include "struct.c"
#include "geraH.c"

int yylex();
void yyerror(char *s);

GHashTable* emigrantes;
GHashTable* eventos;
GHashTable* obras;

Emi emi; char* cEm;
Eve eve; char* cEv;
Obr obr; char* cOb;


%}


%union{
	char* s;
	float f;
	char c;
}

%token <s> STRING

%token <s> ABRE ABREE ABREO FECHA NOME DT CD DST DE RG DTR IDE IDO DES

%type <s> Programa Emigrantes Emigrante DadosP ProcE Evento Obra Eventos Obras IDEvento IDObra IDEventos IDObras DescricaoE
%type <s> Nome DataNasc Cidade Destino Data_Em NomeEvento NomeObra DataEvento DataObra Codigo DtReg Regresso Evs Obs DescricaoO


%%
Programa : Emigrantes ';' Eventos ';' Obras ';'
		 ;

Emigrantes : Emigrante
		   | Emigrantes ';' Emigrante 
		   ;

Emigrante : ABRE Codigo DadosP ProcE Evs Obs FECHA	{//free(cEm);
													 cEm = strdup($2);
													 emi->chave = strdup($2);
													// printf("LLLLL: %s\n", emi->lEventos->next->chave);
													 Emi em = copiaEm(emi);
													 g_hash_table_insert(emigrantes,cEm,em);
													 //freeS(emi->lEventos);
													 //freeS(emi->lObras);
													 DisplayList(emi->lEventos);
													 emi->lEventos=NULL;
													 emi->lObras=NULL;}
		  ;


DadosP : NOME ':' Nome DT ':' DataNasc CD ':' Cidade
	   ;

Evs : IDE ':' IDEventos
	|				{$$=strdup(" ");}
    ;

Obs : IDO ':' IDObras
	|				{$$=strdup(" ");}
	;

IDEventos : IDEvento
		  | IDEventos ',' IDEvento
		  ;

IDObras : IDObra
		| IDObras ',' IDObra
		;

ProcE : DST ':' Destino DE ':' Data_Em RG ':' Regresso DTR ':' DtReg
	  ;

Eventos : Evento
	    | Eventos ';' Evento
	    ;

Evento : ABREE Codigo NOME ':' NomeEvento DES ':' DescricaoE DE ':' DataEvento FECHA 	{cEv = strdup($2);
																						 Eve ev = copiaEv(eve);
																						 g_hash_table_insert(eventos,cEv,ev);}
	   ;

Obras : Obra
	  | Obras ';' Obra 
	  ;

Obra : ABREO Codigo NOME ':' NomeObra DES ':' DescricaoO DE ':' DataObra FECHA	{cOb = strdup($2);
																			 	 Obr ob = copiaOb(obr);
																				 g_hash_table_insert(obras,cOb,ob);}
	 ;


Nome : STRING 			{emi->nome=strdup($1);}
DataNasc : STRING 		{emi->dataN = atoi($1);}
Cidade : STRING 		{emi->cidade=strdup($1);}
Destino : STRING 		{emi->destino=strdup($1);}
Data_Em : STRING 		{emi->dataE=atoi($1);}
Regresso : STRING 		{emi->cidadeR=strdup($1);}
DtReg : STRING 			{emi->dataR=atoi($1);}
IDEvento : STRING 		{emi->lEventos = g_slist_append (emi->lEventos, $1);
						 g_hash_table_insert(eventos,$1,NULL);}
IDObra : STRING 		{emi->lObras = g_slist_append (emi->lObras, $1);
						 g_hash_table_insert(obras,$1,NULL);}

NomeEvento : STRING 	{eve->nome=strdup($1);}
DescricaoE : STRING 	{eve->descricao=strdup($1);}
DataEvento : STRING 	{eve->data=atoi($1);}

NomeObra : STRING 		{obr->nome=strdup($1);}
DescricaoO : STRING 	{obr->descricao=strdup($1);}
DataObra : STRING 		{obr->data=atoi($1);}

Codigo : STRING 

%%

#include "lex.yy.c"


void yyerror(char *s){
	printf("Erro %s  --->   yytext:  %s linha: %d\n", s, yytext, yylineno);
}

void initEstruturas(){
	emigrantes = g_hash_table_new(g_str_hash,g_str_equal);
	eventos = g_hash_table_new(g_str_hash,g_str_equal);
	obras = g_hash_table_new(g_str_hash,g_str_equal);

	emi = (Emi)malloc(sizeof(struct emigrante));
	eve = (Eve)malloc(sizeof(struct evento));
	obr = (Obr)malloc(sizeof(struct obra));
}

int validaDatas(){
	GHashTableIter iter;
	gpointer key, value;

	g_hash_table_iter_init (&iter, emigrantes);
	while (g_hash_table_iter_next (&iter, &key, &value))
	  {
	  	printf("KEY-E %s\n", (char*)key);
	  	if(((Emi)value)->dataE>((Emi)value)->dataR){
	  		printf("ERRO!! -> Data de emigração %d maior que data de regresso %d %s\n", ((Emi)value)->dataE , ((Emi)value)->dataR, (char*)key);
	  		return -1;
	  	}
	    // do something with key and value
	  }
}


int validaSemantica(){
	GHashTableIter iter;
	gpointer key, value;

	g_hash_table_iter_init (&iter, obras);
	while (g_hash_table_iter_next (&iter, &key, &value))
	  {
	  	//printf("KEY %s\n", (char*)key);
	  	if(value==NULL){
	  		printf("ERRO SEMANTICO!! -> Chave de obra sem correspondencia %s\n", (char*)key);
	  		return -1;
	  	}
	    // do something with key and value
	  }

	g_hash_table_iter_init (&iter, eventos);
	while (g_hash_table_iter_next (&iter, &key, &value))
	  {
	  	//printf("KEY %s\n", (char*)key);
	  	if(value==NULL){
	  		printf("ERRO SEMANTICO!! -> Chave de evento sem correspondencia %s\n", (char*)key);
	  		return -1;
	  	}
	    // do something with key and value
	  }
	    validaDatas();

}


int main(){
	initEstruturas();
	
	yyparse();

	validaSemantica();
/*
	printHashTable(emigrantes);
	printHashTable(eventos);
	printHashTable(obras);
*/
	FILE* indiceEmigrantes = fopen("IndiceEmigrantes.html","w");
	fprintf(indiceEmigrantes, "<center><!DOCTYPE html>\n<html>\n<head><meta charset='UTF-8'> </head><body>\n\n<h1>Emigrantes</h1></center>\n\n");
	fprintf(indiceEmigrantes, "<a href=grafo.html><p> <-- Pagina inicial </p>\n</a>");

	fclose(indiceEmigrantes);
	
	FILE* indiceEventos = fopen("IndiceEventos.html","w");
	fprintf(indiceEventos, "<center><!DOCTYPE html>\n<html>\n<head><meta charset='UTF-8'> </head><body>\n\n<h1>Eventos</h1></center>\n\n");
	fprintf(indiceEventos, "<a href=grafo.html><p> <-- Pagina inicial </p>\n</a>");

	fclose(indiceEventos);

	FILE* indiceObras = fopen("IndiceObras.html","w");
	fprintf(indiceObras, "<center><!DOCTYPE html>\n<html>\n<head><meta charset='UTF-8'> </head><body>\n\n<h1>Obras</h1></center>\n\n");
	fprintf(indiceObras, "<a href=grafo.html><p> <-- Pagina inicial </p>\n</a>");

	fclose(indiceObras);

	FILE* indicePartida = fopen("IndicePartida.html","w");
	fprintf(indicePartida, "<center><!DOCTYPE html>\n<html>\n<head><meta charset='UTF-8'> </head><body>\n\n<h1>Partidas</h1></center>\n\n");
	fprintf(indicePartida, "<a href=grafo.html><p> <-- Pagina inicial </p>\n</a>");

	fclose(indicePartida);

	FILE* indiceRegresso = fopen("IndiceRegresso.html","w");
	fprintf(indiceRegresso, "<center><!DOCTYPE html>\n<html>\n<head><meta charset='UTF-8'> </head><body>\n\n<h1>Regresso</h1></center>\n\n");
	fprintf(indiceRegresso, "<a href=grafo.html><p> <-- Pagina inicial </p>\n</a>");

	fclose(indiceRegresso);

	geraHtml(emigrantes,eventos,obras);

	FILE* file = fopen("dot.dot","w+");

	fprintf(file, "digraph{\n");
	fprintf(file, "rankdir = LR\n");
	fprintf(file, "\tEmigrante [ href=\"IndiceEmigrantes.html\", color = blue];\n");
	fprintf(file, "\tEvento[ href=\"IndiceEventos.html\", color = red];\n");
	fprintf(file, "\tObra[ href=\"IndiceObras.html\", color = green];\n");
	fprintf(file, "\tEmigrante->Obra [label = \"fez\"];\n");
	fprintf(file, "\tEmigrante->Evento [label = \"participou\"];\n");
	fprintf(file, "\tLocalizacao [shape = octagon]\n");
	fprintf(file, "\tEmigrante->Localizacao [label=\"tem\"];\n");
	fprintf(file, "\tPartida [href=\"IndicePartida.html\", shape = egg];\n");
	fprintf(file, "\tRegresso [href=\"IndiceRegresso.html\", shape = egg];\n");
	fprintf(file, "\tLocalizacao->Partida [label = \"emigrou de\"];\n");
	fprintf(file, "\tLocalizacao->Regresso [label = \"regressou a\"];\n}");

	return 0;
}
