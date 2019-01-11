#ifndef HIDRANTE_H
#define HIDRANTE_H

typedef void* hidrante;

/*cria um objeto 'retangulo' com as informações passadas*/
hidrante createHidrante(char* id, char* cor1, char* cor2,double x, double y);

/*cria o codigo svg do retangulo em questao*/
char* createHidranteSvg(hidrante hidr);

/*Retorna W*/
char* getIdHidr(hidrante hidr);

/*Retorna H*/
void* getCircHidr(hidrante hidr);

/*Libera Memoria*/
void freeHidr(hidrante hidr);

void setColorFillHidr(void* semaf, char* color);
void setColorStrokeHidr(void* semaf, char* color);

char* reportHidrante(void* hidr);

//Comparador de objeto
int compareHidrante(void* hdA, void* hdB, int dim);

//Cria codigo Hash
int hashCodeHidrante(void* hdA, int Modulo);

//Comparador para hash
int HashCompareHidrante(void* hid, void* id);

#endif