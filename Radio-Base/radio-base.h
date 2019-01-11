#ifndef RADIOB_H
#define RADIOB_H


typedef void* radioB;

/*cria um objeto 'retangulo' com as informações passadas*/
radioB createRadioB(char* id, char* cor1, char* cor2,double x, double y);

/*cria o codigo svg do retangulo em questao*/
char* createRadioBSvg(radioB rb);

/*Retorna W*/
char* getIdRadioB(radioB rb);

/*Retorna H*/
void* getCircRadioB(radioB rb);

void setColorFillRB(void* semaf, char* color);
void setColorStrokeRB(void* semaf, char* color);

/*Libera Memoria*/
void freeRadioB(radioB rb);

char* reportRadioB(void* rb);

//Comparador de objeto
int compareRadioB(void* hdA, void* hdB, int dim);

//Cria codigo Hash
int hashCodeRadioB(void* hdA, int Modulo);

//Comparador para RadioB
int HashCompareRadioB(void* rb, void* id);

#endif