#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <heap.h>

bool heap_inicializa(HEAP *heap, unsigned tamanhoMaximo, tipoHeap tipo)
{
  heap->tamanhoMaximo = tamanhoMaximo;
  heap->ocupados = 0;
  heap->tipo = tipo;
  heap->dados = NULL;
  return true;
}

bool heap_destroi(HEAP *heap)
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

bool heap_constroi(HEAP *heap, const TIPO_DADO *valores, unsigned tamanho)
{
  if ((!heap_vazia(heap)) || (heap->dados != NULL))
  {
    return false;
  }

  heap->ocupados = tamanho;
  heap->dados = (TIPO_DADO *) realloc(heap->dados, tamanho * sizeof(TIPO_DADO));
  memcpy(heap->dados, valores, tamanho * sizeof(TIPO_DADO));

  /* heapify */
  for (unsigned inicio = (tamanho - 1) / 2; inicio >= 0; inicio--)
  {
    heapfy(heap, inicio, tamanho);

    if (inicio == 0) // Para evitar o underflow do unsigned que seria causado pelo inicio--
    {
      break;
    }
  }

  return true;
}

bool heapfy(HEAP *heap, unsigned inicio, unsigned final)
{
  unsigned raiz, filho;
  raiz = inicio;

  while (FILHO_ESQUERDO_NODO(raiz) < final)
  {
    filho = FILHO_ESQUERDO_NODO(raiz);

    switch (heap->tipo)
    {
      case MAX_HEAP:
        if (((filho + 1) < final) && (heap->dados[filho + 1] > heap->dados[filho]))
        {
          filho = FILHO_DIREITO_NODO(raiz);
        }

        break;

      case MIN_HEAP:
        if (((filho + 1) < final) && (heap->dados[filho + 1] < heap->dados[filho]))
        {
          filho = FILHO_DIREITO_NODO(raiz);
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

unsigned heap_tamanho(const HEAP *heap)
{
  return heap->ocupados;
}

bool heap_vazia(const HEAP *heap)
{
  return (heap->ocupados == 0);
}

bool tipo_heap(const HEAP *heap, tipoHeap *tipo)
{
  *tipo = heap->tipo;
  return true;
}

bool heap_inverte(HEAP *heap)
{
  heap->tipo = heap->tipo == MIN_HEAP ? MAX_HEAP : MIN_HEAP;

  /* heapify */
  for (unsigned inicio = (heap->ocupados - 1) / 2; inicio >= 0; inicio--)
  {
    heapfy(heap, inicio, heap->ocupados);

    if (inicio == 0) // Para evitar o underflow do unsigned que seria causado pelo inicio--
    {
      break;
    }
  }

  return true;
}

bool heap_peek(const HEAP *heap, TIPO_DADO *valor)
{
  if (heap_vazia(heap))
  {
    return false;
  }

  *valor = heap->dados[0];
  return true;
}

bool heap_pop(HEAP *heap, TIPO_DADO *valor)
{
  if (heap_vazia(heap))
  {
    return false;
  }

  *valor = heap->dados[0];
  heap->ocupados = heap->ocupados - 1;
  heap->dados[0] = heap->dados[heap->ocupados];
  heap->dados = (TIPO_DADO *) realloc(heap->dados, heap->ocupados * sizeof(TIPO_DADO));
  heapfy(heap, 0, heap->ocupados);
  return true;
}

bool heap_pop_push(HEAP *heap, TIPO_DADO *valor, const TIPO_DADO *entrando)
{
  if (heap_vazia(heap))
  {
    return false;
  }

  *valor = heap->dados[0];
  heap->dados[0] = *entrando;
  heapfy(heap, 0, heap->ocupados);
  return true;
}

bool heap_push(HEAP *heap, const TIPO_DADO *valor)
{
  bool rearranjar;
  unsigned inicio;

  if (heap_cheia(heap))
  {
    return false;
  }

  heap->dados = (TIPO_DADO *) realloc(heap->dados, (heap->ocupados + 1) * sizeof(TIPO_DADO));
  heap->dados[heap->ocupados] = *valor;
  heap->ocupados = heap->ocupados + 1;
  rearranjar = false;

  switch (heap->tipo)
  {
    case MIN_HEAP:
      if (heap->dados[NODO_PAI(heap->ocupados - 1)] > heap->dados[heap->ocupados - 1])
      {
        rearranjar = true;
      }

      break;

    case MAX_HEAP:
      if (heap->dados[NODO_PAI(heap->ocupados - 1)] < heap->dados[heap->ocupados - 1])
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
      heapfy(heap, inicio, heap->ocupados);

      if (inicio == 0) // Para evitar o underflow do unsigned que seria causado pelo inicio--
      {
        break;
      }
    }
  }

  return true;
}

void heapDump(const HEAP *heap)
{
  unsigned tamanho;
  unsigned e, d;
  tamanho = heap_tamanho(heap);
  printf("========================\n");
  printf("%s\n", heap->tipo == MAX_HEAP ? "Max heap" : "Min heap");
  printf("Capacidade maxima: %u\n", heap->tamanhoMaximo);
  printf("Posicoes ocupadas: %u\n", heap->ocupados);
  printf("Pos Chave Esq Dir Pai\n");
  printf("-----------------------\n");

  for (int nodo = 0; nodo < tamanho; nodo++)
  {
    e = FILHO_ESQUERDO_NODO(nodo);
    d = FILHO_DIREITO_NODO(nodo);
    printf("%3u %5d %3d %3d %3d\n", nodo, heap->dados[nodo], e > tamanho - 1 ? -1 : e, d > tamanho - 1 ? -1 : d,
           nodo == 0 ? -1 : NODO_PAI(nodo));
  }

  printf("========================\n\n");
}

bool heap_remove_chave(HEAP *heap, const TIPO_DADO *valor)
{
  unsigned tamanho, i;

  if (heap_vazia(heap))
  {
    return false;
  }

  tamanho = heap_tamanho(heap);

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
  heap->dados = (TIPO_DADO *) realloc(heap->dados, heap->ocupados * sizeof(TIPO_DADO));

  for (i = heap->ocupados / 2; i >= 0; i--)
  {
    heapfy(heap, i, heap->ocupados);

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
