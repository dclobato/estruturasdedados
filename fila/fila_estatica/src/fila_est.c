#include <stdio.h>
#include <stdbool.h>
#include <fila_est.h>

bool fila_inicializa(FILA *fila)
{
  fila->inicio = fila->final = 0;
  return true;
}

bool fila_destroi(FILA *fila)
{
  fila->inicio = fila->final = 0;
  return true;
}

unsigned int fila_tamanho(const FILA *fila)
{
  unsigned int final;
  final = fila->final + (fila->final < fila->inicio ? TAM_FILA : 0);
  return (final - fila->inicio);
}

bool fila_vazia(const FILA *fila)
{
  return (fila->inicio == fila->final);
}

bool fila_cheia(const FILA *fila)
{
  return (((fila->final + 1) % TAM_FILA) == fila->inicio);
}

void fila_imprime(const FILA *fila)
{
  unsigned int i;

  for (i = 0; i < TAM_FILA; i++)
  {
    printf("[%03u]: %d", i, fila->dados[i]);

    if (i == fila->inicio)
    {
      printf(" (inicio)");
    }

    if (i == fila->final)
    {
      printf(" (final)");
    }

    printf("\n");
  }
}

bool fila_enfileira(FILA *fila, const TIPO_DADO *valor)
{
  if ((!valor) || (((fila->final + 1) % TAM_FILA) == fila->inicio))
  {
    return false;
  }

  fila->dados[fila->final] = *valor;
  fila->final = (fila->final + 1) % TAM_FILA;
  return true;
}

bool fila_enfileira_prioridade(FILA *fila, const TIPO_DADO *valor)
{
  unsigned int in, i;
  unsigned int limite;

  if ((!valor) || (fila_tamanho(fila) == TAM_FILA - 1))
  {
    return false;
  }

  if (fila_vazia(fila))
  {
    return fila_enfileira(fila, valor);
  }

  in = (fila->final - 1 + TAM_FILA) % TAM_FILA;
  i = 0;
  limite = fila_tamanho(fila);

  while (i < limite)
  {
    if (fila->dados[in] <= *valor)
    {
      break;
    }

    fila->dados[(in + 1 + TAM_FILA) % TAM_FILA] = fila->dados[in];
    in = (in - 1 + TAM_FILA) % TAM_FILA;
    i++;
  }

  fila->dados[(in + 1 + TAM_FILA) % TAM_FILA] = *valor;
  fila->final = (fila->final + 1 + TAM_FILA) % TAM_FILA;
  return true;
}

bool fila_desenfileira(FILA *fila, TIPO_DADO *valor)
{
  if (fila->inicio == fila->final)
  {
    return false;
  }

  *valor = fila->dados[fila->inicio];
  fila->inicio = (fila->inicio + 1) % TAM_FILA;
  return true;
}
