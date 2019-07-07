#ifndef DEF_HEAP
#define DEF_HEAP
#include <stdbool.h>

// this snippet from stackoverflow
// http://stackoverflow.com/questions/3982348/implement-generic-swap-macro-in-c
#define swap(x,y) do \
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
bool inicializa_heap(HEAP *heap, unsigned tamanhoMaximo, tipoHeap tipo);
bool destroi_heap(HEAP *heap);
bool constroi_heap(HEAP *heap, const TIPO_DADO *valores, unsigned tamanho);
unsigned tamanho_heap(const HEAP *heap);
bool heap_vazia(const HEAP *heap);
bool heap_cheia(const HEAP *heap);
bool inverte_heap (HEAP *heap);
bool tipo_heap (const HEAP *heap, tipoHeap *tipo);

// Recuperação de informação
bool peek_heap(const HEAP *heap, TIPO_DADO *valor);
bool pop_heap(HEAP *heap, TIPO_DADO *valor);

// Inserção de chaves
bool pop_push_heap(HEAP *heap, TIPO_DADO *valor, const TIPO_DADO *entrando);
bool push_heap(HEAP *heap, const TIPO_DADO *valor);

// Remoção de chaves
bool remove_chave_heap(HEAP *heap, const TIPO_DADO *valor);

// Internos
bool __heapfy(HEAP *heap, unsigned inicio, unsigned final);
void dump_heap(const HEAP *heap);
unsigned pai_nodo_heap(unsigned nodo);
unsigned filho_esquerdo_nodo_heap(unsigned nodo);
unsigned filho_direito_nodo_heap(unsigned nodo);
#endif
