#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>
#include <gmodule.h> 
#include "struct.c"

void printHashTable(void* a){
	GHashTableIter iter;
	gpointer key, value;

	g_hash_table_iter_init (&iter, a);

	while (g_hash_table_iter_next (&iter, &key, &value))
	  {
	  	printf("KEY %s\n", (char*)key);
  		printf("Nome %s \n", ((Emi)value)->nome);

	  }
}
void criaHtmlEventos(GSList *lEventos, FILE* fEmi, char* nomeHtmlEmi, char*nomeEmi,GHashTable* eventos){
	for(GSList *l = lEventos;l!=NULL;l=l->next){
  				//procura eventos e cria ficheiros html para cada eventos do emigrante
  				gpointer value = l->data;
  				Eve e = g_hash_table_lookup(eventos, value);
  				//criar ficheiro se nao existe
  				char nomeEventosHtml[10];
  				sprintf(nomeEventosHtml, "%s.html",(char*)value);
  				FILE *fEv = fopen(nomeEventosHtml,"r+");//pagina de evento do emigrante

  				if(fEv!=NULL){
  					//ficheiro existe
  					fseek(fEv,0,SEEK_END);
  					//Linka a pagina de emigrantes da respetiva letra
  					fprintf(fEv, "<a href=%s><li>%s</li></a>\n",nomeHtmlEmi,nomeEmi);
  					//guarda nome de eventos e linka a pagina do evento
  					fprintf(fEmi, "<a href=%s><li>%s</li></a>\n",nomeEventosHtml,e->nome);
  					fclose(fEv);
  				}
  				else{
  					//temos que criar o ficheiro
  					fEv = fopen(nomeEventosHtml,"w");
  					fprintf(fEv, "<center><!DOCTYPE html>\n<html>\n<head><meta charset='UTF-8'> </head><body>\n\n<h1>%s</h1></center>\n\n",e->nome);
					fprintf(fEv, "<a href=grafo.html><p> <-- Pagina inicial </p>\n</a>");
  					//guardo info do evento
  					fprintf(fEv, "<li><b>Nome do evento:</b><p> %s<p></li>\n",e->nome);
	  				fprintf(fEv, "<li><b>Descrição:</b><p> %s<p></li>\n",e->descricao);
	  				fprintf(fEv, "<li><b>Ano de ocorrencia:</b><p> %d<p></li>\n",e->data);
  					//fprintf(fEv, "<a href=%s><li>%s</li></a>\n",nomeHtml,nome);
  					fprintf(fEv, "<p><b>Participantes: </b></p>\n");
  					fprintf(fEv, "<a href=%s><li>%s</li></a>\n",nomeHtmlEmi,nomeEmi);
  					fprintf(fEmi, "<a href=%s><li>%s</li></a>\n",nomeEventosHtml,e->nome);

  					fclose(fEv);
  				}

  			}
}

void criaHtmlObras(GSList *lObras, FILE* fEmi, char* nomeHtmlEmi, char*nomeEmi,GHashTable* obras){
	for(GSList *l = lObras;l!=NULL;l=l->next){
  				//procura obras e cria ficheiros html para cada obra do emigrante
  				gpointer value = l->data;
  				Obr o = g_hash_table_lookup(obras, value);
  				//criar ficheiro se nao existe
  				char nomeObrasHtml[10];
  				sprintf(nomeObrasHtml, "%s.html",(char*)value);
  				FILE *fOb = fopen(nomeObrasHtml,"r+");//pagina de obra do emigrante

  				if(fOb!=NULL){
  					//ficheiro existe
  					fseek(fOb,0,SEEK_END);
  					//Linka a pagina de emigrantes da respetiva letra
  					fprintf(fOb, "<a href=%s><li>%s</li></a>\n",nomeHtmlEmi,nomeEmi);
  					//guarda nome de eventos e linka a pagina da Obra
  					fprintf(fEmi, "<a href=%s><li>%s</li></a>\n",nomeObrasHtml,o->nome);
  					fclose(fOb);
  				}
  				else{
  					//temos que criar o ficheiro
  					fOb = fopen(nomeObrasHtml,"w");
  					fprintf(fOb, "<center><!DOCTYPE html>\n<html>\n<head><meta charset='UTF-8'> </head><body>\n\n<h1>%s</h1></center>\n\n",o->nome);
					fprintf(fOb, "<a href=grafo.html><p> <-- Pagina inicial </p>\n</a>");

  					//guardo info do evento
  					fprintf(fOb, "<li><b>Nome do evento:</b><p> %s<p></li>\n",o->nome);
	  				fprintf(fOb, "<li><b>Descrição:</b><p> %s<p></li>\n",o->descricao);
	  				fprintf(fOb, "<li><b>Ano de ocorrencia:</b><p> %d<p></li>\n",o->data);
	  				fprintf(fOb, "<b>Participantes:</b>\n");

  					//fprintf(fEv, "<a href=%s><li>%s</li></a>\n",nomeHtml,nome);
  					fprintf(fEmi, "<a href=%s><li>%s</li></a>\n",nomeObrasHtml,o->nome);

  					fclose(fOb);
  				}

  			}
}

void geraHtmlEmigrantes(char i,GHashTable* emigrantes,GHashTable* eventos,GHashTable* obras){
	GHashTableIter iter;
	gpointer key, value;

	char nomeHtml[17];
	sprintf(nomeHtml, "Emigrantes-%c.html",i);
	char nomeP[17];
	sprintf(nomeP, "Partidas-%c.html",i);
	char nomeR[17];
	sprintf(nomeR, "Regresso-%c.html",i);
	//printf("%s\n", nomeHtml);
	FILE* emHtml = fopen(nomeHtml,"w+");//Pagina de Emigrantes da letra
	FILE* partHtml = fopen(nomeP,"w+");
	FILE* regHtml = fopen(nomeR,"w+");
	fprintf(emHtml, "<center><!DOCTYPE html>\n<html>\n<head><meta charset='UTF-8'> </head><body>\n\n<h1>Emigrantes - %c</h1></center>\n\n",i);
	fprintf(emHtml, "<a href=IndiceEmigrantes.html><p> <-- Indice Emigrantes </p>\n</a>");

	fprintf(partHtml, "<center><!DOCTYPE html>\n<html>\n<head><meta charset='UTF-8'> </head><body>\n\n<h1>Partidas - %c</h1></center>\n\n",i);
	fprintf(partHtml, "<a href=IndiceEventos.html><p> <-- Indice Eventos </p>\n</a>");

	fprintf(regHtml, "<center><!DOCTYPE html>\n<html>\n<head><meta charset='UTF-8'> </head><body>\n\n<h1>Regressos - %c</h1></center>\n\n",i);
	fprintf(regHtml, "<a href=IndiceRegresso.html><p> <-- Indice Regressos </p>\n</a>");

	g_hash_table_iter_init (&iter, emigrantes);
	while (g_hash_table_iter_next (&iter, &key, &value))
	  {
	  	if((((Emi)value)->nome)[0] == i ){
	  		char nomeHtmlEmi[10];
	  		sprintf(nomeHtmlEmi, "%s.html",(char*)key);
	  		FILE *fEmi = fopen(nomeHtmlEmi,"w");//pagina htm do emigrante
	  		fprintf(emHtml, "<a href=%s><p>%s</p>\n</a>",nomeHtmlEmi,(((Emi)value)->nome));

	  		fprintf(fEmi, "<center><!DOCTYPE html>\n<html>\n<head><meta charset='UTF-8'> </head><body>\n\n<h1>%s</h1></center>\n\n",((Emi)value)->nome);
			fprintf(fEmi, "<a href=grafo.html><p> <-- Pagina inicial </p>\n</a>");
	  		fprintf(fEmi, "<p><b>Nasceu a:</b> %d</p>\n", (((Emi)value)->dataN));
	  		fprintf(fEmi, "<p><b>Emigrou de: <a href=%s.html></b> %s</p></a>\n",(((Emi)value)->cidade), (((Emi)value)->cidade));//pagina partida ultima
	  		fprintf(fEmi, "<p><b>Emigrou para:</b> %s</p>\n", (((Emi)value)->destino));
  			fprintf(fEmi, "<p><b>Emigrou em:</b> %d</p>\n", (((Emi)value)->dataE));
  			fprintf(fEmi, "<p><b>Regressou para: <a href=%s.html></b> %s</p></a>\n",(((Emi)value)->cidadeR), (((Emi)value)->cidadeR));//pagina chegada ultima
  			fprintf(fEmi, "<p><b>Regressou a:</b> %d</p>\n", (((Emi)value)->dataR));
	  		char* nomeEmi = ((Emi)value)->nome;
  			fprintf(fEmi, "<p><b>Eventos participados:</b>\n</p>");
	  		criaHtmlEventos(((Emi)value)->lEventos,fEmi,nomeHtmlEmi,nomeEmi,eventos);
	  		fprintf(fEmi, "<p><b>Obras efetuadas: </b></p>\n");
	  		criaHtmlObras(((Emi)value)->lObras,fEmi,nomeHtmlEmi,nomeEmi,obras);
  			fclose(fEmi);
  			
		}
		//partida
		if((((Emi)value)->cidade)[0]==i){
			char nomeHtmlP[30];
	  		sprintf(nomeHtmlP, "%s.html",((Emi)value)->cidade);
	  		rmSubstr(nomeHtmlP," ");
	  		FILE *fPar = fopen(nomeHtmlP,"r");//pagina htm do emigrante
	  		if(fPar==NULL){
	  			fPar = fopen(nomeHtmlP,"w");
				fprintf(partHtml, "<a href=%s><p><li>%s</li></p>\n</a>",nomeHtmlP,(((Emi)value)->cidade));
				fprintf(fPar, "<center><!DOCTYPE html>\n<html>\n<head><meta charset='UTF-8'> </head><body>\n\n<h1>%s</h1></center>\n\n",((Emi)value)->cidade);
				fprintf(fPar, "<a href=%s.html><p><li>%s</li></p>\n</a>",(((Emi)value)->chave),(((Emi)value)->nome));
			}
			else{
				fclose(fPar);
				fPar = fopen(nomeHtmlP,"a");
				fprintf(fPar, "<a href=%s.html><p><li>%s</li></p>\n</a>",(((Emi)value)->chave),(((Emi)value)->nome)); 

			}
			fclose(fPar);
		}
		//Regresso
		if((((Emi)value)->cidadeR)[0]==i){
			char nomeHtmlR[30];
	  		sprintf(nomeHtmlR, "%s.html",((Emi)value)->cidadeR);
	  		rmSubstr(nomeHtmlR," ");
	  		FILE *fReg = fopen(nomeHtmlR,"r");//pagina htm do regresso
	  		if(fReg==NULL){
	  			fReg = fopen(nomeHtmlR,"w");
				fprintf(regHtml, "<a href=%s><p><li>%s</li></p>\n</a>",nomeHtmlR,(((Emi)value)->cidadeR));
				fprintf(fReg, "<center><!DOCTYPE html>\n<html>\n<head><meta charset='UTF-8'> </head><body>\n\n<h1>%s</h1></center>\n\n",((Emi)value)->cidadeR);
	  			fprintf(fReg, "<a href=%s.html><p><li>%s</li></p>\n</a>",(((Emi)value)->chave),(((Emi)value)->nome));
	  		}
	  		else{
	  			fclose(fReg);
	  			fReg = fopen(nomeHtmlR,"a");
				fprintf(fReg, "<a href=%s.html><p><li>%s</li></p>\n</a>",(((Emi)value)->chave),(((Emi)value)->nome));

	  		}
			fclose(fReg);
		}
	  }

	FILE* indiceEmigrantes = fopen("IndiceEmigrantes.html","a");
	FILE* indicePartida = fopen("IndicePartida.html","a");
	FILE* indiceRegresso = fopen("IndiceRegresso.html","a");
	fprintf(indiceEmigrantes, "<a href=%s><li>%c</li></a>",nomeHtml,i);
	fprintf(indicePartida, "<a href=%s><li>%c</li></a>",nomeP,i);
	fprintf(indiceRegresso, "<a href=%s><li>%c</li></a>",nomeR,i);
	fseek(indiceEmigrantes,0,SEEK_END);
	fseek(indicePartida,0,SEEK_END);
	fseek(indiceRegresso,0,SEEK_END);

	if(i=='Z'){
		fclose(indiceEmigrantes);
		fclose(emHtml);
		fclose(partHtml);
		fclose(indicePartida);
		fclose(indiceRegresso);
		return;
	}
	  geraHtmlEmigrantes(((int)(i))+1,emigrantes,eventos,obras);
}

void geraHtmlEventos(int i,GHashTable *eventos){
	char nomeHtml[17];
	sprintf(nomeHtml, "Eventos-%c.html",i);
	//printf("%s\n", nomeHtml);
	FILE* emHtml = fopen(nomeHtml,"w+");
	fprintf(emHtml, "<center><!DOCTYPE html>\n<html>\n<head><meta charset='UTF-8'> </head><body>\n\n<h1>Eventos - %c</h1></center>\n\n",i);
	fprintf(emHtml, "<a href=IndiceEventos.html><p> <-- Indice Eventos </p>\n</a>");

	GHashTableIter iter;
	gpointer key, value;

	g_hash_table_iter_init (&iter, eventos);
	while (g_hash_table_iter_next (&iter, &key, &value))
	{
		if((((Eve)value)->nome)[0] == i ){
			//testar se a pagina já existe
			char nomeEventosHtml[50];
			sprintf(nomeEventosHtml, "%s.html",(char*)key);
			FILE *fEv = fopen(nomeEventosHtml,"r+");
			if(fEv!=NULL){
				//ficheiro ja existe so precisamos de linka-lo ao nome do evento
				fclose(fEv);
				fprintf(emHtml, "<a href=%s><li>%s</li></a>",nomeEventosHtml,((Eve)value)->nome); 
			}
			else{
				//ficheiro nao existe temos que o criar
				fEv = fopen(nomeEventosHtml,"w");
				fprintf(fEv, "<center><!DOCTYPE html>\n<html>\n<head><meta charset='UTF-8'> </head><body>\n\n<h1>Eventos</h1></center>\n\n");
	  			fprintf(fEv, "<li><b>Nome do evento:</b><p> %s<p></li>\n",((Eve)value)->nome);
	  			fprintf(fEv, "<li><b>Descrição:</b><p> %s<p></li>\n",((Eve)value)->descricao);
	  			fprintf(fEv, "<li><b>Ano de ocorrencia:</b><p> %d<p></li>\n",((Eve)value)->data);
	  			fprintf(emHtml, "<a href=%s><li>%s</li></a>",nomeEventosHtml,((Eve)value)->nome); 
	  			fclose(fEv);
			}
		}
	}
	FILE* indiceEventos = fopen("IndiceEventos.html","a");
	fprintf(indiceEventos, "<a href=%s><li>%c</li></a>",nomeHtml,i);
	fseek(indiceEventos,0,SEEK_END);

	if(i=='Z'){
		fclose(indiceEventos);
		fclose(emHtml);
		return;
	}
	  geraHtmlEventos(((int)(i))+1,eventos);
}

void geraHtmlObras(int i,GHashTable *obras){
	char nomeHtml[17];
	sprintf(nomeHtml, "Obras-%c.html",i);
	//printf("%s\n", nomeHtml);
	FILE* emHtml = fopen(nomeHtml,"w+");
	fprintf(emHtml, "<center><!DOCTYPE html>\n<html>\n<head><meta charset='UTF-8'> </head><body>\n\n<h1>Obras - %c</h1></center>\n\n",i);
	fprintf(emHtml, "<a href=IndiceObras.html><p> <-- Indice Obras </p>\n</a>");

	GHashTableIter iter;
	gpointer key, value;

	g_hash_table_iter_init (&iter, obras);
	while (g_hash_table_iter_next (&iter, &key, &value))
	{
		if((((Obr)value)->nome)[0] == i ){
			//testar se a pagina já existe
			char nomeObrasHtml[10];
			sprintf(nomeObrasHtml, "%s.html",(char*)key);
			FILE *fOb = fopen(nomeObrasHtml,"r+");
			if(fOb!=NULL){
				//ficheiro ja existe so precisamos de linka-lo ao nome do evento
				fprintf(emHtml,"<a href=%s> <li>%s</li> </a>",nomeObrasHtml,((Obr)value)->nome); 
				fclose(fOb);
			}
			else{
				//ficheiro nao existe temos que o criar
				fOb = fopen(nomeObrasHtml,"w");
				fprintf(fOb, "<center><!DOCTYPE html>\n<html>\n<head><meta charset='UTF-8'> </head><body>\n\n<h1>Obras</h1></center>\n\n");
	  			fprintf(fOb, "<li><b>Nome do evento:</b><p> %s<p></li>\n",((Obr)value)->nome);
	  			fprintf(fOb, "<li><b>Descrição:</b><p> %s<p></li>\n",((Obr)value)->descricao);
	  			fprintf(fOb, "<li><b>Ano de ocorrencia:</b><p> %d<p></li>\n",((Obr)value)->data);
	  			fprintf(emHtml,"<a href=%s><li>%s</li></a>",nomeObrasHtml,((Obr)value)->nome); 
	  			fclose(fOb);
			}
		}
	}
	FILE* indiceObras = fopen("IndiceObras.html","a");
	fprintf(indiceObras, "<a href=%s><li>%c</li></a>",nomeHtml,i);
	fseek(indiceObras,0,SEEK_END);

	if(i=='Z'){
		fclose(indiceObras);
		fclose(emHtml);
		return;
	}
	  geraHtmlObras(((int)(i))+1,obras);
}

void geraHtml(GHashTable *emigrantes, GHashTable *eventos, GHashTable *obras){
	char i = 'A';
	geraHtmlEmigrantes(i,emigrantes,eventos,obras);
	geraHtmlEventos(i,eventos);
	geraHtmlObras(i,obras);
}