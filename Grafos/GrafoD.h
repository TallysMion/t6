#ifndef _GRAFOD_LIB_
#define _GRAFOD_LIB_

typedef void* GrafoD;   
typedef void* Aresta;   
typedef void* Vertice;


/*
TAD Grafos direcionados
*/

//cria estrutura grafo
void* GRAFO_CREATE(int modulo);

//cria e insere vertice
void *grafoD_criar(GrafoD gd, char *id, double x, double y);

//função insere uma aresta
void grafoD_insereAresta(GrafoD gd, char *vID1,  char *vID2, char *leftCEP, char *rightCEP, double size, double speed, char* nome);

//função retorna uma lista de adjacentes - destinos
void *grafoD_listaAdjacente(Vertice v1);

//retorna true se a1 for adjacente a a2 e false se não for
int grafoD_Adjacente(Vertice a1, Vertice a2);

//compara "xy" grafo
int compareGD(Vertice v1, Vertice v2, int dim);

//compara cep encontrado com cep procurado - 1 p/ true(igual) e 0 p/ false(diferente)
int compareH_CEP(void *itemA, Aresta itemB);

//compara id encontrado com id procurado
int compareH_ID(void* itemA, Vertice itemB);

//hash encoding function
int hashFunction(void *String, int n);

//da Free no grafo
void freeGrafoD(void* grafo, void***table);

//retorna o nome da rua da resta passada
void *getRua(void *aresta);

//print caminho no txt
void* txtCaminho(void *listaArestas);

//print caminho no svg
void* svgCaminho(void *listaArestas, char *cor, double* inic, double* end);

//Desbloqueia os itens do grafo
void GrafoD_unlock(void* grafo);

 //Bloqueia os vertices que estao nessa area
void GrafoD_blockVertices(void* grafo,double w,double h,double x,double y);

 //Bloqueia as arestas que passam por essa area
void GrafoD_blockArestas(void* grafo,double w,double h,double x,double y);

//double getPos(void *ar, int i);
//void* getKDT(void *grafo);
//void* getAresta(void *v);

void* caminho(void* grafo,double* Start, double* idEnd, int mod, void*** ar);

//gera svg do grafo
char* grafoToSvg(void* grafo);

void *** GrafoD_arestaTable(void* grafo,int mod);

#endif
