#ifndef LISTA_H
#define LISTA_H

typedef void* Lista;
typedef void* Posic;

//cria Lista
Lista Lista_createLista();

//retorna o comprimento da lista
int Lista_lenght(Lista lista);

//insere um item na lista
Posic Lista_insert(Lista lista, void* item);

//remove um item da lista
void Lista_remove(Lista lista, Posic p);

//busca o valor da lista, na posição p
void* Lista_get(Lista lista, Posic p);

//insere um item apos o item informado
Posic Lista_insertBefore(Lista lista, Posic p, void* item);

//insere um item antes do item informado
Posic Lista_insertAfter(Lista lista, Posic p, void* item);

//retorna a posição do primeiro item
Posic Lista_getFirst(Lista lista);

//retorna a posição do proximo item em relação ao informado
Posic Lista_getNext(Lista lista, Posic p);

//retorna a posição do ultimo item
Posic Lista_getLast(Lista lista);

//retorna a posição anterior ao item informado
Posic Lista_getPrevious(Lista lista, Posic p);

//Inseri os itens de uma lista no final da outra
void Lista_insertAll(Lista lista, Lista lista2);

//Concatena duas listas
void Lista_insertLista(Lista* lista, Lista* lista2);

//precisa de uma função free -> causando leek de memoria
void freeLista(Lista* lista);

#endif