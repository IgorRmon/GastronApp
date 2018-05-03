#define uma 	0
#define duas	1
#define tres	2
#define	quatro	3
#define cinco	4

typedef struct bistro Bistro;
typedef struct no 	  No;

/// funções visiveis ao usuário
No*  rest_lst_new();
No*  rest_lst_begin(No* lista);
No*  rest_lst_clear(No* lista);
void rest_lst_print(No* lista);
void rest_lst_printTop(No* l);

void    rest_lst_printHanking(No* lista); //
int 	rest_lst_listar_culinaria(No* lista, char* culinaria); //
No* 	rest_lst_busca_nome(No* lista, char* nome); //
void 	rest_avaliarResto(No* restaurante);

int 	rest_restEncontrado(No* l);	/// verifica se encontrou o restaurante desejado
char* 	rest_getLocal(No* l);

/// funções invisíveis ao usuário
static Bistro* new_bistro(FILE* arquivo);
static Bistro* clear_bistro(Bistro* info);
static void print_bistro(Bistro* restaurante);
static void ordena_nome(No* primeiroNo);
static int soma(int *v); // 
static int my_strcmp(char* string1, char* string2);
