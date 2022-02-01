//
// Created by danie on 09/06/2021.
//

#ifndef MAIN_C_UTILITARIOS_H
#define MAIN_C_UTILITARIOS_H

#include <stdbool.h>

bool ler_String(char *buffer, const char *prompt, int tamanho);
bool ler_SimNao(char *prompt);
bool ler_InteiroLongo(long int *iLongo, const char *prompt, long int limite_inferior, long int limite_superior);
bool ler_InteiroLongoSemSinal(unsigned long int *iSemSinal, const char *prompt, unsigned long int limite_inferior,
                              unsigned long int limite_superior);
#endif //MAIN_C_UTILITARIOS_H
