/// para trabalhar com commentarios

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista LISTA;
struct lista{
	char nome[21];
	char depoimento[51];
	LISTA* prox;
};

typedef struct pilha PILHA;
struct pilha{
	LISTA* top;
};

/// funções invisíveis ao usuário
PILHA* com_cria_pilha(){ /// vai estar visivel
	PILHA* nova = (PILHA*)malloc(sizeof(PILHA));
	nova->top = NULL;
	return nova;
}
static int pilha_vazia(PILHA* p){ return (p->top == NULL); }
static void pilha_push(PILHA* p, LISTA n){
	LISTA* novo = (LISTA*)malloc(sizeof(LISTA));
	strcpy(novo->nome, n.nome);
	strcpy(novo->depoimento, n.depoimento);
	novo->prox = p->top;
	p->top = novo;
}

static LISTA pilha_pop(PILHA* p){
	LISTA retorna;
	if(!pilha_vazia(p)){
		strcpy(retorna.nome, p->top->nome);
		strcpy(retorna.depoimento, p->top->depoimento);
		///printf("%s %s", retorna.nome, retorna.depoimento); /// isso sai
		LISTA* limpa = p->top;
		p->top = p->top->prox;
		free(limpa);
	}
	return retorna;

}
static int com_vazio(FILE* arquivo){
	int tamanho_ = 0;
	
	fseek(arquivo, 0, SEEK_END);
    tamanho_ = ftell(arquivo);

    return tamanho_;
}

/// funções visíveis ao usuário

int com_imprimirCom(char* local){
	FILE* arquivo = fopen(local, "rt");
	char str1[21];
	char str2[51];
	char strControl[50];
	if(arquivo != NULL){
		if(com_vazio(arquivo) == 0){ /// se está vazio retorna 1 
			fclose(arquivo);
			return 0;
		}
		fseek(arquivo, 0, SEEK_SET);
		while(fscanf(arquivo, " %[^\n]s", str1) != EOF){
			  fscanf(arquivo, " %[^\n]s", str2);
			  printf("%s: %s\n", str1, str2);
		}
		fclose(arquivo);
		return 1;
	}else printf("Nao foi possivel abrir o arquivo!\n");
	return 0;
}

void com_pilha_begin(PILHA* p, char* local){
	FILE* arquivo = fopen(local, "rt");
	char str1[21];
	char str2[51];
	if(arquivo != NULL){
		PILHA* aux = com_cria_pilha();
		LISTA variavel;
		while((fscanf(arquivo, " %[^\n]s", str1)) != EOF){
			   fscanf(arquivo, " %[^\n]s", str2);
			   strcpy(variavel.nome, str1);
			   strcpy(variavel.depoimento, str2);
			   pilha_push(aux, variavel);
		}
		while(!pilha_vazia(aux)){
			pilha_push(p, pilha_pop(aux));
		}
		free(aux);
		fclose(arquivo);
		
	}else printf("Nao foi possivel abrir o aquivo tente novamente mais tarde!\n");
}
PILHA* com_pilha_clear(PILHA* p, char* local){
	
	FILE* arquivo = fopen(local, "wt");
	if(arquivo != NULL){		
		while(!pilha_vazia(p)){
			LISTA variavel = pilha_pop(p);
			fprintf(arquivo, "%s\n", variavel.nome);
			fprintf(arquivo, "%s\n", variavel.depoimento);
			
		}
		fclose(arquivo);
		free(p);
		return NULL;
	}else{
		printf("nao foi possível abrir o aqrivo!\n");
		exit(1);
	}
	///return NULL;
}
void com_pilha_comentar(PILHA* p, char* u, char* comentario){
	LISTA variavel;
	strcpy(variavel.nome, u);
	strcpy(variavel.depoimento, comentario);
	pilha_push(p, variavel);
}
