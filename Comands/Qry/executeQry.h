#ifndef EXECUTE_QRY_H
#define EXECUTE_QRY_H
#include "../../Fila/fila.h"
#include "../../Config/config.h"

/*percorre a fila comandos, executando os passos nescessários em cada linha, usando info*/
void startQRY(Fila comandos, Info *info);

#endif