#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*libs criadas*/
#include "./utils.h"
#include "./geo.h"
#include "./qry.h"
#include "./list.h"
#include "./svg.h"
#include "./paths.h"
#include "./figures.h"


int main(int argc, char * argv[]){
    List * figuresList = NULL;
    Paths * paths = setPaths(argc, argv);

    if(!paths){ return 0; }

    //setup the read geo
    figuresList = readGeo(paths->geoEntrada, paths->svgGeoSaida);

    //if figuresList is NULL
    if(!figuresList){
        
        freeList(figuresList);
        free_paths(paths);

        return 0;
    }

    handleSvg(paths->svgGeoSaida, figuresList);

    //setup the read qry functions
    if(paths->qry){
        //readQRY will modify the figuresList
        readQRY(figuresList, paths->qryEntrada, paths->txtQrySaida);

        handleSvg(paths->svgQrySaida, figuresList);
    }

    destroyFigureListData(figuresList);

    freeList(figuresList);
    free_paths(paths);

    return 0;
}

//