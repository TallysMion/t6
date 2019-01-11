#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Retangulo/retangulo.h"
#include "../Anotacao/anotacao.h"


typedef struct{
    char *placa;
    double x;
    double y;
    double w;
    double h;
}carro;

/*cria um objeto 'retangulo' com as informações passadas*/
void* createCarro(char* placa, double x, double y, double w, double h){
    carro *result;
    result = (carro*) calloc(1, sizeof(carro));

    result->placa = (char*) calloc(strlen(placa)+2, sizeof(char));
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

//Comparador de objeto
int compareCarro(void* carA, void* carB, int dim){
    carro *cA;
    carro *cB;
    cA = (carro*) carA;
    cB = (carro*) carB;
    dim = dim%2;
    if(!strcmp(cA->placa, cB->placa)) return 0;
    if (dim == 0){
        return cA->x - cB->x;
    }else{
        return cA->y - cB->y;
    }
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
