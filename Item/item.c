#include <stdio.h>
#include <stdlib.h>
#include "../Retangulo/retangulo.h"
#include "../Circulo/circulo.h"
#include <math.h>

#define RETANGULO 0
#define CIRCULO 1

/*Define o tipo do item*/
typedef struct{
    void* value;
    int type;
}Item;

/*cria um item com essas informações*/
void* createItem(void* value,int type){
    Item *it;
    it = (Item*) calloc(1, sizeof(Item));
    it->value = value;
    it->type = type;
    return (void*) it;
}

/*cria o codigo svg do Item em questao*/
char* createSvg(void* it){
    Item *item;
    item = (Item*) it;

    switch(item->type){
        case RETANGULO:
            return createRetanguloSvg(item->value);
        case CIRCULO:
            return createCirculoSvg(item->value);
     }
}

int getType(void* it){
    Item *item;
    item = (Item*) it;
    return item->type;
}

void* getValueItem(void* it){
    Item *item;
    item = (Item*) it;
    return item->value;
}

int getIdDraw(void* it){
        Item *item;
    item = (Item*) it;

    switch(item->type){
        case RETANGULO:
            return getIdRec(item->value);
        case CIRCULO:
            return getIdCirc(item->value);
    }
}

/*Libera Memoria*/
void freeItem(void* it){
    Item *item;
    item = (Item*) it;

    switch(item->type){
        case RETANGULO:
            freeRec(item->value);
            break;
        case CIRCULO:
            freeCirculo(item->value);
            break;
    }

    free(it);

}

int Item_overlap(void* i,void* j){
    Item *itA, *itB;
    itA = (Item*) i;   
    itB = (Item*) j;

    if(itA->type == CIRCULO && itB->type == CIRCULO){
        double *centro1, *centro2;
        double value1, value2, value3, value4;
        centro1 = conrdenadaCentroCirc(itA->value);
        centro2 = conrdenadaCentroCirc(itB->value);
        value1 = *(centro2) - *(centro1);
        value2 = *(centro2+1) - *(centro1+1);
        value3 = sqrt(value1*value1 + value2*value2);
        value4 = getRCirc(itA->value) + getRCirc(itB->value);
        return value3<=value4?1:0;
    }

    if(itA->type == RETANGULO && itB->type == RETANGULO){
        if(getXRec(itA->value) + getWRec(itA->value) < getXRec(itB->value)){
            return 0;
        }
        if(getXRec(itA->value) > getXRec(itB->value)+getWRec(itB->value)){
            return 0;
        }
        if(getYRec(itA->value) + getHRec(itA->value) < getYRec(itB->value)){
            return 0;
        }
        if(getYRec(itA->value) > getYRec(itB->value)+getHRec(itB->value)){
            return 0;
        }
        return 1;        
    }
    if(itA->type == CIRCULO && itB->type == RETANGULO){
        if(getXCirc(itA->value) < getXRec(itB->value) - getRCirc(itA->value)){
            return 0;
        }
        if(getXCirc(itA->value) > getXRec(itB->value) + getWRec(itB->value) + getRCirc(itA->value)){
            return 0;
        }
        if(getYCirc(itA->value) < getYRec(itB->value) - getRCirc(itA->value)){
            return 0;
        }
        if(getYCirc(itA->value) > getYRec(itB->value) + getHRec(itB->value) + getRCirc(itA->value)){
            return 0;
        }
        return 1;
    }
    if(itA->type == RETANGULO && itB->type == CIRCULO){
        if(getXCirc(itB->value) < getXRec(itA->value) - getRCirc(itB->value)){
            return 0;
        }
        if(getXCirc(itB->value) > getXRec(itA->value) + getWRec(itA->value) + getRCirc(itB->value)){
            return 0;
        }
        if(getYCirc(itB->value) < getYRec(itA->value) - getRCirc(itB->value)){
            return 0;
        }
        if(getYCirc(itB->value) > getYRec(itA->value) + getHRec(itA->value) + getRCirc(itB->value)){
            return 0;
        }
        return 1;
    }
    return 0;
}

/*retorna o xi do item*/
double Item_Xi(void* i){
    Item *it;  it = (Item*) i;
    return it->type==RETANGULO ? getXRec(it->value) : getXCirc(it->value) - getRCirc(it->value); 
}

/*retorna o yi do item*/
double Item_Yi(void* i){
    Item *it;  it = (Item*) i;
    return it->type==RETANGULO ? getYRec(it->value) : getYCirc(it->value) - getRCirc(it->value); 
}

/*retorna o xf do item*/
double Item_Xf(void* i){
    Item *it;  it = (Item*) i;
    return it->type==RETANGULO ? getXRec(it->value) + getWRec(it->value) : getXCirc(it->value) + getRCirc(it->value); 
}

/*retorna o yf do item*/
double Item_Yf(void* i){
    Item *it;  it = (Item*) i;
    return it->type==RETANGULO ? getYRec(it->value) + getHRec(it->value) : getYCirc(it->value) + getRCirc(it->value); 
}