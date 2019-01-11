#ifndef CIRCULO_H
#define CIRCULO_H

typedef void* circulo;

/*cria um objeto 'circulo' com as informações passadas*/
circulo createCirculo(int id, char* cor1, char* cor2,double r, double x, double y);

/*cria o codigo svg do circulo em questao*/
char* createCirculoSvg(circulo rect);

/*retorna um vetor[2] com as cordenadas do centro de massa do circulo, sendo [0]=x e [1]=y*/
double *conrdenadaCentroCirc(circulo circ);

/*retorna 1,caso a cordenada x e y em questao 
for um ponto dentro do circulo, caso contrario, retorna 0 */
int isInCirc(double x, double y, circulo circ);

/*retorna 1,caso a cordenada x e y em questao 
for um ponto no circulo, caso contrario, retorna 0 */
int isOnCirc(double x, double y, circulo circ);

/*retorna o r do circulo*/
double getRCirc(circulo circ);

/*retorna o x do circulo*/
double getXCirc(circulo circ);

/*retorna o y do circulo*/
double getYCirc(circulo circ);

int getIdCirc(circulo circ);

/*retorna a cor da borda do circulo*/
char* getCorCirc(circulo circ);

/*libera a memoria ocupada pelo circulo*/
void freeCirculo(circulo circ);

#endif