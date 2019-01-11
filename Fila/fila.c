#include <stdio.h>
#include <stdlib.h>

/*tipo da fila*/
typedef void* Fila;

/*tipo do valor*/
typedef void* Value;

struct item{void *value; struct item* next;};

struct fila{struct item *begin; struct item *end; int size;};

/*cria uma fila vazia*/
Fila create_Fila(){
    struct fila *result;
    result = (struct fila*) calloc(1, sizeof(struct fila));
    result->begin = NULL;
    result->end = NULL;
    result->size = 0;
    return result;
}

/*retorna 1 se a fila esta vazia, 0 caso contrario*/
int empty_Fila(Fila fila){
    struct fila *filaAux;
    filaAux = (struct fila*) fila;
    if(filaAux == NULL || filaAux->begin == NULL){
        return 1;
    }
    return 0;
}

/*adiciona um item na fila*/
void insert_Fila(Fila fila, Value item){
    struct fila *filaAux;
    struct item *value;

    filaAux = (struct fila*) fila;    
    value = (struct item*) calloc(1, sizeof(struct item));
    value->value = item;
    value->next = NULL;

    if(filaAux->begin == NULL){
        filaAux->begin = value;
        filaAux->end = value;
        return;
    }
    
    filaAux->end->next = value;
    filaAux->end = value;
    filaAux->size += 1;
}

/*busca o proximo item da fila, removendo o mesmo da fila,
 é nescessário que a fila nao seja vazia*/
Value remove_Fila(Fila fila){
    struct fila *filaAux;
    struct item *aux;
    void * temp;
    Value temp2;
    if(empty_Fila(fila)){
        return NULL;
    }
    filaAux = (struct fila*) fila;
    aux = filaAux->begin;
    temp = filaAux->begin->next;
    filaAux->begin = temp;
    temp2 = aux->value;
    filaAux->size -= 1;
    return temp2;
}

/*libera a memoria da fila*/
void freeFila(Fila fila){
    while(!empty_Fila(fila)){
        remove_Fila(fila);
    }
    free(fila);
}

/*Retorna o tamanho da fila*/
int lenghFila(Fila fila){
    struct fila *filaAux;
    filaAux = (struct fila*) fila;
    return filaAux->size;
}