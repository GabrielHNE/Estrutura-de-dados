#ifndef PATHS_H
#define PATHS_H

#include "./utils.h"
/*
    Armazena todos os paths e nomes de arquivos do sistema siguel
*/
typedef struct Paths{
    char * entrada;
    char * saida;
    char * geo;
    char * qry;

    // entrada
    char * geoEntrada;
    char * qryEntrada;

    //files name
    char * geoFile;
    char * qryFile;

    //Saida dos svg
    char * svgGeoSaida;
    char * svgQrySaida;

    //txt qry
    char * txtQrySaida;

} Paths;

/*
    Inicializa e direciona os argumentos lido na chamada do programa
*/
static void init_paths(Paths * dirPaths, int argc, char ** argv);

/*
    Obtem o nome do arquivo dado um caminho 'curPaths'
*/
static void getFileName_paths(Paths * curPaths);

/*
    Define o caminho de entrada e saida do sistema siguel
*/
static void setInOut_paths(Paths * curPaths);

/*
    Cria o caminho de saida de leitura do arquivo .geo para o arquivo .svg
*/
static void createSvgGeoPath_paths(Paths * curPaths);

/*
    Coloca a extensão especificada por ext no path_noExt, no qual, path_noExt
    e o nome do arquivo sem a extensao
*/
static char * appendExtension(char * path_noExt, const char * ext);

/*
    Direciona e configura todos os paths lidos como argumentos do programa
*/
Paths * setPaths(int argc, char ** argv);

/*Return the file name with its extension*/
char * getFileName(char * path);

/*Gets the current extension and replace it with the newExt param.
*const char * string: the file name;
*int ch: the point where find the ext;
*const char * newExt: the new extension name;
*/
char * extFileTo(const char * string, int ch, const char * newExt);

/*Concatenate entryPath with the filePath. entryPath can be NULL*/
char * concatFilePath(const char * entryPath, const char * filePath);

/*Direciona o parametro lido como argumento de chamada*/
char * setParam(int pos, char ** argv);

/* Libera os espaços de memoria utilizados pela estrutura*/
void free_paths(Paths * path);


#endif 