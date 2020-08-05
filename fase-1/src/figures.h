/**Figures
 * 
 **/
#ifndef FIGURES_H
#define FIGURES_H

#include "./utils.h"
#include "./list.h"

#include "colisions.h"
#include "circle.h"
#include "rect.h"
#include "text.h"
#include "line.h"

typedef struct Fugure{
    int id;
    char type;

    void * figura;
} Figure;


/*
    Cria um ponto a partir de circulo, usando as coordenadas do ponto e um raio fixo intrinseco a funcao
    retorna um ponteiro para a estrutura Circle
*/
void * newSetPoint(int id, float x, float y, char * b_color, char * f_color, char * props);

/*
    Libera o espaço de memoria utilizado pela estrutura de figuras (Figures), libera o espaço alocado
    de todas as figuras pertencentes a lista.
*/
void destroyFigureListData(List * figures);

/*
* Verifica a relação entre fig1 e fig2.
* retorna: 0 to rect-rect; 1 to rect-circle; 2 to circle-circle; 3 to circle-rect 
*/
int getFiguresRelation(Figure fig1, Figure fig2);

/*
    Libera o espaço de memoria alocado pela figura ocupada na estrutura Figures.
*/
void newFreeFigureData(void * data);

/*
    Direciona, baseado em um array de strings, qual devera ser a figura criada e a posiciona no final da lista 
*/
void newSetFigure(List * figures, Frag * strings);

/*
    Dado um id e uma lista contendo figuras, caso encontre, retorna o ponteiro da figura encontrada.
*/
void * findFigureById(List * figures, int id);

/*
    Remove e deleta a figura de uma lista dado o id desta figura.
*/
void delFigureInList(List *  figures, int id);

/*
    Altera a cor de preenchimento da figura pela cor "color".
*/
void changeFigureColor(void * figure, char * color);

/*
    Altera a cor de borda da figura pela cor "border_color".
*/
void changeFigureBorderColor(void * figure, char * border_color);


/*
    Direciona qual sera o tipo da colisao entre as fig 1 e 2.
    Retorna 1 se se sobrepoem, 2 se não se sobrepoem, -1 se algum erro acontecer com as figuras
*/
int isOverlapping(Figure fig1, Figure fig2);


#endif // FIGURES_H