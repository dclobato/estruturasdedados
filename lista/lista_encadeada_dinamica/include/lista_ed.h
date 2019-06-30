#ifndef DEF_LISTA_ED
#define DEF_LISTA_ED

typedef int TIPO_DADO;

typedef struct __noh
{
  TIPO_DADO dado;
  struct __noh *prox;
} NOH;

typedef struct __lista
{
  unsigned int numElementos;
  NOH *final;
  NOH *dados;
} LISTA;

/*
 * Operacoes de inicializacao, destruicao e metadados
 */
bool inicializa_lista(LISTA *lista);
bool destroi_lista(LISTA *lista);
bool obtem_no_lista(NOH **nodo);
bool libera_no_lista(NOH **nodo);
unsigned int tamanho_lista(const LISTA *lista);

/*
 * Operacoes de recuperacao de dados
 */
void imprime_lista(const LISTA *lista);
void __imprime_lista(const LISTA *lista);
bool consulta_lista(const LISTA *lista, unsigned int posicao,
                    TIPO_DADO *valor);
bool busca_lista(const LISTA *lista, const TIPO_DADO *valor, NOH **nodo);
bool obtem_sucessor(const NOH *nodo, NOH **proximo);
bool obtem_inicio(const LISTA *lista, NOH **nodo);
bool obtem_final(const LISTA *lista, NOH **nodo);


/*
 * Operacoes de insercao
 */
bool insere_lista(LISTA *lista, const TIPO_DADO *valor,
                  unsigned int posicao);
bool insere_ordenado(LISTA *lista, const TIPO_DADO *valor);
bool insere_antes_do_nodo(LISTA *lista, const NOH **nodo,
                          const TIPO_DADO *valor);
bool insere_inicio(LISTA *lista, const TIPO_DADO *valor);
bool insere_final(LISTA *lista, const TIPO_DADO *valor);

/*
 * Operacoes de remocao
 */
bool remove_lista(LISTA *lista, TIPO_DADO *valor, unsigned int posicao);
bool remove_chave(LISTA *lista, const TIPO_DADO *valor);
bool remove_nodo(LISTA *lista, NOH **nodo);
bool remove_inicio(LISTA *lista, TIPO_DADO *valor);
bool remove_final(LISTA *lista, TIPO_DADO *valor);
#endif
