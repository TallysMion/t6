#ifndef ARVOREB_H
#define ARVOREB_H

typedef void* Tree;

// cria um banco de dados novo
Tree BTREE_inicializa(int tam, char*bdName, int objSize, double (*compare)(void*, void*));

// Busca um item na arvore
void* BTREE_busca(Tree arvore, double valor, void* obj);

//Inclui um item na arvore
int BTREE_insere(Tree arvore, double valor, void* obj);

//Remove um item da arvore
int BTREE_deletar(Tree arvore, double valor, void* obj);

//Carrega um Banco de Dados Existente
Tree BTREE_Carrega(char* bdName);

//Retorna o item mais proximo da referencia
//se ctr != 0, permite retorno de item com dist = 0
void* BTREE_closestNeibord(Tree tree, double ref, void* reference, int ctr);

//Limpa a memoria da BTREE
void BTREE_free(Tree tree);

/*
//Retorna todos os itens
Lista BTREE_getAll(Tree arvore); //depende do getAll do BinariFile

//Retorna uma lista de itens que estao entre as referencias
void* BTREE_itensInsideArea(void* tree, void* refInicial, void* refFinal);

*/

void BTREE_PRINT(void* arvore);

#endif