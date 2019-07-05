#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <heap.h>
#include <limits.h>

bool inicializa_heap(HEAP *heap, unsigned tamanhoMaximo, tipoHeap tipo)
{
  heap->tamanhoMaximo = tamanhoMaximo;
  heap->ocupados = 0;
  heap->tipo = tipo;
  heap->dados = NULL;
  return true;
}

bool destroi_heap(HEAP *heap)
{
  heap->tamanhoMaximo = 0;
  heap->ocupados = 0;
  heap->tipo = MAX_HEAP;

  if (heap->ocupados > 0)
  {
    free(heap->dados);
  }

  heap->dados = NULL;
  return true;
}

bool constroi_heap(HEAP *heap, const TIPO_DADO *valores, unsigned tamanho)
{
  unsigned int inicio;

  if ((!heap_vazia(heap)) || heap_cheia(heap) || (heap->dados != NULL))
  {
    return false;
  }

  heap->ocupados = tamanho;
  heap->dados = (TIPO_DADO *) realloc(heap->dados,
                                      tamanho * sizeof(TIPO_DADO));
  memcpy(heap->dados, valores, tamanho * sizeof(TIPO_DADO));

  /* heapify */
  for (inicio = (tamanho - 1) / 2; inicio >= 0; inicio--)
  {
    __heapfy(heap, inicio, tamanho);

    if (inicio ==
        0) // Para evitar o underflow do unsigned que seria causado pelo inicio--
    {
      break;
    }
  }

  return true;
}

bool __heapfy(HEAP *heap, unsigned inicio, unsigned final)
{
  unsigned raiz, filho;
  raiz = inicio;

  while (FILHO_ESQUERDO_HEAP(raiz) < final)
  {
    filho = FILHO_ESQUERDO_HEAP(raiz);

    switch (heap->tipo)
    {
      case MAX_HEAP:
        if (((filho + 1) < final) && (heap->dados[filho + 1] > heap->dados[filho]))
        {
          filho = FILHO_DIREITO_HEAP(raiz);
        }

        break;

      case MIN_HEAP:
        if (((filho + 1) < final) && (heap->dados[filho + 1] < heap->dados[filho]))
        {
          filho = FILHO_DIREITO_HEAP(raiz);
        }

        break;

      default:
        return false;
    }

    switch (heap->tipo)
    {
      case MAX_HEAP:
        if (heap->dados[raiz] < heap->dados[filho])
        {
          swap(heap->dados[filho], heap->dados[raiz]);
          raiz = filho;
        }
        else
        {
          return true; // raiz na posicao correta em relacao aos filhos
        }

        break;

      case MIN_HEAP:
        if (heap->dados[raiz] > heap->dados[filho])
        {
          swap(heap->dados[filho], heap->dados[raiz]);
          raiz = filho;
        }
        else
        {
          return true; // raiz na posicao correta em relacao aos filhos
        }

        break;

      default:
        return false;
    }
  }

  return true;
}

unsigned tamanho_heap(const HEAP *heap)
{
  return heap->ocupados;
}

bool heap_vazia(const HEAP *heap)
{
  return (heap->ocupados == 0);
}

bool heap_tipo(const HEAP *heap, tipoHeap *tipo)
{
  *tipo = heap->tipo;
  return true;
}

bool heap_inverte(HEAP *heap)
{
  unsigned inicio;
  heap->tipo = heap->tipo == MIN_HEAP ? MAX_HEAP : MIN_HEAP;

  /* heapify */
  for (inicio = (heap->ocupados - 1) / 2; inicio >= 0; inicio--)
  {
    __heapfy(heap, inicio, heap->ocupados);

    if (inicio ==
        0) // Para evitar o underflow do unsigned que seria causado pelo inicio--
    {
      break;
    }
  }

  return true;
}

bool peek_heap(const HEAP *heap, TIPO_DADO *valor)
{
  if (heap_vazia(heap))
  {
    return false;
  }

  *valor = heap->dados[0];
  return true;
}

bool pop_heap(HEAP *heap, TIPO_DADO *valor)
{
  if (heap_vazia(heap))
  {
    return false;
  }

  *valor = heap->dados[0];
  heap->ocupados = heap->ocupados - 1;
  heap->dados[0] = heap->dados[heap->ocupados];
  __heapfy(heap, 0, heap->ocupados);
  return true;
}

bool pop_push_heap(HEAP *heap, TIPO_DADO *valor, const TIPO_DADO *entrando)
{
  if (heap_vazia(heap))
  {
    return false;
  }

  *valor = heap->dados[0];
  heap->dados[0] = *entrando;
  __heapfy(heap, 0, heap->ocupados);
  return true;
}

bool push_heap(HEAP *heap, const TIPO_DADO *valor)
{
  bool rearranjar;
  unsigned inicio;

  if (heap_cheia(heap))
  {
    return false;
  }

  heap->dados[heap->ocupados] = *valor;
  heap->ocupados = heap->ocupados + 1;
  rearranjar = false;

  switch (heap->tipo)
  {
    case MIN_HEAP:
      if (heap->dados[PAI_HEAP(heap->ocupados - 1)] > heap->dados[heap->ocupados -
          1])
      {
        rearranjar = true;
      }

      break;

    case MAX_HEAP:
      if (heap->dados[PAI_HEAP(heap->ocupados - 1)] < heap->dados[heap->ocupados -
          1])
      {
        rearranjar = true;
      }

      break;
  }

  if (rearranjar)
  {
    /* heapify */
    for (inicio = heap->ocupados / 2; inicio >= 0; inicio--)
    {
      __heapfy(heap, inicio, heap->ocupados);

      if (inicio ==
          0) // Para evitar o underflow do unsigned que seria causado pelo inicio--
      {
        break;
      }
    }
  }

  return true;
}

void dump_heap(const HEAP *heap)
{
  unsigned tamanho, i;
  unsigned e, d;
  tamanho = tamanho_heap(heap);
  printf("========================\n");
  printf("%s\n", heap->tipo == MAX_HEAP ? "Max heap" : "Min heap");
  printf("Capacidade maxima: %u\n", heap->tamanhoMaximo);
  printf("Posicoes ocupadas: %u\n", heap->ocupados);
  printf("Pos Chave Esq Dir Pai\n");
  printf("-----------------------\n");

  for (i = 0; i < tamanho; i++)
  {
    e = FILHO_ESQUERDO_HEAP(i);
    d = FILHO_DIREITO_HEAP(i);
    printf("%3u %5d %3d %3d %3d\n", i, heap->dados[i], e > tamanho - 1 ? -1 : e,
           d > tamanho - 1 ? -1 : d, i == 0 ? -1 : PAI_HEAP(i));
  }

  printf("========================\n\n");
  return;
}

bool remove_chave_heap(HEAP *heap, const TIPO_DADO *valor)
{
  unsigned tamanho, i;

  if (heap_vazia(heap))
  {
    return false;
  }

  tamanho = tamanho_heap(heap);

  for (i = 0; i < tamanho; i++)
  {
    if (heap->dados[i] == *valor)
    {
      break;
    }
  }

  if (i == tamanho)
  {
    return false;
  }

  heap->dados[i] = heap->dados[tamanho - 1];
  heap->ocupados = heap->ocupados - 1;

  for (i = heap->ocupados / 2; i >= 0; i--)
  {
    __heapfy(heap, i, heap->ocupados);

    if (i == 0) // Para evitar o underflow do unsigned que seria causado pelo inicio--
    {
      break;
    }
  }

  return true;
}

bool heap_cheia(const HEAP *heap)
{
  return (heap->ocupados == heap->tamanhoMaximo);
}
