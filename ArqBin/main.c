//função p/ testes

#include <stdio.h>
#include <stdlib.h>
#include "ArqBin.h"

#include "Lista/lista.h"

typedef struct table{
    int i;
    double j;
}table;

int main(){

    table *ob; ob = (table*) malloc(sizeof(table));
    int get, tam;
    void *aux, *auxi, *posic;
    table* lista;

    newArq("teste.dat", sizeof(table));

    ob->i = 3;
    ob->j = 4.5;

    get = addObject(ob, "teste.dat");
    printf("indice = %d\n", get);
    get = addObject(ob, "teste.dat");
    printf("indice = %d\n", get);
    get = addObject(ob, "teste.dat");
    printf("indice = %d\n", get);

    aux = getObject("teste.dat", 0);
    ob = (table *) aux;
    printf("%d %lf\n", ob->i, ob->j);

    aux = getObject("teste.dat", 1);
    ob = (table *) aux;
    printf("%d %lf\n", ob->i, ob->j);

    aux = getObject("teste.dat", 2);
    ob = (table *) aux;
    printf("%d %lf\n", ob->i, ob->j);

    printf("\ngetAll\n");
    aux = getAll("teste.dat");
    
    void* p = Lista_getFirst(aux);
    while(p){
        table* tb = (table*) Lista_get(aux, p);
        printf("%d %lf\n", tb->i, tb->j);
        p = Lista_getNext(aux, p);
    }
    
    deleteObject("teste.dat", 0);

    printf("\ngetAll\n");
    aux = getAll("teste.dat");
    
    p = Lista_getFirst(aux);
    while(p){
        table* tb = (table*) Lista_get(aux, p);
        printf("%d %lf\n", tb->i, tb->j);
        p = Lista_getNext(aux, p);
    }
    //aux = getObject("teste.dat", 0);


    printf("\nget deletado\n");
    aux = getObject("teste.dat", 0);
    if(aux != NULL){
        ob = (table *) aux;
        printf("%d %lf\n", ob->i, ob->j);
    }
return 0;
}