#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "user.h"
#include "rest.h"
#include "com.h"

#define CLEAR system("clear")

#define MENU1 printf("\nMENU:\n[1] Efetuar Login\n[2] Cadastar novo usuario\n[3] Sair\n\nDigite sua opcao: ")
#define MENU2 printf("\nMENU:\n[1] Listar Restaurantes\n[2] Buscar Restaurante\n[3] Exibir Ranking\n[4] Sair\n\nDigite sua opcao: ")
#define MENUB printf("\nMENU:\n[1] Buscar restaurante por nome\n[2] Buscar restaurante por culinaria\n[*] Outra tecla+ENTER para sair\n\nDigite sua opcao: ")
#define MENUBN printf("\nMENU:\n[1] Avaliar restaurante\n[2] Escrever depoimento\n[3] Ver depoimentos\n[4] Sair\n\nDigite sua opcao: ")

int Le_op(){
	char v;
	int vr;
	scanf(" %c",&v);
	if(isdigit(v)==0) return -1;
	vr=atoi(&v);
	return vr;
}

int main(void){
	User* usuarios = user_criar_listaDeUsuarios(); /// cria uma lista de usuários
	usuarios = user_loadListUser(usuarios);

	No* restaurantes = rest_lst_new();

	restaurantes = rest_lst_begin(restaurantes); /// olhar essa função pos pode estar acontecendo um exit(1);
	
	int op = 0;
	int controle = 0;
	char* u;

	/// pagina 01
	do{
		CLEAR;

		printf("PDF gastronomia!\tBem vindo!\n\n");

		/// estatico
		rest_lst_printTop(restaurantes);
		
		if(controle == 1) printf("Usuário não encontrado! Realize seu cadastro!\n\n");

		MENU1;

		
		op = Le_op(); //AQUI
	
		
		switch(op){
			case 1:
				u = user_Entrar(usuarios);
				///strcpy(u, Entrar(usuarios));
				if(u != NULL) { op = 1; controle = 0; } /// caso o usuário nao exista desvie para linha 48
				else{
					op = 0;
					controle = 1;
				}
			break;

			case 2:
				usuarios = user_Cadastro(usuarios);
				op = 0;
				controle = 0;
			break;
			
			case 3:
				usuarios = user_limpaListaUser(usuarios);
				op = 1;
				exit(1);
			break;
			default: op = 0; break;
		}

	}while(op == 0);
	
	/// pagina 02
	
	op = 0;

	CLEAR;
	char string[30];
	No* comedouro = NULL;
	char controll = '\0';
	char comentario[51];
	PILHA* PilhaDeComentarios;

	do{
		printf("USUARIO: %s !\n",u);
		MENU2;
		
		limpaBuffer();
		op=Le_op(); //AQUI
		
		switch(op){
			case 1:
				CLEAR;
				rest_lst_print(restaurantes);
				printf("\n");
				op = 0;
			break;

			case 2:
				CLEAR;
				MENUB;
				int op1=0;
				op1=Le_op(); // Aqui
				
				switch(op1){
					case 1:
						printf("Digite o nome: ");
						scanf(" %[^\n]s", string);
						comedouro = rest_lst_busca_nome(restaurantes, string);
						CLEAR;
						if(rest_restEncontrado(comedouro)){
		
							int op2=0;
							printf("Restaurante %s encontrado! Escolha uma das opções a seguir:\n\n", string);
							MENUBN;
							op2=Le_op(); //AQUI
							
							switch(op2){
								case 1:
									rest_avaliarResto(comedouro);
									CLEAR;
								break;
								case 2:
									PilhaDeComentarios = com_cria_pilha();
									com_pilha_begin(PilhaDeComentarios, rest_getLocal(comedouro));
									printf("Digite seu comentario: ");
									scanf(" %[^\n]s", comentario);
									com_pilha_comentar(PilhaDeComentarios, u, comentario);
									PilhaDeComentarios = com_pilha_clear(PilhaDeComentarios, rest_getLocal(comedouro));
									CLEAR;
								break;
								case 3:
									controll = '\0';
									while(controll == '\0'){
										CLEAR;
										if(!com_imprimirCom(rest_getLocal(comedouro))){
											printf("Não há comentários para este estabelecimento!\n");
										}
										printf("\nDigite qulquer tecla para sair!\n");
										controll=Le_op();
									}
									CLEAR; 
								break;
								case 4:
									op = 0;
								break;
								default: CLEAR; op=0;
								 break;
							}
							op = 0;
						}else{
							printf("Restaurante não encontrado!\n");
							op = 0;
						}

						op = 0;
					break;
					case 2:
						printf("Digite o tipo de culinária: ");
						scanf(" %[^\n]s", string);
						
						CLEAR;
						if(!rest_lst_listar_culinaria(restaurantes, string)) printf("Não existem restaurantes com esta culinária!\n");
					break;
					
					default: op = 0; CLEAR; break;
				}
				op = 0;
				///system("clear");
			break;
			case 3:
				CLEAR;
				rest_lst_printHanking(restaurantes);
				op = 0;
			break;

			case 4:
				usuarios = user_limpaListaUser(usuarios);
				restaurantes = rest_lst_clear(restaurantes);
			break;

			default: op=0; CLEAR; break;
		}

	}while(op == 0);

	return 0;
}
