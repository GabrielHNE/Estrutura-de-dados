#ifndef TEXT_H
#define TEXT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
    Define a estrutura de um texto
*/
typedef struct Text{
    int id;
    char type;

    //Text properties
    float x;
    float y;
    float r;

    char * b_color;
    char * f_color;
    char * text;
    char * props;

} Text;

/*
    Cria um novo texto e retorna o endereco da estrutura que define o texto
*/
void * newSetText(char fig_type, int id, float x, float y, char * b_color, char * f_color, char * text);

#endif