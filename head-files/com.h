typedef struct lista LISTA;
typedef struct pilha PILHA;

/// sequencia lógica de comenatar
/// begin
/// comenta
/// limpa


/// funções invisíveis ao usuário
static int pilha_vazia(PILHA* p);
static void pilha_push(PILHA* p, LISTA n);
static LISTA pilha_pop(PILHA* p);
static int com_vazio(FILE* arquivo);

/// funções visíveis ao usuário
PILHA* com_cria_pilha();
int com_imprimirCom(char* local);
void com_pilha_begin(PILHA* p, char* local);
PILHA* com_pilha_clear(PILHA* p, char* local);
void com_pilha_comentar(PILHA* p, char* u, char* comentario);
