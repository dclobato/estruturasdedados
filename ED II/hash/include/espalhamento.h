//
// Created by danie on 01/09/2020.
//

#ifndef ESPALHAMENTO_ESPALHAMENTO_H
#define ESPALHAMENTO_ESPALHAMENTO_H

#include <stdbool.h>

static const unsigned short HASH_MIN_N = 4;
static const unsigned short HASH_MAX_N = 50;

typedef struct
{
  char nome[30];
  char email[50];
} REGISTRO;

typedef enum
{
  LIVRE, OCUPADO, REMOVIDO
} EstadoDoSlot;

typedef struct
{
  REGISTRO *chaves;
  EstadoDoSlot *estados;
  unsigned long int tamanho;
  unsigned long int ocupados;
  unsigned short int N;
} HASH;

bool criar_tabela_hash(HASH *tabela);
bool destruir_tabela_hash(HASH *tabela);
bool inserir_na_tabela_hash(HASH *tabela, const REGISTRO *registro);
bool apagar_da_tabela_hash(HASH *tabela, const REGISTRO *registro);
bool busca_na_tabela_hash(const HASH *tabela, REGISTRO *registro);

void ocupacao_da_tabela_hash(const HASH *tabela);

unsigned long tamanho_da_tabela_hash(const HASH *tabela);
unsigned long registros_na_tabela_hash(const HASH *tabela);
double densidade_da_tabela_hash(const HASH *tabela);
bool expandir_tabela_hash(HASH *tabela);
bool encolher_tabela_hash(HASH *tabela);
bool calcula_primo_proximo_2aN(unsigned short N, unsigned long *primo);

unsigned long calcular_valor_do_hash(const char *chave, unsigned long M);

#endif //ESPALHAMENTO_ESPALHAMENTO_H
