#ifndef QUADRA_H
#define QUADRA_H

typedef void* quadra;
typedef void* rectangle;

/*cria um objeto 'retangulo' com as informações passadas*/
quadra createQuadra(char* cep, char* cor1, char* cor2,double w, double h, double x, double y);

/*cria o codigo svg do retangulo em questao*/
char* createQuadraSvg(quadra quad);

/*Retorna W*/
char* getCepQuad(quadra quad);

/*Retorna H*/
rectangle getRecQuad(quadra quad);

void setColorFillQuad(void* semaf, char* color);
void setColorStrokeQuad(void* semaf, char* color);

/*Libera Memoria*/
void freeQuad(quadra quad);

char* reportQuadra(void* quad);

//Cria codigo Hash
int hashCodeQuadra(void* hdA, int Modulo);

//Comparador para Hash
int HashCompareQuadra(void* quad, void* id);

void writerQuadra(void* quad, int seek, void* arq);
void readerQuadra(void* quad, int seek, void* arq);
int getSizeQuadra();
double compareQuadra(void* objA, void* objB);
void* allocarQuadra();

#endif