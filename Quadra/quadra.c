#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Retangulo/retangulo.h"
#include "../Anotacao/anotacao.h"

#define CENTER -3

typedef struct{
    char* cep;
    char* cor1;
    char* cor2;
    double x;
    double y;
    double w;
    double h;
} Quadra;

/*Retorna H*/
void* getRecQuad(void* quad){
    Quadra *qd;
    qd = (Quadra*) quad;
    return createRetangulo(0, qd->cor1, qd->cor2, qd->w, qd->h, qd->x, qd->y);
}

/*cria um objeto 'retangulo' com as informações passadas*/
void* createQuadra(char* cep, char* cor1, char* cor2,double w, double h, double x, double y){
    Quadra *qd;
    qd = (Quadra*) calloc(1, sizeof(Quadra));
    qd->cep = (char*) calloc(155, sizeof(char));
    strcpy(qd->cep, cep);
    qd->cor1 = (char*) calloc(155, sizeof(char));
    strcpy(qd->cor1, cor1);
    qd->cor2 = (char*) calloc(155, sizeof(char));
    strcpy(qd->cor2, cor2);
    qd->h = h;
    qd->w = w;
    qd->x = x;
    qd->y = y;

    return (void*) qd;

}

/*cria o codigo svg do retangulo em questao*/
char* createQuadraSvg(void* quad){
    Quadra *qd;
    qd = (Quadra*) quad;
    retangulo rt = getRecQuad(quad);
    Notation nt = createNotacao("BLACK", 0, 0, qd->x-CENTER, qd->y+CENTER+ qd->h , qd->cep);
    char *resA = createRetanguloSvg(rt);
    char *resB = createNotacaoSvg(nt);

    char *result;
    result = (char*) calloc(strlen(resA) + strlen(resB) + 5, sizeof(char));
    strcpy(result, resA);
    strcat(result, resB);

    freeRec(rt);
    freeAnotacao(nt);
    free(resA);
    free(resB);

    return result;
}

/*Retorna Cep*/
char* getCepQuad(void* quad){
    Quadra *qd;
    qd = (Quadra*) quad;
    return qd->cep;
}



void setColorFillQuad(void* semaf, char* color){
    Quadra *sm;
    sm = (Quadra*) semaf;
    strcpy(sm->cor1, color);
}
void setColorStrokeQuad(void* semaf, char* color){
    Quadra *sm;
    sm = (Quadra*) semaf;
    strcpy(sm->cor2, color);
}

/*Libera Memoria*/
void freeQuad(void* quad){
    Quadra *qd;
    qd = (Quadra*) quad;
    free(qd->cep);
    free(qd->cor1);
    free(qd->cor2);
    free(quad);
}

char* reportQuadra(void* quad){
    Quadra *qd;
    char* result;
    qd = (Quadra*) quad;
    result = (char*) calloc(155, sizeof(char));
    sprintf(result, "Quadra - ID: %s - X: %lf, Y: %lf", qd->cep, qd->x, qd->y);
    return result;
}

//Comparador de objeto
int compareQuadra(void* hdA, void* hdB, int dim){
    Quadra *qdA, *qdB;
    qdA = (Quadra*) hdA;
    qdB = (Quadra*) hdB;
    dim = dim%2;
    if(!strcmp(qdA->cep, qdB->cep)) return 0;
    if (dim == 0){
        return qdA->x - qdB->x;
    }else{
        return qdA->y - qdB->y;
    }
}

//Cria codigo Hash
int hashCodeQuadra(void* hdA, int Modulo){
    Quadra *qdA;
    qdA = (Quadra*) hdA;
    int x = strlen(qdA->cep);
    int hash = 0;
    char *aux = qdA->cep;
    while(*aux != 0){
        hash += x*(*aux);
        aux++;
        x--;
    }
    return Modulo < 0 ? hash : hash%Modulo;
}

int HashCompareQuadra(void* quad, void* cep){
    Quadra *qd, *id;
    qd = (Quadra*) quad;
    id = (Quadra*) cep;
    return strcmp(qd->cep,id->cep);
}