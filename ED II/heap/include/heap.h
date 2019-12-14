#ifndef DEF_HEAP
#define DEF_HEAP

#include <stdbool.h>

// this snippet from stackoverflow
// http://stackoverflow.com/questions/3982348/implement-generic-swap-macro-in-c
#define swap(x, y) do \
  { unsigned char swap_temp[sizeof(x) == sizeof(y) ? (signed)sizeof(x) : -1]; \
    memcpy(swap_temp,&y,sizeof(x)); \
    memcpy(&y,&x,       sizeof(x)); \
    memcpy(&x,swap_temp,sizeof(x)); \
  } while(0)


typedef int TIPO_DADO;

typedef enum
{
    MIN_HEAP,
    MAX_HEAP
} tipoHeap;

typedef struct __heap
{
    unsigned tamanhoMaximo;
    unsigned ocupados;
    tipoHeap tipo;
    TIPO_DADO *dados;
} HEAP;

// Inicialização, destruição e metadados
bool heap_inicializa (HEAP *heap, unsigned tamanhoMaximo, tipoHeap tipo);
bool heap_destroi (HEAP *heap);
bool heap_constroi (HEAP *heap, const TIPO_DADO *valores, unsigned tamanho);
unsigned heap_tamanho (const HEAP *heap);
bool heap_vazia (const HEAP *heap);
bool heap_cheia (const HEAP *heap);
bool heap_inverte (HEAP *heap);
bool tipo_heap (const HEAP *heap, tipoHeap *tipo);

// Recuperação de informação
bool heap_peek (const HEAP *heap, TIPO_DADO *valor);
bool heap_pop (HEAP *heap, TIPO_DADO *valor);

// Inserção de chaves
bool heap_pop_push (HEAP *heap, TIPO_DADO *valor, const TIPO_DADO *entrando);
bool heap_push (HEAP *heap, const TIPO_DADO *valor);

// Remoção de chaves
bool heap_remove_chave (HEAP *heap, const TIPO_DADO *valor);

// Internos
bool __heapfy (HEAP *heap, unsigned inicio, unsigned final);
void __heap_dump (const HEAP *heap);
unsigned __heap_pai_nodo (unsigned nodo);
unsigned __heap_filho_esquerdo_nodo (unsigned nodo);
unsigned __heap_filho_direito_nodo (unsigned nodo);

#endif
