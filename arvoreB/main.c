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

    void* tree = BTREE_inicializa(100, "Teste.dat", sizeof(table), compare);

    table* obj1 = (table*) malloc(sizeof(table));
    table* obj2 = (table*) malloc(sizeof(table));
    table* obj3 = (table*) malloc(sizeof(table));
    table* obj4 = (table*) malloc(sizeof(table));
    table* obj5 = (table*) malloc(sizeof(table));
    table* obj6 = (table*) malloc(sizeof(table));
    table* obj7 = (table*) malloc(sizeof(table));
    table* res;

    obj7->x = 8 ; obj7->y = 00;
    obj6->x = 05; obj1->y = 30;
    obj5->x = 10; obj2->y = 25;
    obj4->x = 15; obj3->y = 20;
    obj3->x = 20; obj4->y = 15;
    obj2->x = 25; obj5->y = 10;
    obj1->x = 30; obj6->y = 05;

    BTREE_insere(tree, obj1->x, obj1);
    BTREE_insere(tree, obj2->x, obj2);
    BTREE_insere(tree, obj3->x, obj3);
    BTREE_insere(tree, obj4->x, obj4);
    BTREE_insere(tree, obj5->x, obj5);
    BTREE_insere(tree, obj6->x, obj6);
    BTREE_insere(tree, obj7->x, obj7);
    BTREE_PRINT(tree); printf("\n\n========================================\n");

    printf("\n\nTeste de Busca\n");
    res = (table*) BTREE_busca(tree, obj1->x, obj1);    
    if(res!=NULL)printf("Função get\n%lf - %lf\n", res->x, res->y);

    // res = (table*) BTREE_busca(tree, obj3->x, obj3);    
    // if(res!=NULL)printf("Função get\n%lf - %lf\n", res->x, res->y);

    // res = (table*) BTREE_busca(tree, obj5->x, obj5);    
    // if(res!=NULL)printf("Função get\n%lf - %lf\n", res->x, res->y);

    BTREE_free(tree);
}