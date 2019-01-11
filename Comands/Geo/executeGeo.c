#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Fila/fila.h"
#include "../../Config/config.h"
#include "comandsGeo.h"

char *getCommandGeo(char* text){
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

int executeGeo(char* text, Info *info){
    char *cmd;
    cmd = getCommandGeo(text);
    /*printf("%s", text);*/
    if(strlen(cmd) == 0){
        return 0;
    }

    if(!strcmp(cmd, "nx")){
        return setConfig(text, info);
    }
    if(!strcmp(cmd, "c")){
        return drawCircle(text, info);
    }
    if(!strcmp(cmd, "r")){
        return drawRectangle(text, info);        
    }
    if(!strcmp(cmd, "o")){
        overlap(text, info);
        return 1;
    }
    if(!strcmp(cmd, "i")){
        isInside(text, info);
        return 1;
    }
    if(!strcmp(cmd, "d")){
        howFar(text, info);
        return 1;
    }
    if(!strcmp(cmd, "a")){
        return drawSufixo(text, info);
    }
    if(!strcmp(cmd, "#") || !strcmp(cmd, "#\r") || !strcmp(cmd, "#\r\n")){
        return close(info);
    }
    if(!strcmp(cmd, "q")){
        return drawQuad(text, info);
    }
    if(!strcmp(cmd, "h")){
        return drawHidr(text, info);
    }
    if(!strcmp(cmd, "s")){
        return drawSemaf(text, info);
    }
    if(!strcmp(cmd, "t")){
        return drawRBase(text, info);
    }
    if(!strcmp(cmd, "cq")){
        return configQuad(text, info);
    }
    if(!strcmp(cmd, "ch")){
        return configHidr(text, info);
    }
    if(!strcmp(cmd, "ct")){
        return configRBase(text, info);
    }
    if(!strcmp(cmd, "cs")){
        return configSemaf(text, info);
    }
    free(cmd);
    return 0;
}

void startGEO(Fila comandos, Info *info){
    int i = 0;
    while(!empty_Fila(comandos)){
        char* aux; aux = (char*) remove_Fila(comandos);
        if(!executeGeo(aux, info)){
            return;
        }
        free(aux);
        i++;
    }
}