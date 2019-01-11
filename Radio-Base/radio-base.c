#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Circulo/circulo.h"
#include "../Anotacao/anotacao.h"


#define SIZE 10
#define CENTER 1


typedef struct{
    char* id;
    char* cor1;
    char* cor2;
    double x;
    double y;
}RadioB;
typedef void* cicle;

/*cria um objeto 'retangulo' com as informações passadas*/
void* createRadioB(char* id, char* cor1, char* cor2,double x, double y){
    RadioB* rb;
    rb = (RadioB*) calloc(1, sizeof(RadioB));
    rb->id   = (char*) calloc(155, sizeof(char));
    rb->cor1 = (char*) calloc(155, sizeof(char));
    rb->cor2 = (char*) calloc(155, sizeof(char));

    strcpy(rb->id  , id);
    strcpy(rb->cor1, cor1);
    strcpy(rb->cor2, cor2);

    rb->x = x;
    rb->y = y;

    return (void*) rb;
}

/*cria o codigo svg do retangulo em questao*/
char* createRadioBSvg(void* raB){
    RadioB *rb;
    rb = (RadioB*) raB;
    circulo cr = createCirculo(0, rb->cor1, rb->cor2, SIZE, rb->x, rb->y);
    Notation nt = createNotacao("BLACK", 0, 0, rb->x+CENTER, rb->y+CENTER, "R");
    char *resA = createCirculoSvg(cr);
    char *resB = createNotacaoSvg(nt);

    char *result;
    result = (char*) calloc(strlen(resA) + strlen(resB) + 5, sizeof(char));
    strcpy(result, resA);
    strcat(result, resB);

    freeCirculo(cr);
    freeAnotacao(nt);
    free(resA);
    free(resB);

    return result;

}

/*Retorna W*/
char* getIdRadioB(void* raB){
    RadioB *rb;
    rb = (RadioB*) raB;
    return rb->id;
}

/*Retorna H*/
cicle getCircRadioB(void* raB){
    RadioB *rb;
    rb = (RadioB*) raB;
    return (void*) createCirculo(0, rb->cor1, rb->cor2, SIZE, rb->x, rb->y);
}

void setColorFillRB(void* semaf, char* color){
    RadioB *sm;
    sm = (RadioB*) semaf;
    strcpy(sm->cor1, color);
}
void setColorStrokeRB(void* semaf, char* color){
    RadioB *sm;
    sm = (RadioB*) semaf;
    strcpy(sm->cor2, color);
}


/*Libera Memoria*/
void freeRadioB(void* raB){
    RadioB *rb;
    rb = (RadioB*) raB;
    free(rb->id);
    free(rb->cor1);
    free(rb->cor2);
    free(raB);
}

char* reportRadioB(void* raB){
    RadioB *rb;
    char* result;
    rb = (RadioB*) raB;
    result = (char*) calloc(155, sizeof(char));
    sprintf(result, "Radio-Base - ID: %s - X: %lf, Y: %lf", rb->id, rb->x, rb->y);
    return result;
}

//Comparador de objeto
int compareRadioB(void* hdA, void* hdB, int dim){
    RadioB *qdA, *qdB;
    qdA = (RadioB*) hdA;
    qdB = (RadioB*) hdB;
    dim = dim%2;
    if(!strcmp(qdA->id, qdB->id)) return 0;
    if (dim == 0){
        return qdA->x - qdB->x;
    }else{
        return qdA->y - qdB->y;
    }
}

//Cria codigo Hash
int hashCodeRadioB(void* hdA, int Modulo){
    RadioB *qdA;
    qdA = (RadioB*) hdA;
    int x = strlen(qdA->id);
    int hash = 0;
    char *aux = qdA->id;
    while(*aux != 0){
        hash += x*(*aux);
        aux++;
        x--;
    }
    return Modulo < 0 ? hash : hash%Modulo;
}

int HashCompareRadioB(void* rb, void* id){
    RadioB *radioB, *idR;
    radioB = (RadioB*) rb;
    idR = (RadioB*) id;
    return strcmp(radioB->id, idR->id);
}