#ifndef ITEM_H
#define ITEM_H

#define RETANGULO 0
#define CIRCULO 1

/*Define o tipo do item*/
typedef void* Item;

/*cria um item com essas informações*/
Item createItem(void* value,int type);

/*cria o codigo svg do Item em questao*/
char* createSvg(Item it);

/* Recupera o tipo do item */
int getType(Item it);

/* Recupera o valor do item */
void* getValueItem(void* it);

/* Recupera o id do desenho */
int getIdDraw(void* it);

/*Libera Memoria*/
void freeItem(Item it);

/*Verifica se dois itens se sobrepoe (1 - true / 0 - false)*/
int Item_overlap(Item i,Item j);

/*retorna o xi do item*/
double Item_Xi(Item i);

/*retorna o yi do item*/
double Item_Yi(Item i);

/*retorna o xf do item*/
double Item_Xf(Item i);

/*retorna o yf do item*/
double Item_Yf(Item i);

#endif
