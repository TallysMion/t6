#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef void* Notation;

typedef struct Anotacao{
    char *cor1;
    double w;
    double h;
    double x;
    double y;
    char *text;
}Anotacao;

Notation createNotacao(char* cor1, double w, double h, double x, double y, char* text){
    Anotacao *result;
    result = (Anotacao *) calloc(1, sizeof(Anotacao));

    result->cor1 = (char *) calloc(strlen(cor1) + 1, sizeof(char)); 
    strcpy(result->cor1, cor1);
    result->w = w;
    result->h = h;
    result->x = x;
    result->y = y;
    result->text = (char *) calloc(strlen(text) + 1, sizeof(char)); 
    strcpy(result->text, text);
        
    return (Notation) result;
}

char* createNotacaoSvg(Notation anot){
    Anotacao *value;
    char *result;
    value = (Anotacao *) anot;
    result = (char*) calloc(555, sizeof(char));
    if(value->w < 0 && value->h < 0 && value->x < 0 && value->y <0){
        sprintf(result, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke-width=\"5\" stroke=\"%s\" stroke-dasharray=\"5,5\"/>",
        value->w*(-1), value->h*(-1), value->x*(-1), value->y*(-1), value->cor1);    
    }else{
        if(value->w == 0 && value->h == 0){
            sprintf(result, "<text x=\"%f\" y=\"%f\" style=\"font-family: Helvetica,Arial,sans-serif;font-weight:bolf;font-size:34; fill:'%s';\">%s</text>",
            value->x, value->y-5, value->cor1, value->text);
        }else{
            if(value->w == -1 && value->h == 1){
                sprintf(result, "<text x=\"%f\" y=\"%f\" style=\"font-family: Helvetica,Arial,sans-serif;font-weight:bolf;font-size:2px; fill:'%s';\">%s</text>",
                value->x, value->y-5, value->cor1, value->text);
            }else{
                if(value->h == 0){
                    sprintf(result, "<text x=\"%f\" y=\"%f\" style=\"font-family: Helvetica,Arial,sans-serif;font-weight:bolf;font-size:34; fill:'%s';\">%s</text>\n<circle cx=\"%f\" cy=\"%f\" r=\"%f\" fill=\"none\" stroke=\"%s\" stroke-dasharray=\"5,5\" stroke-width=\"5\"/>\n",
                    value->x, value->y-5, value->cor1, value->text, value->x, value->y, value->w, value->cor1);
                }else{
                    if(value->w == 0){
                        sprintf(result, "<text x=\"%f\" y=\"%f\" style=\"font-family: Helvetica,Arial,sans-serif;font-weight:bolf;font-size:34; fill:'%s';\">%s</text>\n<rect x=\"%f\" y=\"%f\" width=\"10\" height=\"20\" fill=\"BLACK\"/>\n<rect x=\"%f\" y=\"%f\" width=\"2\" height=\"12\" fill=\"WHITE\"/>\n<rect x=\"%f\" y=\"%f\" width=\"6\" height=\"2\" fill=\"WHITE\"/>\n",
                        value->x, value->y-5, value->cor1, value->text, value->x, value->y, value->x+4, value->y+4, value->x+2, value->y+8);
                    }else{
                        sprintf(result, "<text x=\"%f\" y=\"%f\" style=\"font-family: Helvetica,Arial,sans-serif;font-weight:bolf;font-size:34; fill:'%s';\">%s</text>\n<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"none\" stroke=\"%s\" stroke-dasharray=\"5,5\" stroke-width=\"5\"/>\n",
                        value->x, value->y-5, value->cor1, value->text, value->x, value->y, value->w, value->h, value->cor1);
                    }
                }
            }
        }
    }
    
    return result;

}

void freeAnotacao(Notation anot){
    Anotacao *value;
    char *result;
    value = (Anotacao *) anot;
    free(value->cor1);
    free(value->text);
    free(value);   
}

char* createLine(Notation anot){

    Anotacao *value;
    char *result;
    value = (Anotacao *) anot;
    result = (char*) calloc(555, sizeof(char));

    sprintf(result, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke-width=\"5\" stroke=\"%s\" stroke-dasharray=\"5,5\"/>\n", value->w, value->h, value->x, value->y, value->cor1);    
    return result;
}