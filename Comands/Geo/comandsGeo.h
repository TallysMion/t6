#ifndef COMANDS_GEO_H
#define COMANDS_GEO_H

#include "../../Config/config.h"
#include "../../Item/item.h"

/*função nx - reconfigura o numero maximo de imagens*/
int setConfig(char *text, Info *info);

/*funcao c - cria um circulo no vetor de imagens*/
int drawCircle(char *text, Info *info);

/*duncao r - cria um retangulo no vetor de imagens*/
int drawRectangle(char *text, Info *info);

/*funcao o - verifica se as figuras i e k, passadas em text se sobrepoe, e insere
a pergunta e a resposta na fila de impressao do txt, tambem cria a anotacao de 
sobrepoe e inclue na fila de anotacões*/
int overlap(char *text, Info *info);

/*funcao i - verifica se as cordenadas x e y estao dentro da figura, cordenadas na borda
não são consideradas internas e insere a pergunta e a resposta na fila de impressao do txt*/
int isInside(char *text, Info *info);

/*funcao d - calcula a distancia dos centro de massa das figuras,e insere a pergunta 
e a resposta na fila de impressao do txt*/
int howFar(char *text, Info *info);

/*funcao a - cria um arquivo, imprime os imagens e anotacões, e faz ninhas com a distancia
entre a figura passada e todas as outras do programa*/
int drawSufixo(char *text, Info *info);

/*funcao # - cria um arquivo svg, imprime as imagens e as anotações, cria um arquivo txt, e
imprime a lista de respostas*/
int close(Info *info);

/*novas funçoes incluidas na parte 2 -> t3*/

/*Cria uma nova Quadra*/
int drawQuad(char *text, Info *info);

/*Cria um novo Hidrante*/
int drawHidr(char *text, Info *info);

/*Cria um novo Semaforo*/
int drawSemaf(char *text, Info *info);

/*Cria uma nova Torre de Radio*/
int drawRBase(char *text, Info *info);

/*Configura as cores da Quadra*/
int configQuad(char *text, Info *info);

/*Configura as cores do Hidrante*/
int configHidr(char *text, Info *info);

/*Configura as cores da Torre de Radio*/
int configRBase(char *text, Info *info);

/*Configura as cores dos Semaforos*/
int configSemaf(char *text, Info *info);
    


#endif