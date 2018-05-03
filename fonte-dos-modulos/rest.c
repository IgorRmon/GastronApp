#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rest.h"

struct bistro{					/// essa estrutura só vai ser acessada no módulo
	char nome[20];
	char localGrava[40];
	char local[40];
	char bairro[20];
	char rua[20];
	char numero[20];
	char cep[20];
	char telefone[20];
	char culinaria[20];
	int  estrelas[5];
	//list* comentarios;
};
struct no{					 	/// essa estrutura representa um no da lista
	Bistro* info;
	No* prox;
};


/// funções visíveis ao usuário

No*  rest_lst_new(){ return NULL; }

No*  rest_lst_begin(No* lista){
	
	No* primeiro = lista;
	
	FILE* index;
	if( (index = fopen("Restaurante/index", "rt")) == NULL ){
		system("clear");
		printf("O programa nao pode continuar erro ao abrir arquivo index!\n");
		exit(1);
	}else{
		char nomeArquivoRest[40];
		while( (fscanf(index, " %40s", nomeArquivoRest)) != EOF ){
			FILE* arquivoRest;
			if( (arquivoRest = fopen(nomeArquivoRest, "rt")) == NULL ){
				system("clear");
				printf("O programa nao pode continuar! Erro no arquivo %s", nomeArquivoRest);
				fclose(index);
				exit(1);
			}else{
				if(primeiro == NULL){
					No* novo = (No*)(malloc(sizeof(No)));
					novo->info = new_bistro(arquivoRest);
					novo->prox = NULL;
					primeiro = novo;
				}
				else{
					No* novo = (No*)(malloc(sizeof(No)));
					novo->info = new_bistro(arquivoRest);
					novo->prox = primeiro;
					primeiro = novo;
				}
			}
			fclose(arquivoRest);
		}
		
	}
	
	ordena_nome(primeiro);
	
	return primeiro;
}
No* rest_lst_clear(No* l){
	No* p = l;
	if(p != NULL){
		while( p != NULL){
			No* limpar = p;
			p = p->prox;	
			limpar->info = clear_bistro(limpar->info);
			free(limpar);
		}
	}
	return p;
}
void rest_lst_print(No* lista){
	for(No* imprimir = lista; imprimir != NULL; imprimir = imprimir->prox){
		print_bistro(imprimir->info);
	}
}

/// funções invisíveis ao usuário

static Bistro* new_bistro(FILE* arquivo){
	Bistro* novo = (Bistro*)(malloc(sizeof(Bistro)));
	
	fscanf(arquivo, " %[^\n]s", novo->nome);
	fscanf(arquivo, " %[^\n]s", novo->localGrava);
	fscanf(arquivo, " %[^\n]s", novo->local);
	fscanf(arquivo, " %[^\n]s", novo->bairro);
	fscanf(arquivo, " %[^\n]s", novo->rua);
	fscanf(arquivo, " %[^\n]s", novo->numero);
	fscanf(arquivo, " %[^\n]s", novo->cep);
	fscanf(arquivo, " %[^\n]s", novo->telefone);
	fscanf(arquivo, " %[^\n]s", novo->culinaria);
	
	int a, b, c, d, e;
	
	fscanf(arquivo, " %d", &a);
	fscanf(arquivo, " %d", &b);
	fscanf(arquivo, " %d", &c);
	fscanf(arquivo, " %d", &d);
	fscanf(arquivo, " %d", &e);
	
	novo->estrelas[0] 	= a;
	novo->estrelas[1] 	= b;
	novo->estrelas[2] 	= c;
	novo->estrelas[3] 	= d;
	novo->estrelas[4] 	= e;	
	
	return novo;
}
static Bistro* clear_bistro(Bistro* info){ /// gravar novamnte os arquivos
	
	FILE* arquivo = fopen(info->localGrava, "wt");
	if(arquivo != NULL){
		fprintf(arquivo, "%s\n", info->nome);
		fprintf(arquivo, "%s\n", info->localGrava);
		fprintf(arquivo, "%s\n", info->local);
		fprintf(arquivo, "%s\n", info->bairro);
		fprintf(arquivo, "%s\n", info->rua);
		fprintf(arquivo, "%s\n", info->numero);
		fprintf(arquivo, "%s\n", info->cep);
		fprintf(arquivo, "%s\n", info->telefone);
		fprintf(arquivo, "%s\n", info->culinaria);
		for(int x = 0; x < 5; x++)fprintf(arquivo, "%d\n", info->estrelas[x]); /// talvez mudar
	}
	
	free(info);
	return NULL;
}

static void print_bistro(Bistro* restaurante){
	printf("%s\n", restaurante->nome);
	printf("%s, %s, %s, %s\n", restaurante->rua, restaurante->numero, restaurante->cep, restaurante->bairro);
	printf("%s\n", restaurante->telefone);
	printf("culinaria %s\n\n", restaurante->culinaria);
}
static void ordena_nome(No* primeiroNo){
	for(No* x = primeiroNo; x != NULL; x = x->prox){
		for(No* y = primeiroNo; y != NULL; y = y->prox){
			if( strcmp(x->info->nome, y->info->nome) < 0 ){
				Bistro* aux = x->info;
				x->info = y->info;
				y->info = aux;
			}
		}
	}
}

No* rest_lst_busca_nome(No* lista, char* nome){ //deve retornar null
	No*p;
	char nome1[50];
	strcpy(nome1,nome);
	for(p=lista; p != NULL; p = p->prox){
		char nome2[50];
		strcpy(nome2,p->info->nome);
		if(strcmp(nome2,nome1)==0){
		return p;
	}
	}
return NULL;	
}

int rest_restEncontrado(No* l){
	if(l == NULL) return 0;
	else return 1;
}

int rest_lst_listar_culinaria(No* lista, char* culinaria){
	int cont = 0;
	for(No* l = lista; l != NULL; l = l->prox){
		if(!strcasecmp(l->info->culinaria, culinaria)){
			print_bistro(l->info);
			cont++;
		}
	}
	return cont;
}
void rest_avaliarResto(No* restaurante){
	int op = 0;
	printf("Classifique o restaurante: %s\n", restaurante->info->nome); // 
	printf("5 - *****\n");
	printf("4 - ****\n");
	printf("3 - ***\n");
	printf("2 - **\n");
	printf("1 - *\n");
	printf(">> ");
	scanf(" %d", &op);
	switch(op){
		case 1:
		restaurante->info->estrelas[0] += 1;
		break;
		
		case 2:
		restaurante->info->estrelas[1] += 1;
		break;
		
		case 3:
		restaurante->info->estrelas[2] += 1;
		break;
		
		case 4:
		restaurante->info->estrelas[3] += 1;
		break;
		
		case 5:
		restaurante->info->estrelas[4] += 1;
		break;
		
		default:
		break;
	}
}
static int soma(int *v){
	float numerador=0, denominador=0;
	
	for(int x=0;x<5;x++){
		numerador += v[x]*(x+1);
		denominador+=v[x];
	}
	if(denominador==0){
	 return 0;
	}
	float media1=numerador/denominador;
	int media=media1;
	if(media1-media >= 0.5) return media+1;
	return media; 
}


void rest_lst_printHanking(No* l){
	int m;
	int cont = 1;
	for(int n = 5; n >= 1; n--){
		for(No* p = l; p != NULL; p = p->prox){
			if((m = soma(p->info->estrelas)) == n){
				
				int pass = 20 - strlen(p->info->nome);
				printf("%d° %s",cont, p->info->nome);
				cont++;
				for(int a = 0; a < pass; a++) printf(" ");
				for(int x=0;x < m;x++){
					printf("*");
					if(x == m-1) printf("\n"); 
				}
			}
		}
	}
	printf("\n\n");
}

void rest_lst_printTop(No* l){
	int m;
	int cont = 0;
	int estrelas = 5;
	int top = 1;
	printf("TOP 3 MELHORES:\n");
	for(int n = 0; n < 3; n++){ /// for que conta a quatidade de tops
		for(No* p = l; p != NULL; p = p->prox){ /// for que percorre a lista em busca nós com o maior tamanho
			if((m = soma(p->info->estrelas)) == estrelas){
				
				int pass = 20 - strlen(p->info->nome);
				printf("%d - %s",top, p->info->nome);
				for(int a = 0; a < pass; a++)printf(" ");
				
				cont++;
				top++;
				for(int x=0;x < m;x++){
					printf("*");
					if(x == m-1) printf("\n");
				}
				if(cont == 3) break;
			}
		}
		estrelas--;
		if(cont == 3) break;
	}
	printf("\n");
}

char* rest_getLocal(No* l){
	return l->info->local;
}
