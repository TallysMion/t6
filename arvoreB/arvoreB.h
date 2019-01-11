#ifndef ARVOREB_H
#define ARVOREB_H

void *Pages(int bloco);	                //cria e abre a estrutura paginas

void page(void *pages, int qtd);	//cria e insere uma pagina

void insert(void *page, void *pos);	//insere um bloco

void delet(void *page, void *pos);	//apaga bloco

int compare(void *keyA, void *keyB);    //compara chave de ordenação da arvore

void *getPage(void *pages, void *key);  //retorna pagina com a info buscada

void *getBloco(void *page, void *key);  //retorna info buscada 

#endif
