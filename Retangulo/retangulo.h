#ifndef RETANGULO_H
#define RETANGULO_H

typedef void* retangulo;

/*cria um objeto 'retangulo' com as informações passadas*/
retangulo createRetangulo(int id, char* cor1, char* cor2,double w, double h, double x, double y);

/*cria o codigo svg do retangulo em questao*/
char* createRetanguloSvg(retangulo rect);

/*retorna um vetor[2] com as cordenadas do centro de massa do retangulo, sendo [0]=x e [1]=y*/
double *conrdenadaCentroRec(retangulo rect);

/*retorna 1,caso a cordenada x e y em questao 
for um ponto dentro do retangulo, caso contrario, retorna 0*/
int isInRec(double x, double y, retangulo rect);

/*retorna 1,caso a cordenada x e y em questao 
for um ponto no retangulo, caso contrario, retorna 0*/
int isOnRec(double x, double y, retangulo rect);

/*Retorna W*/
double getWRec(retangulo rect);

/*Retorna H*/
double getHRec(retangulo rect);

/*Retorna X*/
double getXRec(retangulo rect);

/*Retorna y*/
double getYRec(retangulo rect);

/*Retorna Id*/
int getIdRec(retangulo rect);

/*Retorna a cor da borda*/
char* getCorRec(retangulo rect);

/*Libera Memoria*/
double freeRec(retangulo rect);

#endif