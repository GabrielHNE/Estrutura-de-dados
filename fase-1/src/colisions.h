#ifndef COLISIONS_H
#define COLISION_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "circle.h"
#include "rect.h"
#include "line.h"
#include "text.h"

/*
    Verifica se o rect1 sobrepoem o rect2.
    Retorno 1: sobrepoem; 0: não sobrepoem
*/
int rectOverlap(void * rect1, void * rect2);

/*
    Verifica se o circ1 sobrepoem o circ2.
    Retorno 1: sobrepoem; 0: não sobrepoem
*/
int circleOverlap(void * circ1, void * circ2);

/*
    Verifica se o circ sobrepoem o rect.
    Retorno 1: sobrepoem; 0: não sobrepoem
*/
int circRectOverlap(void * circ, void * rect);

//colisions

/*
    Verifica se o ponto (px, py) e interno ao retangulo de coordenadas
    (x, y), largura: w e altura: h 
*/
int isPointInternalToRect(float x, float y, float w, float h, float px, float py);

/*
    Verifica se o ponto (px, py) e interno ao circulo de coordenadas
    (x, y) e raio: r
*/
int isPointInternalToCirc(float r, float x, float y, float px, float py);

//change latter
/*
    Retorna o valor maximo entre a e b
*/
float getMax(float a, float b);

/*
    Retorna o valor minimo entre a e b
*/
float getMin(float a, float b);




#endif