#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Fila/fila.h"
#include "../../Config/config.h"
#include "comandsVia.h"

char *getCommandVia(char* text){
    int i;
    char *aux; 
    aux = (char*)calloc(strlen(text)+2, sizeof(char));
    strcpy(aux,text);
    aux = strtok(aux, " ");
    for(i = 0; *(aux+i); i++){
        if(*(aux+i) == '\n'){
            *(aux+i) = 0;
        }
    }
    return aux;
}

int executeVia(char* text, Info *info){
    char *cmd;
    cmd = getCommandVia(text);
    /*printf("%s", text);*/
    if(strlen(cmd) == 0){
        return 0;
    }

    if(!strcmp(cmd, "v")){
        criarVertice(text, info);
        return 1;
    }
    if(!strcmp(cmd, "e")){
        criarAresta(text, info);
        return 1;
    }

    free(cmd);
    return 0;
}

void startVia(Fila comandos, Info *info){
    int i = 0;
    while(!empty_Fila(comandos)){
        char* aux; aux = (char*) remove_Fila(comandos);
        if(!executeVia(aux, info)){
            return;
        }
        free(aux);
        i++;
    }
}