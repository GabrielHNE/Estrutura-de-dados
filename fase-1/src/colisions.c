#include "colisions.h"

int isPointInternalToRect(float x, float y, float w, float h, float px, float py){
    return (x <= px 
        && (x + w) >= px 
        && y <= py 
        && (y + h) >= py );
}

int isPointInternalToCirc(float r, float x, float y, float px, float py){
    float d = (px - x)*(px - x) + (py - y)*(py - y);

    return( (r*r) >= d);
}

int rectOverlap(void * rect1, void * rect2){
    Rect auxRect1 = *((Rect *)rect1);
    Rect auxRect2 = *((Rect *)rect2);

    return !( (auxRect1.x + auxRect1.w) <= auxRect2.x || auxRect1.x >= (auxRect2.x + auxRect2.w)   //left e bottom
        || (auxRect1.y + auxRect1.h) <= auxRect2.y || auxRect1.y >= (auxRect2.y + auxRect2.h));  //bottom e top
}

int circleOverlap(void * circ1, void * circ2){
    Circle auxCirc1 = *((Circle *)circ1);
    Circle auxCirc2 = *((Circle *)circ2);

    float dist = pow(pow(auxCirc2.cx - auxCirc1.cx , 2) + pow(auxCirc2.cy - auxCirc1.cy, 2), 0.5);
    
    return (dist < (auxCirc1.r + auxCirc2.r));
}

int circRectOverlap(void * circ, void * rect){
    Circle auxCirc = *((Circle *)circ);
    Rect auxRect = *((Rect *)rect);

    float k = auxRect.x + auxRect.w;
    float j = auxRect.y + auxRect.h;

    float a = getMin( k , auxCirc.cx);
    float b = getMin( j , auxCirc.cy);

    float x = getMax(auxRect.x, a); 
    float y = getMax(auxRect.y, b);
    
    float dist = pow( (pow( (x - auxCirc.cx) , 2) + pow( (y - auxCirc.cy) ,2)) , 0.5);
    
    //return 1 if dist smaller than circ.r or 0 if dist higher than circ.r
    return (dist < auxCirc.r);
}

float getMin(float a, float b){
    return (a>=b? b : a);
}

float getMax(float a, float b){
    return (a>=b? a : b);
}
