//
// Created by danie on 01/09/2020.
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <espalhamento.h>

static const unsigned short HASH_MIN_N = 4;
static const unsigned short HASH_MAX_N = 50;

bool criar_tabela_hash(HASH *tabela)
{
  unsigned long M;

  // Inicia a tabela com espaco para 2^HASH_MIN_N - delta posicoes
  if (!calcula_primo_proximo_2aN(HASH_MIN_N, &M))
  {
    return false;
  }

  tabela->N = HASH_MIN_N;
  tabela->tamanho = M;
  tabela->chaves = (REGISTRO *) malloc(sizeof(REGISTRO) * M);
  tabela->estados = (EstadoDoSlot *) malloc(sizeof(EstadoDoSlot) * M);
  for (unsigned int slot = 0; slot < M; slot++)
  {
    tabela->estados[slot] = LIVRE;
  }
  tabela->ocupados = 0;
  return true;
}

bool destruir_tabela_hash(HASH *tabela)
{
  free(tabela->chaves);
  free(tabela->estados);
  tabela->tamanho = 0;
  tabela->ocupados = 0;
  tabela->N = 0;
  return true;
}

unsigned long calcular_valor_do_hash(char *chave, unsigned long M)
{
  unsigned long h, a = 31415, b = 27183;
  for (h = 0; *chave != '\0'; chave++)
  {
    h = (a * h + *chave) % M;
    a = (a * b) % (M - 1);
  }
  return h;
}

bool inserir_na_tabela_hash(HASH *tabela, REGISTRO *registro)
{
  unsigned long h;

  // Se estiver com densidade alta (0.75?), vamos ampliar a tabela
  if (densidade_da_tabela_hash(tabela) > 0.75)
  {
    // Se nao conseguir expandir e nao tiver mais espaco, aborta.
    if (!expandir_tabela_hash(tabela) && (tabela->ocupados == tabela->tamanho))
    {
      return false;
    }
  }

  // A tabela tem espaco para insercao da chave
  h = calcular_valor_do_hash(registro->nome, tabela->tamanho);
  while (tabela->estados[h] == OCUPADO)
  {
    h = (h + 1) % tabela->tamanho;
  }
  memcpy(&tabela->chaves[h], registro, sizeof(REGISTRO));
  tabela->estados[h] = OCUPADO;
  tabela->ocupados++;
  return true;
}

bool busca_na_tabela_hash(HASH *tabela, REGISTRO *registro)
{
  unsigned long h, h_0;

  h = calcular_valor_do_hash(registro->nome, tabela->tamanho);
  h_0 = h;
  while (tabela->estados[h] != LIVRE)
  {
    if ((tabela->estados[h] == OCUPADO) && (strcmp(registro->nome, tabela->chaves[h].nome) == 0))
    {
      memcpy(registro, &tabela->chaves[h], sizeof(REGISTRO));
      return true;
    }
    h = (h + 1) % tabela->tamanho;
    // demos a volta na tabela e nao achamos, entao false
    if (h == h_0)
    {
      break;
    }
  }
  return false;
}

bool apagar_da_tabela_hash(HASH *tabela, REGISTRO *registro)
{
  unsigned long h, h_0;

  if (tabela->ocupados == 0)
  {
    return false;
  }

  h = calcular_valor_do_hash(registro->nome, tabela->tamanho);
  h_0 = h;
  while (tabela->estados[h] != LIVRE)
  {
    if ((tabela->estados[h] == OCUPADO) && (strcmp(registro->nome, tabela->chaves[h].nome) == 0))
    {
      tabela->estados[h] = REMOVIDO;
      tabela->ocupados--;
      // se densidade menor que 0.25, encolher tabela
      if (densidade_da_tabela_hash(tabela) < 0.25)
      {
        encolher_tabela_hash(tabela);
      }
      return true;
    }
    h = (h + 1) % tabela->tamanho;
    // demos a volta na tabela e nao achamos, entao false
    if (h == h_0)
    {
      break;
    }
  }
  return false;
}

unsigned long tamanho_da_tabela_hash(HASH *tabela)
{
  return (tabela->tamanho);
}

unsigned long registros_na_tabela_hash(HASH *tabela)
{
  return (tabela->ocupados);
}

double densidade_da_tabela_hash(HASH *tabela)
{
  return ((double) registros_na_tabela_hash(tabela) / tamanho_da_tabela_hash(tabela));
}

bool expandir_tabela_hash(HASH *tabela)
{
  unsigned long novo_M, M_antigo;
  unsigned short novo_N;

  REGISTRO *novas_chaves, *chaves_antigas;
  EstadoDoSlot *novos_estados, *estados_antigos;

  // Ja esta com o tamanho maximo. abortar
  if (tabela->N == HASH_MAX_N)
  {
    return false;
  }

  // Guarda os componentes da tabela anterior
  M_antigo = tabela->tamanho;
  chaves_antigas = tabela->chaves;
  estados_antigos = tabela->estados;

  // Calcula e aloca componentes da tabela expandida
  novo_N = tabela->N + 1;
  if (!calcula_primo_proximo_2aN(novo_N, &novo_M))
  {
    return false;
  }
  novas_chaves = (REGISTRO *) malloc(sizeof(REGISTRO) * novo_M);
  novos_estados = (EstadoDoSlot *) malloc(sizeof(EstadoDoSlot) * novo_M);
  for (unsigned int slot = 0; slot < novo_M; slot++)
  {
    novos_estados[slot] = LIVRE;
  }

  // Tabela nova vazia
  tabela->chaves = novas_chaves;
  tabela->estados = novos_estados;
  tabela->ocupados = 0;
  tabela->tamanho = novo_M;
  tabela->N = novo_N;

  // percorrer a tabela antiga procurando chaves e inserindo na tabela nova
  for (unsigned long slot = 0; slot < M_antigo; slot++)
  {
    if (estados_antigos[slot] == OCUPADO)
    {
      inserir_na_tabela_hash(tabela, &chaves_antigas[slot]);
    }
  }

  // liberar os componentes da tabela antiga
  free(chaves_antigas);
  free(estados_antigos);

  return true;
}

bool encolher_tabela_hash(HASH *tabela)
{
  unsigned long novo_M, M_antigo;
  unsigned short novo_N;

  REGISTRO *novas_chaves, *chaves_antigas;
  EstadoDoSlot *novos_estados, *estados_antigos;

  // Ja esta com o tamanho minimo. abortar
  if (tabela->N == HASH_MIN_N)
  {
    return false;
  }

  // Guarda os componentes da tabela anterior
  M_antigo = tabela->tamanho;
  chaves_antigas = tabela->chaves;
  estados_antigos = tabela->estados;

  // Calcula e aloca componentes da tabela expandida
  novo_N = tabela->N - 1;
  // Ja estamos no menor tamanho?
  if (!calcula_primo_proximo_2aN(novo_N, &novo_M))
  {
    return false;
  }
  // Ha mais registros do que o numero de slots na nova tabela?
  if (novo_M < registros_na_tabela_hash(tabela))
  {
    return false;
  }
  novas_chaves = (REGISTRO *) malloc(sizeof(REGISTRO) * novo_M);
  novos_estados = (EstadoDoSlot *) malloc(sizeof(EstadoDoSlot) * novo_M);
  for (unsigned int slot = 0; slot < novo_M; slot++)
  {
    novos_estados[slot] = LIVRE;
  }

  // Tabela nova vazia
  tabela->chaves = novas_chaves;
  tabela->estados = novos_estados;
  tabela->ocupados = 0;
  tabela->tamanho = novo_M;
  tabela->N = novo_N;

  // percorrer a tabela antiga procurando chaves e inserindo na tabela nova
  for (unsigned long slot = 0; slot < M_antigo; slot++)
  {
    if (estados_antigos[slot] == OCUPADO)
    {
      inserir_na_tabela_hash(tabela, &chaves_antigas[slot]);
    }
  }

  // liberar os componentes da tabela antiga
  free(chaves_antigas);
  free(estados_antigos);

  return true;
}

bool calcula_primo_proximo_2aN(unsigned short N, unsigned long *primo)
{
  // https://primes.utm.edu/lists/2small/0bit.html
  // https://en.wikipedia.org/wiki/List_of_prime_numbers
  //
  // 2^n - delta[] eh um primo, com HASH_MIN_N <= n <= HASH_MAX_N
  static const unsigned short deltas[] = {3, 1, 3, 1, 5, 3, 3, 9, 3, 1, 3, 19, 15, 1, 5, 1, 3, 9, 3, 15, 3, 39, 5, 39,
                                          57, 3, 35, 1, 5, 9, 41, 31, 5, 25, 45, 7, 87, 21, 11, 57, 17, 55, 21, 115, 59,
                                          81, 27};

  if ((N < HASH_MIN_N) || (N > HASH_MAX_N))
  {
    return false;
  }

  *primo = (unsigned long) pow(2, N) - deltas[N - HASH_MIN_N];
  return true;
}

void ocupacao_da_tabela_hash(HASH *tabela)
{
  unsigned long h;
  printf("--- Ocupacao da tabela ---------------------------------------\n");
  printf("Capacidade total.....: %10lu\n", tabela->tamanho);
  printf("Valor de N...........: %10u\n", tabela->N);
  printf("Slots ocupados (%%)...: %10lu (%.2f%%)\n", tabela->ocupados, densidade_da_tabela_hash(tabela));
  putchar('\n');
  printf("(.) Posicao vazia\n");
  printf("(o) Posicao vazia, mas que ja foi ocupada\n");
  printf("(H) Posicao ocupada por registro na posicao correta\n");
  printf("(C) Posicao ocupada por registro relocado\n");
  printf("-------------------------------------------------------------\n");
  printf("           01234567890123456789012345678901234567890123456789");
  for (unsigned long slot = 0; slot < tabela->tamanho; slot++)
  {
    if (slot % 50 == 0)
    {
      putchar('\n');
      printf("%10lu ", slot);
    }
    switch (tabela->estados[slot])
    {
      case LIVRE:
        putchar('.');
        break;
      case REMOVIDO:
        putchar('o');
        break;
      case OCUPADO:
        h = calcular_valor_do_hash(tabela->chaves[slot].nome, tabela->tamanho);
        if (h == slot)
        {
          putchar('H');
        }
        else
        {
          putchar('C');
        }
        break;
    }
  }
  putchar('\n');
  printf("           01234567890123456789012345678901234567890123456789\n");
  printf("-------------------------------------------------------------\n");
}