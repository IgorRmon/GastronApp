#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED


typedef struct user User;

///typedef struct no No;

User* user_criar_listaDeUsuarios();
char* user_Entrar(User* l);
User* user_Cadastro(User* l);
User* user_limpaListaUser(User* l);
User* user_loadListUser(User* l);


static User* cria_user(User* l, char* login, char* senha, char*nome);
static int valida_nome(char* nome);
static int valida_senha(char* senha);
static int valida_login(char* login,User* l);
void limpaBuffer();

#endif // USER_H_INCLUDED
