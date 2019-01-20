#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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

void writerRadioB(RadioB* rb, int seek, void* arq){
    fseek(arq, seek, SEEK_SET);
    for(int i=0; i<55; i++)
        fwrite(&rb->id[i], sizeof(char), 1, arq);
    for(int i=0; i<55; i++)
        fwrite(&rb->cor1[i], sizeof(char), 1, arq);
    for(int i=0; i<55; i++)
        fwrite(&rb->cor2[i], sizeof(char), 1, arq);
    fwrite(&rb->x, sizeof(double), 1, arq);
    fwrite(&rb->y, sizeof(double), 1, arq);
}

void readerRadioB(RadioB* rb, int seek, void* arq){
    fseek(arq, seek, SEEK_SET);
    for(int i=0; i<55; i++)
        fread(&rb->id[i], sizeof(char), 1, arq);
    for(int i=0; i<55; i++)
        fread(&rb->cor1[i], sizeof(char), 1, arq);
    for(int i=0; i<55; i++)
        fread(&rb->cor2[i], sizeof(char), 1, arq);
    fread(&rb->x, sizeof(double), 1, arq);
    fread(&rb->y, sizeof(double), 1, arq);
}

int getSizeRadioB(){
    return (3*(55*sizeof(char)) + 2* sizeof(double));
}

void* allocarRadioB(){
    RadioB* rb;
    rb = (RadioB*) calloc(1, sizeof(RadioB));
    rb->id   = (char*) calloc(55, sizeof(char));
    rb->cor1 = (char*) calloc(55, sizeof(char));
    rb->cor2 = (char*) calloc(55, sizeof(char));
    return rb;
}

double compareRadioB(RadioB* objA, RadioB* objB){
    if(!strcmp(objA->id, objB->id)) return 0;
    double result = sqrt(pow(objB->x - objA->x, 2) + pow(objB->y - objA->y, 2));
    if(objB->x > objA->x && objB->y > objA->y){
        return result;
    }
    return -result;
}


/*cria um objeto 'retangulo' com as informações passadas*/
void* createRadioB(char* id, char* cor1, char* cor2,double x, double y){
    RadioB* rb;
    rb = (RadioB*) calloc(1, sizeof(RadioB));
    rb->id   = (char*) calloc(55, sizeof(char));
    rb->cor1 = (char*) calloc(55, sizeof(char));
    rb->cor2 = (char*) calloc(55, sizeof(char));

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