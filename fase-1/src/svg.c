#include "./svg.h"

Svg createSVG(char * path){
    Svg svg;
    if(path != NULL){ svg = fopen(path, "w"); }

    return (svg != NULL) ? svg : NULL;
}

void startSVG(Svg svg){
    fprintf(svg, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n");
}

void finishSVG(Svg svg){
    fprintf(svg, "</svg>\n");

    fclose(svg);
}

void handleSvg(char * path, List * figures){
    Svg svg = createSVG(path);

    if(!svg){
        finishSVG(svg);
        return;
    }

    startSVG(svg);

    Node * auxNode = figures->head;

    while(auxNode){  
        Figure * fig = auxNode->data;

        switch (fig->type){
            case 'c':{
                Circle * circle = fig->figura;

                if(circle->props != NULL){
                    insertCirc(svg, circle->cx, circle->cy, circle->r, circle->b_color, circle->f_color, circle->props);
                }else{
                    insertCirc(svg, circle->cx, circle->cy, circle->r, circle->b_color, circle->f_color, "");
                }

                break;
            }
            case 'r':{
                Rect * rect = fig->figura;

                if(rect->props != NULL){
                    insertRect(svg, rect->x, rect->y, rect->w, rect->h, rect->b_color, rect->f_color, rect->props);
                }else{
                    insertRect(svg, rect->x, rect->y, rect->w, rect->h, rect->b_color, rect->f_color, "");
                }
                break;
            }
            case 't':{
                Text * text = fig->figura;

                insertText(svg, text->x, text->y, text->b_color, text->f_color, text->text);
                
                break;
            }
            case 'l':{
                Line * line = fig->figura;

                if(line->props != NULL){
                    insertLine(svg, line->x1, line->y1, line->x1, line->x2, line->s_width, line->b_color, line->props);
                }else{
                    insertLine(svg, line->x1, line->y1, line->x2, line->y2, line->s_width, line->b_color, "");
                }
                break;
            }
            default:
                break;
        }

        auxNode = auxNode->next; 
    }

    finishSVG(svg);
}

//handlign figures
void insertCirc(Svg svg, float cx, float cy, float r, char * border, char * fill, char * properties){
    fprintf(svg, "\t<circle cx=\"%.6fpx\" cy=\"%.6fpx\" r=\"%.6fpx\" stroke=\"%s\" fill=\"%s\" stroke-width=\"1px\" %s/>\n", cx, cy, r, border, fill, properties);
}

void insertRect(Svg svg, float x, float y, float w, float h, char * border, char * fill, char * properties){
    fprintf(svg, "\t<rect x=\"%.6fpx\" y=\"%.6fpx\" width=\"%.6fpx\" height=\"%.6fpx\" stroke=\"%s\" fill=\"%s\" stroke-width=\"1px\" %s/>\n", x, y, w, h, border, fill, properties);
}

void insertText(Svg svg, float x, float y, char * border, char * fill, char * text){
    fprintf(svg, "\t<text x=\"%.6fpx\" y=\"%.6fpx\" stroke=\"%s\" fill=\"%s\" stroke-width=\"1px\">%s</text>\n", x, y, border, fill, text);
}

void insertLine(Svg svg, float x1, float y1, float x2, float y2, float stroke_w, char * b_color, char * props){
    fprintf(svg, "\t<line x1=\"%fpx\" y1=\"%fpx\" x2=\"%fpx\" y2=\"%fpx\" stroke=\"%s\" stroke-width=\"%.6f\" />\n", x1, y1, x2, y2, b_color, stroke_w);
}

//