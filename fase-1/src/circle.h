#ifndef CIRCLE_H
#define CIRCLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
    Define a estrutura de um circulo
*/
typedef struct Circle{
    int id;
    char type;

    //circle properties
    float cx;
    float cy;
    float r;

    char * b_color;
    char * f_color;
    char * props;

} Circle;

/*
    Cria um novo circulo e retorna o endereco da estrutura que define o circulo
*/
void * newSetCircle(char fig_type, int id, float r, float x, float y, char * b_color, char * f_color, char * props);


#endif