#ifndef LINE_H
#define LINE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
    Define a estrutura de uma linha
*/
typedef struct Line{
    int id;
    char type;

    //line properties
    float x1;
    float y1;
    float x2;
    float y2;
    float s_width;

    char * b_color;
    char * props;

} Line;

/*
    Cria uma nova linha e retorna o endereco da estrutura que define a linha
*/
void * newSetLine(int id, float x1, float y1, float x2, float y2, char * b_color, char * props);

#endif