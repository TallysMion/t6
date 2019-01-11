#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Config/config.h"
#include "../../Grafos/GrafoD.h"

/*comando 'v' do EC*/
void criarVertice(char* text,Info *info){
    char *aux, *id;
    double x, y;
    aux = text; aux += 2;
    id = (char*) calloc(55, sizeof(char));
    sscanf(aux, "%s %lf %lf", id, &x, &y);
    grafoD_criar(info->bd->grafo, id, x, y);
    free(id);
    if(x+5 > info->conf->x) { info->conf->x = x+5;}
    if(y+5 > info->conf->y) { info->conf->y = y+5;}
}

/*comando 'e' do EC*/
void criarAresta(char* text,Info *info){
    char *aux, *idA, *idB, *leftCep, *rightCep, *nome;
    double size, speed;
    aux = text; aux += 2;
    idA =      (char*) calloc(55, sizeof(char));
    idB =      (char*) calloc(55, sizeof(char));
    leftCep =  (char*) calloc(55, sizeof(char));
    rightCep = (char*) calloc(55, sizeof(char));
    nome =     (char*) calloc(55, sizeof(char));
    sscanf(aux, "%s %s %s %s %lf %lf %s", idA, idB, rightCep, leftCep, &size, &speed, nome);
    grafoD_insereAresta(info->bd->grafo, idA, idB, leftCep, rightCep, size, speed, nome);
    free(idA);
    free(idB);
    free(leftCep);
    free(rightCep);
    free(nome);
}
