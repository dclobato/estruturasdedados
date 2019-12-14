#include <stdio.h>
#include <stdbool.h>
#include <fila_est.h>

bool fila_inicializar(FILA *fila)
{
  fila->inicio = fila->final = 0;
  return true;
}

bool fila_destruir(FILA *fila)
{
  fila->inicio = fila->final = 0;
  return true;
}

unsigned int fila_numero_de_elementos(const FILA *fila)
{
  unsigned int final;
  // Garantir que o final é sempre maior que o início por causa do buffer circular
  final = fila->final + (fila->final < fila->inicio ? TAM_FILA : 0);
  return (final - fila->inicio);
}

unsigned int fila_numero_de_nos_livres(const FILA *fila)
{
  return (fila_numero_de_elementos(fila) - TAM_FILA - 1);
}

bool fila_esta_vazia(const FILA *fila)
{
  return (fila->inicio == fila->final);
}

bool fila_esta_cheia(const FILA *fila)
{
  return (((fila->final + 1) % TAM_FILA) == fila->inicio);
}

void fila_imprimir(const FILA *fila)
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

bool fila_enfileirar(FILA *fila, const TIPO_DADO *valor)
{
  if ((valor == NULL) || (fila_esta_cheia(fila)))
  {
    return false;
  }

  fila->dados[fila->final] = *valor;
  fila->final = (fila->final + 1) % TAM_FILA;
  return true;
}

bool fila_enfileirar_com_prioridade(FILA *fila, const TIPO_DADO *valor)
{
  unsigned int in, i;
  unsigned int limite;

  if ((valor == NULL) || (fila_esta_cheia(fila)))
  {
    return false;
  }

  if (fila_esta_vazia(fila))
  {
    return fila_enfileirar(fila, valor);
  }

  in = (fila->final - 1 + TAM_FILA) % TAM_FILA;
  i = 0;
  limite = fila_numero_de_elementos(fila);

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

bool fila_desenfileirar(FILA *fila, TIPO_DADO *valor)
{
  if (fila_esta_vazia(fila))
  {
    return false;
  }

  *valor = fila->dados[fila->inicio];
  fila->inicio = (fila->inicio + 1) % TAM_FILA;
  return true;
}

bool fila_head(const FILA *fila, TIPO_DADO *valor)
{
  if (fila_esta_vazia(fila))
  {
    return false;
  }

  *valor = fila->dados[fila->inicio];
  return true;
}
bool fila_tail(const FILA *fila, TIPO_DADO *valor)
{

  if (fila_esta_vazia(fila))
  {
    return false;
  }
  *valor = fila->dados[(fila->final + TAM_FILA - 1) % TAM_FILA];
  return true;
}
