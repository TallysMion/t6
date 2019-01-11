#ifndef Fila_H
#define Fila_H

/*tipo da fila*/
typedef void* Fila;

/*tipo do item*/
typedef void* Value;

/*cria uma fila vazia*/
Fila create_Fila();

/*retorna 1 se a fila esta vazia, 0 caso contrario*/
int empty_Fila(Fila fila);

/*adiciona um item na fila*/
void insert_Fila(Fila fila, Value item);

/*busca o proximo item da fila, removendo o mesmo da fila,*/
/* é nescessário que a fila possua pelo menos 1 item*/
Value remove_Fila(Fila fila);

void freeFila(Fila fila);

int lenghFila(Fila fila);

#endif