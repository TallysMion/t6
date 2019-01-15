#include <stdio.h>
#include <stdlib.h>
#include "arvoreB.h"
#include <math.h>

typedef struct{
    double x;
    double y;
}table;

double compare(void* a, void *b){
    table *objA, *objB;
    objA = (table*) a;
    objB = (table*) b;

    return sqrt((pow(objB->x - objA->x, 2) + pow(objB->y - objA->y, 2)));
}


int main(){

    void* tree = BTREE_inicializa(2048, "Teste.dat", sizeof(table), compare);

    table* obj = (table*) malloc(sizeof(table));
    obj->x = 10; obj->y = 20;
    BTREE_insere(tree, obj->x, obj);

    table *res = (table*) BTREE_busca(tree, obj->x, obj);    
    printf("Função get\n%lf - %lf\n", res->x, res->y);

    BTREE_free(tree);
}