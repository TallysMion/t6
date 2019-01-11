#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../Config/config.h"
#include "../../Circulo/circulo.h"
#include "../../Retangulo/retangulo.h"
#include "../../Anotacao/anotacao.h"
#include "../../Quadra/quadra.h"
#include "../../Radio-Base/radio-base.h"
#include "../../Semaforo/semaforo.h"
#include "../../Hidrante/hidrante.h"
#include "../../Item/item.h"

int setConfig(char *text,Info *info){
    char* aux;
    int i;
    aux = text;
    aux += 3;
    i = (int) strtol(aux, NULL, 10);
    if(i<=0){return 0;}    
    info->size = i;
    return 1;
}

int drawCircle(char *text, Info *info){
    char *aux, *cor1, *cor2; 
    int i, id;
    double r, x, y;
    void* circ;
    Item item;

    aux = text;

    cor1 = (char*) calloc (25, sizeof(char)); 
    cor2 = (char*) calloc (25, sizeof(char));  

    aux = text; aux += 2;

    if(Lista_lenght(info->bd->Drawer) >= info->size){
        printf("\nValor Maximo Exedido\n");
        return 0;
    }

    sscanf(aux, "%d %s %s %lf %lf %lf", &id, cor1, cor2, &r, &x, &y);
    
    circ = createCirculo(id, cor1, cor2, r, x, y);
    item = createItem(circ, CIRCULO);
    free(cor1);
    free(cor2);
    Lista_insert(info->bd->Drawer, item);
    
    if(x + r > info->conf->x) { info->conf->x = x+r;}
    if(y + r > info->conf->y) { info->conf->y = y+r;}
    
    return 1;
}

int drawRectangle(char *text, Info *info){
    char *aux, *cor1, *cor2; 
    int i, id;
    double w, h, x, y;
    retangulo rect;
    Item item;

    aux = text;

    cor1 = (char*) calloc (25, sizeof(char)); 
    cor2 = (char*) calloc (25, sizeof(char)); 
    
    aux = text; aux += 2;
    
    if(Lista_lenght(info->bd->Drawer) >= info->size){
        printf("\nValor Maximo Exedido\n");
        return 0;
    }
    
    sscanf(aux, "%d %s %s %lf %lf %lf %lf", &id, cor1, cor2, &w, &h, &x, &y);    
    rect = createRetangulo(id, cor1, cor2, w, h, x, y);
    item = createItem(rect, RETANGULO);
    free(cor1);
    free(cor2);
    Lista_insert(info->bd->Drawer, item);

    if(x+w > info->conf->x) { info->conf->x = x+w;}
    if(y+h > info->conf->y) { info->conf->y = y+h;}

    return 1;
}
        
int overlap(char *text, Info *info){
    Notation nt;
    char *aux;
    int idI, idJ;
    Item ij, ik;

    aux = (char*) calloc (strlen(text)+2, sizeof(char));

    strcpy(aux, text);
    insert_Fila(info->respGEO, aux);
    aux = text; aux += 2;   

    sscanf(aux, "%d %d", &idI, &idJ);

    ij = NULL;
    ik = NULL;

    //recupera ij e ik
    void *t, *temp;
    t = Lista_getFirst(info->bd->Drawer);
    while(1){
        temp = Lista_get(info->bd->Drawer,t);
        if(temp){
            Item it = temp;
            int auxT;
            auxT = getIdDraw(it);

            if(auxT == idI){
                ij = it;
            }
            if(auxT == idJ){
                ik = it;
            }

            if(ik && ij){
                break;
            }

            t = Lista_getNext(info->bd->Drawer, t);
        }else{
        break;
        }
    }

    //verifica se dois itens se sobrepor
    if(Item_overlap(ij, ik) == 1){
        double x = Item_Xi(ij) < Item_Xi(ik) ? Item_Xi(ij) : Item_Xi(ik);
        double y = Item_Yi(ij) < Item_Yi(ik) ? Item_Yi(ij) : Item_Yi(ik);
        double w = Item_Xf(ij) > Item_Xf(ik) ? Item_Xf(ij) : Item_Xf(ik);
        double h = Item_Yf(ij) > Item_Yf(ik) ? Item_Yf(ij) : Item_Yf(ik);
        w -= x;
        h -= y;
        nt = createNotacao("red", w, h, x, y, "SOBREPOE");    
        insert_Fila(info->notsGeo, nt);
        insert_Fila(info->respGEO, "SIM\n");
    }else{
        insert_Fila(info->respGEO, "NAO\n");
    }

    return 1;
}



int isInside(char *text, Info *info){
    char *aux, *outTxt, *aux2;
    int res, j;    
    double k,l;    
    Item it;
    
    aux = text; aux += 2;
    sscanf(aux, "%d %lf %lf", &j, &k, &l);

    void *t, *temp;
    t = Lista_getFirst(info->bd->Drawer);
    while(1){
        temp = Lista_get(info->bd->Drawer,t);
        if(temp){
            int auxT;
            auxT = getIdDraw(it);
            if(auxT == j){
                it = temp;
                break;
            }
            t = Lista_getNext(info->bd->Drawer, t);
        }else{
        break;
        }
    }

    aux = (char*) calloc (strlen(text)+2, sizeof(char));
    strcpy(aux, text);
    insert_Fila(info->respGEO, aux);

    res = getType(it)==RETANGULO?isInRec(k,l,getValueItem(it)):isInCirc(k,l,getValueItem(it));  
    res?insert_Fila(info->respGEO, "SIM\n"):insert_Fila(info->respGEO, "NAO\n");
    return 1;

}

int howFar(char *text, Info *info){
    char* aux, *outTxt, *aux2, *res; 
    int idI, idJ; 
    int j, k;  
    double *cj, *ck, x, y;    
    Item ij, ik;
    

    aux = text; aux += 2;

    
    sscanf(aux, "%d %d", &idI, &idJ);

    ij = NULL;
    ik = NULL;

    void *t, *temp;
    t = Lista_getFirst(info->bd->Drawer);
    while(1){
        temp = Lista_get(info->bd->Drawer,t);
        if(temp){
            Item it = temp;
            int auxT;
            auxT = getIdDraw(it);

            if(auxT == idI){
                ij = it;
            }
            if(auxT == idJ){
                ik = it;
            }

            if(ik && ij){
                break;
            }

            t = Lista_getNext(info->bd->Drawer, t);
        }else{
        break;
        }
    }

    if(!ij || !ik){
        return 1;
    }

    cj = getType(ij)==RETANGULO?conrdenadaCentroRec(getValueItem(ij)):conrdenadaCentroCirc(getValueItem(ij));
    ck = getType(ik)==RETANGULO?conrdenadaCentroRec(getValueItem(ik)):conrdenadaCentroCirc(getValueItem(ik));

    x = ck[0] - cj[0];
    y = ck[1] - cj[1];

    x = x>0?x:-x;
    y = y>0?y:-y;

    res = (char*) calloc(40, sizeof(char));
    sprintf(res, "%f\n",sqrt(pow(x, 2.0) + pow(y,2.0)));
    aux = (char*) calloc (strlen(text)+2, sizeof(char));
    strcpy(aux, text);
    insert_Fila(info->respGEO, aux);
    aux = (char*) calloc (strlen(text)+2, sizeof(char));
    strcpy(aux, res);
    insert_Fila(info->respGEO, aux);
    free(res);
    return 1;
}

int drawSufixo(char *text, Info *info){
    char *path, *aux, *suf, *auxCor;
    int i, id;
    void* temp;
    double *c1, *c2, midx, midy, dis;
    Posic t;
    Notation auxN;
    Fila *auxF;
    FILE *arqSVG;

    suf = text; suf += 2;

    sscanf(suf, "%d %s", &id, suf);
    
    while(*suf == ' ')suf++;
    for(i=0; i<= strlen(suf); i++){
        if(*(suf+i) == '\n'){
            *(suf+i) = 0;
            break;
        }
    }


    path = (char*) calloc (255, sizeof(char));
    sprintf(path, "%s/%s", info->o, info->f);
    if(*path == '/') path++;
    aux = path;
    aux += strlen(path);
    while(*aux != '.')aux--;
    strcpy(aux, "-"); strcat(aux, suf); 
    strcat(aux, ".svg");
    arqSVG = fopen(path, "w");
    fprintf(arqSVG,"<svg xmlns=\"http://www.w3.org/2000/svg\" width = \"%lf\" height = \"%lf\">\n", info->conf->x, info->conf->y);


    t=Lista_getFirst(info->bd->Drawer);
    while(1){
        temp = Lista_get(info->bd->Drawer,t);
        if(temp){
            
            Item it = Lista_get(info->bd->Drawer, t);
            fprintf(arqSVG, "%s\n", createSvg(it));
            t = Lista_getNext(info->bd->Drawer, t);
        }else{
        break;
        }
    }

    auxF = create_Fila();

    while(!empty_Fila(info->notsGeo)){
        auxN = (Notation) remove_Fila(info->notsGeo);
        insert_Fila(auxF,(void*) auxN);
        fprintf(arqSVG, "%s\n", createNotacaoSvg(auxN));
    }
    free(info->notsGeo);
    info->notsGeo = auxF;

    Item it;
    t=Lista_getFirst(info->bd->Drawer);
    while(1){
        temp = Lista_get(info->bd->Drawer,t);
        if(temp){   

            if(id == getIdDraw(temp)){
                it = temp;
                break;
            }         

            t = Lista_getNext(info->bd->Drawer, t);
        }else{
        break;
        }
    }

    if(getType(it) == RETANGULO){
        c1 = conrdenadaCentroRec(getValueItem(it));
        auxCor = getCorRec(getValueItem(it));
    }else{
        c1 = conrdenadaCentroCirc(getValueItem(it));
        auxCor = getCorCirc(getValueItem(it));
    }

    for(i=0; *(auxCor + i); i++){
        if(*(auxCor + i) == '\n'){
            *(auxCor + i) = 0;
        }
    }

    Notation nt;

                
    t=Lista_getFirst(info->bd->Drawer);
    while(1){
        temp = Lista_get(info->bd->Drawer,t);
        if(temp){   

        if(temp != it){
            
            if(getType(temp) == RETANGULO){
                c2 = conrdenadaCentroRec(getValueItem(temp));
            }else{
                c2 = conrdenadaCentroCirc(getValueItem(temp));
            }
            fprintf(arqSVG, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"2\" stroke=\"%s\" />",
            *c1,*(c1+1),*c2,*(c2+1), auxCor);
            midx = *c1      + (*c2      -   *c1)    /2;
            midy = *(c1+1)  + (*(c2+1)  -   *(c1+1))/2;
            aux = (char*) calloc(25, sizeof(char));
            dis = sqrt(pow(*c2-*c1,2)+pow(*(c2+1)-*(c1+1),2));
            fprintf(arqSVG,"<text x=\"%f\" y=\"%f\" style=\"font-family: Helvetica,Arial,sans-serif;font-weight:bolf;font-size:34; fill:'%s';\">%f</text>\n", midx, midy,auxCor, dis);                                

        }

        t = Lista_getNext(info->bd->Drawer, t);
        }else{
        break;
        }
    }



        //imprimir quadras
    Lista quadras = KDT_getAll(info->bd->QuadrasTree);
    t=Lista_getFirst(quadras);
    while(1){
        temp = Lista_get(quadras,t);
        if(temp){
            
            Item it = Lista_get(quadras, t);
            fprintf(arqSVG, "%s\n", createQuadraSvg(it));
            t = Lista_getNext(quadras, t);
        }else{
        break;
        }
    }

    //imprimir semaforos
    Lista semaforos = KDT_getAll(info->bd->SemaforosTree);
    t=Lista_getFirst(semaforos);
    while(1){
        temp = Lista_get(semaforos,t);
        if(temp){
            
            Item it = Lista_get(semaforos, t);
            fprintf(arqSVG, "%s\n", createSemaforoSvg(it));
            t = Lista_getNext(semaforos, t);
        }else{
        break;
        }
    }

    //imprimir hidrantes
    Lista hidrantes = KDT_getAll(info->bd->HidrantesTree);
    t=Lista_getFirst(hidrantes);
    while(1){
        temp = Lista_get(hidrantes,t);
        if(temp){
            
            Item it = Lista_get(hidrantes, t);
            fprintf(arqSVG, "%s\n", createHidranteSvg(it));
            t = Lista_getNext(hidrantes, t);
        }else{
        break;
        }
    }

    //imprimir torres-base
    Lista radios = KDT_getAll(info->bd->RadioBaseTree);
    t=Lista_getFirst(radios);
    while(1){
        temp = Lista_get(radios,t);
        if(temp){
            
            Item it = Lista_get(radios, t);
            fprintf(arqSVG, "%s\n", createRadioBSvg(it));
            t = Lista_getNext(radios, t);
        }else{
        break;
        }
    }



    fprintf(arqSVG,"</svg>");
    fclose(arqSVG);
    //free(path);
    return 1;
}

int close(Info *info){
    char *path, *aux;
    int i;
    void* temp;
    Notation auxN;
    Fila *auxF;
    FILE *arqSVG, *arqTXT;
    Posic t;
    

    path = (char*) calloc (255, sizeof(char));
    sprintf(path, "%s/%s", info->o, info->f);
    if(*path == '/') path++;
    aux = path;
    aux += strlen(path);
    while(*aux != '.')aux--;
    strcpy(aux, ".svg");
    arqSVG = fopen(path, "w");
    
    fprintf(arqSVG,"<svg xmlns=\"http://www.w3.org/2000/svg\" width = \"%lf\" height = \"%lf\">\n", info->conf->x, info->conf->y);

    t=Lista_getFirst(info->bd->Drawer);
    while(1){
        temp = Lista_get(info->bd->Drawer,t);
        if(temp){
            
            Item it = Lista_get(info->bd->Drawer, t);
            fprintf(arqSVG, "%s\n", createSvg(it));
            t = Lista_getNext(info->bd->Drawer, t);
        }else{
        break;
        }
    }


    auxF = create_Fila();
    while(!empty_Fila(info->notsGeo)){
        auxN = (Notation) remove_Fila(info->notsGeo);
        insert_Fila(auxF,(void*) auxN);
        fprintf(arqSVG, "%s\n", createNotacaoSvg(auxN));
    }
    free(info->notsGeo);
    info->notsGeo = auxF;


    //imprimir quadras
    Lista quadras = KDT_getAll(info->bd->QuadrasTree);
    t=Lista_getFirst(quadras);
    do{
        temp = Lista_get(quadras,t);
        if(temp){            
            Item it = Lista_get(quadras, t);
            fprintf(arqSVG, "%s\n", createQuadraSvg(it));
            t = Lista_getNext(quadras, t);
        }
    }while(temp);


    //imprimir semaforos
    Lista semaforos = KDT_getAll(info->bd->SemaforosTree);
    t=Lista_getFirst(semaforos);
    while(t){
        temp = Lista_get(semaforos,t);
        if(temp){
            
            Item it = Lista_get(semaforos, t);
            fprintf(arqSVG, "%s\n", createSemaforoSvg(it));
            t = Lista_getNext(semaforos, t);
        }else{
        break;
        }
    }
    

    //imprimir hidrantes
    Lista hidrantes = KDT_getAll(info->bd->HidrantesTree);
    t=Lista_getFirst(hidrantes);
    while(t){
        temp = Lista_get(hidrantes,t);
        if(temp){
            
            Item it = Lista_get(hidrantes, t);
            fprintf(arqSVG, "%s\n", createHidranteSvg(it));
            t = Lista_getNext(hidrantes, t);
        }else{
        break;
        }
    }


    //imprimir torres-base
    Lista radios = KDT_getAll(info->bd->RadioBaseTree);
    t=Lista_getFirst(radios);
    while(t){
        temp = Lista_get(radios,t);
        if(temp){
            
            Item it = Lista_get(radios, t);
            fprintf(arqSVG, "%s\n", createRadioBSvg(it));
            t = Lista_getNext(radios, t);
        }else{
        break;
        }
    }


    fprintf(arqSVG,"</svg>");

    fclose(arqSVG);

    aux = path;
    aux += strlen(path);
    while(*aux != '.')aux--;
    strcpy(aux, ".txt");

    arqTXT = fopen(path, "w");
    Fila filaTemp = create_Fila();
    while(!empty_Fila(info->respGEO)){
        aux = (char*) remove_Fila(info->respGEO);
        insert_Fila(filaTemp, aux);
        fprintf(arqTXT, "%s", aux);
    }
    freeFila(info->respGEO);
    info->respGEO = filaTemp;
    fclose(arqTXT);
    //free(path);
    return 0;
}
/*printInFile(path, "\n<svg xmlns=\"http://www.w3.org/2000/svg\">\n");*/




/*novas funçoes incluidas na parte 2 -> t3*/

/*Cria uma nova Quadra*/
int drawQuad(char *text, Info *info){
    char *aux, *cep;
    double w, h, x, y;
    quadra quad;
    Item item;

    cep = (char*) calloc (55, sizeof(char));
    
    aux = text; aux += 2;
    sscanf(aux, "%s %lf %lf %lf %lf", cep, &x, &y, &w, &h);
    
    quad = createQuadra(cep, info->conf->cstrkQuad, info->conf->cfillQuad, w, h, x, y);
    KDT_insert(info->bd->QuadrasTree, quad);
    insert_hashtable(info->bd->cepQuadraHash, quad);
    free(cep);

    if(x+w > info->conf->x) { info->conf->x = x+w;}
    if(y+h > info->conf->y) { info->conf->y = y+h;}

    return 1;
}

/*Cria um novo Hidrante*/
int drawHidr(char *text, Info *info){
    char *aux;
    char* id;
    double x, y;
    hidrante hidr;
    Item item;

    id = (char*) calloc(155, sizeof(char));

    aux = text; aux += 2;
    sscanf(aux, "%s %lf %lf", id, &x, &y);
    
    hidr = createHidrante(id, info->conf->cstrkHidr, info->conf->cfillHidr, x, y);
    KDT_insert(info->bd->HidrantesTree, hidr);
    insert_hashtable(info->bd->HidrantesHash, hidr);
    free(id);
    if(x+5 > info->conf->x) { info->conf->x = x+5;}
    if(y+5 > info->conf->y) { info->conf->y = y+5;}
    return 1;
}

/*Cria um novo Semaforo*/
int drawSemaf(char *text, Info *info){
    char *aux;
    char* id;
    double x, y;
    semaforo semaf;
    Item item;

    id = (char*) calloc(155, sizeof(char));

    aux = text; aux += 2;
    sscanf(aux, "%s %lf %lf", id, &x, &y);
    
    semaf = createSemaforo(id, info->conf->cstrkSemaf, info->conf->cfillSemaf, x, y);
    KDT_insert(info->bd->SemaforosTree, semaf);
    insert_hashtable(info->bd->SemaforosHash, semaf);
    free(id);
    if(x+5 > info->conf->x) { info->conf->x = x+5;}
    if(y+5 > info->conf->y) { info->conf->y = y+5;}
    return 1;
}

/*Cria uma nova Torre de Radio*/
int drawRBase(char *text, Info *info){
    char *aux;
    char* id;
    double x, y;
    radioB rb;
    Item item;

    id = (char*) calloc(155, sizeof(char));

    aux = text; aux += 2;
    sscanf(aux, "%s %lf %lf", id, &x, &y);
    
    rb = createRadioB(id, info->conf->cstrkRBase, info->conf->cfillRBase, x, y);
    KDT_insert(info->bd->RadioBaseTree, rb);
    insert_hashtable(info->bd->RadioBaseHash, rb);
    free(id);
    if(x+5 > info->conf->x) { info->conf->x = x+5;}
    if(y+5 > info->conf->y) { info->conf->y = y+5;}
    return 1;
}

/*Configura as cores da Quadra*/
int configQuad(char *text, Info *info){
    char *aux, *cor1, *cor2;

    cor1 = (char*) calloc (55, sizeof(char));
    cor2 = (char*) calloc (55, sizeof(char));

    aux = text; aux += 3;
    sscanf(aux, "%s %s", cor1, cor2);

    strcpy(info->conf->cstrkQuad, cor1);
    strcpy(info->conf->cfillQuad, cor2);
    free(cor1);
    free(cor2);
    return 1;
}

/*Configura as cores do Hidrante*/
int configHidr(char *text, Info *info){
    char *aux, *cor1, *cor2;

    cor1 = (char*) calloc (55, sizeof(char));
    cor2 = (char*) calloc (55, sizeof(char));


    aux = text; aux += 3;
    sscanf(aux, "%s %s", cor1, cor2);

    strcpy(info->conf->cstrkHidr, cor1);
    strcpy(info->conf->cfillHidr, cor2);
    free(cor1);
    free(cor2);
    return 1;
}

/*Configura as cores da Torre de Radio*/
int configRBase(char *text, Info *info){
    char *aux, *cor1, *cor2;

    cor1 = (char*) calloc (55, sizeof(char));
    cor2 = (char*) calloc (55, sizeof(char));

    aux = text; aux += 3;
    sscanf(aux, "%s %s", cor1, cor2);

    strcpy(info->conf->cstrkRBase, cor1);
    strcpy(info->conf->cfillRBase, cor2);
    free(cor1);
    free(cor2);
    return 1;
}

/*Configura as cores dos Semaforos*/
int configSemaf(char *text, Info *info){
    char *aux, *cor1, *cor2;

    cor1 = (char*) calloc (55, sizeof(char));
    cor2 = (char*) calloc (55, sizeof(char));

    aux = text; aux += 3;
    sscanf(aux, "%s %s", cor1, cor2);

    strcpy(info->conf->cstrkSemaf, cor1);
    strcpy(info->conf->cfillSemaf, cor2);
    free(cor1);
    free(cor2);
    return 1;
}