#ifndef CONFIG_H
#define CONFIG_H

/*imports*/
#include "../Lista/lista.h"
#include "../Fila/fila.h"
#include "../KDTREE/kdtree.h"
#include "../HashTable/hashtable.h"
#include "../Grafos/GrafoD.h"


/*entrutura das informações base do programa*/
typedef struct config{
    
    char *cstrkQuad;
    char *cfillQuad;
    char *cstrkHidr;
    char *cfillHidr;
    char *cstrkSemaf;
    char *cfillSemaf;
    char *cstrkRBase;
    char *cfillRBase;

    char *colorMud;
    char *colorMudec;

    double x;
    double y;

}Config;

typedef struct database{
    void*** ar0;
    int maxDrawerSize;
    Lista   *Drawer;

    KDT         HidrantesTree;
    KDT         SemaforosTree;
    KDT         QuadrasTree;
    KDT         RadioBaseTree;
    KDT         carroTree;

    HashTable   carroHash;
    HashTable   Reg;
    HashTable   EstabelecimentoType;
    HashTable   *EstabHash; /*id*/
    HashTable   *enderecoPessoa; /*cep*/
    HashTable   *HidrantesHash; /*id*/
    HashTable   *SemaforosHash; /*id*/ 
    HashTable   *RadioBaseHash; /*id*/
    HashTable   *PessoaCepHash; /*cpf*/
    HashTable   *cepQuadraHash; /*cep*/
    HashTable   *enderecoEstab; /*cep*/

    GrafoD      grafo;

}Database;

typedef struct Info{
    char *e;
    char *f;
    char *o;
    char *q;
    char *ec;
    char *pm;
    char *via;

    int size;

    Fila notsGeo; /*Anotações para SVG*/
    Fila notsQRY; /*Anotações para SVG*/
    Fila notsEC;  /*Anotações para SVG*/
    Fila notsPm;  /*Anotações para SVG*/
    Fila notsVia; /*Anotações para SVG*/

    Fila respGEO; /*Anotações para TXT*/
    Fila respQRY; /*Anotações para TXT*/
    Fila respEC;  /*Anotações para TXT*/
    Fila respPM;  /*Anotações para TXT*/
    Fila respVia; /*Anotações para TXT*/

    Database *bd; /*banco de dados*/

    Config *conf; /*configurações*/

}Info;



/*formata um path*/
char* format(char *value);

/*le o argv e inicia as informações do programa*/
Info* configIn(int argc, const char *argv[]);

/*inclui as linhas do arquivo de entrada na fila e retorna a fila*/
Fila getCommandsForGEO(Info* info);

/*inclui as linhas do arquivo de entrada na fila e retorna a fila*/
Fila getCommandsForQRY(Info* info);

/*inclui as linhas do arquivo de entrada na fila e retorna a fila*/
Fila getCommandsForEC(Info* info);

/*inclui as linhas do arquivo de entrada na fila e retorna a fila*/
Fila getCommandsForPM(Info* info);

/*inclui as linhas do arquivo de entrada na fila e retorna a fila*/
Fila getCommandsForVIA(Info* info);

/*libera a memoria de config*/
void freeConfig(Info *info);

/*Inicia as hash do GEO*/
void inicGEO(Info* info, int size);

/*Inicia as Hash do PM*/
void inicPM(Info* info, int size);

/*Inicia as Hash do EC*/
void inicEC(Info* info, int size);

/*Inicia a estrutura da Via*/
void inicVIA(Info* info, int size);

#endif