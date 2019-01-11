#ifndef ANOTACAO_H
#define ANOTACAO_H

/*define o tipo da anotacao*/
typedef void* Notation;

/*retorna uma anotação baseada nos parametros passados*/
Notation createNotacao(char* cor1, double w, double h, double x, double y, char* text);

/*Cria e retorna o codigo svg da anotacao passada*/
char* createNotacaoSvg(Notation anot);

/*libera a memoria da anotacao*/
void freeAnotacao(Notation anot);

/*cria e retorna o codigo svg da linha passada*/
char* createLine(Notation anot);

#endif