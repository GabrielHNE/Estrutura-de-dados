#ifndef RECT_H
#define RECT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
    Define a estrutura de um retangulo
*/
typedef struct Rect{
    int id;
    char type;

    //Rect properties
    float x;
    float y;
    float w;
    float h;

    char * b_color;
    char * f_color;
    char * props;

} Rect;

/*
    Cria um novo retangulo e retorna o endereco da estrutura que define o retangulo
*/
void * newSetRect(char fig_type, int id, float w, float h, float x, float y, char * b_color, char * f_color, char * props);


#endif