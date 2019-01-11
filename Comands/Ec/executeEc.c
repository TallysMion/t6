#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Fila/fila.h"
#include "../../Config/config.h"
#include "comandsEc.h"

char *getCommandEc(char* text){
    int i;
    char *aux; 
    aux = (char*)calloc(strlen(text)+2, sizeof(char));
    sscanf(text, "%s ", aux);
    aux = strtok(aux, " ");
    for(i = 0; *(aux+i); i++){
        if(*(aux+i) == '\n'){
            *(aux+i) = 0;
        }
    }
    return aux;
}

int executeEc(char* text, Info *info){
     char *cmd;
     cmd = getCommandEc(text);
     /*printf("%s", text);*/
     if(strlen(cmd) == 0){
         return 0;
     }

    if(!strcmp(cmd, "t")){
        return newEstabType(text, info);
    }

    if(!strcmp(cmd, "e")){
        return newEstab(text, info);
    }
  
    free(cmd);
    return 0;
}

void startEc(Fila comandos, Info *info){
    int i = 0;
    while(!empty_Fila(comandos)){
        char* aux; aux = (char*) remove_Fila(comandos);
        if(!executeEc(aux, info)){
            return;
        }
        if(aux)
        free(aux);
        i++;
    }
}