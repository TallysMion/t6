#include <stdio.h>
#include <stdlib.h>
//include biblioteca KDTREE

typedef struct page{
	void *Path;
	void *key; //ordenada por key
}pages;

int id = 0;

//----------------------------------------------------------------------------------------------------------

//compare function p/ kd de pages
int compareKD(){

}

//cria estrutura paginas
void *Pages(int bloco){

	pages *e;
	e = KDT_create(compareKD, 2, freePages);

	return e;
}

//free function
void freePages(void *page){
	pages *p;

	p = (pages *) page;
	free(p->Path);
	free(p->key);
}

//cria um novo no em branco
void page(void *page, int qtd){

	//cria nova pagina
	char *nome;
	pages *pg;
	int i;
	FILE *f;

	nome = concat("page ", id);
	nome = concat(nome, ".txt");
	id = id + 1;
	
	pg = calloc(1, sizeof(pages));
	pg->Path = calloc(strlen(nome)+1, sizeof(char));
	strcpy(pg->Path, nome);

	//insere pagina
	pg->key = calloc(qtd, sizeof(void*));

	KDT_insert(page, pg);

	//abre page
	f = fopen(pg->Path, "w");
	fprintf(f, "%d\n", 0);	//qtd de objetos no arquivo
	fclose(f);
}

