#ifndef SEMAFORO_H
#define SEMAFORO_H

typedef void* semaforo;

/*cria um objeto 'retangulo' com as informações passadas*/
semaforo createSemaforo(char* id, char* cor1, char* cor2,double x, double y);

/*cria o codigo svg do retangulo em questao*/
char* createSemaforoSvg(semaforo semaf);

/*Retorna W*/
char* getIdSemaf(semaforo semaf);

/*Retorna H*/
void* getCircSemaf(semaforo semaf);

void setColorFillSemaf(void* semaf, char* color);
void setColorStrokeSemaf(void* semaf, char* color);

/*Libera Memoria*/
void freeSemaf(semaforo semaf);

char* reportSemaforo(void* semaf);

//Comparador de objeto
int compareSemaforo(void* hdA, void* hdB, int dim);

//Cria codigo Hash
int hashCodeSemaforo(void* hdA, int Modulo);

//Comparação para hashTable
int HashCompareSemaf(void* semaf, void* id);

#endif