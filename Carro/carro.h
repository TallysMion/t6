#ifndef CARRO_H
#define CARRO_H

typedef void* carro;

/*cria um objeto 'retangulo' com as informações passadas*/
carro createCarro(char* placa, double x, double y, double w, double h);

/*cria o codigo svg do retangulo em questao*/
char* createCarroSVG(carro car);

/*Retorna placa*/
char* getPlacaCarro(carro car);

/*Retorna Rec*/
void* getRecCarro(carro car);

/*Libera Memoria*/
void freeCarro(carro car);

char* reportCarro(void* car);

//Comparador de objeto
int compareCarro(void* carA, void* carB, int dim);

//Cria codigo Hash
int hashCodeCarro(void* car, int Modulo);

//Comparador para hash
int HashCompareCarro(void* carA, void* carB);

#endif