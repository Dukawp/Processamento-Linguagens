%{
#include <stdio.h>
#include <ctype.h>


char** palavras;
char* split;
int it = 0;
char*  nomesCategorias[100];
int contCategorias[100];

FILE *fp;

char* lowerCASE(char * str){
	int i;
	for(i = 0; str[i]!='\0'; i++){
  		str[i] = tolower(str[i]);
	}
	return str;
}

void addRegisto(char* nome){
	int found=0;
	int i;
    if(strcmp(nome,"@string")){
	for(i=0;i<30 && nomesCategorias[i]!=NULL && found==0;i++){
		if(!strcmp(nomesCategorias[i],nome)){
			found=1;
			contCategorias[i]++;
		}
	}
	if(nomesCategorias[i]==NULL && found==0){
		nomesCategorias[i] = strdup(nome);
		contCategorias[i]++;
	}
    }
}

%}

%x ARR

%%

@[A-Za-z]+	{
	printf("%s\n",yytext);
	char* aux = lowerCASE(yytext);
	addRegisto(aux);
}


.|\n 	{;}


%%
void initArrayCategorias(){
	int i;
	for(i=0;i<100;i++){
		nomesCategorias[i]=NULL;
		contCategorias[i]=0;
	}
}

int yywrap(){
	return 1;
}

int main(){
	int i=0;
	initArrayCategorias();
	fp = fopen("indice.html", "w");
	yylex();

	for(i=0;i<20 && nomesCategorias[i]!=NULL ;i++){
		fprintf(fp,"<p>%s -> %d\n</p>", nomesCategorias[i],contCategorias[i]);
	}
	fclose(fp);
	return 0;
}
