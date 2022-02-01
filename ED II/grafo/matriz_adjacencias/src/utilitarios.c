//
// Created by danie on 09/06/2021.
//

#include "utilitarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

bool ler_InteiroLongo(long int *iLongo, const char *prompt, long int limite_inferior, long int limite_superior)
{
  char buffer[4096];
  char *p;

  if (!iLongo)
  {
    return false;
  }

  do
  {
    if (prompt)
    {
      printf("%s (%ld a %ld): ", prompt, limite_inferior, limite_superior);
    }

    memset(buffer, 0, 4096);
    fgets(buffer, 4096, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    p = NULL;
    errno = 0;
    *iLongo = strtol(buffer, &p, 10);
    if ((p == buffer) || (errno == ERANGE) || (*p && *p != '\n'))
    {
      return false;
    }
  } while ((*iLongo < limite_inferior) || (*iLongo > limite_superior));

  return true;
}

bool ler_InteiroLongoSemSinal(unsigned long int *iSemSinal, const char *prompt, unsigned long int limite_inferior,
                              unsigned long int limite_superior)
{
  char buffer[4096];
  char *p;

  if (!iSemSinal)
  {
    return false;
  }

  do
  {
    if (prompt)
    {
      printf("%s (%lu a %lu): ", prompt, limite_inferior, limite_superior);
    }

    memset(buffer, 0, 4096);
    fgets(buffer, 4096, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    p = NULL;
    errno = 0;
    *iSemSinal = strtoul(buffer, &p, 10);
    if ((p == buffer) || (errno == ERANGE) || (*p && *p != '\n'))
    {
      return false;
    }
  } while ((*iSemSinal < limite_inferior) || (*iSemSinal > limite_superior));

  return true;
}

bool ler_String(char *buffer, const char *prompt, int tamanho)
{
  if (!buffer)
  {
    return false;
  }

  if (prompt != NULL)
  {
    printf("%s (ate %d caracteres): ", prompt, tamanho);
  }

  memset(buffer, 0, tamanho);
  fgets(buffer, tamanho, stdin);
  buffer[strcspn(buffer, "\n")] = '\0';
  return true;
}

bool ler_SimNao(char *prompt)
{
  char buffer[4096];

  do
  {
    if (prompt)
    {
      printf("%s (S/N): ", prompt);
    }

    memset(buffer, 0, 4096);
    fgets(buffer, 4096, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    switch (buffer[0])
    {
      case 'S':
      case 's':
        return true;
      case 'N':
      case 'n':
        return false;
    }
  } while (1);
}