#include "./utils.h"

int findString(const char * string, const char * find /*find in string*/, int start){
    
    if(string == NULL || find == NULL || start < 0){ return -2;} 

    int length = strlen(string);
    int findStrLength = strlen(find);

    if(start < length && length >= findStrLength){
        for(int i = start; i < length; i++){
            int match = 0;

            //primeira ocorrencia
            if(string[i] == find[0]){
                int j = 1; 
                match = 1;

                //verifica as proximas ocorrencias
                for(j; j < findStrLength; j++){
                    if(string[i+j] != find[j]){
                        match = 0;
                        
                        j = findStrLength; // finaliza o programa pois j fica grande ... por enquanto mais seguro que o break;
                    }
                }
            }

            if(match){ return i;}
        }
    }

    
    //se nao deu match com a find entao retorna nao encontrado
    return -1;

    //return -2 => error in params
    //return -1 => not found;
}

//-----------Handling Files-----

FILE * getFile(const char * path, const char * mode){
    FILE * tmpGeo = fopen(path, mode);

    if(!tmpGeo){
        return NULL;
    }

    return tmpGeo;
}

//------------------------------

//--------------Frag------------
Frag * fragString(const char * string, const char * delim){
    char * buffer;
    Frag * array = (Frag *) malloc(sizeof(Frag));    
    int size = strlen(string);

    array->index = 0;

    buffer = (char *) malloc(size + 1);
    strcpy(buffer, string);

    //start
    char * ptr;
    ptr = strtok(buffer, delim);

    while(ptr != NULL){
        array->index++;
        ptr = strtok(NULL, delim);
    }
    //end

    //config
    memset(buffer, '\0', size+1);   //set the whole buffer to null again 
    strcpy(buffer, string);         //copy all the string again

    array->array = (char **) malloc((array->index) * sizeof(char *)); //allocate the necessary indexes
    //endconfig

    //restart
    int i = 0;
    ptr = strtok(buffer, delim);

    while(ptr != NULL){
        array->array[i] = malloc(strlen(ptr) + 1);
        strcpy(array->array[i], ptr);

        i++;
        ptr = strtok(NULL, delim);
    }

    //rend
    free(buffer);
    return array;
}

void free_fragString(Frag * array){
    //free no array
    size_t index = array->index;

    int i = 0;
    for(i; i < index; i++){
        free(array->array[i]);
    }

    free(array->array);
    free(array);
}
//------------------------------

//-----------Fig text-----------
char * concatString_text(char ** array, size_t start, size_t arraySize){
    int i = start;
    int sizeCounter = 0;


    //calcula o tamanho da string
    for(i; i < arraySize; i++){
        sizeCounter += strlen(array[i])+1;
    }

    sizeCounter += 1;

    char * tmpString = (char *) malloc(sizeCounter * sizeof(char));
    // char * dest = (char *) malloc(sizeCounter * sizeof(char));
    memset(tmpString, '\0', sizeCounter);

    // i = start + 1;
    // strcpy(tmpString, array[start]);
    i = start;

    for(i; i < arraySize; i++){
        strcat(tmpString, " ");
        strcat(tmpString, array[i]);
    }

    //strcpy(dest, tmpString);
    //free(tmpString);
    strcat(tmpString, "\0");
    return tmpString;
}
