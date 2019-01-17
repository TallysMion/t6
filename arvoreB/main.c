#include <stdio.h>
#include <stdlib.h>
#include "arvoreB.h"
#include <math.h>
#include "../Lista/lista.h"

typedef struct{
    double x;
    double y;
}table;

double compare(void* a, void *b){
    table *objA, *objB;
    objA = (table*) a;
    objB = (table*) b;
    double result = sqrt((pow(objB->x - objA->x, 2) + pow(objB->y - objA->y, 2)));
    if(objB->x > objA->x && objB->y > objA->y){
        return result;
    }
    return -result;
}


int main(){

    void* tree = BTREE_inicializa(100, "Teste.dat", sizeof(table), compare);

    table* obj0 = (table*) malloc(sizeof(table));
    table* obj1 = (table*) malloc(sizeof(table));
    table* obj2 = (table*) malloc(sizeof(table));
    table* obj3 = (table*) malloc(sizeof(table));
    table* obj4 = (table*) malloc(sizeof(table));
    table* obj5 = (table*) malloc(sizeof(table));
    table* obj6 = (table*) malloc(sizeof(table));
    table* obj7 = (table*) malloc(sizeof(table));
    table* obj8 = (table*) malloc(sizeof(table));
    table* obj9 = (table*) malloc(sizeof(table));
    table* objA = (table*) malloc(sizeof(table));
    table* objB = (table*) malloc(sizeof(table));
    table* objC = (table*) malloc(sizeof(table));
    table* objD = (table*) malloc(sizeof(table));
    table* objE = (table*) malloc(sizeof(table));
    table* objF = (table*) malloc(sizeof(table));
    table* clos = (table*) malloc(sizeof(table));
    table* refA = (table*) malloc(sizeof(table));
    table* refB = (table*) malloc(sizeof(table));
    table* res;

    obj0->x =  1; obj0->y =  1;//36.35
    obj1->x =  9; obj1->y =  2;//29,20
    obj2->x = 20; obj2->y =  3;//20,80
    obj3->x =  8; obj3->y =  4;//28,84
    obj4->x =  3; obj4->y =  5;//15,13
    obj5->x =  7; obj5->y =  6;//40,49
    obj6->x =  4; obj6->y =  7;//30,87
    obj7->x =  4; obj7->y =  8;//30,46
    obj8->x =  5; obj8->y =  9;//29,15
    obj9->x =  6; obj9->y = 10;//29,73
    objA->x = 11; objA->y = 11;//22,8
    objB->x = 25; objB->y = 12;//10,63
    objC->x = 14; objC->y = 13;//7,28
    objD->x = 28; objD->y = 14;//7,21
    objE->x = 12; objE->y = 15;//20,61
    objF->x = 15; objF->y = 16;//5
    clos->x = 12; clos->y = 10;
    refA->x =  3; refA->y =  5;
    refB->x =  9; refB->y = 10;

    BTREE_insere(tree, obj0->x, obj0);
    BTREE_insere(tree, obj1->x, obj1);
    BTREE_insere(tree, obj2->x, obj2);
    BTREE_insere(tree, obj3->x, obj3);
    BTREE_insere(tree, obj4->x, obj4);
    BTREE_insere(tree, obj5->x, obj5);
    BTREE_insere(tree, obj6->x, obj6);
    BTREE_insere(tree, obj7->x, obj7);
    BTREE_insere(tree, obj8->x, obj8);
    BTREE_insere(tree, obj9->x, obj9);
    BTREE_insere(tree, objA->x, objA);
    BTREE_insere(tree, objB->x, objB);
    BTREE_insere(tree, objC->x, objC);
    BTREE_insere(tree, objD->x, objD);
    BTREE_insere(tree, objE->x, objE);
    BTREE_insere(tree, objF->x, objF);
    
    printf("\n\nTeste de Busca\n");
    res = (table*) BTREE_busca(tree, obj1->x, obj1);    
    if(res!=NULL)printf("Função get\n%lf - %lf\n", res->x, res->y);

    res = (table*) BTREE_busca(tree, obj3->x, obj3);    
    if(res!=NULL)printf("Função get\n%lf - %lf\n", res->x, res->y);

    res = (table*) BTREE_busca(tree, obj5->x, obj5);    
    if(res!=NULL)printf("Função get\n%lf - %lf\n", res->x, res->y);

    int del;
    
    del = BTREE_deletar(tree, obj6->x, obj6);
    del?printf("\nDeletado com sucesso;\n"):printf("\nErro na Delecao;\n");

    res = (table*) BTREE_busca(tree, obj6->x, obj6);    
    res!=NULL?printf("Função get\n%lf - %lf\n", res->x, res->y):printf("\nObjeto não Encontrado");
        
    del = BTREE_deletar(tree, obj7->x, obj7);
    del?printf("\nDeletado com sucesso;\n"):printf("\nErro na Delecao;\n");

    res = (table*) BTREE_busca(tree, obj7->x, obj7);    
    res!=NULL?printf("Função get\n%lf - %lf\n", res->x, res->y):printf("\nObjeto não Encontrado");

    printf("\n\nGetALL\n");
    Lista ls = BTREE_getAll(tree);
    void* p = Lista_getFirst(ls);
    while(p){
        res = (table*) Lista_get(ls, p);
        res!=NULL?printf("Função get\n%lf - %lf\n", res->x, res->y):printf("\nObjeto não Encontrado");
        p = Lista_getNext(ls, p);
    }

    res = (table*) BTREE_closestNeibord(tree, clos->x, clos, 0);
    res!=NULL?printf("Função closestNeibord\n %lf - %lf -> %lf - %lf\n",clos->x, clos->y, res->x, res->y):printf("\nObjeto não Encontrado");

    printf("\n\nBusca Area\n");
    ls = BTREE_itensInsideArea(tree, refA->x, refA, refB->x, refB);
    p = Lista_getFirst(ls);
    while(p){
        res = (table*) Lista_get(ls, p);
        res!=NULL?printf("Item entre [%lf - %lf] e [%lf = %lf] -> [%lf - %lf]\n",refA->x, refA->y, refB->x, refB->y, res->x, res->y):printf("\nObjeto não Encontrado");
        p = Lista_getNext(ls, p);
    }
    printf("\n\n\n\n==============================================================");
    printf("\n                    ArvoreB antes do Free                     \n");
    printf("==============================================================\n\n\n\n");
    BTREE_PRINT(tree);
    BTREE_free(tree);

    tree = BTREE_Carrega("Teste.dat", compare);

    printf("\n\n\n\n==============================================================");
    printf("\n                    ArvoreB apos o Free                       \n");
    printf("==============================================================\n\n\n\n");
    BTREE_PRINT(tree);
    BTREE_free(tree);

}