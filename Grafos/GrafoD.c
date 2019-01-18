#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../KDTREE/kdtree.h"
#include "../HashTable/hashtable.h"
#include "../Lista/lista.h"
#include "../Config/config.h"
#include "../Anotacao/anotacao.h"
#include "../Fila/fila.h"
#include "../Registrador/registrador.h"
#include <limits.h>
#include <math.h>

typedef struct VerticeV{
    char *id;
    double x;
    double y;
    struct ArestaP *aresta;
    int disable;
    int idDijkstra;
    struct ArestaP *anteriorDijkstra;
}VerticeV;

typedef struct ArestaP{
    VerticeV *v2;
    VerticeV *v1;
    int disable;
    char *nome; 
    char *cepR;
    char *cepL;
    double tam;
    double speed;
    struct ArestaP *next;
    double peso0;
    double peso1;
}ArestaP;

typedef struct Grafo{
    KDT vertices;
    HashTable left;
    HashTable right;
    HashTable ID;
}Grafo;

//-------------------------------------------------------------------------------------------------------------

void freeArestaP(void* a){
    ArestaP *ar;
    ar = (ArestaP*) a;
    if(ar == NULL) return;
    free(ar->cepL);
    free(ar->cepR);
    free(ar->nome);
    ar->v2 = NULL;
    void* a2 = ar->next;
    free(ar);
    freeArestaP(a2);
}

void freeVerticeV(void* v){
    VerticeV *vt;
    vt = (VerticeV*) v;
    free(vt->id);
    freeArestaP(vt->aresta);
}


void freeGrafoD(void* grafo, void*** ar0){
    if(grafo == NULL) return;
    Grafo *gr; gr = (Grafo*)grafo;

    if(ar0!=NULL){
        Lista vertices;
        vertices = KDT_getAll(gr->vertices);
        int size = Lista_lenght(vertices);
        freeLista(vertices);
        for(int i=0; i<size; i++)
            free(ar0[i]);
        free(ar0);
    }
    
    if(gr->vertices != NULL)
    freeKDTree(gr->vertices);
    if(gr->left != NULL)
    free_hashtable(gr->left);
    if(gr->right != NULL)
    free_hashtable(gr->right);
    if(gr->ID != NULL)
    free_hashtable(gr->ID);
    free(gr);
}

//compara "xy" grafo
int compareGD(Vertice v1, Vertice v2, int dim){

    VerticeV *V1;
    VerticeV *V2;

    V1 = (VerticeV *) v1;
    V2 = (VerticeV *) v2;
    dim = dim % 2;

    if(dim==0){
       return V2->x - V1->x;
    }else{
        return V2->y - V1->y;
    }
}

//compara cep encontrado com cep procurado - 1 p/ true(igual) e 0 p/ false(diferente)
int compareH_CEP(HashTable itemA, Aresta itemB){

    ArestaP *found, *search;
    int i;

    found = (ArestaP *) itemA;
    search = (ArestaP *) itemB;

    i = strcmp(found->cepL,search->cepL);
    if(i==0){
        return 1;
    }
    i = strcmp(found->cepL,search->cepR);
    if(i==0){
        return 1;
    }
    i = strcmp(found->cepR,search->cepR);
    if(i==0){
        return 1;
    }
    i = strcmp(found->cepR,search->cepL);
    if(i==0){
        return 1;
    }

    return 0;
} 

//compara id encontrado com id procurado
int compareH_ID(HashTable itemA, Vertice itemB){

    VerticeV *found, *search;

    found = (VerticeV *) itemA;
    search = (VerticeV *) itemB;

    return strcmp(found->id,search->id);

} 

//hash encoding function
int hashFunctionArest(void *Item, int n){
    ArestaP * v;
    v = (ArestaP*)Item;
    char *string;
    int tam, hash;

    string = (char *) v->nome;

    tam = strlen(string);
    hash = 0;

    while(*string != 0){
        hash += tam*(*string);
        string++;
        tam--;
    }
    return n < 0 ? hash : hash%n;
}

//hash encoding function
int hashFunction(void *Item, int n){
    VerticeV * v;
    v = (VerticeV*)Item;
    char *string;
    int tam, hash;

    string = (char *) v->id;

    tam = strlen(string);
    hash = 0;

    while(*string != 0){
        hash += tam*(*string);
        string++;
        tam--;
    }
    return n < 0 ? hash : hash%n;
}

//cria estrutura grafo
void* GRAFO_CREATE(int n){
    Grafo* result;

    result = (Grafo*) calloc(1, sizeof(Grafo));
    result->vertices = KDT_create(compareGD,2, freeVerticeV);
    result->left = create_hashtable(n,compareH_CEP, hashFunctionArest);
    result->right = create_hashtable(n,compareH_CEP, hashFunctionArest);
    result->ID = create_hashtable(n,compareH_ID, hashFunction);
    return (void*) result;
}

//cria e insere vertice
void *grafoD_criar(GrafoD gd, char *id, double x, double y){

    Grafo *gr;
    gr = (Grafo*)gd;

    VerticeV *grafo;
    grafo= calloc(1, sizeof(VerticeV));
    grafo->id = calloc(strlen(id)+2, sizeof(char));
    strcpy(grafo->id,id);
    grafo->disable = 0;
    grafo->x = x;
    grafo->y = y;
    grafo->aresta = NULL;

    KDT_insert(gr->vertices, grafo);
    insert_hashtable(gr->ID, grafo);

    return (void *) gd;
}

//função insere uma aresta
void grafoD_insereAresta(GrafoD gd, char *vID1,  char *vID2, char *leftCEP, char *rightCEP, double size, double speed, char* nome){

    VerticeV *V1, *aux;
    Grafo *GD;

    GD = (Grafo *) gd;

    aux = calloc(1, sizeof(VerticeV));
    aux->id = calloc(strlen(vID1)+2, sizeof(char));
    strcpy(aux->id, vID1);
    V1 = (VerticeV *) get_hashtable(GD->ID, aux);
    freeVerticeV(aux);

    ArestaP *atual;
    if(V1->aresta == NULL){
        V1->aresta = calloc(1, sizeof(ArestaP));
        atual = V1->aresta;
    }else{
        atual = V1->aresta;
        while(atual->next != NULL){
            atual = atual->next;
        }
        atual->next = calloc(1, sizeof(ArestaP));
        atual = atual->next;
    }

    atual->v1 = V1;
    
    aux = calloc(1, sizeof(VerticeV));
    aux->id = calloc(strlen(vID2)+2, sizeof(char));
    strcpy(aux->id, vID2);
    atual->v2 = (VerticeV *) get_hashtable(GD->ID, aux);
    freeVerticeV(aux);

    atual->disable = 0;
    atual->nome = calloc(strlen(nome)+2, sizeof(char));
    strcpy(atual->nome, nome);
    atual->cepR = calloc(strlen(rightCEP)+2,sizeof(char));
    strcpy(atual->cepR, rightCEP);
    atual->cepL = calloc(strlen(leftCEP)+2,sizeof(char));
    strcpy(atual->cepL, leftCEP);
    atual->tam = size;
    atual->speed = speed;
    atual->next = NULL;


    insert_hashtable(GD->left, atual);
    insert_hashtable(GD->right, atual);

}

//função retorna uma lista de adjacentes - destinos
void *grafoD_listaAdjacente(Vertice v1){

    VerticeV *grafo = (VerticeV *) v1;

    return grafo->aresta;

}

//retorna true se a1 for adjacente a a2 e false se não for
int grafoD_Adjacente(Vertice a1, Vertice a2){

    VerticeV *v1 = (VerticeV *) a1;
    VerticeV *v2 = (VerticeV *) a2;

    while(v1->aresta->next!=NULL){
        if(strcmp(v1->aresta->v2->id,v1->id)==0){
            return 1;
        }
    }

    return 0;

}

double orientation(ArestaP *A, ArestaP *B){
    double x1, x2, x3;
    double y1, y2, y3;
    x1 =    A->v1->x;
    x2 =    B->v1->x;
    x3 =    B->v2->x;
    y1 =    A->v1->y;
    y2 =    B->v1->y;
    y3 =    B->v2->y;
    return (y2 - y1)*(x3 - x2) - (y3 - y2)*(x2 - x1);
}


//print caminho no txt
void* txtCaminho(void *listaArestas){
    if(listaArestas == NULL)    return NULL;
    Lista result = Lista_createLista();
    void *item;
    ArestaP *aresta;
    char *str;
    int i;
    ArestaP *ctrl;

    item = Lista_getFirst(listaArestas);
    str = (char*) calloc(255, sizeof(char));
    aresta = (ArestaP *) Lista_get(listaArestas, item);
    sprintf(str,"Siga pela rua %s,\n",aresta->nome);
    Lista_insert(result, str);
    ctrl = aresta;

    while(item != NULL){

        aresta = (ArestaP *) Lista_get(listaArestas, item);
        if(strcmp(aresta->nome, ctrl->nome)){
            str = (char*) calloc(255, sizeof(char));
            if(orientation(ctrl, aresta) < 0){
                sprintf(str,"Vire a esquerda na rua %s,\n",aresta->nome);
            }else if(orientation(ctrl, aresta) > 0){
                sprintf(str,"Vire a direita na rua %s,\n",aresta->nome);
            }else{
                sprintf(str,"Siga em Frente na rua %s,\n",aresta->nome);
            }
            Lista_insert(result, str);
            ctrl = aresta;
        }
        item = Lista_getNext(listaArestas, item);
    }
    Lista_insert(result, "Voce Alcançou seu destino!!\n");
    return result;
}


//print caminho no svg
void* svgCaminho(void *listaArestas, char *cor, double* inic, double* end){
    if(listaArestas == NULL)    return NULL;
    void *itemA, *itemB, *svg, *notation, *posic;
    ArestaP *ar1, *ar2;
    char *svgCode;

    Lista result = Lista_createLista();
    if(Lista_lenght(listaArestas) == 0){
        notation = createNotacao(cor, *inic, *(inic+1), *end, *(end+1), "");
        svgCode = createLine(notation);
        Lista_insert(result, svgCode);
        return result;
    }

    if(inic != NULL){
        ar2 = Lista_get(listaArestas, Lista_getFirst(listaArestas));    
        notation = createNotacao(cor, *inic, *(inic+1), ar2->v1->x, ar2->v1->y, "");
        svgCode = createLine(notation);
        Lista_insert(result, svgCode);
    }

    posic = Lista_getFirst(listaArestas);    
    while(posic != NULL){

        ar1 = (ArestaP *) Lista_get(listaArestas, posic);
        if(ar1){
            notation = createNotacao(cor, ar1->v1->x, ar1->v1->y, ar1->v2->x, ar1->v2->y, "");
            svgCode = createLine(notation);
            Lista_insert(result, svgCode);
        }
        posic  = Lista_getNext(listaArestas, posic);
    }    
    if(end != NULL){
        ar1 = Lista_get(listaArestas, Lista_getLast(listaArestas));    
        notation = createNotacao(cor, ar1->v2->x, ar1->v2->y, *end, *(end+1), "");
        svgCode = createLine(notation);
        Lista_insert(result, svgCode);
    }
    
    return result;
}

/*void GrafoD_toWhite(void* grafo){
    Grafo *gr;
    gr = (Grafo*) grafo;
    Lista ls;
     ls = KDT_getAll(gr->vertices);
    void *posic; posic = Lista_getFirst(ls);
    while(1){
        void *item; item = Lista_get(ls, posic);
        if(item){
            VerticeV *aux;
            aux = (VerticeV*) item;
            aux->estado = 0;
        }else{break;}
        posic = Lista_getNext(ls, posic);
    }
}*/

//desbloqueia o grafo
void GrafoD_unlock(void* grafo){
    Grafo *gr;
    gr = (Grafo*) grafo;
    Lista ls;
    ls = getAll_hashtable(gr->left);
    void *posic; posic = Lista_getFirst(ls);
    while(1){
        void *item; item = Lista_get(ls, posic);
        if(item){
            ArestaP *aux;
            aux = (ArestaP*) item;
            aux->tam = aux->disable;
        }else{break;}
        posic = Lista_getNext(ls, posic);
    }

    ls = KDT_getAll(gr->vertices);
    posic = Lista_getFirst(ls);
    while(1){
        void *item; item = Lista_get(ls, posic);
        if(item){
            VerticeV *aux;
            aux = (VerticeV*) item;
            aux->disable = 0;
        }else{break;}
        posic = Lista_getNext(ls, posic);
    }
}

//Bloqueia os vertices que estao nessa area
void GrafoD_blockVertices(void* grafo,double w,double h,double x,double y){
    Grafo *gr;
    gr = (Grafo*) grafo;
    VerticeV *refA; refA = (VerticeV*) calloc(1, sizeof(VerticeV));
    VerticeV *refB; refB = (VerticeV*) calloc(1, sizeof(VerticeV));
    refA->x = x;
    refA->y = y;
    refB->x = x+w;
    refB->y = y+h;
    Lista toBlock = itensInsideArea(gr->vertices, refA, refB);
    void *posic; posic = Lista_getFirst(toBlock);
    while(1){
        void *item; item = Lista_get(toBlock, posic);
        if(item){
            VerticeV *aux;
            aux = (VerticeV*) item;
            aux->disable = 1;
        }else{break;}
        posic = Lista_getNext(toBlock, posic);
    }
}

int intercept(double alpha, double beta, double w, double h, double x, double y){
    double x2 = x+w;
    double y2 = y+h;
    double fx1, fx2, fy1, fy2;
    fx1 = alpha*x  + beta;
    fx2 = alpha*x2 + beta;
    fy1 = (y  - beta)/alpha;
    fy2 = (y2 - beta)/alpha;
    
    if(fx1 >= y && fx1 <= y2) return 1;
    if(fx2 >= y && fx2 <= y2) return 1;
    if(fy1 >= x && fy1 <= x2) return 1;
    if(fy2 >= x && fy2 <= x2) return 1;
    return 0;
 }

void blockArestas(void *grafo, double w,double h,double x,double y){
    Grafo *gr;
    gr = (Grafo*) grafo;
    Lista ls = getAll_hashtable(gr->right);
    void* posic;
    
    posic = Lista_getFirst(ls);
    while(posic){
        ArestaP *atual = (ArestaP*) Lista_get(ls, posic);
        //verifica se aresta intercepta
        double alpha, beta;
        alpha = (atual->v2->y - atual->v1->y) / (atual->v2->x - atual->v1->x);
        beta = atual->v1->y - (alpha* atual->v1->x);
        //se intercepta
        if((atual->v2->x > x+w && atual->v1->x > x+h) || (atual->v2->x < x && atual->v1->x < x)){
            posic = Lista_getNext(ls, posic); continue;    
        } 
        if((atual->v2->y > y+h && atual->v1->y > y+h) || (atual->v2->y < y && atual->v1->y < y)){
            posic = Lista_getNext(ls, posic); continue;    
        } 
        if(intercept(alpha, beta, w, h, x, y)){
            //blokeia a aresta
            atual->disable = atual->tam;
            atual->tam = __DBL_MAX__;
        }
        posic = Lista_getNext(ls, posic);
     }
    //fim percorre
}

void GrafoD_blockArestas(void* grafo,double w,double h,double x,double y){  
    blockArestas(grafo, w, h, x, y);
}

double getPos(void *ar, int i){

    VerticeV *vert;

    vert = (VerticeV *) ar;

    if(i==0){
        return vert->x;
    }else if(i==1){
        return vert->y;
    }
}

void* getKDT(void *grafo){

    Grafo *gd;

    gd = (Grafo *) grafo;

    return gd->vertices;
}

void* getAresta(void *v){
    VerticeV *ver;
    ver = (VerticeV*) v;
    return ver->aresta;
}


//Dijkstra
//------------------------------------------------------------------------------------------------------------------------------------------

//Recebe uma lista de Vertices, e retorna uma tabela de arestas



ArestaP*** arestaTable(void* grafo, int size, int mod){
    int i, j;
    Grafo* gr;
    gr = (Grafo*) grafo;
    Lista ls = getAll_hashtable(gr->right);
    size = Lista_lenght(ls);
    ArestaP ***result;
    result = (ArestaP***) calloc(size, sizeof(ArestaP**));
    for(i = 0; i < size; i++){
        result[i] = (ArestaP**) calloc(size, sizeof(ArestaP*));
    }
    void* posic;
    size = Lista_lenght(ls);
    i=0;
    posic = Lista_getFirst(ls);
    while(posic){
        ArestaP* item = Lista_get(ls, posic);
        result[item->v1->idDijkstra][item->v2->idDijkstra] = item;
        item->peso0 = (item->tam);
        item->peso1 = (item->speed==0? 0 : item->tam/item->speed);
        posic = Lista_getNext(ls, posic);
        i++;
    }

    return result;

}

void* inicListVert(Lista vertices){
    void *posic, *item;
    ArestaP *atual;
    int i, j;
    int size = Lista_lenght(vertices);

    VerticeV **verts;
    verts = (VerticeV**) calloc(size, sizeof(VerticeV*));
    posic = Lista_getFirst(vertices);
    i = 0;

    while(posic!=NULL){
        VerticeV* it = (VerticeV*) Lista_get(vertices, posic);
        if(it && it->disable==0){
            verts[i] = (VerticeV*) it;
            verts[i]->idDijkstra = i;
            i++;
        }
        posic = Lista_getNext(vertices, posic);
    }
}

void *** GrafoD_arestaTable(void* grafo,int mod){
    Grafo *gr; gr = (Grafo*)grafo;
    Lista vertices;
    vertices = KDT_getAll(gr->vertices);
    int size = Lista_lenght(vertices);
    inicListVert(vertices);
    return (void***) arestaTable(grafo, size, mod);
}

//Recebe uma tabela de arestas e o numero de vertices, retorna uma tabela do tamanho das arestas
double **distTable(ArestaP ***arestas, int sizeVertices){
    void *posic, *item;
    ArestaP *atual;
    int i, j;

    
    double **result;
    result = (double**) calloc(sizeVertices, sizeof(double*));
    for(i=0; i<sizeVertices; i++)
        result[i] = (double*) calloc(sizeVertices, sizeof(double));

    for(i = 0; i < sizeVertices; i++){
        for(j = 0; j < sizeVertices; j++){
            if(arestas[i][j] == NULL){
                result[i][j] = -1.0;
            }else{
                double aux = (arestas[i][j]->tam)<0.0?(arestas[i][j]->tam)*(-1.0):(arestas[i][j]->tam);
                result[i][j] = aux;
            }
            
        }
    }
    return result;
}


//Recebe uma tabela de arestas e o numero de vertices, retorna uma tabela do tempo das arestas
double **timeTable(ArestaP ***arestas, int sizeVertices){
    void *posic, *item;
    ArestaP *atual;
    int i, j;

    
    double **result;
    result = (double**) calloc(sizeVertices, sizeof(double*));
    for(i=0; i<sizeVertices; i++)
        result[i] = (double*) calloc(sizeVertices, sizeof(double));

    for(i = 0; i < sizeVertices; i++){
        for(j = 0; j < sizeVertices; j++){
            if(arestas[i][j] == NULL){
                result[i][j] = -1.0;
            }else{
                double a = (arestas[i][j]->tam)<0.0?(arestas[i][j]->tam)*(-1.0):(arestas[i][j]->tam);
                double b = arestas[i][j]->speed;
                double aux = b!=0?(a/b):0.0;
                result[i][j] = aux;
            }
        }
    }
    return result;
}

int minDistance(int dist[], int sptSet[], int qtd) 
{ 
    int min, min_index; 
    min = INT_MAX;

    for (int v = 0; v < qtd; v++){
        if (sptSet[v] == 0 && dist[v] < min){
            min = dist[v], min_index = v; 
        }
    }
    return min_index; 
} 



void dijkstra(ArestaP*** arestas, int inicial, int final, int qtd, int mod)
{
	int dist[qtd];
	int sptSet[qtd];
    void *list;

	for (int i = 0; i < qtd; i++) 
	    dist[i] = INT_MAX, sptSet[i] = 0; 

	dist[inicial] = 0; 

	for (int count = 0; count < qtd; count++)                                   
	{ 
	    int u = minDistance(dist, sptSet, qtd);
        sptSet[u] = 1; 
        for (int v = 0; v < qtd; v++){
            if (!sptSet[v]){
                if(arestas[u][v] != NULL){
                    if(dist[u] != INT_MAX){
                        double peso = mod?arestas[u][v]->peso1:arestas[u][v]->peso0;
                        if(dist[u]+peso < dist[v]){
                            ArestaP *ar = (ArestaP*) arestas[u][v];
                            ar->v2->anteriorDijkstra = ar;
                            dist[v] = dist[u] + peso;      
                        }
                    }
                }                    
            }
        }
    }
}

int minDistanceA(int dist[], int sptSet[], int qtd, VerticeV* vFinal[], int u) 
{ 
    int min, min_index; 
    min = INT_MAX;

    for (int v = 0; v < qtd; v++){

        double distCalc = dist[v]==INT_MAX?INT_MAX:(dist[v] + sqrt( pow(vFinal[u]->x - vFinal[v]->x, 2) + pow(vFinal[u]->y - vFinal[v]->y, 2) ) );
        if (sptSet[v] == 0 && distCalc < min){
            min = distCalc;
            min_index = v; 
        }
    }
    return min_index; 
} 

void dijkstraA(ArestaP*** arestas, int inicial, int final, int qtd, int mod, Lista vertices)
{
	int dist[qtd];
	int sptSet[qtd];
    void *list;

    VerticeV* vFinal[qtd];
    int vsize = Lista_lenght(vertices);
    void* Posic = Lista_getFirst(vertices);
    while(Posic){
        VerticeV* aux = (VerticeV*) Lista_get(vertices, Posic);
        if(aux->disable == 0){
            vFinal[aux->idDijkstra] = aux;
        }else{
            if(aux->idDijkstra >= 0){
                for(int i=0; i<vsize; i++){
                    arestas[i][aux->idDijkstra] = NULL;
                    arestas[aux->idDijkstra][i] = NULL;
                }
            }
        }
        Posic = Lista_getNext(vertices, Posic);
    }


	for (int i = 0; i < qtd; i++) 
	    dist[i] = INT_MAX, sptSet[i] = 0; 

	dist[inicial] = 0; 

	for (int count = 0; count < qtd; count++)                                   
	{ 
	    int u = minDistanceA(dist, sptSet, qtd, vFinal, final);
        if(u == final){
            break;
        }
        sptSet[u] = 1; 
        for (int v = 0; v < qtd; v++){
            if (!sptSet[v]){
                if(arestas[u][v] != NULL){
                    if(dist[u] != INT_MAX){
                        double peso = mod?arestas[u][v]->peso1:arestas[u][v]->peso0;
                        if(dist[u]+peso < dist[v]){
                            ArestaP *ar = (ArestaP*) arestas[u][v];
                            ar->v2->anteriorDijkstra = ar;
                            dist[v] = dist[u] + peso;      
                        }
                    }
                }                    
            }
        }
        if(u == final){
            break;
        }
    }
}

void limparAnterior(void* grafo){
    Grafo* gr;
    gr = (Grafo*) grafo;
    Lista ls = KDT_getAll(gr->vertices);
    void* posic;
    VerticeV* item;

    posic = Lista_getFirst(ls);
    while(posic!=NULL){
        item = (VerticeV*) Lista_get(ls, posic);
        if(item){
            item->anteriorDijkstra = NULL;
            posic = Lista_getNext(ls, posic);
        }else{
            break;
        }
    }

}


Lista caminho(void* grafo,double* idStart,double* idEnd, int mod, void*** ar){
    limparAnterior(grafo);
    Grafo* gr;
    ArestaP*** arestas;
    double** pesos;
    int inicial;
    int final;
    gr = (Grafo*) grafo;
    Lista vertices;
    vertices = KDT_getAll(gr->vertices);
    int size = Lista_lenght(vertices);
    //chamar rota -> requisitos
    //tabela de arestas
    
    if(ar==NULL){
        inicListVert(vertices);
        arestas = arestaTable(grafo, size, mod);
    }else{
        arestas = (ArestaP***) ar;
    }
    //tabela de pesos
    
    
    VerticeV *aux;
    VerticeV* auxV;

    //indice do vertice inicia
    aux = (VerticeV*) calloc(1, sizeof(VerticeV));
    aux->id = "";
    aux->x = *(idStart);
    aux->y = *(idStart+1);
    auxV = (VerticeV*) closestNeibord(gr->vertices,(void*)  aux);
    if(auxV->disable == 1){
        return NULL;
    }


    // auxV = (VerticeV*) closest(gr->vertices, aux);
    inicial = auxV->idDijkstra; 

    //indice do vertice final
    aux = (VerticeV*) calloc(1, sizeof(VerticeV));
    aux->id = "";
    aux->x = *(idEnd);
    aux->y = *(idEnd+1);
    auxV = (VerticeV*) closestNeibord(gr->vertices,(void*) aux);
    if(auxV->disable == 1){
        KDT kdt_aux = KDT_create(compareGD,2, freeVerticeV);
        Lista ls = KDT_getAll(gr->vertices);
        void* posic = Lista_getFirst(ls);
        while(posic){
            VerticeV* it = (VerticeV*) Lista_get(ls,posic);
            if(!it->disable)
                KDT_insert(kdt_aux, it);
            posic = Lista_getNext(ls, posic);
        }
        auxV = (VerticeV*) closestNeibord(kdt_aux,(void*)  aux);
        freeKDTreeSimple(kdt_aux);
    }
    // auxV = (VerticeV*) closest(gr->vertices, aux);
    final = auxV->idDijkstra;


    if(inicial == final){
        return Lista_createLista();
    }
    //dijkstra(arestas, inicial, final, size, mod);//textando
    dijkstraA(arestas, inicial, final, size, mod, vertices);//textando

    if(auxV->anteriorDijkstra == NULL){
        return NULL;
    }
    Lista ls = Lista_createLista();
    while(auxV->anteriorDijkstra != NULL){
        if(Lista_getFirst(ls) == NULL){
            Lista_insert(ls, auxV->anteriorDijkstra);
        }else{
            void* auxPosic;
            auxPosic = Lista_getFirst(ls);
            Lista_insertAfter(ls, auxPosic, auxV->anteriorDijkstra);
        }
        auxV = auxV->anteriorDijkstra->v1;
    }
    if(ar==NULL){
        int i;
        for(i = 0; i < size; i++){
            free(arestas[i]);
        }
        free(arestas);
        freeLista(vertices);
    }
    return ls;
}


char* grafoToSvg(void* grafo){
    Grafo *gr; gr = (Grafo*) grafo;
    void* posic;

    Lista aux  = KDT_getAll(gr->vertices);
    Lista aux2 = getAll_hashtable(gr->right);
    
    char* temp;
    char* result;
    
    result = (char*) calloc(Lista_lenght(aux)*150 + Lista_lenght(aux2)*300,sizeof(char));
    strcpy(result, "");

    posic = Lista_getFirst(aux);
    while(posic){
        VerticeV *itVert = (VerticeV*) Lista_get(aux, posic);
        temp = (char*) calloc(150, sizeof(char));
        sprintf(temp, "<circle cx=\"%f\" cy=\"%f\" r=\"10\" fill=\"BLACK\"/>\n", itVert->x, itVert->y);
        strcat(result, temp);
        posic = Lista_getNext(aux, posic);
    }

    posic = Lista_getFirst(aux2);
    while(posic){
        ArestaP *itArest = (ArestaP*) Lista_get(aux2, posic);
        temp = (char*) calloc(300, sizeof(char));
        sprintf(temp, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke-width=\"1\" stroke=\"BLACK\"/>\n<circle cx=\"%f\" cy=\"%f\" r=\"5\" fill=\"RED\"/>\n", itArest->v1->x, itArest->v1->y, itArest->v2->x, itArest->v2->y, (itArest->v2->x - (itArest->v2->x - itArest->v1->x)/10) , (itArest->v2->y - (itArest->v2->y - itArest->v1->y)/10) );
        strcat(result, temp);
        posic = Lista_getNext(aux2, posic);
    }
    return result;
}
