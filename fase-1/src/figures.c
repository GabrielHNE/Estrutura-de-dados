#include "./figures.h"
#include <math.h>


void * newSetPoint(int id, float x, float y, char * b_color, char * f_color, char * props){
    float r = 1.0; //

    //cria o ponto a partir do circle mas com um r definido
    void * point = (Circle *) newSetCircle('c', id, r, x, y, b_color, f_color, NULL);

    return point;
}

void destroyFigureListData(List * figures){
    //clear data in the list
    Node * tmpNode = figures->head;

    while (tmpNode){
        newFreeFigureData(tmpNode->data);
        tmpNode = tmpNode->next; 
    }
}

int getFiguresRelation(Figure fig1, Figure fig2){
    if(fig1.type == 'c'){

        if(fig2.type == 'r'){
            //return relation is circle-rect
            return 3;
        }

        if(fig2.type == 'c'){
            //return 1 or 0
            //relation is circle-circle
            return 2;
        }
        
    }else if(fig1.type == 'r'){
        if(fig2.type == 'c'){
            //return 1 or 0
            //relation is rect-circle
            return 1;
        }

        if(fig2.type == 'r'){
            //return 1 or 0
            //relation is rect-rect
            return 0;
            
        }
    }

    //error occurred in procedure
    return -1;
}

void newFreeFigureData(void * data){
    Figure * fig = data;

    if(fig->type == 'c'){
        Circle * circle = fig->figura;

        free(circle->b_color);
        free(circle->f_color);

        if(circle->props != NULL){
            free(circle->props);
        }

        free(fig->figura);

    }else if(fig->type == 'r'){
        Rect * rect = fig->figura;

        free(rect->b_color);
        free(rect->f_color);

        if(rect->props != NULL){
            free(rect->props);
        }

        free(fig->figura);

    }else if(fig->type == 't'){
        Text * text = fig->figura;

        free(text->b_color);
        free(text->f_color);
        free(text->text);
    
        free(fig->figura);

    }else if(fig->type == 'l'){
        Line * line = fig->figura;

        free(line->b_color);

        if(line->props != NULL){
            free(line->props);
        }

        free(fig->figura);

    }

    free(fig);
}

void newSetFigure(List * figures, Frag * strings){
    Figure * figura = (Figure *)malloc(sizeof(Figure));
    
    if(!strcmp(strings->array[0], "t")){
        char obj = 't';
        int id = atoi(strings->array[1]);
        float x = atof(strings->array[2]);
        float y = atof(strings->array[3]);

        figura->id = id;
        figura->type = obj;
        //create and allocated the text
        char * text = concatString_text(strings->array, 6, strings->index);

        figura->figura = (Text *) newSetText(obj, id, x, y, strings->array[4], strings->array[5], text);

        //destroy the text
        free(text);

    }else if(!strcmp(strings->array[0], "c")){
        char obj = 'c';
        int id = atoi(strings->array[1]);
        float r = atof(strings->array[2]);
        float x = atof(strings->array[3]);
        float y = atof(strings->array[4]);

        figura->id = id;
        figura->type = obj;
        figura->figura = (Circle *) newSetCircle(obj, id, r, x, y, strings->array[5], strings->array[6], NULL);

    }else if(!strcmp(strings->array[0], "r")){
        char obj = 'r';
        int id = atoi(strings->array[1]);
        float w = atof(strings->array[2]);
        float h = atof(strings->array[3]);
        float x = atof(strings->array[4]);
        float y = atof(strings->array[5]);

        figura->id = id;
        figura->type = obj;
        figura->figura = (Rect *) newSetRect(obj,id, w, h, x, y, strings->array[6], strings->array[7], NULL);

    }else if(!strcmp(strings->array[0], "nx")){
        free(figura);
        return;
    }

    if(figura != NULL){
        pushBack(figures, figura);
    }

}

void * findFigureById(List * figures, int id){
    //clear data in the list
    Node * tmpNode = figures->head;

    //when tmpNode be null it exits
    while (tmpNode){
        Figure * obj = tmpNode->data;

        if(obj->id == id){
            return (Figure *)tmpNode->data;
        }

        tmpNode = tmpNode->next; 
    }

    //if it does not find the id returns null
    return NULL;
}

void delFigureInList(List *  figures, int id){

    Node * tmpNode = figures->head;

    while (tmpNode){
        Figure * fig = (Figure *)tmpNode->data;

        if(fig->id == id){
            if(tmpNode == figures->head){
                //saves the prev and next nodes
                figures->head = tmpNode->next;
                
            } else if(tmpNode == figures->tail){
                
                figures->tail = tmpNode->prev;
            } else {
                Node * prevNode = tmpNode->prev;
                
                prevNode->next = tmpNode->next;
                prevNode->next->prev = prevNode;
            }

            //free the node
            //fig == tmpNode->data
            newFreeFigureData(fig);
            free(tmpNode);
            return;
        }
        tmpNode = tmpNode->next; 
    }
    
}

void changeFigureColor(void * figure, char * color){
    Figure * fig = (Figure *) figure;

    if(fig->type == 'r'){
        Rect * rect = fig->figura;

        free(rect->f_color);

        rect->f_color = malloc(strlen(color) + 1);
        strcpy(rect->f_color, color);

    }else if(fig->type == 'c'){

        Circle * circle = fig->figura;

        free(circle->f_color);
        
        circle->f_color = malloc( strlen(color) + 1);
        strcpy(circle->f_color, color);

    }else if(fig->type == 't'){

        Text * text = fig->figura;

        free(text->f_color);
        text->f_color = malloc( strlen(color) + 1);

        strcpy(text->f_color, color);
    }

}

void changeFigureBorderColor(void * figure, char * border_color){
    Figure * fig = (Figure *)figure;

    if(fig->type == 'r'){
        Rect * rect = fig->figura;

        free(rect->b_color);

        rect->b_color = (char *)malloc( strlen(border_color) + 1);
        strcpy(rect->b_color, border_color);

    }else if(fig->type == 'c'){
        Circle * circle = fig->figura;

        free(circle->b_color);
        
        circle->b_color = malloc( strlen(border_color) + 1);
        strcpy(circle->b_color, border_color);

    }else if(fig->type == 't'){
        Text * text = fig->figura;

        free(text->b_color);
        
        text->b_color = malloc( strlen(border_color) + 1);
        strcpy(text->b_color, border_color);
    }
}

//colisions
int isOverlapping(Figure fig1, Figure fig2){
    int relation = getFiguresRelation(fig1, fig2);

    switch(relation){
        case 0:{
            return rectOverlap(fig1.figura, fig2.figura);
        }
        case 1:{
            return circRectOverlap(fig2.figura, fig1.figura);
        }
        case 2:{
            return circleOverlap(fig1.figura, fig2.figura);
        }
        case 3:{
            return circRectOverlap(fig1.figura, fig2.figura);
        }
        default:
            return -1;
    }
}



//