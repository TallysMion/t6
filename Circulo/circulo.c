#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef void* circulo;

typedef struct cir{
    int id;
    char *cor1;
    char *cor2;
    double r;
    double x;
    double y;
}cir;

/*cria um objeto 'circulo' com as informações passadas*/
circulo createCirculo(int id, char* cor1, char* cor2, double r, double x, double y){
    cir *result = NULL;
    result = (cir*) calloc(1, sizeof(cir));        
    result->cor1 = (char*) calloc(strlen(cor1)+2, sizeof(char)); strcpy(result->cor1, cor1);
    result->cor2 = (char*) calloc(strlen(cor2)+2, sizeof(char)); strcpy(result->cor2, cor2);
    result->r = r;
    result->x = x;
    result->y = y;
    result->id = id;

    return (circulo) result;

}

/*cria o codigo svg do circulo em questao*/
char* createCirculoSvg(circulo circ){
    char *result;
    cir *value;
    value = (cir*) circ;   
    result = (char*) calloc(255, sizeof(char));

    sprintf(result,"<circle cx=\"%f\" cy=\"%f\" r=\"%f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"5\" style=\"opacity:0.7\"/>",
    value->x, value->y, value->r, value->cor2, value->cor1);

    return result;

}

/*retorna um vetor[2] com as cordenadas do centro de massa do circulo, sendo [0]=x e [1]=y */
double *conrdenadaCentroCirc(circulo circ){
    double *result;
    cir *value;
    value = (cir*) circ;

    result = (double*) calloc(2, sizeof(double));

    *(result)   = value->x;
    *(result+1) = value->y;

    return result;    
}

/*retorna 1,caso a cordenada x e y em questao 
for um ponto dentro do circulo, caso contrario, retorna 0/ */
int isInCirc(double x, double y, circulo circ){
    double a;
    double b;
    double c;

    cir *value;
    value = (cir*) circ;

    if(x == value->x && y == value->y){
        return 1;
    }

    a = (x-value->x);
    b = (y-value->y);

    c = sqrt(a*a + b*b);

    if(c<value->r){
        return 1;
    }
    return 0;

}

int isOnCirc(double x, double y, circulo circ){
    double a;
    double b;
    double c;
    
    cir *value;
    value = (cir*) circ;

    a = (x-value->x);
    b = (y-value->y);

    c = sqrt(a*a + b*b);

    if(c<=value->r){
        return 1;
    }


    return 0;

}


double getRCirc(circulo circ){
    cir *value;
    value = (cir*) circ;

    return value->r;
}
double getXCirc(circulo circ){
    cir *value;
    value = (cir*) circ;

    return value->x;
}
double getYCirc(circulo circ){
    cir *value;
    value = (cir*) circ;

    return value->y;
}

int getIdCirc(circulo circ){
    cir *value;
    value = (cir*) circ;

    return value->id;
}

char* getCorCirc(circulo circ){
    cir *value;
    value = (cir*) circ;

    return value->cor1;
}

void freeCirculo(circulo circ){
    char *result;
    cir *value;
    value = (cir*) circ;  
    free(value->cor1);
    free(value->cor2);
    free(value);
} 