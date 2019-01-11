#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Fila/fila.h"
#include "../../Grafos/GrafoD.h"
#include "../../KDTREE/kdtree.h"
#include "../../Registrador/registrador.h"
#include "../../Config/config.h"
#include "comandsQry.h"

char *getCommandQry(char* text){
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

int executeQry(char* text, Info *info){
    char *cmd;
    cmd = getCommandQry(text);
    /*printf("%s", text);*/
    if(strlen(cmd) == 0){
        return 0;
    }

    if(!strcmp(cmd, "q?")){
        reportRec(text, info);
        return 1;
    }
    if(!strcmp(cmd, "Q?")){
        reportCirc(text, info);
        return 1;
    }
    if(!strcmp(cmd, "dq")){
        deleteQuadrasRec(text, info); 
        return 1;       
    }
    if(!strcmp(cmd, "dle")){
        deleteUrbamEqRec(text, info);
        return 1;
    }
    if(!strcmp(cmd, "Dq")){
        deleteQuadrasCirc(text, info);
        return 1;
    }
    if(!strcmp(cmd, "Dle")){
        deleteUrbamEqCirc(text, info);
        return 1;
    }
    if(!strcmp(cmd, "cc")){
        colorChange(text, info);
        return 1;
    }
    if(!strcmp(cmd, "crd?")){
        equipOnCepOrId(text, info);
        return 1;
    }
    if(!strcmp(cmd, "crb?")){
        closestRBase(text, info);
        return 1;
    }
    if(!strcmp(cmd, "m?")){
        whoIsHere(text, info);
        return 1;
    }
    if(!strcmp(cmd, "mr?")){
        whoIsInThisArea(text, info);
        return 1;
    }  
    if(!strcmp(cmd, "dm?")){
        whoAreYou(text, info);
        return 1;
    }
    if(!strcmp(cmd, "de?")){
        whoAreYouEstab(text, info);
        return 1;
    }
    if(!strcmp(cmd, "rip")){
        bread(text, info);
        return 1;
    }
    if(!strcmp(cmd, "ecq?")){
        whatHaveHere(text, info);
        return 1;
    }
    if(!strcmp(cmd, "ecr?")){
        whatHaveInThisArea(text, info);
        return 1;
    }
    if(!strcmp(cmd, "tecq?")){
        whatHaveHere_typeOrder(text, info);
        return 1;
    }
    if(!strcmp(cmd, "tecr?")){
        whatHaveInThisArea_typeOrder(text, info);
        return 1;
    }
    if(!strcmp(cmd, "hmpe?")){
        closestHidrant(text, info);
        return 1;
    }
    if(!strcmp(cmd, "hmp?")){
        closestHidrantFromRB(text, info);
        return 1;
    }
    if(!strcmp(cmd, "fec")){
        closeEstab(text, info);
        return 1;
    }
    if(!strcmp(cmd, "mud")){
        mudancaPessoa(text, info);
        return 1;
    }
    if(!strcmp(cmd, "mudec")){
        mudancaEstab(text, info);
        return 1;
    }
    if(!strcmp(cmd, "dpr")){
        desapropriar(text, info);
        return 1;
    }
    //Funções do t5
    if(!strcmp(cmd, "@m?")){
        pessoaToReg(text, info);
        return 1;
    }
    if(!strcmp(cmd, "@e?")){
        enderecoToReg(text, info);
        return 1;
    }
    if(!strcmp(cmd, "@g?")){
        equipUrbanToReg(text, info);
        return 1;
    }
    if(!strcmp(cmd, "@xy")){
        cordToReg(text, info);
        return 1;
    }
    if(!strcmp(cmd, "@tp?")){
        theClosestEstab(text, info);
        return 1;
    }
    if(!strcmp(cmd, "p?")){
        simpleRout(text, info);
        return 1;
    }
    if(!strcmp(cmd, "sp?")){
        multRout(text, info);
        return 1;
    }
    if(!strcmp(cmd, "au")){
        create_Carro(text, info);
        return 1;
    }
    if(!strcmp(cmd, "dc")){
        detectColision(text, info);
        return 1;
    }
    if(!strcmp(cmd, "rau")){
        remove_Carro(text, info);
        return 1;
    }
    
    free(cmd);
    return 0;
}

void startQRY(Fila comandos, Info *info){
    int i = 0;
    while(!empty_Fila(comandos)){
        char* aux; aux = (char*) remove_Fila(comandos);
        printf("%s", aux);
        if(!executeQry(aux, info)){
            return;
        }
        free(aux);
        i++;
    }
    closeQRY(info);
}