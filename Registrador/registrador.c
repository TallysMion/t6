#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Grafos/GrafoD.h"

typedef struct {
    char* id;
    void* value;
}Reg;

void writerReg(Reg* reg, int seek, void* arq){
    fseek(arq, seek, SEEK_SET);
    for(int i=0; i<55; i++)
        fwrite(&reg->id[i], sizeof(char), 1, arq);
    double* v = (double*) reg->value;
    fwrite(&v[0], sizeof(double), 1, arq);
    fwrite(&v[1], sizeof(double), 1, arq);
}
void readerReg(Reg* reg, int seek, void* arq){
    fseek(arq, seek, SEEK_SET);
    for(int i=0; i<55; i++)
        fread(&reg->id[i], sizeof(char), 1, arq);
    double* v = (double*) reg->value;
    fread(&v[0], sizeof(double), 1, arq);
    fread(&v[1], sizeof(double), 1, arq);
}
int getSizeReg(){
    return (55*sizeof(char) + 2* sizeof(double));
}

//Cria uma estrutura de registrador
void* create_Reg(char* id, void* value){
    Reg* rg;
    rg = (Reg*) calloc(1, sizeof(Reg));
    rg->id = (char*) calloc(55, sizeof(char));
    strcpy(rg->id, id);
    rg->value = value;
    return (void*) rg;
}

void setValueReg(void* reg, void* value){
    Reg* rg;
    rg = (Reg*) reg;
    rg->value = value;
}

void free_Reg(void* reg){
    Reg* rg;
    rg = (Reg*) reg;
    free(rg->id);
    free(rg);
}

//Retorna o id do registrador
char* getId_Reg(void* reg){
    Reg* rg;
    rg = (Reg*) reg;
    return rg->id;
}

//Retorna o valor no Registrador
void* getValue_Reg(void* reg){
    Reg* rg;
    rg = (Reg*) reg;
    return rg->value;
}

//Cria codigo Hash
int hashCodeRegistrador(void* Regist, int Modulo){
    Reg *rg;
    rg = (Reg*) Regist;
    int x = strlen(rg->id);
    int hash = 0;
    char *aux = rg->id;
    while(*aux != 0){
        hash += x*(*aux);
        aux++;
        x--;
    }
    return Modulo < 0 ? hash : hash%Modulo;
}

//Comparador para hash
int HashCompareRegistrador(void* Regist, void* RegistB){
    Reg *rg, *rg2;
    rg = (Reg*) Regist;
    rg2 = (Reg*) RegistB;
    return strcmp(rg->id, rg2->id);
}
