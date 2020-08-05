#ifndef QRY_H
#define QRY_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    created headers
*/
#include "./utils.h"
#include "./svg.h"
#include "./list.h"
#include "./figures.h"

/**
 Lê o arquivo .qry e inicia o arquivo txr para anotar os testes
 * */
void readQRY(List * figures, const char * input, const char * txtInput); //definir como fazer as operações

/*
    Direciona os parametros do arquivo qry para suas respectivas funcoes fazendo alteracoes no txt
    e percorrendo a lista de figuras
*/
void handleQryParam(List * figures, Frag * strings, FILE * txt);


/*
    Deleta os dados da figura encontrada na lista a partir do id, retirando-a da lista tambem.
*/
void delFigureInList(List *  figures, int id);

/*
    Trata o parametro "o?" do arquivo .qry e escreve a operação no txt.
    Verifica se fig1 e fig2 colidem e desenha um retangulo que envolve ambas as figuras
*/
void overrideParam(void * fig1, void * fig2, List * figures, FILE * txt);

/*
    Trata o parametro "i?" do arquivo .qry e escreve a operação no txt.
    Verifica se um ponto é interno a figura "fig" e cria um ponto com uma linha ao centro de massa de "fig"
*/
void insideParam(void * fig, float x, float y, List * figures, FILE * txt);


void delFigureParam(List * figures, Frag * strings, FILE * txt);
void paintFigureParam(List * figures, Frag * strings, FILE * txt);

#endif //QRY_H

//