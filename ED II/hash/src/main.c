#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <espalhamento.h>

int main()
{
  HASH tabela;
  REGISTRO p, q;

  if (!criar_tabela_hash(&tabela))
  {
    printf("Erro na criacao da tabela\n");
    exit(1);
  }

  ocupacao_da_tabela_hash(&tabela);

  // Inserir primeira chave
  strcpy(p.nome, "Chicoh");
  strcpy(p.email, "chicoh@ceu.org.br");

  if (!inserir_na_tabela_hash(&tabela, &p))
  {
    printf("Falha na insercao\n");
    exit(1);
  }
  else
  {
    printf("Inserido\n");
  }

  // Inserir segunda chave
  strcpy(p.nome, "Joao Grilo");
  strcpy(p.email, "joaogrilo@ceu.org.br");

  if (!inserir_na_tabela_hash(&tabela, &p))
  {
    printf("Falha na insercao\n");
    exit(1);
  }
  else
  {
    printf("Inserido\n");
  }

  // Inserir chave duplicada para produzir colisao
  if (!inserir_na_tabela_hash(&tabela, &p))
  {
    printf("Falha na insercao\n");
    exit(1);
  }
  else
  {
    printf("Inserido\n");
  }

  ocupacao_da_tabela_hash(&tabela);

  // Recuperando uma chave que existe
  strcpy(q.nome, "Joao Grilo");
  if (!busca_na_tabela_hash(&tabela, &q))
  {
    printf("Erro na recuperacao\n");
  }
  else
  {
    printf("O email de %s eh %s\n", q.nome, q.email);
  }

  // Recuperando uma chave que nao existe
  strcpy(q.nome, "Raimundo Nonato");
  if (!busca_na_tabela_hash(&tabela, &q))
  {
    printf("Erro na recuperacao\n");
  }
  else
  {
    printf("O email de %s eh %s\n", q.nome, q.email);
  }

  // Removendo uma chave que existe
  strcpy(q.nome, "Chicoh");
  if (apagar_da_tabela_hash(&tabela, &q))
  {
    printf("%s removido\n", q.nome);
  }
  else
  {
    printf("%s nao existe na tabela\n", q.nome);
  }

  // Removendo uma chave que nao existe
  strcpy(q.nome, "Raimundo Nonato");
  if (apagar_da_tabela_hash(&tabela, &q))
  {
    printf("%s removido\n", q.nome);
  }
  else
  {
    printf("%s nao existe na tabela\n", q.nome);
  }

  // mostrando a tabela
  ocupacao_da_tabela_hash(&tabela);

  // Ampliando
  printf("Expandindo a tabela...\n");
  expandir_tabela_hash(&tabela);

  // mostrando a tabela
  ocupacao_da_tabela_hash(&tabela);

  if (destruir_tabela_hash(&tabela))
  {
    printf("Tabela destruida\n");
  }
  else
  {
    printf("Problema para destruir a tabela\n");
  }

  return 0;
}
