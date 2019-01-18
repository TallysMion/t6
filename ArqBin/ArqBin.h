#ifndef ARQBIN_H
#define ARQBIN_H

void newArq(char* pathName, int sizeBloco); //cria arquivo vazio e escreve o header

int addObject(void *object, char* pathName, void (*writer)(void* obj, int seek, void* arq));	//escreve objeto no arquivo, retorna o indice do objeto ou null se o arquivo esta cheio

void* getObject(char* pathName, int indice, void (*reader)(void* obj, int seek, void* arq)); //retorna objeto no arquivo

void* getAll(char* pathName, void (*reader)(void* obj, int seek, void* arq)); //retorna um vetor com todos os objetos do arquivo e ultima posição nula

void deleteObject(char* pathName, int indice); //apaga objeto do arquivo

#endif
