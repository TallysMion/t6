#ifndef EXECUTE_EC_H
#define EXECUTE_EC_H
#include "../../Fila/fila.h"
#include "../../Config/config.h"

/*percorre a fila comandos, executando os passos nescessários em cada linha, usando info*/
void startEc(Fila comandos, Info *info);

#endif