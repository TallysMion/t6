#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef void* retangulo;

typedef struct rec{
    int id;
    char *cor1;
    char *cor2;
    double w;
    double h;
    double x;
    double y;
}rec;

/*cria um objeto 'retangulo' com as informações passadas*/
retangulo createRetangulo(int id, char* cor1, char* cor2, double w, double h, double x, double y){
    rec *result = NULL;
    result = (rec*) calloc(1, sizeof(rec));        
    result->cor1 = (char*) calloc(strlen(cor1)+2, sizeof(char)); strcpy(result->cor1, cor1);
    result->cor2 = (char*) calloc(strlen(cor2)+2, sizeof(char)); strcpy(result->cor2, cor2);
    result->w = w;
    result->h = h;
    result->x = x;
    result->y = y;
    result->id = id;

    return (retangulo) result;

}

/*cria o codigo svg do retangulo em questao*/
char* createRetanguloSvg(retangulo rect){
    char *result;
    rec *value;
    value = (rec*) rect;   
    result = (char*) calloc(255, sizeof(char));

    sprintf(result,"<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"5\" style=\"opacity:0.7\"/>",
    value->x, value->y, value->w, value->h, value->cor2, value->cor1);

    return result;

}

/*retorna um vetor[2] com as cordenadas do centro de massa do retangulo, sendo [0]=x e [1]=y*/
double *conrdenadaCentroRec(retangulo rect){
    double *result;
    rec *value;
    value = (rec*) rect;

    
    result = (double*) calloc(2, sizeof(double));

    *(result)   = value->x + (value->w / 2);
    *(result+1) = value->y + (value->h / 2);

    return result;    
}

/*retorna 1,caso a cordenada x e y em questao 
for um ponto dentro do retangulo, caso contrario, retorna 0*/
int isInRec(double x, double y, retangulo rect){
    rec *value;
    value = (rec*) rect;

    if(x > value->x && x < (value->x + value->w)){
        if(y > value->y && y < (value->y + value->h)){
            return 1;
        }   
    }

    return 0;

}

int isOnRec(double x, double y, retangulo rect){
    rec *value;
    value = (rec*) rect;

    if(x >= value->x && x <= (value->x + value->w)){
        if(y >= value->y && y <= (value->y + value->h)){
            return 1;
        }   
    }

    return 0;

}

char* getCorRec(retangulo rect){
    rec *value;
    value = (rec*) rect; 

    return value->cor1;
}

double getWRec(retangulo rect){
    rec *value;
    value = (rec*) rect; 

    return value->w;
}

double getHRec(retangulo rect){
    rec *value;
    value = (rec*) rect; 

    return value->h;
}

double getXRec(retangulo rect){
    rec *value;
    value = (rec*) rect; 

    return value->x;
}

double getYRec(retangulo rect){
    rec *value;
    value = (rec*) rect; 

    return value->y;
}

int getIdRec(retangulo rect){
    rec *value;
    value = (rec*) rect; 

    return value->id;
}

double freeRec(retangulo rect){
    rec *value;
    value = (rec*) rect; 

    free(value->cor1);
    free(value->cor2);
    free(rect);
}