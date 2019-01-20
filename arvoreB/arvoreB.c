#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../ArqBin/ArqBin.h"
#include "../Lista/lista.h"

typedef struct No{
    int pai;
	int total_elementos;
	int max_elementos;
	int total_filhos;
	int max_filhos;
    int minha_pos;
    double* elementos;
	int* elementoData;
	int* filhos;
}Node;

typedef struct{
    double (*compare)(void*, void*);
    int blockSize;
    Node* raiz;
    FILE* arq;
    char* Data;
	long int headerSize;
	void (*writer)(void* obj, int seek, void* arq);
	void (*reader)(void* obj, int seek, void* arq);
	void* (*allocar)();
}Tree;

typedef struct{
    int blockSize;
    int raiz;
    char* BFILE;
}Header;

typedef struct{
	double key;
	int data;
}info;

//prototip
int ler_disco(Tree* arvore, int seek, Node *folha);
void printNode(Tree* tree, Node* nd);
Node* inicializa_folha(int block);

//Funções Auxiliares

//testar se sizeof(Node) <= block
int calcTam(int block){
    block -= 6*sizeof(int);
    int result = block/(2*sizeof(int)+sizeof(double));
    return result;
}

//Funções Estruturais


Tree* BTREE_Carrega(char* bdName, double (*compare)(void*, void*), void (*writer)(void* obj, int seek, void* arq), void (*reader)(void* obj, int seek, void* arq), void* (*allocar)()){
	FILE* arq = fopen(bdName, "r+b");
	Header* hd = (Header*) malloc(sizeof(Header)); 
	hd->BFILE = malloc(55*sizeof(char));
	fread(&hd->blockSize, sizeof(int), 1, arq);
	fread(&hd->raiz, sizeof(int), 1, arq);
	for(int i = 0; i < 55; i++){
		fread(&hd->BFILE[i], sizeof(char), 1, arq);
	}
	fclose(arq);
	Tree* result = (Tree*) malloc(sizeof(Tree));
	result->compare = compare;
	result->blockSize = hd->blockSize;
	result->Data = hd->BFILE;
	result->arq = fopen(bdName, "r+b");
	result->raiz = inicializa_folha(hd->blockSize);
	result->writer = writer;
	result->reader = reader;
	result->allocar = allocar;
	ler_disco(result, hd->raiz, result->raiz);
	result->headerSize = result->raiz->minha_pos;
	return result;

}

//testar se sizeof(Node) <= block
Node* inicializa_folha(int block) {
    int tam = calcTam(block);
	Node* folha = (Node*)malloc(sizeof(Node));

	folha->max_elementos = 2 * tam - 1;
	folha->pai = -1;
	folha->total_elementos = 0;
	folha->total_filhos = 0;
	folha->minha_pos = -1;
	folha->max_filhos = 2 * tam;

	folha->elementos    = (double*) malloc(sizeof(double)*(2 * tam - 1));
    folha->elementoData = (int*) 	malloc(sizeof(int)* (2 * tam -1));
	folha->filhos       = (int*) 	malloc(sizeof(int) * 2 * tam);


	for (int i = 0; i < folha->max_elementos; i++){
		folha->elementos[i] = -1;
        folha->elementoData[i] = -1;
    }
	for (int i = 0; i < folha->max_filhos; i++)
		folha->filhos[i] = -1;

	
	return folha;
}

int sizeNode(Tree* tree){
	Node* nd = inicializa_folha(tree->blockSize);
	int result = sizeof(nd);
	free(nd);
	return result;
}

//compare compara a distancia entre os objetos retorna 0 se o elemento for igual, 
// negativo se estiver antes e positivo se estiver depois do obj comparado
// o primeiro é o objeto de referencia, o segundo o da  celula
Tree* BTREE_inicializa(int tam, char*bdName, int objSize, double (*compare)(void*, void*), void (*writer)(void* obj, int seek, void* arq), void (*reader)(void* obj, int seek, void* arq), void* (*allocar)()) {
	Tree* arvore = (Tree*)malloc(sizeof(Tree));
    arvore->compare = compare;
    arvore->blockSize = tam;
	arvore->raiz = NULL;
	arvore->arq = fopen(bdName, "w+b");
	arvore->writer = writer;
	arvore->reader = reader;
	arvore->allocar = allocar;
    char* dataPath = (char*) malloc(sizeof(char)*55);
    strcpy(dataPath, bdName);
	for(int i=0; i<strlen(dataPath); i++) if(*(dataPath+i) == '.') *(dataPath+i) = 0;
    strcat(dataPath, "_Data.dat");
    arvore->Data = dataPath;
	newArq(dataPath, objSize);
    
    Header *hd = (Header*)malloc(sizeof(Header));
    hd->blockSize = tam;
    hd->raiz = -1;
    hd->BFILE = dataPath;
    
    fwrite(&hd->blockSize, sizeof(int), 1, arvore->arq);
	fwrite(&hd->raiz, sizeof(int), 1, arvore->arq);
	for(int i = 0; i<55; i++)
		fwrite(&hd->BFILE[i], sizeof(char), 1, arvore->arq);
	

	arvore->headerSize = ftell(arvore->arq);
	fclose(arvore->arq);
	arvore->arq = fopen(bdName, "r+b");
    return arvore;
}

//Leitura do Node no indice Seek
int ler_disco(Tree* arvore, int seek, Node *folha)
{
	// do seek na posição do arquivo
	if (fseek(arvore->arq, seek, SEEK_SET) == -1)
		return 0;
	// armazeno em um buffer
	// folha = inicializa_folha(arvore->blockSize);
	
	int fSize = sizeof(folha);
	
	fread(folha, 				fSize, 1, arvore->arq);
	for(int i=0; i < folha->max_elementos; i++)
		fread(&folha->elementos[i], 	sizeof(double), 1, arvore->arq);
	for(int i=0; i < folha->max_elementos; i++)
		fread(&folha->elementoData[i], 	sizeof(int), 	1, arvore->arq);
	for(int i=0; i < folha->max_filhos; i++)
		fread(&folha->filhos[i], 		sizeof(int), 	1, arvore->arq);

	
	
	
	folha->minha_pos = seek;

	return 1;
}

int escrever_disco(Tree* arvore, int seek, Node *folha)
{
    // Insiro o pointer na posição que eu passei e escrevo o nó
	if (fseek(arvore->arq, seek, SEEK_SET) == -1)
		return 0;
	if (folha->minha_pos == -1)
		folha->minha_pos = ftell(arvore->arq);
	
	int fSize = sizeof(folha);
 
	
	fwrite((void *)folha				, fSize, 1, arvore->arq);
	for(int i=0; i < folha->max_elementos; i++)
		fwrite(&folha->elementos[i], sizeof(double), 1, arvore->arq);
	for(int i=0; i < folha->max_elementos; i++)
		fwrite(&folha->elementoData[i], sizeof(int), 1, arvore->arq);
	for(int i=0; i < folha->max_filhos; i++)
		fwrite(&folha->filhos[i], sizeof(int), 1, arvore->arq);
	
	return 1;
}

//retorna o indice do obj esta na folha
int busca_elemento(Tree* arvore, Node* f, double valor, void* obj) {
	for (int i = 0; i < f->max_elementos; i++) {
		if (f->elementos[i] == valor) {
            void* ob = getObject(arvore->Data, f->elementoData[i], arvore->reader, arvore->allocar);
            if(arvore->compare(ob, obj)==0)
			return f->elementoData[i];
		}
	}
	return -1;
}

//retorna o indice do elemento esta na folha
int busca_indice(Tree* arvore, Node* f, double valor, double obj) {
	for (int i = 0; i < f->max_elementos; i++) {
		if (f->elementos[i] == valor) {
            if(f->elementoData[i] == obj)
			return i;
		}
	}
	return -1;
}


/* metodo para buscar em uma folha,
 sendo este recursivo e armazenado apenas um no na memoria
 O retorno, é o obj
 */
void* _busca(Tree* arvore, Node* folha, double valor, void* obj) {	
	int indice = busca_elemento(arvore, folha, valor, obj);
    if (indice >= 0) {
		return getObject(arvore->Data, folha->elementoData[indice], arvore->reader, arvore->allocar);
	}
	else {
		int i;
		for (i = 0; i < folha->max_elementos; i++) {
			if(folha->elementos[i] == -1) break;
			if (folha->filhos[i] != -1 && valor <= folha->elementos[i]) {
				Node* temp = inicializa_folha(arvore->blockSize);
				ler_disco(arvore, folha->filhos[i], temp);
                int res = busca_elemento(arvore, temp, valor, obj);
				if (res >= 0) 
				{
					free(temp);
					return getObject(arvore->Data, res, arvore->reader, arvore->allocar);
				}
                return _busca(arvore, temp, valor, obj);
				free(temp);
			}
		}
		if (folha->filhos[i] != -1) {
				Node* temp = inicializa_folha(arvore->blockSize);
				ler_disco(arvore, folha->filhos[i], temp);
                int res = busca_elemento(arvore, temp, valor, obj);
				if (res >= 0) 
				{
					free(temp);
					return getObject(arvore->Data, res, arvore->reader, arvore->allocar);
				}
                return _busca(arvore, temp, valor, obj);
				free(temp);
		}
	}
	return NULL;
}

void* BTREE_busca(Tree* arvore, double valor, void* obj) {
	return _busca(arvore, arvore->raiz, valor, obj);
}




// ordena os elementos da folha
void ordenar(Node* f) {
	for(int i=0; i<f->max_elementos; i++){
		for(int j=i; j<f->max_elementos; j++){
			if((f->elementos[i] > f->elementos[j] && f->elementos[j] != -1) || (f->elementos[i] == -1 && f->elementos[j] != -1)){
				double akey = f->elementos[i];
				int aData = f->elementoData[i];
				int aFilho = f->filhos[i];
				f->elementos[i] = f->elementos[j];
				f->elementoData[i] = f->elementoData[j];
				f->filhos[i] = f->filhos[j];
				f->elementos[j] = akey;
				f->elementoData[j] = aData;
				f->filhos[j] = aFilho;
			}
		}
	}
	for(int i=0; i<f->max_filhos; i++){
		if(f->filhos[i] == -1){
			for(int j = i+1; j<f->max_filhos; j++){
				if(f->filhos[j] != -1){
					f->filhos[i] = f->filhos[j];
					f->filhos[j] = -1;
					break;
				}
			}
		}
	}
}

void adicionar_elemento(Tree* arvore,  Node* folha, double elem, int obj) {
	int child = -1;
	for (int i = 0; i < folha->max_elementos; i++) {
		if (elem < folha->elementos[i]) {
			double elemAux = folha->elementos[i];
			int dAux = folha->elementoData[i];
			int cAux = folha->filhos[i+1];
			folha->elementos[i] = elem;
            folha->elementoData[i] = obj;
			folha->filhos[i+1] = child;
			elem = elemAux;
			obj = dAux;
			child = cAux;
		}
		if(folha->elementos[i] == -1){
			double elemAux = folha->elementos[i];
			int dAux = folha->elementoData[i];
			int cAux = folha->filhos[i+1];
			folha->elementos[i] = elem;
            folha->elementoData[i] = obj;
			folha->filhos[i+1] = child;
			elem = elemAux;
			obj = dAux;
			child = cAux;
			break;
		}
	}
	folha->total_elementos++;
}


int add_filho(Node* pai, int seek) {
	for (int i = 0; i < pai->max_filhos; i++) {
		if (pai->filhos[i] == -1) {
			pai->filhos[i] = seek;
			pai->total_filhos++;
			break;
		}
	}
	return 1;
}

int total_filhos(Node* f) {
	int total = 0;
	for (int i = 0; i < f->max_filhos; i++) {
		if (f->filhos[i] != -1)
			total++;
	}
	return total;
}

int total_elementos(Node* f) {
	int total = 0;
	for (int i = 0; i < f->max_elementos; i++)
	{
		if (f->elementos[i] != -1)
			total++;
	}
	return total;
}

//refazer
int split(Tree* arvore, Node* pai, double valor, int obj) {
	//função que splita a raiz
	double valores[pai->max_elementos+1];
	int datas[pai->max_elementos+1];

	//lista os elementos, incluindo o novo
	for(int i=0; i < pai->max_elementos; i++){
		valores[i] = pai->elementos[i];
		datas[i] = pai->elementoData[i];
	}
	valores[pai->max_elementos] = valor;
	datas[pai->max_elementos] = obj;

	for(int i=0; i <= pai->max_elementos; i++){
		for(int j=i; j <= pai->max_elementos; j++){
			if(valores[i] > valores[j]){
				double valAux = valores[i];
				int dataAux = datas[i];
				valores[i] = valores[j];
				datas[i] = datas[j];
				valores[j] = valAux;
				datas[j] = dataAux;
			}
		}
	}


	//0 até meio-1 -> filho1 -> filhos e elementos
	int meio = pai->max_elementos/2;

	Node* filho1 = inicializa_folha(arvore->blockSize);
	Node* filho2 = inicializa_folha(arvore->blockSize);

	//meio + 1 -> maxElementos -> filho2 -> filhos e elementos
	filho1->total_elementos = 0;
	for(int i=0; i < meio; i++){
		filho1->elementos[i] = valores[i];
		filho1->elementoData[i] = datas[i];
		filho1->total_elementos++;
	}

	filho2->total_elementos = 0;
	for(int i=meio+1; i <= pai->max_elementos; i++){
		filho2->elementos[i-(meio+1)] = valores[i];
		filho2->elementoData[i-(meio+1)] = datas[i];
		filho2->total_elementos++;
	}

	for(int i = 0; i < meio; i++)
		filho1->filhos[i] = pai->filhos[i];

	for(int i = meio+1; i < pai->max_filhos; i++)
		filho2->filhos[i-(meio+1)] = pai->filhos[i];



	int posA, posB;
	//filho[0] = filho 1
	filho1->pai = pai->minha_pos;
	fseek(arvore->arq, 0, SEEK_END);
	posA = ftell(arvore->arq);
	escrever_disco(arvore, posA, filho1);

	//filho[1] = filho 2
	filho2->pai = pai->minha_pos;
	// fseek(arvore->arq, 0, SEEK_END);
	posB = ftell(arvore->arq);
	escrever_disco(arvore, posB, filho2);

	//raiz -> limpa filhos e elementos
	for(int i = 0; i < pai->max_elementos; i++){
		pai->elementos[i] = -1;
		pai->elementoData[i] = -1;
	}

	for(int i = 0; i < pai->max_filhos; i++)
		pai->filhos[i] = -1;

	//elemento[0] = meio e meio data
	pai->total_elementos = 1;
	pai->total_filhos = 2;
	pai->elementos[0] = valores[meio];
	pai->elementoData[0] = datas[meio];
	pai->filhos[0] = posA;
	pai->filhos[1] = posB;

	//atualiza o arquivo
	escrever_disco(arvore, pai->minha_pos, pai);

	return 1;
}

int retira_elemento(Tree* arvore, Node* folha, double elem, void* obj) {
	for (int i = 0; i < folha->max_elementos; i++) {
		if (folha->elementos[i] == elem) {
            void* ob = getObject(arvore->Data, folha->elementoData[i], arvore->reader, arvore->allocar);
            if(arvore->compare(ob, obj) == 0){
                folha->elementos[i] = -1;
                deleteObject(arvore->Data, folha->elementoData[i]);
                folha->elementoData[i] = -1;
				folha->total_elementos--;
                return i;
            }
		}
	}
	return -1;
}

info* searchRight(Tree* arvore, Node* folha){
	for(int i = folha->max_elementos-1; i>=0; i--){
		if(folha->elementos[i] != -1){
			if(folha->filhos[i+1] != -1){
				Node* nd = inicializa_folha(arvore->blockSize);
				ler_disco(arvore, folha->filhos[i+1], nd);
				return searchRight(arvore, nd);
			}
			info* result = (info*) malloc(sizeof(info));
			result->key = folha->elementos[i];
			result->data = folha->elementoData[i];
			folha->elementos[i] = -1;
			folha->elementos[i] = -1;
			escrever_disco(arvore, folha->minha_pos, folha);
			return result;
		}
	}
}

void merge(Tree* arvore, Node* folha){
	if(folha->total_elementos >= folha->max_elementos/2) return;
	if(folha->pai == -1) return;

	Node* pai = inicializa_folha(arvore->blockSize);
	ler_disco(arvore, folha->pai, pai);

	int i;
	for(i=0; i<pai->max_filhos; i++)
		if(pai->filhos[i] == folha->minha_pos) break;

	Node* dir = inicializa_folha(arvore->blockSize);
	if(i+i < pai->max_filhos && pai->filhos[i+1] != -1 ){
		ler_disco(arvore, pai->filhos[i+1], dir);
	}else{
		free(dir);
		dir = NULL;
	}

	Node* esq = inicializa_folha(arvore->blockSize);
	if(i-1 >=0 && pai->filhos[i-1] != -1){
		ler_disco(arvore, pai->filhos[i-1], esq);
	}else{
		free(esq);
		esq = NULL;
	}
	if(dir == NULL && esq == NULL){
		double elem[folha->max_elementos*2];
		int dats[folha->max_elementos*2];

		int k=0;
		for(int j=0; j<folha->max_elementos; j++){
			if(folha->elementos[j] == -1) break;
			elem[k] = folha->elementos[j];
			dats[k] = folha->elementoData[j];
			k++;
		}
		for(int j=0; j<pai->max_elementos; j++){
			elem[k] = pai->elementos[j];
			dats[k] = pai->elementos[j];
			k++;
		}
		
		if(k+1 < pai->max_elementos){
			pai->filhos[i] = -1;
			for(int i=0; i < k+1; i++){
				pai->elementos[i] = elem[i];
				pai->elementoData[i] = dats[i];
			}
			pai->total_elementos = k;
			pai->total_filhos = 0;
		}else{
			pai->filhos[i] = -1;
			for(int i=0; i < k+1; i++){
				pai->elementos[i] = -1;
				pai->elementoData[i] = -1;
			}
			pai->total_elementos = 0;
			pai->total_filhos = 0;

			for(int i=0; i < k+1; i++){
				adicionar_elemento(arvore, pai, elem[i], dats[i]);
			}
			
		}
		

	}

	if(dir == NULL && esq != NULL){
		double elem[folha->max_elementos*2];
		int dats[folha->max_elementos*2];

		int k=0;
		for(int j=0; j<folha->max_elementos; j++){
			if(folha->elementos[j] == -1) break;
			elem[k] = folha->elementos[j];
			dats[k] = folha->elementoData[j];
			k++;
		}

		for(int j=0; j<esq->max_elementos; j++){
			if(esq->elementos[j] == -1) break;
			elem[k] = esq->elementos[j];
			dats[k] = esq->elementoData[j];
			k++;
		}
		elem[k] = pai->elementos[i-1];
		dats[k] = pai->elementoData[i-1];

		if(k+1 < esq->max_elementos){
			for(int j=0; j<esq->max_elementos; j++){
				esq->elementos[j] = -1;
				esq->elementoData[j] = -1;
			}
			for(int j=0; j<=k; j++){
				esq->elementos[j] = elem[j];
				esq->elementoData[j] = dats[j];
			}
			esq->total_elementos = k;
			ordenar(esq);

			pai->elementos[i-1] = -1;
			pai->elementoData[i-1] = -1;
			pai->filhos[i] = -1;
			pai->total_elementos--;
			if(pai->total_elementos == 0){
				esq->minha_pos = pai->minha_pos;
			}

			ordenar(pai);
			ordenar(esq);
			escrever_disco(arvore, pai->minha_pos, pai);
			escrever_disco(arvore, esq->minha_pos, esq);
			free(pai);
			free(esq);
		}else{

			for(int m=0; m<=k; m++){
				for(int n=m; n<=k; n++){
					if(elem[m] > elem[n]){
						double eAux = elem[m];
						int dAux = dats[m];
						elem[m] = elem[n];
						dats[m] = dats[n];
						elem[n] = eAux;
						dats[n] = dAux;
					}
				}
			}

			int meio = k/2;
			pai->elementos[i-1] = elem[meio];
			pai->elementoData[i-1] = dats[meio];
			for(int j=0; j<esq->max_elementos; j++){
				esq->elementos[j] = -1;
				esq->elementoData[j] = -1;
			}
			for(int j=0; j<meio; j++){
				esq->elementos[j] = elem[j];
				esq->elementoData[j] = dats[j];
			}
			esq->total_elementos = meio;

			for(int j=(meio+1); j<=k; j++){
				folha->elementos[j-(meio+1)] = elem[j];
				folha->elementoData[j-(meio+1)] = dats[j];
			}
			folha->total_elementos = k-(meio);

			ordenar(pai);
			ordenar(esq);
			ordenar(folha);
			escrever_disco(arvore, pai->minha_pos, pai);
			escrever_disco(arvore, esq->minha_pos, esq);
			escrever_disco(arvore, folha->minha_pos, folha);


		}
		return;
	}
	if(esq == NULL && dir != NULL){
		double elem[folha->max_elementos*2];
		int dats[folha->max_elementos*2];

		int k=0;
		for(int j=0; j<folha->max_elementos; j++){
			if(folha->elementos[j] == -1) break;
			elem[k] = folha->elementos[j];
			dats[k] = folha->elementoData[j];
			k++;
		}

		for(int j=0; j<dir->max_elementos; j++){
			if(dir->elementos[j] == -1) break;
			elem[k] = dir->elementos[j];
			dats[k] = dir->elementoData[j];
			k++;
		}
		elem[k] = pai->elementos[i];
		dats[k] = pai->elementoData[i];

		if(k+1 < dir->max_elementos){
			for(int j=0; j<dir->max_elementos; j++){
				dir->elementos[j] = -1;
				dir->elementoData[j] = -1;
			}
			for(int j=0; j<=k; j++){
				dir->elementos[j] = elem[j];
				dir->elementoData[j] = dats[j];
			}
			dir->total_elementos = k;
			ordenar(dir);

			pai->elementos[i] = -1;
			pai->elementoData[i] = -1;
			pai->filhos[i] = -1;
			pai->total_elementos--;
			if(pai->total_elementos == 0){
				dir->minha_pos = pai->minha_pos;
			}
			ordenar(pai);
			ordenar(dir);

			escrever_disco(arvore, pai->minha_pos, pai);
			escrever_disco(arvore, dir->minha_pos, dir);
			free(pai);
			free(dir);
		}else{

			for(int m=0; m<=k; m++){
				for(int n=m; n<=k; n++){
					if(elem[m] > elem[n]){
						double eAux = elem[m];
						int dAux = dats[m];
						elem[m] = elem[n];
						dats[m] = dats[n];
						elem[n] = eAux;
						dats[n] = dAux;
					}
				}
			}

			int meio = k/2;
			pai->elementos[i] = elem[meio];
			pai->elementoData[i] = dats[meio];

			for(int j=0; j<meio; j++){
				folha->elementos[j] = elem[j];
				folha->elementoData[j] = dats[j];
			}
			folha->total_elementos = meio;
			for(int j=0; j<dir->max_elementos; j++){
				dir->elementos[j] = -1;
				dir->elementoData[j] = -1;
			}
			for(int j=(meio+1); j<=k; j++){
				dir->elementos[j-(meio+1)] = elem[j];
				dir->elementoData[j-(meio+1)] = dats[j];
			}
			dir->total_elementos = k-(meio);

			ordenar(pai);
			ordenar(dir);
			ordenar(folha);
			escrever_disco(arvore, pai->minha_pos, pai);
			escrever_disco(arvore, folha->minha_pos, folha);
			escrever_disco(arvore, dir->minha_pos, dir);


		}
		return;
	}


}

int _deletar(Tree* arvore, Node* folha, double valor, void* obj) {
	if (busca_elemento(arvore, folha, valor, obj) != -1) {
		int ctr = retira_elemento(arvore, folha, valor, obj);
		if(ctr >= 0){
			if(folha->filhos[ctr] != -1){
				Node* nd = inicializa_folha(arvore->blockSize);
				ler_disco(arvore, folha->filhos[ctr], nd);
				info* infoData = searchRight(arvore, nd);
				folha->elementos[ctr] = infoData->key;
				folha->elementoData[ctr] = infoData->data;
				escrever_disco(arvore, folha->minha_pos, folha);
			}
			return folha->minha_pos;
		}
		
	}
	else {
		int i;
		for (i = 0; i < folha->max_elementos; i++) {
			if(folha->elementos[i] == -1) break;
			if (folha->filhos[i] != -1 && valor <= folha->elementos[i]) {
				Node* temp = inicializa_folha(arvore->blockSize);
				ler_disco(arvore, folha->filhos[i], temp);
                int res = busca_elemento(arvore, temp, valor, obj);
				if (res >= 0) 
				{
					int ctr = retira_elemento(arvore, temp, valor, obj);
					if(ctr >= 0){
						if(temp->filhos[ctr] != -1){
							Node* nd = inicializa_folha(arvore->blockSize);
							ler_disco(arvore, temp->filhos[ctr], nd);
							info* infoData = searchRight(arvore, nd);
							temp->elementos[ctr] = infoData->key;
							temp->elementoData[ctr] = infoData->data;
						}
						escrever_disco(arvore, temp->minha_pos, temp);
						return temp->minha_pos;
					}
				}
                return _deletar(arvore, temp, valor, obj);
			}
		}
		if (folha->filhos[i] != -1) {
				Node* temp = inicializa_folha(arvore->blockSize);
				ler_disco(arvore, folha->filhos[i], temp);
                int res = busca_elemento(arvore, temp, valor, obj);
				if (res >= 0) 
				{
					int ctr = retira_elemento(arvore, temp, valor, obj);
					if(ctr >= 0){
						if(temp->filhos[ctr] != -1){
							Node* nd = inicializa_folha(arvore->blockSize);
							ler_disco(arvore, temp->filhos[ctr], nd);
							info* infoData = searchRight(arvore, nd);
							temp->elementos[ctr] = infoData->key;
							temp->elementoData[ctr] = infoData->data;
						}
						escrever_disco(arvore, temp->minha_pos, temp);
						return temp->minha_pos;
					}
				}
                return _deletar(arvore, temp, valor, obj);
		}
	}
	return -1;	
}

int BTREE_deletar(Tree* arvore, double valor, void* obj) {
	int i = _deletar(arvore, arvore->raiz, valor, obj);
	Node* nd = inicializa_folha(arvore->blockSize);
	ler_disco(arvore, i, nd);
	ordenar(nd);
	merge(arvore, nd);
	if(nd->pai == arvore->raiz->minha_pos){
		ler_disco(arvore, arvore->raiz->minha_pos, arvore->raiz);
	}
	escrever_disco(arvore, i, nd);
	return i;
}

//Verificar -> split em um no inferior, 
int explodir(Tree* arvore, Node* folha, double valor, int obj, int idfilho2) 
{
	//se qtd = max_elementos, faz split e se chama para inserir no pai, 
	if(folha->total_elementos < folha->max_elementos){
		adicionar_elemento(arvore, folha, valor, obj);
		int indice = busca_indice(arvore, folha, valor, obj);
		folha->filhos[indice+1] = idfilho2;
		escrever_disco(arvore, folha->minha_pos, folha);
		return 1;
	}
	if(folha->pai == -1){
		return split(arvore, folha, valor, obj);
	}
	//separo esse node em 2 node, relacionando com o pai

	//se pai == -1 -> criar nova raiz

	//inserir ob
	//função que splita a raiz
	double valores[folha->max_elementos+1];
	int datas[folha->max_elementos+1];

	//lista os elementos, incluindo o novo
	for(int i=0; i < folha->max_elementos; i++){
		valores[i] = folha->elementos[i];
		datas[i] = folha->elementoData[i];
	}
	valores[folha->max_elementos] = valor;
	datas[folha->max_elementos] = obj;

	for(int i=0; i <= folha->max_elementos; i++){
		for(int j=i; j <= folha->max_elementos; j++){
			if(valores[i] > valores[j]){
				double valAux = valores[i];
				int dataAux = datas[i];
				valores[i] = valores[j];
				datas[i] = datas[j];
				valores[j] = valAux;
				datas[j] = dataAux;
			}
		}
	}


	//0 até meio-1 -> filho1 -> filhos e elementos
	int meio = folha->max_elementos/2;

	Node* filho1 = inicializa_folha(arvore->blockSize);
	Node* filho2 = inicializa_folha(arvore->blockSize);

	//meio + 1 -> maxElementos -> filho2 -> filhos e elementos
	filho1->total_elementos = 0;
	for(int i=0; i < meio; i++){
		filho1->elementos[i] = valores[i];
		filho1->elementoData[i] = datas[i];
		filho1->total_elementos++;
	}

	filho2->total_elementos = 0;
	for(int i=meio+1; i <= folha->max_elementos; i++){
		filho2->elementos[i-(meio+1)] = valores[i];
		filho2->elementoData[i-(meio+1)] = datas[i];
		filho2->total_elementos++;
	}

	for(int i = 0; i < meio; i++)
		filho1->filhos[i] = folha->filhos[i];

	for(int i = meio+1; i < folha->max_filhos; i++)
		filho2->filhos[i-(meio+1)] = folha->filhos[i];



	//filho[0] = filho 1
	filho1->pai = folha->pai;
	filho1->minha_pos = folha->minha_pos;
	escrever_disco(arvore, filho1->minha_pos, filho1);

	//filho[1] = filho 2
	fseek(arvore->arq, 0, SEEK_END);
	int pos = ftell(arvore->arq);
	escrever_disco(arvore, pos, filho2);

	//chama a recurção para inserir acima
	Node* pai = inicializa_folha(arvore->blockSize);
	ler_disco(arvore, folha->pai, pai);

	// printf("\n\nExplodir\n");
	// printNode(arvore, filho1);
	// printNode(arvore, filho2);

	explodir(arvore, pai, valores[meio], datas[meio], pos);
	
	return 1;
}


int inserir_filho(Tree* arvore, Node* folha, double valor, double obj) 
{
	Node* temp = inicializa_folha(arvore->blockSize);
	if (folha->filhos[0] != -1)  
	{
		int i;
		for(i=0; i < folha->max_elementos; i++){
			if(valor < folha->elementos[i] || folha->elementos[i] == -1){
				break;
			}
		}
		ler_disco(arvore, folha->filhos[i], temp);
		if (total_elementos(temp) > 0 )
		{
				if (total_elementos(temp) == temp->max_elementos) 
				{
					// se essa porra estiver cheia vou ter que explodir caraaaalho
					// saco eim
					explodir(arvore, temp, valor, obj, -1);
					ler_disco(arvore, arvore->raiz->minha_pos, arvore->raiz);
					return 1;
				}
				// se nao tiver cheio, taca pau nesse carrinho.. 
				adicionar_elemento(arvore, temp, valor, obj);
				ordenar(temp);
				escrever_disco(arvore, temp->minha_pos, temp); // atualiza no disco
		}
		else 
		{
			// insere nessa porra que ele nao tem nenhum filho msm
			adicionar_elemento(arvore, temp, valor, obj);
			ordenar(temp);
			escrever_disco(arvore, temp->minha_pos, temp); // atualiza no disco
		}
	}

	return 1;
}

int BTREE_insere(Tree* arvore, double valor, void* obj) {
	int data = addObject(obj, arvore->Data, arvore->writer);
	if (arvore->raiz == NULL) {
		// Primeira folha a ser inserida na arvore..
		arvore->raiz = inicializa_folha(arvore->blockSize);

		Node* folha = arvore->raiz;
		adicionar_elemento(arvore, folha, valor, data);
		//folha->pai = 0; // posicao inicial desse cara..
		fseek(arvore->arq, 0, SEEK_END);	
		int pos = ftell(arvore->arq);
		folha->minha_pos = pos;
		if (escrever_disco(arvore, pos, folha)) {
			//printf("ok escrita\n");
		}
		ler_disco(arvore, pos, folha);
		rewind(arvore->arq);
		fseek(arvore->arq, sizeof(int), SEEK_SET);
		fwrite(&pos, sizeof(int), 1, arvore->arq);
	}
	else {
		Node* f = arvore->raiz;
		if (f->filhos[0] != -1) {
			// se esse cara tiver filhos, devo inserir neles..
			inserir_filho(arvore, f, valor, data);
		}
		else {
			if (total_elementos(f) == f->max_elementos) {
				split(arvore, f, valor, data);

			}
			else {
				// nao atingiu ainda o limite..
				adicionar_elemento(arvore, f, valor, data);
				// re-escrevo ele no arquivo
				escrever_disco(arvore, f->minha_pos, arvore->raiz);

			}
		}
	}

	return 0;
}

void _closestNeibord(Tree* tree, Node* no,double ref,void* reference,int ctr, double* minDist, void** minDistObj){
	for(int i=0; i<no->max_elementos; i++){
		if(no->elementos[i] != -1){
			void* obj = getObject(tree->Data, no->elementoData[i], tree->reader, tree->allocar);
			double dist = tree->compare(obj, reference);
			if(dist < 0) dist = -dist;
			if(dist < *minDist){
				if(ctr != 0 || minDist != 0){
					*minDist = dist;
					*minDistObj = obj;
				}
			}
		}
	}
	for(int i=0; i<no->max_elementos; i++){
		if(abs(ref - no->elementos[i]) < *minDist){
			if(ref - no->elementos[i] <= 0){
				if(no->filhos[i] != -1){
					Node* folha = inicializa_folha(tree->blockSize);
					ler_disco(tree, no->filhos[i], folha);
					_closestNeibord(tree, folha, ref, reference, ctr, minDist, minDistObj);
				}
				if(ref - no->elementos[i+1] >= 0){
					if(no->filhos[i+1] != -1){
						Node* folha = inicializa_folha(tree->blockSize);
						ler_disco(tree, no->filhos[i+1], folha);
						_closestNeibord(tree, folha, ref, reference, ctr, minDist, minDistObj);
					}
				}
			}else{
				if(no->filhos[i+1] != -1){
					Node* folha = inicializa_folha(tree->blockSize);
					ler_disco(tree, no->filhos[i+1], folha);
					_closestNeibord(tree, folha, ref, reference, ctr, minDist, minDistObj);
				}
			}
		}
	}
}

void* BTREE_closestNeibord(Tree* tree, double ref, void* reference, int ctr){
	if(tree->raiz == NULL)
		return NULL;

	if(tree->raiz->elementos[0] == -1)
		return NULL;


	double * minDist = (double*) malloc(sizeof(double));
	void** minDistObj = (void**) malloc(sizeof(void*));
	*minDist = 0;
	
	int i = 0;
	do{
		if(i >= tree->raiz->max_elementos) return NULL;
		if(tree->raiz->elementos[i] != -1){
			*minDistObj = getObject(tree->Data, tree->raiz->elementoData[i], tree->reader, tree->allocar);
			if(*minDistObj==NULL) continue;
			*minDist = abs(tree->compare(reference, *minDistObj));
		}
		i++;
	}while(*minDist==0 || ctr);

	Node* folha = inicializa_folha(tree->blockSize);
	ler_disco(tree, tree->raiz->minha_pos, folha);

	_closestNeibord(tree, folha, ref, reference, ctr, minDist, minDistObj);

	return *minDistObj;

}

//Libera a memoria principal
void BTREE_free(Tree* arvore){
	fclose(arvore->arq);
	free(arvore->Data);
	if(arvore->raiz != NULL){
		free(arvore->raiz);
	}
	free(arvore);
}

void printNode(Tree* tree, Node* nd){
	printf("\nLocal: %d", nd->minha_pos);
	
	printf("\nElementos: \n");
	for(int i = 0; i < nd->max_elementos; i++)
		printf("| %lf  |", nd->elementos[i]);

	printf("\nElementoData: \n");
	for(int i = 0; i < nd->max_elementos; i++)
		printf("| %d  |", nd->elementoData[i]);

	printf("\nFilhos: \n");
	for(int i = 0; i < nd->max_filhos; i++)
		printf("| %d  |", nd->filhos[i]);

	for(int i = 0; i < nd->max_filhos; i++){
		if(nd->filhos[i] != -1){
			Node* node = inicializa_folha(tree->blockSize);
			ler_disco(tree, nd->filhos[i], node);
			printNode(tree, node);
		}
	}
	

}
void BTREE_PRINT(Tree* arvore){
	if(arvore->raiz!=NULL){
		printNode(arvore, arvore->raiz);
	}
}

Lista BTREE_getAll(Tree* arvore){ return getAll(arvore->Data, arvore->reader, arvore->allocar);}

void _Inside(Tree* tree,Node* folha,double valorInicial,void* refInicial,double valorFinal,void* refFinal,Lista ls){
	for(int i=0; i<folha->max_elementos; i++){
		if(folha->elementos[i] == -1) break;
		void* obj = getObject(tree->Data, folha->elementoData[i], tree->reader, tree->allocar);
		double left, right;
		left = tree->compare(refInicial, obj);
		right = tree->compare(obj, refFinal);
		//Verificar se o teste esta  funcionando
		if(left >= 0 && right>=0){
			Lista_insert(ls, obj);
		}
	}
	int i;
	for(i=0; i<folha->max_elementos; i++){
		if(folha->elementos[i] == -1 || folha->filhos[i] == -1) break;
		if(valorInicial <= folha->elementos[i] && folha->elementos[i] <= valorFinal){
			Node *nd = inicializa_folha(tree->blockSize);
			ler_disco(tree, folha->filhos[i], nd);
			_Inside(tree, nd, valorInicial, refInicial, valorFinal, refFinal, ls);
		}
	}
	if(folha->elementos[i-1] <= valorFinal && folha->filhos[i] != -1){
			Node *nd = inicializa_folha(tree->blockSize);
			ler_disco(tree, folha->filhos[i], nd);
			_Inside(tree, nd, valorInicial, refInicial, valorFinal, refFinal, ls);
	}
}

Lista BTREE_itensInsideArea(Tree* tree, double valorInicial, void* refInicial,double valorFinal, void* refFinal){
	Lista ls = Lista_createLista();
	_Inside(tree, tree->raiz, valorInicial, refInicial, valorFinal, refFinal, ls);
	return ls;
}