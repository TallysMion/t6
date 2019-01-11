#ifndef EXECUTE_PM_H
#define EXECUTE_PM_H
#include "../../Fila/fila.h"
#include "../../Config/config.h"

/*percorre a fila comandos, executando os passos nescessários em cada linha, usando info*/
void startPm(Fila comandos, Info *info);

#endif