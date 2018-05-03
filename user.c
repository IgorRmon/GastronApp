#include "user.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

struct user{
    char nome[51];
    char login[21];
    char senha[9];
    User* prox;
};

User* user_criar_listaDeUsuarios(){
    return NULL;
}

void limpaBuffer(){
(void)scanf("%*[^\n]");
(void)getchar();
}

static User* cria_user(User* l, char* login, char* senha, char *nome){
    User* novo=(User*)malloc(sizeof(User));
    strcpy(novo->nome,nome);
    strcpy(novo->login,login);
    strcpy(novo->senha,senha);
    novo->prox=l;
    return novo;
}

char* user_Entrar(User* l){
    User* t;
	char login[21];
	char senha[9];
	
	/// pede login
    printf("Login: ");
    scanf(" %[^\n]s", login);
    /// pede senha
    printf("Senha: ");
    scanf(" %[^\n]s", senha);
    
    for(t=l;t!=NULL;t=t->prox){
    if(((strcmp(t->login,login))==0) && ((strcmp(t->senha,senha))==0)){
        return (t->nome);
    }
    }limpaBuffer();
    return NULL;
}

static int valida_nome(char* nome){
    int i=0;
    char aux[51];
    strcpy(aux,nome);
    while(aux[i]!='\0'){
        if((!isalpha(aux[i])) && (aux[i]!=95) && (aux[i]!=45) && (aux[i]!=46) && (aux[i]!=32))
            return 0;
    i++;
    }
    return 1;
}

static int valida_login(char* login, User* l){ // Funcao que valida o login digitado pelo usuario
    int i=0;
    char aux[21];
    strcpy(aux,login);

    while(aux[i]!='\0'){       //Percorre todo o login digitado e verifica letra por letra
        if((((!isalnum(aux[i])) && (aux[i] !=95))) && ((aux[i])!= 45 && (aux[i])!=46 )){
          return 0;
        }
        i++;
    }

    User* t;
     for(t=l;t!=NULL;t=t->prox){ // Se passar no teste de compatibilidade entra nesse caso onde vai buscar se existe um login com o mesmo nome
        if(strcmp(login,t->login)==0)
        return 0;
        
    }
    return 1;
}

static int valida_senha(char* senha){
    char aux[9];
    int i=0;
    strcpy(aux,senha);

    while(aux[i]!='\0'){
        if(!isalnum(aux[i]))
            return 0;
        i++;
    }
    return 1;
}

User* user_Cadastro(User* l){
    char nome[51],login[21],senha[9];
    int a=0;
    int control=0;
    do{
		limpaBuffer();
		system("clear");
		printf("Nome: ");
		scanf ( "%50[^\n]",nome);
		printf("Login: ");
		scanf(" %s",login);
		printf("Senha: ");
		scanf(" %s",senha);
		limpaBuffer();
		system("clear");	
		if((valida_nome(nome)==1)&&(valida_senha(senha)==1)&&(valida_login(login,l)==1)){
			a=1;
		}
		else { system("clear"); printf("Impossível realizar cadastro tente novamente!\n");  sleep(3);}		
    }while(a==0);
    
    l=cria_user(l,login,senha,nome);
    printf("CADASTRO REALIZADO COM SUCESSO\n");
    sleep(2);
    return l;
}

User* user_limpaListaUser(User* l){
	FILE* arquivo = fopen("Utilizadores", "wt");
	User* t=l;

	if(arquivo != NULL){
	if(l != NULL){
            	while(t!=NULL){
            		fprintf(arquivo, "%s\n",t->nome);
            		fprintf(arquivo, "%s\n",t->login);
            		fprintf(arquivo, "%s\n",t->senha);
            		User* a=t;
            		t=t->prox;
            		free(a);
            	}
	}
    	}
	else{
		system("cls");
		printf("Nao foi possivel abrir o arquivo");
		exit(1);
	}

	return NULL;
}

User* user_loadListUser(User* l){
	FILE* arquivo = fopen("Utilizadores", "rt");
	if(arquivo == NULL){
		printf("Nao podemos abrir o arquivo! Tente mais tarde\n");
		exit(1);
	}else{
		char linha[51];
		while( fscanf(arquivo, " %[^\n]s", linha) != EOF ){
			User* novo = (User*)malloc(sizeof(User));
			strcpy(novo->nome, linha);
			fscanf(arquivo, " %s", linha);
			strcpy(novo->login, linha);
			fscanf(arquivo, " %s", linha);
			strcpy(novo->senha, linha);
			novo->prox = l;
			l = novo; 
		}
	}
	
	return l;
}
