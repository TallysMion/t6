#ifndef EXECUTE_Via_H
#define EXECUTE_Via_H
#include "../../Fila/fila.h"
#include "../../Config/config.h"

/*percorre a fila comandos, executando os passos nescessários em cada linha, usando info*/
void startVia(Fila comandos, Info *info);

#endif