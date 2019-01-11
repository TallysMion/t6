#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main(){

    int i;

    Lista ls;
    Posic pos[10];
    ls = Lista_createLista();

    printf("%d\n", Lista_lenght(ls));
    for(i=0;i<10;i++){
        int *j; 
        j = (int*) calloc(1, sizeof(int));
        *j = i;
        pos[i] = Lista_insert(ls, (void*) j);
    }
    printf("%d\n", Lista_lenght(ls));

    printf("%d\n", *((int*)Lista_get(ls, pos[2])));
    printf("%d\n", *((int*)Lista_get(ls, pos[6])));

    Posic t;
    t=Lista_getFirst(ls);
    while(1){
        void* i = Lista_get(ls,t);
        if(i){
            printf("%d\n", *((int*)i));
            t = Lista_getNext(ls, t);
        }else{
            break;
        }
        
    }
    t=Lista_getLast(ls);
    while(1){
        void* i = Lista_get(ls,t);
        if(i){
            printf("%d\n", *((int*)i));
            t = Lista_getPrevious(ls, t);
        }else{
            break;
        }
        
    }

    int *j; j = (int*) calloc(1, sizeof(int));
    *j = -1; 
    Lista_insertAfter(ls, Lista_getFirst(ls), j);
    j = (int*) calloc(1, sizeof(int));
    *j = -2; 
    Lista_insertBefore(ls, Lista_getLast(ls), j);

    t=Lista_getFirst(ls);
    while(1){
        void* i = Lista_get(ls,t);
        if(i){
            printf("%d\n", *((int*)i));
            t = Lista_getNext(ls, t);
        }else{
            break;
        }
        
    }

}