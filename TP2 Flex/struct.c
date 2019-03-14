#include <stdlib.h>
#include <string.h>

typedef struct info{
    char* valor;
    struct info* next;
} *Info;


typedef struct ll
{   
    char* categoria;
    struct info* autores;
    struct info* titulos;
    struct info* chaves;
    struct ll* next;
    
} *LL;



struct info* insertValor(struct info* info, char* valor){

    struct info* aux = info;

    if(valor!=NULL){

        if(aux == NULL){
            aux = (Info)malloc(sizeof(struct info));
            aux->valor = strdup(valor);
            aux->next = NULL;
            return aux;
        }

        else{

            while(aux->next!= NULL){
               aux = aux->next;
            }
            struct info* newInfo = (Info)malloc(sizeof(struct info));
            newInfo->valor = strdup(valor);
            newInfo->next = NULL;

            aux->next = newInfo;
            newInfo->next = NULL;

            return info;
        }
    }
}

int strcicmp(char const *a, char const *b)
{
    for (;; a++, b++) {
        int d = tolower(*a) - tolower(*b);
        if (d != 0 || !*a)
            return d;
    }
}

void RemoveSpaces(char* source)
{
  char* i = source;
  char* j = source;
  while(*j != 0)
  {
    *i = *j++;
    if(*i != ' ')
      i++;
  }
  *i = 0;
}

void rmSubstr(char *str, const char *toRemove)
{
    size_t length = strlen(toRemove);
    while((str = strstr(str, toRemove)))
    {
        memmove(str, str + length, 1 + strlen(str + length));
    }
}

void rmSetaFim(char* c){
    int i=0;
    while(c[i]!='\0'){
        i++;
    }
    if((c[i-1]=='>')&&(c[i-2]=='-')){
        c[i-1]='\0';
        c[i-2]=' ';
    }
}

void rmHifenRep(char* c){
    int i=0;
    while(c[i]!='\0'){
        if((c[i]=='-')&&(c[i+1]=='-')){
            c[i]=' ';
        }
    i++;
    }
}

void repetidaSeta(char* c){
    int i=0;
    int x=0;
    while(c[i]!='\0'){
        if((c[i]=='-')&&(c[i+1]=='>')&&(c[i]=='-')&&(c[i+1]=='>')){
            x=i;
        rmSubstr(c,"->->");
        /*
            while(x<i+5){
                c[x]=c[x+1];
                x++;
            }*/
            c[i]='-';
            c[i+1]='>';
        }
        i++;
    }
}

void pontoRep(char* c){
    int i=0;
    while(c[i]!='\0'){
        if(c[i]=='.')
            c[i]='_';
        i++;
    }
}
void hifenRep(char* c){
    int i=0;
    while(c[i]!='\0'){
        if(c[i]=='-')
            c[i]='_';
        i++;
    }
}




struct ll* insertInfo(struct ll* lista, char* cat, char* chave, char* aut, char* tit){
    //printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");

    //printf("CAT %s\n CHAV %s\n AUT %s\n TIT %s\n",cat,chave,aut,tit );
    RemoveSpaces(cat);
    rmSubstr(tit,"}");
    rmSubstr(tit,"\\");
    rmSubstr(tit,"\"");
    rmSubstr(tit,"\'");
    rmSubstr(tit,"\~");
    rmSubstr(tit,"\´");
    rmSubstr(tit,"\`");
    rmSubstr(tit,"/");
    rmSubstr(tit,"?");
    rmSubstr(tit,"(");
    rmSubstr(tit,")");
    rmSubstr(tit,"{");
    rmSubstr(tit,",\0");

    rmSubstr(aut,"}");
    rmSubstr(aut,"\\");
    rmSubstr(aut,"\"");
    rmSubstr(aut,"\'");
    rmSubstr(aut,"\~");
    rmSubstr(aut,"\´");
    rmSubstr(aut,"\`");
    rmSubstr(aut,"/");
    rmSubstr(aut,"?");
    rmSubstr(aut,")");
    rmSubstr(aut,"(");
    rmSubstr(aut,"{");
    rmSubstr(aut,",\0");

    struct ll* aux = lista;
    if(aux == NULL){
        aux = (LL)malloc(sizeof(struct ll));
        aux->categoria = strdup(cat);
        aux->chaves =  insertValor(aux->chaves,chave);
        aux->autores =  insertValor(aux->autores,aut);
        aux->titulos =  insertValor(aux->titulos,tit);
        aux->next = NULL;
                //printf("insere: cat %s CHAV %s aut %s TIT %s\n", aux->categoria, aux->info->chave[i],aux->info->autor[i],aux->info->title[i]);
        return aux;
    }

    else{
      //  printf("\n\nNOVAINSERÇAO\n");
        while(aux->next!= NULL){
            int x = strcmp(aux->categoria,cat);
        //  printf("Cate1: %s Cate2 %s %d \n",aux->categoria, cat, x);
            if(strcmp(aux->categoria,cat)==0){
        //      printf("categoria igual\n");
                aux->chaves =  insertValor(aux->chaves,chave);
                aux->autores =  insertValor(aux->autores,aut);
                aux->titulos =  insertValor(aux->titulos,tit);
                return lista;
            }
           aux = aux->next;
        }
        if(strcmp(aux->categoria,cat)==0){
            aux->chaves =  insertValor(aux->chaves,chave);
            aux->autores =  insertValor(aux->autores,aut);
            aux->titulos =  insertValor(aux->titulos,tit);
            return lista;
        }
        //printf("inseriu %s\n", cat);
        struct ll* newInfo = (LL)malloc(sizeof(struct ll));
        newInfo->categoria = strdup(cat);
        newInfo->chaves =  insertValor(newInfo->chaves,chave);
        newInfo->autores =  insertValor(newInfo->autores,aut);
        newInfo->titulos =  insertValor(newInfo->titulos,tit);
        newInfo->next=NULL;
        //printf("vai inserir %d %s %s %s %s\n", i, newInfo->categoria, newInfo->info->chave[i],newInfo->info->autor[i],newInfo->info->title[i]);

        aux->next = newInfo;
        newInfo->next = NULL;

        return lista;
    }
}

void imprimeL(LL ll, int it){
    LL l = ll;

    while(l!=NULL){
        int i = 0;
        printf("categoria: %s\n", l->categoria);
        while(i<it){
            //printf("CHAV %s aut %s TIT %s\n",l->info->chave[i],l->info->autor[i],l->info->title[i]);
            i++;
        }
        l=l->next;
    }
}

char *read_from_file(const char *filename)
{
    long int size = 0;
    FILE *file = fopen(filename, "r");

    if(!file) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);

    char *result = (char *) malloc(size);
    if(!result) {
        fputs("Memory error.\n", stderr);
        return NULL;
    }

    if(fread(result, 1, size, file) != size) {
        fputs("Read error.\n", stderr);
        return NULL;
    }

    fclose(file);
    return result;
}