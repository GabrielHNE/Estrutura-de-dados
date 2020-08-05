/*
    Este arquivo SVG tem por objetivo fornecer os métodos que irão 
    formar nosso arquivo .svg;
*/

#ifndef SVG_H
#define SVG_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "./utils.h"
#include "./figures.h"

#include "circle.h"
#include "rect.h"
#include "text.h"
#include "line.h"

/*Pseudônimo para criação do svg*/
typedef FILE * Svg;
/*
    Cria o arquivo .svg baseado no caminho 'path' e retorna seu endereco
*/
Svg createSVG(char * path);

/*
    Inicia o cabeçalho do arquivo svg no arquivo svg a partir do pseudônimo Svg
*/
void startSVG(Svg svg);


/*
    Finaliza o rodapé do arquivo svg no arquivo svg a partir do pseudônimo Svg
*/
void finishSVG(Svg svg);

/*
    Direciona as figuras encontradas em figures para a inserção no svg 
*/
void handleSvg(char * path, List * figures);

/*
    Insere um circulo no arquivo svg
*/
void insertCirc(Svg svg, float cx, float cy, float r, char * border, char * fill, char * properties);

/*
    Insere um retangulo no arquivo svg
*/
void insertRect(Svg svg, float x, float y, float w, float h, char * border, char * fill, char * properties);

/*
    Insere um texto no arquivo svg
*/
void insertText(Svg svg, float x, float y, char * border, char * fill, char * text);

/*
    Insere uma linha no arquivo svg
*/
void insertLine(Svg svg, float x1, float y1, float x2, float y2, float stroke_w, char * b_color, char * props);

/*
    Insere um circulo de raio definido no arquivo svg
*/
void insertPoint(Svg svg, float x, float y, char * b_color, char * f_color, char * props);

#endif //SVG_H
