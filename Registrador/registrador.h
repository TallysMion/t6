#ifndef REGISTRADOR_H
#define REGISTRADOR_H

typedef void* regis;

//Cria uma estrutura de registrador
void* create_Reg(char* id, void* value);

//Função de Free
void free_Reg(void* reg);

//Retorna o id do registrador
char* getId_Reg(void* Reg);

//Retorna o valor no Registrador
void* getValue_Reg(void* Reg);

//Codigo hash
int hashCodeRegistrador(void* Regist, int Modulo);

//Comparador para Hash
int HashCompareRegistrador(void* Regist, void* RegistB);

//Set value para reg
void setValueReg(void* reg, void* value);

#endif