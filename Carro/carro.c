#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Retangulo/retangulo.h"
#include "../Anotacao/anotacao.h"
#include <math.h>


typedef struct{
    char *placa;
    double x;
    double y;
    double w;
    double h;
}carro;

void writerCarro(carro* car, int seek, FILE* arq){
    fseek(arq, seek, SEEK_SET);
    for(int i=0; i<55; i++)
        fwrite(&car->placa[i], sizeof(char), 1, arq);
    fwrite(&car->x, sizeof(double), 1, arq);
    fwrite(&car->y, sizeof(double), 1, arq);
    fwrite(&car->w, sizeof(double), 1, arq);
    fwrite(&car->h, sizeof(double), 1, arq);
}

void readerCarro(carro* car, int seek, void* arq){
    fseek(arq, seek, SEEK_SET);
    for(int i=0; i<55; i++)
        fread(&car->placa[i], sizeof(char), 1, arq);
    fread(&car->x, sizeof(double), 1, arq);
    fread(&car->y, sizeof(double), 1, arq);
    fread(&car->w, sizeof(double), 1, arq);
    fread(&car->h, sizeof(double), 1, arq);
}

int getSizeCarro(){
    return(4*sizeof(double) + 55*sizeof(char));
}
double compareCarro(carro* objA, carro* objB){
    double result = sqrt(pow(objB->x - objA->x, 2) + pow(objB->y - objA->y, 2));
    if(objB->x > objA->x && objB->y > objA->y){
        return result;
    }
    return -result;
}

/*cria um objeto 'retangulo' com as informações passadas*/
void* createCarro(char* placa, double x, double y, double w, double h){
    carro *result;
    result = (carro*) calloc(1, sizeof(carro));

    result->placa = (char*) calloc(55, sizeof(char));
    strcpy(result->placa, placa);
    result->x = x;
    result->y = y;
    result->w = w;
    result->h = h;

    return (void*) result;

}

/*cria o codigo svg do retangulo em questao*/
char* createCarroSVG(void* car){
    carro* c;
    c = (carro*) car;
    retangulo rt = createRetangulo(0, "BLUE", "YELLOW", c->w, c->h, c->x, c->y);
    Notation nt = createNotacao("Black", -1, 1, (c->x+5), (c->y + c->h/2 + 5), c->placa);
    char *rec, *not, *result;
    rec = createRetanguloSvg(rt);
    not = createNotacaoSvg(nt);

    int len = strlen(rec) + strlen(not) + 10;
    result = (char*) calloc(len, sizeof(char));
    strcpy(result, rec);
    strcat(result, not);
    freeRec(rt);
    freeAnotacao(nt);
    free(rec);
    free(not);
    return(result);
}

/*Retorna placa*/
char* getPlacaCarro(void* car){
    carro* c;
    c = (carro*) car;
    return c->placa;
}

/*Retorna Rec*/
void* getRecCarro(void* car){
    carro* c;
    c = (carro*) car;
    return createRetangulo(0, "BLUE", "YELLOW", c->w, c->h, c->x, c->y);
}

/*Libera Memoria*/
void freeCarro(void* car){
    carro* c;
    c = (carro*) car;
    free(c->placa);
    free(car);
}

char* reportCarro(void* car){
    carro* c;
    c = (carro*) car;
    char* result;
    result = (char*) calloc(55,sizeof(char));
    sprintf(result, "Carro -> placa: %s", c->placa);
    return result;
}


//Cria codigo Hash
int hashCodeCarro(void* car, int Modulo){
    carro *c;
    c = (carro*) car;
    int x = strlen(c->placa);
    int hash = 0;
    char *aux = c->placa;
    while(*aux != 0){
        hash += x*(*aux);
        aux++;
        x--;
    }
    return Modulo < 0 ? hash : hash%Modulo;
}

//Comparador para hash
int HashCompareCarro(void* carA, void* carB){
    carro *cA, *cB;
    cA = (carro*) carA;
    cB = (carro*) carB;
    return strcmp(cA->placa, cB->placa);
}
