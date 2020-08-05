#include "line.h"

void * newSetLine(int id, float x1, float y1, float x2, float y2, char * b_color, char * props){
    Line * line = (Line *) malloc(sizeof(Line));

    line->type = 'l';
    line->id = id;

    //improvisado
    line->x1 = x1;
    line->y1 = y1;
    line->x2 = x2;
    line->y2 = y2;
    line->s_width = 2.0;

    //malloc the colors size
    line->b_color    = malloc(strlen(b_color) + 1);

    //set the colors in the figure
    strcpy(line->b_color, b_color);

    if(props != NULL){
        line->props = malloc(strlen(props) + 1);
        strcpy(line->props, props);
    }else{
        line->props = NULL;
    }

    return line;
}