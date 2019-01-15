#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "../Lista/lista.h"


//primeiro iteom -> long int
//incluir sizeblock no header

long int primeiroItem;

typedef short int mark;
static mark full = 1;
static mark empty = 0;

//cria arquivo vazio e escreve o header
void newArq(char* pathName, int sizeBloco){

    FILE *arq;
    char *size;
    int qtd;
    long int zero;
    zero = 0;

    //size = malloc(sizeBloco*sizeof(char));
    //sprintf(size, "%d", sizeBloco);

    arq = fopen(pathName, "wb");
    qtd = fwrite(&zero, sizeof(long int), 1,arq); //escreve contador de objetos = 0
    qtd = fwrite(&sizeBloco, sizeof(int), 1,arq);   //escreve tamanho do bloco
    //qtd = fwrite(" ", sizeof(char), 1,arq);
    //qtd = fwrite("\n", sizeof(char), 1,arq);   //marca pos. livre
    primeiroItem = ftell(arq);
    //printf("primeiro = %d\n", primeiroItem);
    qtd = fwrite(&empty, sizeof(mark), 1,arq);   //marca pos. livre
    fclose(arq);
}

//escreve objeto no arquivo, retorna o indice do objeto
int addObject(void *object, char* pathName){

    FILE *arq;
    int qtd, n, pos, tam, block;
    long int indice, next;
    char str[6], aux;

    //tam = getTam(pathName);
    
    //procura espaço vazio -> transformar em função
    arq = fopen(pathName, "r+b");
    fread(&indice, sizeof(long int), 1, arq);
    fread(&block, sizeof(int), 1, arq);    
    rewind(arq);
    
    
    int c = 0;
    mark emp;
    while(1){
        
        qtd = fseek(arq, (primeiroItem + c*(block + sizeof(mark))), SEEK_SET);    
        fread(&emp, sizeof(mark), 1, arq);
        if(emp==0) break;
        if(c==indice) break;
        c++;
    }

    //add objeto
    long int offSet = (primeiroItem + c*(block + sizeof(mark)));
    qtd = fseek(arq, offSet, SEEK_SET);
    printf("pos escrita = %li\n", ftell(arq));
    qtd = fwrite(&full, sizeof(mark), 1,arq);   //marca pos. livre
    qtd = fwrite(object, block, 1, arq);
    if(c==indice){
        next = indice+1;
        //qtd = fwrite(&next, sizeof(int), 1,arq);   //marca pos. livre
        qtd = fwrite(&empty, sizeof(mark), 1,arq);   //marca pos. livre
        rewind(arq);
        fwrite(&next, sizeof(long int), 1,arq);
    }
    fclose(arq);

    return c;
}

//retorna objeto no arquivo
void* getObject(char* pathName, int indice){

    FILE *arq;
    int c = 0;
    int pos, block;
    long int qtd;
    void* ob;
    char str[6], bn;
    mark emp;
    

    arq = fopen(pathName, "r+b");
    fread(&qtd, sizeof(long int), 1, arq);
    fread(&block, sizeof(int), 1, arq);    
    rewind(arq);
    pos = fseek(arq, primeiroItem, 0);
    qtd = fseek(arq, (primeiroItem + indice*(block + sizeof(mark))), SEEK_SET);    
    fread(&emp, sizeof(mark), 1, arq);  
    if(emp == empty) return NULL;
    ob = (void*) malloc(block);
    fread(ob, block, 1, arq);
    fclose(arq);
    return ob;
} 

//retorna um vetor com todos os objetos do arquivo e ultima posição nula
void* getAll(char* pathName){

    FILE *arq;
    int block, pos;
    long int qtd;
    mark emp;
    
    Lista lista = Lista_createLista();

    arq = fopen(pathName, "r+b");
    fread(&qtd, sizeof(long int), 1, arq);
    fread(&block, sizeof(int), 1, arq);  
    lista = calloc(qtd, block);
    //preenche lista
    rewind(arq);
    pos = fseek(arq, primeiroItem, 0);
    
    for(int c=0; c<qtd; c++){
        fseek(arq, (primeiroItem + c*(block + sizeof(mark))), SEEK_SET);    
        fread(&emp, sizeof(mark), 1, arq);
        if(emp == 1){
             void *ob; ob = (void*) malloc(block);
             fread(ob, block, 1, arq);
             Lista_insert(lista, ob);
        }
    }
    fclose(arq);

    return lista;
}


//apaga objeto do arquivo
void deleteObject(char* pathName, int indice){

    FILE *arq;
    int pos, block, n;
    long int qtd;

    //encontra object
    arq = fopen(pathName, "r+b");
    fread(&qtd, sizeof(long int), 1, arq);
    fread(&block, sizeof(int), 1, arq); 
    pos = fseek(arq, primeiroItem, 0);
    if(indice >= qtd || indice < 0) return;

    long int offSet = (primeiroItem + indice*(block + sizeof(mark)));
    qtd = fseek(arq, offSet, SEEK_SET);
    qtd = fwrite(&empty, sizeof(mark), 1,arq);   //marca pos. livre

    fclose(arq);


}