#ifndef KDTREE_H
#define KDTREE_H

typedef void* KDT;
typedef void* KTD_Value;


/* Cria uma KD-Tree*/
void* KDT_create(int (*compare)(void*, void*, int), int dimension, void (*freeFunc)(void*));

/* Insere um Valor na KD-Tree*/
void   KDT_insert(KDT tree, KTD_Value value);

/*Retorna o tamanho da tree*/
int KDT_Size(void* tree);

/* Limpa a memoria da KD-Tree*/
void   freeKDTree(KDT tree);

/* Recupera uma lista com todos os valores da KD-Tree*/
void*  KDT_getAll(KDT tree);

/*Recupera um valor da arvore, com uma comparação iqual a referencia*/
void*  KDT_getKTD_Value(KDT tree, KTD_Value reference);

/*Remove um valor da arvore, com uma comparação iqual a referencia*/
void   KDT_remove(KDT tree, KTD_Value reference);

/*Retorna o item mais proximo da referencia*/
void* closestNeibord(void* tree, void* reference);

/*Retorna o item mais proximo da referencia*/
void* closest(void* tree, void* reference);

/*Retorna uma lista de itens que estao entre as referencias*/
void* itensInsideArea(void* tree, void* refInicial, void* refFinal);

double pontos_dist(double x1, double x2, double y1, double y2);

void* closestEqualNeibord(void* tree, void* reference);

void* getEsq(void* no);

void* getDir(void* no);

void* getValue(void* no);

void* getBranch(void* no, int id);

void* getNo(void *tree);

void freeKDTreeSimple(void* tree);

#endif