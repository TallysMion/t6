#include <stdio.h>
#include <stdlib.h>



//typedef void* Item;
typedef struct it{
    void *value;
    struct it* next;
    struct it* prev;
}Item;

//typedef void* Lista;
typedef struct{
    Item* inicio;
    Item* fim;
    int size;
}Lista;

//typedef void* Posic;
typedef struct{
    Lista* lista;
    Item* it;
}Posic;

//cria Lista
void* Lista_createLista(){
    Lista *result;
    result = (Lista*) calloc(1, sizeof(Lista));
    result->size = 0;
    result->inicio = NULL;
    result->fim = NULL;
    return (void*)result;
}

//retorna o comprimento da lista
int Lista_lenght(void* lista){
    Lista *list;
    list = (Lista*)lista;
    return list->size;
}

//insere um item na lista
void* Lista_insert(void* lista, void* item){
    Lista *list;
    list = (Lista*)lista;

    Item *it;
    it = (Item*) calloc(1,sizeof(Item));
    it->value = item;
    it->next = NULL;
    it->prev = list->fim;
    if(list->fim){
        list->fim->next=it;
    }
    if(list->size == 0){
        list->inicio = it;
    }
    list->fim = it;

    Posic* ps;
    ps = (Posic*) calloc(1, sizeof(Posic));
    ps->lista = lista;
    ps->it = it;

    list->size++;

    return (void*) ps;
}

void Lista_insertLista(void* list, void* list2){
    Lista *lista, *lista2;
    lista = (Lista*) list;
    lista2= (Lista*) list2;
    if(list2 == NULL) return;
    if(list == NULL){list = list2; return;}
    if(lista->size == 0){
        lista->size = lista2->size;
        lista->inicio = lista2->inicio;
        lista->fim = lista2->fim;
        return;
    }
    if(lista2->size == 0){
        return;
    }
    lista->size += lista2->size;
    lista->fim->next = lista2->inicio;
    lista2->inicio->prev = lista->fim;
    lista->fim = lista2->fim;
}

//remove um item da lista
void Lista_remove(void* lista, void* p){
    Posic *pos;
    pos = (Posic*) p;
    Lista *ls;
    ls = (Lista*) lista;
    if(pos->lista != lista){
        return;
    }

    Item *it;
    it = (Item*) pos->it;
    if(it == ls->inicio){
        ls->inicio = it->next;
    }else{
        it->prev->next = it->next;
    }
    if(it == ls->fim){
        ls->fim = it->prev;
    }else{
        it->next->prev = it->prev;
    }
    it->next = NULL;
    it->prev = NULL;
    it->value = NULL;
    pos->it = NULL;
    pos->lista = NULL;
    free(it);
    free(p);

    Lista *list;
    list = (Lista*)lista;
    list->size--;

}

//busca o valor da lista, na posição p
void* Lista_get(void* lista, void* p){
    if(p == NULL){
        return NULL;
    }
    Posic *pos;
    pos = (Posic*) p;
    if(pos->lista != lista){
        return NULL;
    }

    Item *it;
    it = (Item*) pos->it;
    if(it == NULL) return NULL;
    return it->value;
}

//insere um item apos o item informado
void* Lista_insertBefore(void* lista, void* p, void* item){
    Lista *list;
    list = (Lista*)lista;

    Posic *pos;
    pos = (Posic*) p;

    if(pos->lista != lista){
        return NULL;
    }

    Item *it;
    it = (Item*) calloc(1,sizeof(Item));
    it->value = item;

    it->next = pos->it->next;
    it->prev = pos->it;

    if(pos->it->next){
        pos->it->next->prev = it;
    }
    pos->it->next = it;


    Posic* ps;
    ps = (Posic*) calloc(1, sizeof(Posic));
    ps->lista = lista;
    ps->it = it;

    list->size++;

    if(list->fim->next){
        list->fim = list->fim->next;
    }

    return (void*) ps;
}

//insere um item antes do item informado
void* Lista_insertAfter(void* lista, void* p, void* item){
    Lista *list;
    list = (Lista*)lista;

    Posic *pos;
    pos = (Posic*) p;

    if(pos->lista != lista){
        return NULL;
    }

    Item *it;
    it = (Item*) calloc(1,sizeof(Item));
    it->value = item;

    it->prev = pos->it->prev;
    it->next = pos->it;

    if(pos->it->prev){
        pos->it->prev->next = it;
    }
    pos->it->prev = it;


    Posic* ps;
    ps = (Posic*) calloc(1, sizeof(Posic));
    ps->lista = lista;
    ps->it = it;

    list->size++;


    if(list->inicio->prev){
        list->inicio = list->inicio->prev;
    }

    return (void*) ps;
}

//retorna a posição do primeiro item
void* Lista_getFirst(void* lista){
    Lista *list;
    list = (Lista*)lista;
    if(list == NULL) return NULL;
    if(list->size == 0){
        return NULL;
    }

    Posic *pos;
    pos = (Posic*) calloc(1, sizeof(Posic));
    pos->it = list->inicio;
    pos->lista = lista;
    return pos;
}

//retorna a posição do proximo item em relação ao informado
void* Lista_getNext(void* lista, void* p){
    Posic *pos;
    pos = (Posic*) p;
    
    if(pos->lista != lista){
        return NULL;
    }
    if(pos->it == NULL){
        return NULL;
    }

    Posic *result;
    result = (Posic*) calloc(1,sizeof(Posic));

    result->it = pos->it->next;
    result->lista = lista;

    if(result->it == NULL){
        result = NULL;
    }

    return result;
}

//retorna a posição do ultimo item
void* Lista_getLast(void* lista){
    Lista *list;
    list = (Lista*)lista;

    if(list->size == 0){
        return NULL;
    }

    Posic *pos;
    pos = (Posic*) calloc(1, sizeof(Posic));
    pos->it = list->fim;
    pos->lista = lista;
    return pos;
}

//retorna a posição anterior ao item informado
void* Lista_getPrevious(void* lista, void* p){
    Posic *pos;
    pos = (Posic*) p;
    
    if(pos->lista != lista){
        return NULL;
    }

    Posic *result;
    result = (Posic*) calloc(1,sizeof(Posic));

    result->it = pos->it->prev;
    result->lista = lista;

    if(result->it == NULL){
        result = NULL;
    }

    return result;
}

//testar
void Lista_insertAll(void* lista, void* lista2){
    Lista_insertLista(lista, lista2);
}


void freeLista(void* lista){
    Item *a, *p;
    Lista* ls;
    ls = (Lista*) lista;
    a = ls->inicio;
    while(a != NULL){
        p = a->next;
        free(a);
        a = p;
    }
}


