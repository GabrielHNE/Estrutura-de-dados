#include "./paths.h"

static void init_paths(Paths * dirPaths, int argc, char ** argv) {  
    int i = 1;  //pula o nome do programa

    for(i; i < argc; i++){

        //Setup the entry path
        if( !strcmp(argv[i], "-e") ){
            dirPaths->entrada = setParam(i, argv);
            i++;
        }
        
        //Set up the geo path
        if( !strcmp(argv[i], "-o") ){
            dirPaths->saida = setParam(i, argv);
            i++;
        }
        
        //Set up the qry path
        if( !strcmp(argv[i], "-f") ){
            dirPaths->geo = setParam(i, argv);
            i++;
        }
        
        //Set up the output path
        if( !strcmp(argv[i], "-q") ){
            dirPaths->qry = setParam(i, argv);
            i++;
        }       
    }
}

static void getFileName_paths(Paths * curPaths){

    //As the .geo  file will awalys exists its not necessary to use the if statement on it
    curPaths->geoFile = getFileName(curPaths->geo); //we pass the geo path (-f) to avoid the missing entry path, as it may not exist (-e is optional)
    
    //validade if its not null
    if(curPaths->qry){
        curPaths->qryFile = getFileName(curPaths->qry); //we do the same with the qry if it is not null
    }
}

static void setInOut_paths(Paths * curPaths){
     if(curPaths->entrada){
        curPaths->geoEntrada = concatFilePath(curPaths->entrada, curPaths->geo);
        
        if(curPaths->qry){curPaths->qryEntrada = concatFilePath(curPaths->entrada, curPaths->qry);}

    }else{
        curPaths->geoEntrada = concatFilePath(NULL, curPaths->geo);
        
        if(curPaths->qry){ curPaths->qryEntrada = concatFilePath(NULL, curPaths->qry);}

    }
}

static void createSvgGeoPath_paths(Paths * curPaths){
    char * tmpExt = extFileTo(curPaths->geoFile, '.', ".svg");
    curPaths->svgGeoSaida = concatFilePath(curPaths->saida, tmpExt);
    
    free(tmpExt);
}

static char * appendExtension(char * path_noExt, const char * ext){
    char * svgQry = (char *) malloc( strlen(path_noExt) + strlen(ext) + 1 );

    strcpy(svgQry, path_noExt);
    strcat(svgQry, ext);

    return svgQry;
}

static void createNewPaths_paths(Paths * curPaths){

    //it doesn't make any verification b'cause geo file is not nullable
    createSvgGeoPath_paths(curPaths);

    //if qry exist then set the .txt and the .svg
    if(curPaths->qry != NULL){
        //[ file_name, File_extension ]
        Frag * Strings_geo = fragString(curPaths->geoFile, ".");
        Frag * Strings_qry = fragString(curPaths->qryFile, ".");

        //sum the file_name size of the geo and qry + 2: (+1 '-'), (+1 '\0')
        char * fileName_noExt = malloc( strlen(Strings_geo->array[0]) + strlen(Strings_qry->array[0]) + 2 );

        strcpy(fileName_noExt, Strings_geo->array[0]);
        
        strcat(fileName_noExt, "-");
        strcat(fileName_noExt, Strings_qry->array[0]); //file_nameGeo-file_nameQry
        
        //create the qry modifications svg path
        char * svgNoext = appendExtension(fileName_noExt, ".svg");
        char * txtNoext = appendExtension(fileName_noExt, ".txt");


        if(curPaths->saida){
            curPaths->svgQrySaida = concatFilePath( curPaths->saida, svgNoext );
            curPaths->txtQrySaida = concatFilePath( curPaths->saida, txtNoext );
        }

        free(svgNoext);
        free(txtNoext);
        free(fileName_noExt);
        free_fragString(Strings_geo);
        free_fragString(Strings_qry);
    }
}

Paths * setPaths(int argc, char ** argv){
    Paths * auxPaths = (Paths *) malloc(sizeof(Paths));

    auxPaths->entrada     = NULL; //-e
    auxPaths->saida       = NULL; //-o
    auxPaths->geo         = NULL; //-f
    auxPaths->qry         = NULL; //-q
    auxPaths->geoFile     = NULL; 
    auxPaths->qryFile     = NULL;
    auxPaths->qryEntrada  = NULL; // -e + -f
    auxPaths->geoEntrada  = NULL; // -e + -q
    auxPaths->svgGeoSaida = NULL; // -o + -e + .svg
    auxPaths->svgQrySaida = NULL; // -o + -q + '-' + e + '.svg'
    auxPaths->txtQrySaida = NULL; // -o + -q + '-' + e + '.txt'

    //Parses the array looking for the initial params
    init_paths(auxPaths, argc, argv);

    if( !(auxPaths->geo && auxPaths->saida) ){

        free_paths(auxPaths);
        return NULL;
    }

    getFileName_paths(auxPaths);
    setInOut_paths(auxPaths);   

    createNewPaths_paths(auxPaths);

    return auxPaths;
}

char * getFileName(char * path){
    char * fileName;

    //split the string in the bar if it exists if its not just return the string
    Frag * Strings = fragString(path, "/");
    size_t StrLen = Strings->index;

    fileName = (char *) malloc(strlen( Strings->array[ StrLen - 1]) + 1); //
    strcpy(fileName,  Strings->array[ StrLen - 1 ]);

    free_fragString(Strings);

    return fileName;
}

char * concatFilePath(const char * entryPath, const char * filePath){
    char * path = NULL;
    char * tmpPath = NULL;

    size_t entryLen = 0; 
    size_t fileLen = strlen(filePath);

    //flags
    int entryExists = 0;
    
    if(entryPath != NULL){
        entryLen = strlen(entryPath);

        entryExists = 1;

        if(findString(entryPath, "/", entryLen-1) != (entryLen - 1)){  
            // add a "/"
            tmpPath = (char *) malloc((entryLen + 2) * sizeof(char));
            strcpy(tmpPath, entryPath);
            strcat(tmpPath, "/");
        }else{
            // just cpy the entryPath
            tmpPath = (char *) malloc((entryLen + 1) * sizeof(char));
            strcpy(tmpPath, entryPath);
        }
    }

    //filePath
    if(entryExists){
        //.
        if(findString(filePath, ".", 0) == 0){
            //..
            if(findString(filePath, ".", 1) == 0){
                path = (char *) realloc(tmpPath, (strlen(tmpPath) + fileLen - 2) * sizeof(char));
                strcat(path, &filePath[3]); //starts after the "../"<string>
            }else{
                path = (char *) realloc(tmpPath,(strlen(tmpPath) + fileLen - 1) * sizeof(char));
                strcat(path, &filePath[2]); //starts at "./<string>"
            }

        }else if(findString(filePath, "/",0) == 0){ // 
            //the realloc creates a new block saving the previously. In reallocatino it shink 1 byte (char size) to remove the bar in the strcat;
            path = (char *) realloc(tmpPath, (strlen(tmpPath) + fileLen) * sizeof(char));
            strcat(path, &filePath[1]); //starts at "/"<string>
        }else{
            //it reallocates the full size of filePath + '/0' in the poreviously block
            path = (char *) realloc(tmpPath, (strlen(tmpPath) + fileLen + 1) * sizeof(char));
            strcat(path, filePath);
        }

    }else{
        
        //if it doesn't exist we have to setup the path again
        path = (char *) malloc((fileLen + 1) * sizeof(char));
        strcpy(path, filePath);
    }

    return path;
}

char * extFileTo(const char * string, int ch, const char * newExt){
    char * newString = malloc(strlen(string) + 1);
    strcpy(newString, string);

    char * ptrCh = strrchr(newString, ch);

    if(ptrCh){
        int len = strlen(ptrCh);
        int i;
        for(i = 1; i < len; i++){
            ptrCh[i] = newExt[i];
        }
    }

    return newString;
}

char * setParam(int pos, char ** argv){
    char * string = NULL; 

    if(argv[pos+1] != NULL){
        string = (char*) malloc( strlen( argv[pos+1] ) + 1 );
        strcpy(string, argv[pos+1]); 
    }

    return string; //retorna o add da string
}

void free_paths(Paths * path){
    free(path->entrada);
    free(path->saida);

    free(path->geo);
    free(path->qry);

    free(path->qryEntrada);
    free(path->geoEntrada);

    free(path->geoFile);
    free(path->qryFile);

    free(path->svgGeoSaida);
    free(path->svgQrySaida);
    free(path->txtQrySaida);

    free(path);
}