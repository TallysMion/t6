#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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

void writerQuadra(Quadra* quad, int seek, void* arq){
    fseek(arq, seek, SEEK_SET);
    fwrite(&quad->x, sizeof(double), 1, arq);
    fwrite(&quad->y, sizeof(double), 1, arq);
    fwrite(&quad->w, sizeof(double), 1, arq);
    fwrite(&quad->h, sizeof(double), 1, arq);
    for(int i=0; i<55; i++)
        fwrite(&quad->cep[i], sizeof(char), 1, arq);
    for(int i=0; i<55; i++)
        fwrite(&quad->cor1[i], sizeof(char), 1, arq);
    for(int i=0; i<55; i++)
        fwrite(&quad->cor2[i], sizeof(char), 1, arq);
}
void readerQuadra(Quadra* quad, int seek, void* arq){
    fseek(arq, seek, SEEK_SET);
    fread(&quad->x, sizeof(double), 1, arq);
    fread(&quad->y, sizeof(double), 1, arq);
    fread(&quad->w, sizeof(double), 1, arq);
    fread(&quad->h, sizeof(double), 1, arq);
    for(int i=0; i<55; i++)
        fread(&quad->cep[i], sizeof(char), 1, arq);
    for(int i=0; i<55; i++)
        fread(&quad->cor1[i], sizeof(char), 1, arq);
    for(int i=0; i<55; i++)
        fread(&quad->cor2[i], sizeof(char), 1, arq);
}
int getSizeQuadra(){
    return (3*(55*sizeof(char)) + 4* sizeof(double));
}

void* allocarQuadra(){
    Quadra *qd;
    qd = (Quadra*) calloc(1, sizeof(Quadra));
    qd->cep = (char*) calloc(55, sizeof(char));
    qd->cor1 = (char*) calloc(55, sizeof(char));
    qd->cor2 = (char*) calloc(55, sizeof(char));
    return qd;
}

double compareQuadra(Quadra* objA, Quadra* objB){
    double result = sqrt(pow(objB->x - objA->x, 2) + pow(objB->y - objA->y, 2));
    if(objB->x > objA->x && objB->y > objA->y){
        return result;
    }
    return -result;
}

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
    qd->cep = (char*) calloc(55, sizeof(char));
    strcpy(qd->cep, cep);
    qd->cor1 = (char*) calloc(55, sizeof(char));
    strcpy(qd->cor1, cor1);
    qd->cor2 = (char*) calloc(55, sizeof(char));
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