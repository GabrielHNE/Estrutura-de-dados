#include "./qry.h"

void readQRY(List * figures , const char * input, const char * txtInput){
    FILE * qryArq = getFile(input, "r"); //opens the  designated file as only read
    FILE * txtArq = getFile(txtInput, "w"); //creates the designated file to be written

    //if qry generates an error returns a NULL list
    if(qryArq == NULL){ 

        return;
    }

    //if txt generates an error returns a NULL list
    if(txtArq == NULL){ 
        
        return;
    }

    //lê o arquivo qry
    char buff[500];
    Frag * strings;

    while(fgets(buff, 500, qryArq)){
        strings = fragString(buff, " ");
        //funcao que faz as alteracoes na lista
        handleQryParam(figures, strings, txtArq);

        free_fragString(strings);
    }

    fclose(qryArq);
    fclose(txtArq);
}

/*
** 
*/
void handleQryParam(List * figures, Frag * strings, FILE * txt){
    
    //praticamento feito
    if(!strcmp(strings->array[0], "o?")){
        int first_id = atoi(strings->array[1]);
        int sec_id = atoi(strings->array[2]);

        //search by the figure Id and returns it
        Figure * fig1 = (Figure *) findFigureById(figures, first_id);
        Figure * fig2 = (Figure *) findFigureById(figures, sec_id);

        if(fig1 == NULL){

            return;
        }

        if(fig2 == NULL){

            return;
        }
        
        overrideParam(fig1, fig2, figures, txt);
        return;
    }
    
    if(!strcmp(strings->array[0], "i?")){
        int id = atoi(strings->array[1]);

        Figure * fig = (Figure *) findFigureById(figures, id);

        if(fig == NULL){
            return;
        }

        float x = atof(strings->array[2]);
        float y = atof(strings->array[3]);
        
        insideParam(fig, x, y, figures, txt);
        return;
    }
    
    if(!strcmp(strings->array[0], "delf")){  
        int id =  atoi(strings->array[1]);

        Figure * fig = (Figure *) findFigureById(figures, id);

        //write to txt
        fprintf(txt, "delf %d\n", id);

        if(fig == NULL){
            return;
        }

        if(fig->type == 'r'){
            Rect * rect = fig->figura;

            //Write to txt
            fprintf(txt, "%d %c %f %f %f %f %s %s\n", rect->id, rect->type, rect->w, rect->h, rect->x, rect->y, rect->b_color, rect->f_color);

        }else if(fig->type == 'c'){
            Circle * circle = fig->figura;
            //Write to txt
            fprintf(txt, "%d %c %f %f %f %s %s\n", circle->id, circle->type, circle->r, circle->cx, circle->cy, circle->b_color, circle->f_color);

        }else if(fig->type == 't'){
            Text * text = fig->figura;
            //Write to txt
            fprintf(txt, "%d %c %f %f %s %s\n", text->id, text->type, text->x, text->y, text->b_color, text->f_color);

        }

        delFigureInList(figures, id);
        return;
    }

    if(!strcmp(strings->array[0], "delf*")){
        int first_id = atoi(strings->array[1]);
        int last_id = atoi(strings->array[2]);
        int i = first_id;

        //write to txt
        fprintf(txt, "delf %d %d\n", first_id, last_id);

        for(i; i <= last_id; i++){

            Figure * fig = (Figure *) findFigureById(figures, i);

            //write to txt
            fprintf(txt, "delf %d\n", i);

            if(fig == NULL){
                return;
            }
            
            if(fig->type == 'r'){
                Rect * rect = fig->figura;

                //Write to txt
                fprintf(txt, "%d %c %f %f %f %f %s %s\n", rect->id, rect->type, rect->w, rect->h, rect->x, rect->y, rect->b_color, rect->f_color);

            }else if(fig->type == 'c'){
                Circle * circle = fig->figura;
                //Write to txt
                fprintf(txt, "%d %c %f %f %f %s %s\n", circle->id, circle->type, circle->r, circle->cx, circle->cy, circle->b_color, circle->f_color);

            }else if(fig->type == 't'){
                Text * text = fig->figura;
                //Write to txt
                fprintf(txt, "%d %c %f %f %s %s\n", text->id, text->type, text->x, text->y, text->b_color, text->f_color);

            }

            delFigureInList(figures, i);
        }
        return;
    }
    
    if(!strcmp(strings->array[0], "pnt")){ 
        int id = atoi(strings->array[1]);

        
        Figure * fig = (Figure *)findFigureById(figures, id);

        if(fig == NULL){
            return;
        }

        fprintf(txt, "pnt %d %s %s\n", id, strings->array[2], strings->array[3]);

        if(fig->type == 'r'){
            Rect * rect = fig->figura;

            //Write to txt
            fprintf(txt, "%f %f\n", rect->x, rect->y);

        }else if(fig->type == 'c'){
            Circle * circle = fig->figura;
            //Write to txt
            fprintf(txt, "%f %f\n", circle->cx, circle->cy);

        }else if(fig->type == 't'){
            Text * text = fig->figura;
            //Write to txt
            fprintf(txt, "%f %f\n", text->x, text->y);
        }


        changeFigureBorderColor(fig, strings->array[2]);

        changeFigureColor(fig, strings->array[3]);

        return;
    }
    
    if(!strcmp(strings->array[0], "pnt*")){
        int first_id = atoi(strings->array[1]);
        int last_id = atoi(strings->array[2]);
        int id = first_id;

        //Write to txt
        fprintf(txt, "pnt* %d %d %s %s\n", first_id, last_id, strings->array[3], strings->array[4]);

        for(id; id <= last_id; id++){
            Figure * fig =(Figure *) findFigureById(figures, id);

            if(fig == NULL){
                return;
            }

            fprintf(txt, "pnt %d %s %s\n", id, strings->array[3], strings->array[4]);

            if(fig->type == 'r'){
                Rect * rect = fig->figura;

                //Write to txt
                fprintf(txt, "%f %f\n", rect->x, rect->y);

            }else if(fig->type == 'c'){
                Circle * circle = fig->figura;
                //Write to txt
                fprintf(txt, "%f %f\n", circle->cx, circle->cy);

            }else if(fig->type == 't'){
                Text * text = fig->figura;
                //Write to txt
                fprintf(txt, "%f %f\n", text->x, text->y);
            }

            changeFigureBorderColor(fig, strings->array[3]);

            changeFigureColor(fig, strings->array[4]);
        }

        return;
    }
    
}

void overrideParam(void * fig1, void * fig2, List * figures, FILE * txt){
    
    Figure * figura1 = (Figure *) fig1;
    Figure * figura2 = (Figure *) fig2;


    char fig1_name[100];
    char fig2_name[100];

    
    if(figura1->type == 'r'){
        strcpy(fig1_name, "Retangulo");
    }else{
        strcpy(fig1_name, "Circulo");
    }

    if(figura2->type == 'r'){
        strcpy(fig2_name, "Retangulo");
    }else{
        strcpy(fig2_name, "Circulo");
    }

    //criar o retangulo tracejado
    int rel = getFiguresRelation(*figura1, *figura2);

    switch(rel){
        case 0:{
            Rect * rect1 = figura1->figura;
            Rect * rect2 = figura2->figura;

            float x = getMin( rect1->x, rect2->x);
            float y = getMin(rect1->y, rect2->y);

            float a1 = rect1->x + rect1->w;
            float a2 = rect2->x + rect2->w;

            float b1 = rect1->y + rect1->h;
            float b2 = rect2->y + rect2->h;

            float w = getMax(a1 , a2) - getMin(rect1->x, rect2->x);
            float h = getMax( b1, b2) - getMin(rect1->y, rect2->y);

            Figure * newFig = (Figure *)malloc(sizeof(Figure));
            newFig->id = -1;
            newFig->type = 'r';

            char isOverlapped[50];

            //function validation
            if(isOverlapping(*figura1, *figura2) == 1){
                strcpy(isOverlapped, "sobrepoem");
                //create rect
                newFig->figura = (Rect *)newSetRect('r', -1, w, h, x, y, "black", "white", "fill-opacity=\"0.0\"");

            }else if(isOverlapping(*figura1, *figura2) == 0){
                strcpy(isOverlapped, "não sobrepoem");
                //make dashed rect
                newFig->figura = (Rect *)newSetRect('r', -1, w, h, x, y, "black", "white", "stroke-dasharray=\"5\" fill-opacity=\"0.0\"");
            }
            
            //print the result to the txt file
            fprintf(txt, "o? %d %d\n%d: %s, %d: %s. %s\n",  rect1->id, rect2->id, rect1->id, fig1_name, rect2->id, fig2_name, isOverlapped);      


            if(newFig != NULL){
                pushBack(figures, newFig);
            }

            return;
        }
        case 1:{
            Rect * rect = figura1->figura;
            Circle * circle = figura2->figura;

            float x = getMin(rect->x, circle->cx - circle->r);
            float y = getMin(rect->y, circle->cy - circle->r);

            float a1 = rect->x + rect->w;
            float a2 = circle->cx + circle->r;

            float b1 = rect->y + rect->h;
            float b2 = circle->cy + circle->r;

            float w = getMax(a1 , a2) - getMin(rect->x, circle->cx - circle->r);
            float h = getMax(b1, b2) - getMin(rect->y, circle->cy - circle->r);
            
            Figure * newFig = (Figure *)malloc(sizeof(Figure));
            newFig->id = -1;
            newFig->type = 'r';

            //string that says if both are overlapping each other
            char isOverlapped[50]; 

            //function validation
            if(isOverlapping(*figura1, *figura2) == 1){
                strcpy(isOverlapped, "sobrepoem");

                //create rect
                newFig->figura = (Rect *) newSetRect('r', -1, w, h, x, y, "black", "white", "fill-opacity=\"0.0\"");

            }else if(isOverlapping(*figura1, *figura2) == 0){
                strcpy(isOverlapped, "não sobrepoem");
                
                //make dashed rect
                newFig->figura = (Rect *) newSetRect('r', -1, w, h, x, y, "black", "white", "stroke-dasharray=\"5\" fill-opacity=\"0.0\"");
            }

            //write to the txt
            fprintf(txt, "o? %d %d\n%d: %s, %d: %s. %s\n",  rect->id, circle->id, rect->id, fig1_name, circle->id, fig2_name, isOverlapped);
            
            if(newFig != NULL){
                pushBack(figures, newFig);
            }
            return;
        }
        case 2:{ 
            Circle * circle1 = figura1->figura;
            Circle * circle2 = figura2->figura;

            float x = getMin(circle1->cx - circle1->r, circle2->cx - circle2->r);
            float y = getMin(circle1->cy - circle1->r, circle2->cy - circle2->r);

            float a1 = circle1->cx + circle1->r;
            float a2 = circle2->cx + circle2->r;

            float b1 = circle1->cy + circle1->r;
            float b2 = circle2->cy + circle2->r;

            float w = getMax(a1 , a2) - getMin(circle1->cx - circle1->r, circle2->cx - circle2->r);
            float h = getMax( b1, b2) - getMin(circle1->cy - circle1->r, circle2->cy - circle2->r);

            //NewFig to hold the rectangle
            Figure * newFig = (Figure *)malloc(sizeof(Figure));
            newFig->id = -1;
            newFig->type = 'r';

            //string that says if both are overlapping each other
            char isOverlapped[50];

            //function validation
            if(isOverlapping(*figura1, *figura2) == 1){
                //print the result to the txt file
                strcpy(isOverlapped, "sobrepoem");

                //create rect
                newFig->figura = (Rect *) newSetRect('r', -1, w, h, x, y, "black", "white", "fill-opacity=\"0.0\"");

            }else if(isOverlapping(*figura1, *figura2) == 0){
                //print the result to the txt file
                strcpy(isOverlapped, "não sobrepoem");
        
                //make dashed rect
                newFig->figura = (Rect *) newSetRect('r', -1, w, h, x, y, "black", "white", "stroke-dasharray=\"5\" fill-opacity=\"0.0\"");
            }
            
            //write to the txt
            fprintf(txt, "o? %d %d\n%d: %s, %d: %s. %s\n",  circle1->id, circle2->id, circle1->id, fig1_name, circle2->id, fig2_name, isOverlapped);

            if(newFig != NULL){
                pushBack(figures, newFig);
            }
            return;
        }
        case 3:{
            Circle * circle = figura1->figura;
            Rect * rect = figura2->figura;

            float x = getMin(circle->cx - circle->r, rect->x);
            float y = getMin(circle->cy - circle->r, rect->y);

            float a1 = circle->cx + circle->r;
            float a2 = rect->x + rect->w;

            float b1 = circle->cy + circle->r;
            float b2 = rect->y + rect->h;

            float w = getMax(a1 , a2) - getMin(circle->cx - circle->r, rect->x);
            float h = getMax( b1, b2) - getMin(circle->cy - circle->r, rect->y);

            //NewFig to hold the rectangle
            Figure * newFig = (Figure *)malloc(sizeof(Figure));
            newFig->id = -1;
            newFig->type = 'r';

            //string that says if both are overlapping each other
            char isOverlapped[50];

            //function validation
            if(isOverlapping(*figura1, *figura2) == 1){
                //print the result to the txt file
                strcpy(isOverlapped, "sobrepoem");

                //create rect
                newFig->figura = (Rect *) newSetRect('r', -1, w, h, x, y, "black", "white", "fill-opacity=\"0.0\"");

            }else if(isOverlapping(*figura1, *figura2) == 0){
                //print the result to the txt file
                strcpy(isOverlapped, "não sobrepoem");

                //make dashed rect
                newFig->figura = (Rect *) newSetRect('r', -1, w, h, x, y, "black", "white", "stroke-dasharray=\"5\" fill-opacity=\"0.0\"");
            }
            
            //write to the txt
            fprintf(txt, "o? %d %d\n%d: %s, %d: %s. %s\n",  circle->id, rect->id, circle->id, fig1_name, rect->id, fig2_name, isOverlapped);

            if(newFig != NULL){
                pushBack(figures, newFig);
            }
            return;
        }
        default:
            return;
    }
}

void insideParam(void * fig, float x, float y, List * figures, FILE * txt){

    Figure * figure = (Figure *)fig;
    
    Figure * newFigure = (Figure *)malloc(sizeof(Figure));
    newFigure->id = -1;
    newFigure->type = 'c';

    Figure * newLine = (Figure *)malloc(sizeof(Figure));
    newLine->id = -2;
    newLine->type = 'l';
    
    if(figure->type == 'r'){
        Rect * rect = figure->figura;

        char isIntern[50];

        if(isPointInternalToRect(rect->x, rect->y, rect->w, rect->h, x, y)){
            strcpy(isIntern, "Interno");
            //create the point and the line
            newFigure->figura = (Circle *) newSetPoint(-1, x, y, "blue", "blue", NULL);
            newLine->figura   = (Line *) newSetLine(-2, ((rect->w)/2 + rect->x), ((rect->h)/2 + rect->y), x, y, "blue", NULL);
        }else{
            strcpy(isIntern, "Nao interno");

            newFigure->figura= (Circle *) newSetPoint(-1, x, y, "magenta", "magenta", NULL);
            newLine->figura = (Line *) newSetLine(-2, ((rect->w/2) + rect->x), ((rect->h)/2 + rect->y), x, y, "magenta", NULL);
        }

        //write to txt
        fprintf(txt, "i? %d %f %f\n%c. %s\n", rect->id, x, y, rect->type, isIntern);

    }else if(figure->type == 'c'){
        Circle * circle = figure->figura;

        char isIntern[50];

        if(isPointInternalToCirc(circle->r, circle->cx, circle->cy, x, y)){
            strcpy(isIntern, "Interno");
            
            newFigure->figura = (Circle *) newSetPoint(-1, x, y, "blue", "blue", NULL);
            newLine->figura = (Line *) newSetLine(-1, circle->cx, circle->cy, x, y, "blue", NULL);

        }else{
            strcpy(isIntern, "Nao interno");
            
            newFigure->figura = (Circle *) newSetPoint(-1, x, y, "magenta", "magenta", NULL);
            newLine->figura = (Line *) newSetLine(-1, circle->cx, circle->cy, x, y, "magenta", NULL);
        }

        //write to txt
        fprintf(txt, "i? %d %f %f\n%c. %s\n", circle->id, x, y, circle->type, isIntern);
    }

    if(newFigure != NULL){
        pushBack(figures, newFigure);
    }

    if(newLine != NULL){
        pushBack(figures, newLine);
    }

}



//