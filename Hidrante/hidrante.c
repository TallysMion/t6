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
} Hidrante;


/*cria um objeto 'retangulo' com as informações passadas*/
void* createHidrante(char* id, char* cor1, char* cor2,double x, double y){
   Hidrante *hid;
   hid = (Hidrante*) calloc(1,sizeof(Hidrante));
   hid->id = (char*) calloc(155, sizeof(char));
   strcpy(hid->id, id);
   hid->cor1 = (char*) calloc(155, sizeof(char));
   strcpy(hid->cor1, cor1);
   hid->cor2 = (char*) calloc(155, sizeof(char));
   strcpy(hid->cor2, cor2);
   hid->x = x;
   hid->y = y;
   
    return (void*) hid;

}

/*cria o codigo svg do retangulo em questao*/
char* createHidranteSvg(void* hidr){
    Hidrante *hid;
    hid = (Hidrante*) hidr;
    circulo cr = createCirculo(0, hid->cor1, hid->cor2, SIZE, hid->x, hid->y);
    Notation nt = createNotacao("BLACK", 0, 0, hid->x+CENTER, hid->y+CENTER, "H");
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
char* getIdHidr(void* hidr){
    Hidrante *hid;
    hid = (Hidrante*) hidr;
    return hid->id;
}

/*Retorna H*/
void* getCircHidr(void* hidr){
    Hidrante *hid;
    hid = (Hidrante*) hidr;
    return createCirculo(0, hid->cor1, hid->cor2, SIZE, hid->x, hid->y);
}

void setColorFillHidr(void* semaf, char* color){
    Hidrante *sm;
    sm = (Hidrante*) semaf;
    strcpy(sm->cor1, color);
}

void setColorStrokeHidr(void* semaf, char* color){
    Hidrante *sm;
    sm = (Hidrante*) semaf;
    strcpy(sm->cor2, color);
}

/*Libera Memoria*/
void freeHidr(void* hidr){
    if(hidr == NULL) return;
    Hidrante *hid;
    hid = (Hidrante*) hidr;
    free(hid->id);
    free(hid->cor1);
    free(hid->cor2);
    free(hidr);
}

char* reportHidrante(void* hidr){
    Hidrante *hid;
    char* result;
    hid = (Hidrante*) hidr;
    result = (char*) calloc(155, sizeof(char));
    sprintf(result, "Hidrante - ID: %s - X: %lf, Y: %lf", hid->id, hid->x, hid->y);
    return result;
}

//Comparador de objeto
int compareHidrante(void* hdA, void* hdB, int dim){
    Hidrante *hidA;
    Hidrante *hidB;
    hidA = (Hidrante*) hdA;
    hidB = (Hidrante*) hdB;
    dim = dim%2;
    if(!strcmp(hidA->id, hidB->id)) return 0;
    if (dim == 0){
        return hidA->x - hidB->x;
    }else{
        return hidA->y - hidB->y;
    }
}

//Cria codigo Hash
int hashCodeHidrante(void* hdA, int Modulo){
    Hidrante *hidA;
    hidA = (Hidrante*) hdA;
    int x = strlen(hidA->id);
    int hash = 0;
    char *aux = hidA->id;
    while(*aux != 0){
        hash += x*(*aux);
        aux++;
        x--;
    }
    return Modulo < 0 ? hash : hash%Modulo;
}

int HashCompareHidrante(void* hid, void* id){
    Hidrante *hidr, *idH;
    hidr = (Hidrante*) hid;
    idH = (Hidrante*) id;
    return strcmp(hidr->id, idH->id);
}

