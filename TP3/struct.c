#include <gmodule.h>

typedef struct ll
{   
    char* chave;
    struct ll* next;
    
} *LL;

struct ll* insertValor(struct ll* ll, char* valor){

    struct ll* aux = ll;

    if(valor!=NULL){

        if(aux == NULL){
            aux = (LL)malloc(sizeof(struct ll));
            aux->chave = strdup(valor);
            aux->next = NULL;
            return aux;
        }

        else{

            while(aux->next!= NULL){
               aux = aux->next;
            }
            struct ll* newInfo = (LL)malloc(sizeof(struct ll));
            newInfo->chave = strdup(valor);
            newInfo->next = NULL;

            aux->next = newInfo;
            newInfo->next = NULL;

            return ll;
        }
    }
}

typedef struct emigrante{
	char* chave;
	char* nome;
	int dataN;
	char* cidade;
	char* destino;
	int dataE;
	char* cidadeR;
	int dataR;
	GSList *lEventos;
	GSList *lObras;
}*Emi;

typedef struct evento{
	char* nome;
	char* descricao;
	int data;
}*Eve;

typedef struct obra{
	char* nome;
	char* descricao;
	int data;
}*Obr;

void freeS(LL head){
	LL temp=NULL;
	while(head) 
		{
		  temp = head->next;
		  free(head);
		  head = temp;
		}
	
}
void freeEm(Emi emi){
	free(emi->nome);
	free(emi->cidade);
	free(emi->destino);
	free(emi->cidadeR);
	g_slist_free(emi->lEventos);
	g_slist_free(emi->lObras);
}

void DisplayList (GSList *list)
{
    int    nIndex;
    GSList *node;

    for (nIndex = 0; node = g_slist_nth (list, nIndex); nIndex++) {

        g_print ("EVENTO----: %s\n", (char *) node->data);
    }
}

Emi copiaEm(Emi e){
	Emi novo = (Emi)malloc(sizeof(struct emigrante));
	novo->chave = strdup(e->chave);
	novo->nome = strdup(e->nome);
	novo->dataN = e->dataN;
	novo->cidade = strdup(e->cidade);
	novo->destino = strdup(e->destino);
	novo->dataR = e->dataR;
	novo->dataE = e->dataE;
	novo->cidadeR = strdup(e->cidadeR);
	//printf("levento: %s\n", e->lEventos->chave);
	novo->lEventos = g_slist_copy(e->lEventos);
	novo->lObras = g_slist_copy(e->lObras);	
}

Eve copiaEv(Eve e){
	Eve novo = (Eve)malloc(sizeof(struct evento));
	novo->nome = strdup(e->nome);
	novo->descricao = strdup(e->descricao);
	novo->data = e->data;
}

Obr copiaOb(Obr e){
	Obr novo = (Obr)malloc(sizeof(struct obra));
	novo->nome = strdup(e->nome);
	novo->descricao = strdup(e->descricao);
	novo->data = e->data;
}
void rmSubstr(char *str, const char *toRemove)
{
    size_t length = strlen(toRemove);
    while((str = strstr(str, toRemove)))
    {
        memmove(str, str + length, 1 + strlen(str + length));
    }
}