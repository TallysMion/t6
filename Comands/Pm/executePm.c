#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Fila/fila.h"
#include "../../Config/config.h"
#include "comandsPm.h"

char *getCommandPm(char* text){
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

int executePm(char* text, Info *info){
    char *cmd;
    cmd = getCommandPm(text);
    /*printf("%s", text);*/
    if(strlen(cmd) == 0){
        return 0;
    }

    if(!strcmp(cmd, "p")){
        return createPessoa(text, info);
    }

    if(!strcmp(cmd, "m")){
        return setEndereco(text, info);
    }

    // Exemplo para reconhecer comando
    // if(!strcmp(cmd, "nx")){
    //     return setConfig(text, info);
    // }
    
    free(cmd);
    return 0;
}

void startPm(Fila comandos, Info *info){
    int i = 0;
    while(!empty_Fila(comandos)){
        char* aux; aux = (char*) remove_Fila(comandos);
        if(!executePm(aux, info)){
            return;
        }
        if(aux)
        free(aux);
        i++;
    }
}