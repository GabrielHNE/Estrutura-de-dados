#include "circle.h"

void * newSetCircle(char fig_type, int id, float r, float x, float y, char * b_color, char * f_color, char * props){

    Circle * circle = (Circle *)malloc(sizeof(Circle));

    circle->type = fig_type;
    circle->id = id;
    circle->r = r;
    circle->cx = x;
    circle->cy = y;

    //malloc the colors size
    circle->b_color = malloc(strlen(b_color) + 1);
    circle->f_color = malloc(strlen(f_color) + 1);

    //set the colors in the figure
    strcpy(circle->b_color, b_color);
    strcpy(circle->f_color, f_color);

    if(props != NULL){
        circle->props     = malloc(strlen(props) + 1);
        strcpy(circle->props, props);
    }else{
        circle->props = NULL;
    }

    return circle;
}