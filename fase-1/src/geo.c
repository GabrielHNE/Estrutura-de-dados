#include "./geo.h"

FILE * openGEO(char * path){
    FILE * tmpGeo = fopen(path, "r");

    if(!tmpGeo){
        
        return NULL;
    }

    return tmpGeo;
}

List * readGeo(char * input, char * output){
    //Abrir o File com o input path
    FILE * geoArq = openGEO(input);
    
    //if it generates an error returns a NULL list
    if(geoArq == NULL){ 
        return NULL;
    }

    //inicia a lista que irá armazenar os elementos do arquivo
    List * figures = initList();
    
    char buff[500];



    Frag * strings;
    Frag * auxStr;

    while(fgets(buff, 500, geoArq)){
        auxStr = fragString(buff, "\n");
        strings = fragString(auxStr->array[0], " ");
        
        free_fragString(auxStr);

        newSetFigure(figures, strings);

        free_fragString(strings);
    }

    fclose(geoArq);
    
    return figures;
}

//