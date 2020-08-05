/*
    Arquivo que possui variaveis diversar sem um dominio especifico. Utiliza-se apenas de bibliotecas padrão
*/

#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
   Procura a partir de um ponto inicial start o char find na string 'string' e retorna a posição de 'find'
*/
int findString(const char * string, const char * find, int start);

/*-----Handling Files-----*/

//returns the file in the path with the choose mode
FILE * getFile(const char * path, const char * mode);
/*------------------------*/


/*----------Fig text---------*/
char * concatString_text(char ** array, size_t start, size_t arraySize);
/*---------------------------*/

/**
 * Define a estrutura que fragmenta strings
 * array aponta para as strings.
 * index guarda o tamanho do vetor.
 **/
typedef struct Frag {
    char ** array;
    size_t index;
} Frag;

/*
   Fatia uma string baseado em um delimitador 'delim' e retorna o endereco da estrutura
*/
Frag * fragString(const char * string, const char * delim);

/*
    Limpa todos os endereco alocados por array
*/
void free_fragString(Frag * array);

#endif //