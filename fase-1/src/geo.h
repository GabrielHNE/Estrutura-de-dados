#ifndef GEO_H
#define GEO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    included lib
*/
#include "./utils.h"
#include "./svg.h"
#include "./list.h"
#include "./figures.h"

/*
    Abre o arquivo .geo para leitura no caminho especificado por "path" e retorna o endereco do arquivo para leituras.
*/
FILE * openGEO(char * path);

/*
    Coordena a leitura do arquivo .geo no caminho especificado por input e cria um arquivo .svg especificado por output
*/
List * readGeo(char * input, char * output);

#endif //