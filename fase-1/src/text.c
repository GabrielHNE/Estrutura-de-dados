#include "text.h"

void * newSetText(char fig_type, int id, float x, float y, char * b_color, char * f_color, char * text){
    //create in the stack to be returned
    Text * textFig = (Text *) malloc(sizeof(Text));
    
    textFig->type   = fig_type;
    textFig->id    = id;
    textFig->x     = x;
    textFig->y     = y;
    
    //malloc to the colors
    textFig->b_color    = malloc(strlen(b_color) + 1);
    textFig->f_color    = malloc(strlen(f_color) + 1);
    textFig->text       = malloc(strlen(text) + 1);

    //set the colors
    strcpy(textFig->b_color, b_color);
    strcpy(textFig->f_color, f_color);

    strcpy(textFig->text, text);

    return textFig;
}