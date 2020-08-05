#include "rect.h"

void * newSetRect(char fig_type, int id, float w, float h, float x, float y, char * b_color, char * f_color, char * props){
    Rect * rect = (Rect*)malloc(sizeof(Rect));

    rect->type = fig_type;
    rect->id = id;
    rect->w = w;
    rect->h = h;
    rect->x = x;
    rect->y = y;

    //malloc the colors size
    rect->b_color    = malloc(strlen(b_color) + 1);
    rect->f_color      = malloc(strlen(f_color) + 1);

    //set the colors in the figure
    strcpy(rect->b_color, b_color);
    strcpy(rect->f_color, f_color);

    if(props != NULL){
        rect->props     = malloc(strlen(props) + 1);
        strcpy(rect->props, props);
    }else{
        rect->props = NULL;
    }

    return rect;
}