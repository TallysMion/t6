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
}Semaforo;


/*cria um objeto 'retangulo' com as informações passadas*/
void* createSemaforo(char* id, char* cor1, char* cor2,double x, double y){
    Semaforo* sm;
    sm = (Semaforo*) calloc(1, sizeof(Semaforo));

    sm->id   = (char*) calloc(155, sizeof(char));
    sm->cor1 = (char*) calloc(155, sizeof(char));
    sm->cor2 = (char*) calloc(155, sizeof(char));

    strcpy(sm->id  , id);
    strcpy(sm->cor1, cor1);
    strcpy(sm->cor2, cor2);

    sm->x = x;
    sm->y = y;

    return (void*) sm;
}

/*cria o codigo svg do retangulo em questao*/
char* createSemaforoSvg(void* semaf){
    Semaforo *sm;
    sm = (Semaforo*) semaf;
    circulo cr = createCirculo(0, sm->cor1, sm->cor2, SIZE, sm->x, sm->y);
    Notation nt = createNotacao("BLACK", 0, 0, sm->x+CENTER, sm->y+CENTER, "S");
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
char* getIdSemaf(void* semaf){
    Semaforo *sm;
    sm = (Semaforo*) semaf;
    return sm->id;
}

/*Retorna H*/
void* getCircSemaf(void* semaf){
    Semaforo *sm;
    sm = (Semaforo*) semaf;
    return (void*) createCirculo(0, sm->cor1, sm->cor2, SIZE, sm->x, sm->y);
}

void setColorFillSemaf(void* semaf, char* color){
    Semaforo *sm;
    sm = (Semaforo*) semaf;
    strcpy(sm->cor1, color);
}
void setColorStrokeSemaf(void* semaf, char* color){
    Semaforo *sm;
    sm = (Semaforo*) semaf;
    strcpy(sm->cor2, color);
}

/*Libera Memoria*/
void freeSemaf(void* semaf){
    if(semaf==NULL) return;
    Semaforo *sm;
    sm = (Semaforo*) semaf;
    free(sm->id);
    free(sm->cor1);
    free(sm->cor2);
    free(semaf);
}

char* reportSemaforo(void* semaf){
    Semaforo *sm;
    char* result;
    sm = (Semaforo*) semaf;
    result = (char*) calloc(155, sizeof(char));
    sprintf(result, "Semaforo - ID: %s - X: %lf, Y: %lf", sm->id, sm->x, sm->y);
    return result;
}

//Comparador de objeto
int compareSemaforo(void* hdA, void* hdB, int dim){
    Semaforo *qdA, *qdB;
    qdA = (Semaforo*) hdA;
    qdB = (Semaforo*) hdB;
    dim = dim%2;
    if(!strcmp(qdA->id, qdB->id)) return 0;
    if (dim == 0){
        return qdA->x - qdB->x;
    }else{
        return qdA->y - qdB->y;
    }
}

//Cria codigo Hash
int hashCodeSemaforo(void* hdA, int Modulo){
    Semaforo *qdA;
    qdA = (Semaforo*) hdA;
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

int HashCompareSemaf(void* semaf, void* id){
    Semaforo *sem, *idS;
    sem = (Semaforo*) semaf;
    idS = (Semaforo*) id;
    return strcmp(sem->id, idS->id);
}