#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "ArqBin.h"
// #include "../Lista/lista.h"
// #include "../Grafos/GrafoD.h"

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
    int size;
    int blockSize;
    Node* raiz;
    FILE* arq;
    char* Data;
	long int headerSize;
}Tree;

typedef struct{
    double (*compare)(void*, void*);
    int size;
    int blockSize;
    int raiz;
    char* BFILE;
}Header;

//prototip
int ler_disco(Tree* arvore, int seek, Node *folha);

//Funções Auxiliares

//testar se sizeof(Node) <= block
int calcTam(int block){
    block -= 6*sizeof(int);
    int result = block/(4*sizeof(int)+2*sizeof(double));
    return result;
}

//Funções Estruturais


Tree* BTREE_Carrega(char* bdName){
	FILE* arq = fopen(bdName, "rb+");
	Header* hd = (Header*) malloc(sizeof(Header)); 
	fread(hd, sizeof(Header), 1, arq);
	fclose(arq);
	Tree* result = (Tree*) malloc(sizeof(Tree));
	result->compare = hd->compare;
	result->size = hd->size;
	result->blockSize = hd->blockSize;
	result->Data = hd->BFILE;
	result->arq = fopen(bdName, "wb+");
	result->raiz = (Node*) malloc(sizeof(Node));
	ler_disco(result, hd->raiz, result->raiz);
	return result;

}

//testar se sizeof(Node) <= block
Node* inicializa_folha(int block) {
    int tam = calcTam(block);
	Node* folha = (Node*)malloc(block);

	folha->max_elementos = 2 * tam - 1;
	folha->pai = -1;
	folha->total_elementos = 0;
	folha->total_filhos = 0;
	folha->minha_pos = -1;
	folha->max_filhos = 2 * tam;

	folha->elementos    = (double*) folha 				+ 6*sizeof(int); 					//(double*)    malloc(sizeof(double)*(2 * tam - 1));
    folha->elementoData = (int*) 	folha->elementos 	+ (sizeof(double)*(2 * tam - 1));  	//(int*)malloc(sizeof(int)* 2 * tam -1);
	folha->filhos       = (int*) 	folha->elementoData + (sizeof(int)* 2 * tam -1);		//(int*) malloc(sizeof(int) * 2 * tam);


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
Tree* BTREE_inicializa(int tam, char*bdName, int objSize, double (*compare)(void*, void*)) {
	Tree* arvore = (Tree*)malloc(sizeof(Tree));
    arvore->compare = compare;
	arvore->size = 0;
    arvore->blockSize = tam;
	arvore->raiz = NULL;
	arvore->arq = fopen(bdName, "w+b");
    char* dataPath = (char*) malloc(sizeof(char)*255);
    strcpy(dataPath, bdName);
	for(int i=0; i<strlen(dataPath); i++) if(*(dataPath+i) == '.') *(dataPath+i) = 0;
    strcat(dataPath, "_Data.dat");
    arvore->Data = dataPath;
	newArq(dataPath, objSize);
    
    Header *hd = (Header*)malloc(sizeof(Header));
    hd->compare = compare;
    hd->size = 0;
    hd->blockSize = tam;
    hd->raiz = -1;
    hd->BFILE = dataPath;
	

    
    fwrite((void *)hd, sizeof(Header), 1, arvore->arq);
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
	folha = inicializa_folha(arvore->blockSize);
	
	int fSize = sizeof(folha);
	int eSize = sizeof(folha->elementos);
	int dSize = sizeof(folha->elementoData);
	int cSize = sizeof(folha->filhos); 
	
	fread(folha, 				fSize, 1, arvore->arq);
	fread(folha->elementos, 	eSize, 1, arvore->arq);
	fread(folha->elementoData, 	dSize, 1, arvore->arq);
	fread(folha->filhos, 		cSize, 1, arvore->arq);
	folha->minha_pos = seek;

	return 1;
}

//retorna o indice do elemento esta na folha
int busca_elemento(Tree* arvore, Node* f, double valor, void* obj) {
	for (int i = 0; i < f->max_elementos; i++) {
		if (f->elementos[i] == valor) {
            void* ob = getObject(arvore->Data, f->elementoData[i]);
            if(arvore->compare(ob, obj)==0)
			return f->elementoData[i];
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
		return getObject(arvore->Data, folha->elementoData[indice]);
	}
	else {
		for (int i = 0; i < folha->max_filhos; i++) {
			if (folha->filhos[i] != -1) {
				Node* temp = (Node*)malloc(sizeof(Node));
				ler_disco(arvore, folha->filhos[i], temp);
                int res = busca_elemento(arvore, folha, valor, obj);
				if (res >= 0) 
				{
					free(temp);
					return getObject(arvore->Data, res);
				}
                return _busca(arvore, temp, valor, obj);
				// if (res >= 0)
				// 	return getObject(arvore->Data, res);
				free(temp);
			}
		}
	}
	return NULL;
}

void* BTREE_busca(Tree* arvore, double valor, void* obj) {
	return _busca(arvore, arvore->raiz, valor, obj);
}


//Precisa de Atenção e Verificar
int escrever_disco(Tree* arvore, int seek, Node *folha)
{
    //tem q andar o tamanho do header********************************
	// Insiro o pointer na posição que eu passei e escrevo o nó
	if (fseek(arvore->arq, seek, SEEK_SET) == -1)
		return 0;
	if (folha->minha_pos == -1)
		folha->minha_pos = ftell(arvore->arq);
	
	int fSize = sizeof(folha);
	int eSize = sizeof(folha->elementos);
	int dSize = sizeof(folha->elementoData);
	int cSize = sizeof(folha->filhos); 
	
	fwrite((void *)folha				, fSize, 1, arvore->arq);
	fwrite((void *)folha->elementos		, eSize, 1, arvore->arq);
	fwrite((void *)folha->elementoData	, dSize, 1, arvore->arq);
	fwrite((void *)folha->filhos		, cSize, 1, arvore->arq);
	
	return 1;
}

// ordena os elementos da folha
void ordenar(Node* f) {
	int trocas = 1;
	while (trocas > 0) {
		trocas = 0;
		int i = 0;
		while (i < f->max_elementos - 1) {
			if (f->elementos[i] > f->elementos[i + 1] && f->elementos[i+1] != -1) {
				int temp = f->elementos[i];
                int tempData = f->elementoData[i];
				f->elementos[i] = f->elementos[i + 1];
                f->elementoData[i] = f->elementos[i+1];
				f->elementos[i + 1] = temp;
                f->elementos[i + 1] = tempData;
				trocas++;
			}
			i++;
		}
	}
}

void adicionar_elemento(Tree* arvore,  Node* folha, double elem, void* obj) {
	for (int i = 0; i < folha->max_elementos; i++) {
		if (folha->elementos[i] == -1) {
			folha->elementos[i] = elem;
            int data = addObject(obj, arvore->Data);
            folha->elementoData[i] = data;
			break;
		}
	}
	ordenar(folha);
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
int split(Tree* arvore, Node* pai, double valor, void* obj) {
	//função que splita a raiz
	double valores[pai->max_elementos+1];
	int datas[pai->max_elementos+1];

	//lista os elementos, incluindo o novo
	for(int i=0; i < pai->max_elementos; i++){
		valores[i] = pai->elementos[i];
		datas[i] = pai->elementoData[i];
	}
	valores[pai->max_elementos] = valor;
	datas[pai->max_elementos] = addObject(obj, arvore->Data);

	for(int i=0; i <= pai->max_elementos; i++){
		for(int j=0; j <= pai->max_elementos; j++){
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
		filho2->elementos[i-meio+1] = valores[i];
		filho2->elementoData[i-meio+1] = datas[i];
		filho2->total_elementos++;
	}

	for(int i = 0; i < meio; i++)
		filho1->filhos[i] = pai->filhos[i];

	for(int i = meio+1; i < pai->max_filhos; i++)
		filho2->filhos[i-meio+1] = pai->filhos[i];


	//raiz -> limpa filhos e elementos
	for(int i = 0; i < pai->max_elementos; i++){
		pai->elementos[i] = -1;
		pai->elementoData[i] = -1;
	}

	for(int i = 0; i < pai->max_filhos; i++)
		pai->filhos[i] = -1;

	int pos;
	//filho[0] = filho 1
	filho1->pai = pai->minha_pos;
	fseek(arvore->arq, 0, SEEK_END);
	pos = ftell(arvore->arq);
	escrever_disco(arvore, pos, filho1);
	pai->filhos[0] = pos;

	//filho[1] = filho 2
	filho2->pai = pai->minha_pos;
	// fseek(arvore->arq, 0, SEEK_END);
	pos = ftell(arvore->arq);
	escrever_disco(arvore, pos, filho2);
	pai->filhos[1] = pos;

	//elemento[0] = meio e meio data
	pai->elementos[0] = valores[meio];
	pai->elementoData[0] = datas[meio];

	//atualiza o arquivo
	escrever_disco(arvore, pai->minha_pos, pai);

	return 1;
}

int retira_elemento(Tree* arvore, Node* folha, double elem, void* obj) {
	for (int i = 0; i < folha->max_elementos; i++) {
		if (folha->elementos[i] == elem) {
            void* ob = getObject(arvore->Data, folha->elementoData[i]);
            if(arvore->compare(ob, obj) == 0){
                folha->elementos[i] = -1;
                deleteObject(arvore->Data, folha->elementoData[i]);
                folha->elementoData[i] = -1;
                return 1;
            }
		}
	}
	ordenar(folha);
	return 0;
}


int _deletar(Tree* arvore, Node* folha, double valor, void* obj) {
	if (busca_elemento(arvore, folha, valor, obj) != -1) {
		int ctr = retira_elemento(arvore, folha, valor, obj);
		if(ctr)	return 1;
	}
	else {
		for (int i = 0; i < folha->max_filhos; i++) {
			if (folha->filhos[i] != -1) {
				Node* temp = (Node*)malloc(sizeof(Node));
				ler_disco(arvore, folha->filhos[i], temp);
				if (busca_elemento(arvore, folha, valor, obj) != -1) 
				{
					int ctr = retira_elemento(arvore, folha, valor, obj);
					if(ctr){
						free(temp);
						return 1;
					}
				}
				if (_deletar(arvore, temp, valor, obj) == 1)
					return 1;
				free(temp);
			}
		}
	}
	return 0;	
}

int BTREE_deletar(Tree* arvore, double valor, void* obj) {
	return _deletar(arvore, arvore->raiz, valor, obj);
}

int explodir(Tree* arvore, Node* folha, double valor, void* obj) 
{
	Node* pai = inicializa_folha(arvore->blockSize);
	int meio = folha->max_elementos / 2;
	int val_meio = folha->elementos[meio];
    int val_meioData = folha->elementoData[meio];
	folha->elementos[meio] = -1;
    folha->elementoData[meio] = -1;
	adicionar_elemento(arvore, folha, valor, obj);

	ler_disco(arvore, folha->pai, pai);
	if (total_elementos(pai) < folha->max_elementos)
	{
		void* val_meioObj  = getObject(arvore->Data, val_meioData);
		adicionar_elemento(arvore, pai, val_meio, val_meioObj);

		ordenar(pai);
		ordenar(folha);
		int index_maior = folha->max_elementos - 1;
		int i = 0;
		Node* irmao = inicializa_folha(arvore->blockSize);
		while (i < folha->max_filhos) {
			if (pai->filhos[i] == folha->minha_pos) {
				if (i + 1 != folha->max_filhos && pai->filhos[i + 1] != -1) {
					ler_disco(arvore, pai->filhos[i + 1], irmao);
					adicionar_elemento(arvore, irmao, folha->elementos[index_maior], getObject(arvore->Data, folha->elementoData[index_maior]));
					folha->elementos[index_maior] = -1;
                    deleteObject(arvore->Data, folha->elementoData[index_maior]);
                    folha->elementoData[index_maior] = -1;
					ordenar(irmao);
				}
			}
			i += 1;
		}

		if (irmao->minha_pos != -1)
			escrever_disco(arvore, irmao->minha_pos, irmao);
		escrever_disco(arvore, folha->minha_pos, folha);
		escrever_disco(arvore, pai->minha_pos, pai);
	}
	else {
		Node* nova_raiz = inicializa_folha(arvore->blockSize);
		Node* irmao = inicializa_folha(arvore->blockSize);
		
		add_filho(nova_raiz, pai->minha_pos);
		
		fseek(arvore->arq, 0, SEEK_END);
		int pos = ftell(arvore->arq);
		escrever_disco(arvore, pos, irmao);
		
		add_filho(nova_raiz, irmao->minha_pos);

		fseek(arvore->arq, 0, SEEK_END);
		pos = ftell(arvore->arq);
		escrever_disco(arvore, pos, nova_raiz);		
		pai->pai = nova_raiz->minha_pos;
		void* val_meioObj  = getObject(arvore->Data, val_meioData);
		explodir(arvore, pai, val_meio, val_meioObj);

		arvore->raiz = nova_raiz;

	}
	return 1;
}


int inserir_filho(Tree* arvore, Node* folha, double valor, void* obj) 
{
	Node* temp = inicializa_folha(arvore->blockSize);
	if (folha->filhos[0] != -1)  
	{
		ler_disco(arvore, folha->filhos[0], temp);
		if (total_elementos(temp) > 0 )
		{
				if (total_elementos(temp) == temp->max_elementos) 
				{
					// se essa porra estiver cheia vou ter que explodir caraaaalho
					// saco eim
					explodir(arvore, temp, valor, obj);

					return 1;
				}
				// se nao tiver cheio, taca pau nesse carrinho.. 
				adicionar_elemento(arvore, temp, valor, obj);
				ordenar(temp);
				escrever_disco(arvore, folha->filhos[0], temp); // atualiza no disco
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
	if (arvore->raiz == NULL) {
		// Primeira folha a ser inserida na arvore..
		arvore->raiz = inicializa_folha(arvore->blockSize);

		Node* folha = arvore->raiz;
		adicionar_elemento(arvore, folha, valor, obj);
		//folha->pai = 0; // posicao inicial desse cara..
		fseek(arvore->arq, 0, SEEK_END);	
		int pos = ftell(arvore->arq);
		folha->minha_pos = pos;
		if (escrever_disco(arvore, pos, folha)) {
			//printf("ok escrita\n");
		}
		ler_disco(arvore, pos, folha);

	}
	else {
		Node* f = arvore->raiz;
		if (f->filhos[0] != -1) {
			// se esse cara tiver filhos, devo inserir neles..
			inserir_filho(arvore, f, valor, obj);
		}
		else {
			if (total_elementos(f) == f->max_elementos) {
				split(arvore, f, valor, obj);

			}
			else {
				// nao atingiu ainda o limite..
				adicionar_elemento(arvore, f, valor, obj);
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
			void* obj = getObject(tree->Data, tree->raiz->elementoData[i]);
			double dist = abs(tree->compare(obj, minDistObj));
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
		if(tree->raiz->elementoData[i] != -1){
			*minDistObj = getObject(tree->Data, tree->raiz->elementoData[i]);
			*minDist = abs(tree->compare(reference, minDistObj));
		}
		i++;
	}while(*minDist==0 || ctr);

	Node* folha = inicializa_folha(tree->blockSize);
	ler_disco(tree, tree->raiz->minha_pos, folha);

	_closestNeibord(tree, folha, ref, reference, ctr, minDist, minDistObj);

	return minDistObj;

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
	if(arvore->raiz!=NULL)
		printNode(arvore, arvore->raiz);
}