#include <stdio.h>
#include <stdlib.h>
#include "../Config/config.h"
#include "../Fila/fila.h"
#include "../Comands/Geo/executeGeo.h"
#include "../Comands/Qry/executeQry.h"
#include "../Comands/Ec/executeEc.h"
#include "../Comands/Pm/executePm.h"
#include "../Comands/Via/executeVia.h"

int main(int argc, const char *argv[]){
    //configurações
    Info *info;
    Fila comandos;    
    info = configIn(argc, argv);    

    comandos = getCommandsForGEO(info);    
    if(comandos){
        inicGEO(info, lenghFila(comandos));
        startGEO(comandos, info);
    }else{
        printf("Arquivo .geo (obrigatorio) nao encontrado\n");
        return -1;
    }
    printf(".geo Concluido\n");
    comandos = getCommandsForEC(info); 
    if(comandos){
        inicEC(info, lenghFila(comandos));
        startEc(comandos, info);
    }
    printf(".ec Concluido\n");
    comandos = getCommandsForPM(info); 
    if(comandos){
        inicPM(info, lenghFila(comandos));
        startPm(comandos, info);
    }
    printf(".pm Concluido\n");
    comandos = getCommandsForVIA(info);
    if(comandos){
        inicVIA(info, lenghFila(comandos));
        startVia(comandos, info);
    }
    printf(".via Concluido\n");
    printf("Iniciando qry -> %s\n", info->q);
    comandos = getCommandsForQRY(info); 
    if(comandos)  
    startQRY(comandos, info);

    freeFila(comandos);
    freeConfig(info);       
    return 0;
}