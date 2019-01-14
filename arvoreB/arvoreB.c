#include <stdlib.h>
#include <stdio.h>
#include "../Lista/lista.h"
#include <math.h>
#include "../Grafos/GrafoD.h"

typedef struct No{
    int pai;
	int total_elementos;
	int max_elementos;
	int total_filhos;
	int max_filhos;
    double* elementos;
	int* elementoData;
	int* filhos;
    int minha_pos;
}Node;

typedef struct{
    int (*compare)(void*, void*);
    int size;
    int blockSize;
    Node* raiz;
    FILE* arq;
    char* Data;
}Tree;

typedef struct{
    int (*compare)(void*, void*);
    int size;
    int blockSize;
    int raiz;
    char* BFILE;
}Header;


//Funções Auxiliares

//testar se sizeof(Node) <= block
int calcTam(int block){
    block -= 6*sizeof(int);
    int result = block/(4*sizeof(int)+2*sizeof(double));
    return result;
}

//Funções Estruturais

//testar se sizeof(Node) <= block
Node* inicializa_folha(int block) {
    int tam = calcTam(block);
	Node* folha = (Node*)malloc(sizeof(Node));

	folha->max_elementos = 2 * tam - 1;
	folha->pai = -1;
	folha->filhos       = (double*) malloc(sizeof(int) * 2 * tam);
    folha->elementoData = (int*) malloc(sizeof(int)* 2 * tam -1);
	folha->elementos    = (int*)    malloc(sizeof(double)*(2 * tam - 1));

	folha->total_elementos = 0;
	folha->total_filhos = 0;
	folha->minha_pos = -1;
	folha->max_filhos = 2 * tam;

	for (int i = 0; i < folha->max_elementos; i++){
		folha->elementos[i] = -1;
        folha->elementoData[i] = -1;
    }
	for (int i = 0; i < folha->max_filhos; i++)
		folha->filhos[i] = -1;

	return folha;
}

//compare compara a distancia entre os objetos retorna 0 se o elemento for igual, 
// negativo se estiver antes e positivo se estiver depois do obj comparado
// o primeiro é o objeto de referencia, o segundo o da  celula
Tree* BTREE_inicializa(int tam, char*bdName, int objSize, int (*compare)(void*, void*)) {
	Tree* arvore = (Tree*)malloc(sizeof(Tree));
    arvore->compare = compare;
	arvore->size = 0;
    arvore->blockSize = tam;
	arvore->raiz = NULL;
	arvore->arq = fopen(bdName, "wb+");
    char* dataPath = (char*) malloc(sizeof(char)*strlen(bdName)+10);
    strcpy(dataPath, bdName);
    strcpy(dataPath, "_Data");
    arvore->Data = dataPath;
	newArq(dataPath, objSize);
    
    Header *hd = (Header*)malloc(sizeof(Header));
    hd->compare = compare;
    hd->size = 0;
    hd->blockSize = tam;
    hd->raiz = -1;
    hd->BFILE = dataPath;

    
    fwrite((void *)hd, sizeof(Header), 1, arvore->arq);

    return arvore;
}

//Leitura do Node no indice Seek
int ler_disco(Tree* arvore, int seek, Node *folha)
{
	// do seek na posição do arquivo
	if (fseek(arvore->arq, seek, SEEK_SET) == -1)
		return 0;
	// armazeno em um buffer
	char *buf = (char*)malloc(sizeof(Node));
	fread(buf, sizeof(Node), 1, arvore->arq);
	// copio o buffer para a estrutura.. 
	memcpy(folha, buf, sizeof(Node));

	return 1;
}

//retorna o indice do elemento esta na folha
int busca_elemento(Tree* arvore, Node* f, int valor, void* obj) {
	for (int i = 0; i < f->max_elementos; i++) {
		if (f->elementos[i] == valor) {
            void* ob = getObject(arvore->Data, f->elementoData[i]);
            if(arvore->compare(ob, obj)==0)
			return i;
		}
	}
	return -1;
}


/* metodo para buscar em uma folha,
 sendo este recursivo e armazenado apenas um no na memoria
 O retorno, é o indice do elemento no data, usando compare para achar o elemento igual
 */
void* _busca(Tree* arvore, Node* folha, int valor, void* obj) {	
	int indice = busca_elemento(arvore, folha, valor, obj);
    if (indice >= 0) {
		return getObject(arvore, folha->elementoData[indice]);
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
					return getObject(arvore, res);
				}
                res = _busca(arvore, temp, valor, obj);
				if (res >= 0)
					return getObject(arvore, res);
				free(temp);
			}
		}
	}
	return NULL;
}

void* BTREE_busca(Tree* arvore, int valor, void* obj) {
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
	fwrite((void *)folha, sizeof(Node), 1, arvore->arq);
	
	return 1;
}

// ordena os elementos da folha
void ordenar(Node* f) {
	int trocas = 1;
	while (trocas > 0) {
		trocas = 0;
		int i = 0;
		while (i < f->max_elementos - 1) {
			if (f->elementos[i] > f->elementos[i + 1]) {
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

void adicionar_elemento(Tree* arvore,  Node* folha, int elem, void* obj) {
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

int split(Tree* arvore, Node* pai, int valor, void* obj) {
	Node* filho1 = inicializa_folha(arvore->blockSize);
	Node* filho2 = inicializa_folha(arvore->blockSize);

	int meio = (pai->max_elementos / 2);
	int val_meio = pai->elementos[meio];
    int val_meioData = pai->elementoData[meio];

	int val_meio2 = pai->elementos[meio + 1];
    int val_meio2Data = pai->elementoData[meio + 1];

	for (int i = 0; i < pai->max_elementos; i++){
		filho1->elementos[i] = pai->elementos[i];
        filho1->elementoData[i] = pai->elementoData[i];
    }

	for (int i = 0; i < pai->max_filhos; i++){
		filho1->filhos[i] = pai->filhos[i];
    }

	filho1->elementos[meio] = valor;
    int data = addObject(obj, arvore->Data);
    filho1->elementoData[meio] = data;
	filho1->elementos[meio + 1] = -1;
	filho1->pai = pai->minha_pos;
	filho1->total_elementos = pai->total_elementos - 1;

	filho2->pai = pai->minha_pos;
	filho2->total_elementos = 1;

	//memset(folha->elementos, 0x0, sizeof(folha->elementos));
	for (int i = 0; i < pai->max_elementos; i++){
		pai->elementos[i] = -1;
        pai->elementoData[i] = -1;
    }
	for (int i = 0; i < pai->max_filhos; i++)
		pai->filhos[i] = -1;

	pai->total_elementos = 1;
	adicionar_elemento(arvore, pai, val_meio, val_meioData);
	adicionar_elemento(arvore, filho2, val_meio2, val_meio2Data);
	ordenar(filho1);

    //andar o tamanho do header e verificar escrita em arquivo
	fseek(arvore->arq, 0, SEEK_END);
	int pos = ftell(arvore->arq);
	escrever_disco(arvore, pos, filho1);

	int pos2 = ftell(arvore->arq);
	escrever_disco(arvore, pos2, filho2);

	add_filho(pai, pos);
	add_filho(pai, pos2);

	escrever_disco(arvore, pai->minha_pos, pai);
	return 1;
}

int retira_elemento(Tree* arvore, Node* folha, int elem, void* obj) {
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


int _deletar(Tree* arvore, Node* folha, int valor, void* obj) {
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

int BTREE_deletar(Tree* arvore, int valor, void* obj) {
	return _deletar(arvore, arvore->raiz, valor, obj);
}

int explodir(Tree* arvore, Node* folha, int valor, void* obj) 
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
		adicionar_elemento(arvore, pai, val_meio, val_meioData);

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
		explodir(arvore, pai, val_meio, val_meioData);

		arvore->raiz = nova_raiz;

	}
	return 1;
}


int inserir_filho(Tree* arvore, Node* folha, int valor, void* obj) 
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
			escrever_disco(arvore, folha->filhos[0], temp); // atualiza no disco
		}
	}

	return 1;
}

int BTREE_insere(Tree* arvore, int valor, void* obj) {
	if (arvore->raiz == NULL) {
		// Primeira folha a ser inserida na arvore..
		arvore->raiz = inicializa_folha(arvore->blockSize);

		Node* folha = arvore->raiz;
		adicionar_elemento(arvore, folha, valor, obj);
		//folha->pai = 0; // posicao inicial desse cara..		
		if (escrever_disco(arvore, 0, folha)) {
			//printf("ok escrita\n");
		}

	}
	else {
		Node* f = arvore->raiz;
		if (f->filhos[0] != -1) {
			// se esse cara tiver filhos, devo inserir neles..
			inserir_filho(arvore, arvore->raiz, valor, obj);
		}
		else {
			if (total_elementos(f) == f->max_elementos) {
				split(arvore, arvore->raiz, valor, obj);
			}
			else {
				// nao atingiu ainda o limite..
				adicionar_elemento(arvore, f, valor, obj);
				// re-escrevo ele no arquivo
				escrever_disco(arvore, f->pai, arvore->raiz);

			}
		}
	}

	return 0;
}