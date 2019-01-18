#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../Item/item.h"
#include "../../Config/config.h"
#include "../../Circulo/circulo.h"
#include "../../Retangulo/retangulo.h"
#include "../../Anotacao/anotacao.h"
#include "../../Quadra/quadra.h"
#include "../../Radio-Base/radio-base.h"
#include "../../Semaforo/semaforo.h"
#include "../../Hidrante/hidrante.h"
#include "../../Pessoa/pessoa.h"
#include "../../Estabelecimento/estabelecimento.h"
#include "../../arvoreB/arvoreB.h"
#include "../../HashTable/hashtable.h"
#include "../../Registrador/registrador.h"
#include "../../Carro/carro.h"


/*Reporta quadras e equipamentos dentro do retanguo*/
void reportRec(char* text,Info *info){
        char* temp;
        temp = (char*) calloc (155, sizeof(char));
        strcpy(temp, text);
        insert_Fila(info->respQRY, temp);
        insert_Fila(info->respQRY, "\n");
        char *aux;
        double x, y , w, h;
        double xi, yi, xf, yf;
        void* i;
        Posic t;

        aux = text; aux += 3;
        sscanf(aux, "%lf %lf %lf %lf", &x, &y, &w, &h);

        /*info->quadras*/
        Lista quadras = KDT_getAll(info->bd->QuadrasTree);
        t=Lista_getFirst(quadras);
        while(1){
            i = Lista_get(quadras,t);
            if(i){

                Item it = Lista_get(quadras, t);
                void* rc = getRecQuad(it);                    

                xi = getXRec(rc);
                xf = xi + getWRec(rc);
                yi = getYRec(rc);
                yf = yi + getHRec(rc);

                if(xi >= x && yi >= y && xf <= x+w && yf <= y+h){

                    char * temp; temp = (char*) calloc(155, sizeof(char));
                    sprintf(temp, "Quadra. -  id: %s  -  x: %lf  -  y: %lf\n", getCepQuad(it), getXRec(rc), getYCirc(rc));
                    insert_Fila(info->respQRY, temp);
                }                    
                
                t = Lista_getNext(quadras, t);
            }else{
            break;
            }
        }

        /*hidrantes*/

        Lista hidrantes = KDT_getAll(info->bd->HidrantesTree);
        t=Lista_getFirst(hidrantes);
        while(1){
            i = Lista_get(hidrantes,t);
            if(i){
                
                Item it = Lista_get(hidrantes, t);
                void* circ = getCircHidr(it);

                xi = getXCirc(circ) - getRCirc(circ);
                xf = getXCirc(circ) + getRCirc(circ);
                yi = getYCirc(circ) - getRCirc(circ);
                yf = getYCirc(circ) + getRCirc(circ);

                if(xi >= x && yi >= y && xf <= x+w && yf <= y+h){
                    char * temp; temp = (char*) calloc(155, sizeof(char));
                    sprintf(temp, "Hidr. -  id: %s  -  x: %lf  -  y: %lf\n", getIdHidr(it), getXCirc(circ), getYCirc(circ));
                    insert_Fila(info->respQRY, temp);
                }                    
                
                t = Lista_getNext(hidrantes, t);
            }else{
            break;
            }
        }

        /*info->radio-base*/

        Lista radios = KDT_getAll(info->bd->RadioBaseTree);
        t=Lista_getFirst(radios);
        while(1){
            i = Lista_get(radios,t);
            if(i){
                
                Item it = Lista_get(radios, t);
                void* circ = getCircRadioB(it);

                xi = getXCirc(circ) - getRCirc(circ);
                xf = getXCirc(circ) + getRCirc(circ);
                yi = getYCirc(circ) - getRCirc(circ);
                yf = getYCirc(circ) + getRCirc(circ);

                if(xi >= x && yi >= y && xf <= x+w && yf <= y+h){
                    char * temp; temp = (char*) calloc(155, sizeof(char));
                    sprintf(temp, "Radios. -  id: %s  -  x: %lf  -  y: %lf\n", getIdRadioB(it), getXCirc(circ), getYCirc(circ));
                    insert_Fila(info->respQRY, temp);
                }                    
                
                t = Lista_getNext(radios, t);
            }else{
            break;
            }
        }

        /*info->semaforo*/

        Lista semaforos = KDT_getAll(info->bd->SemaforosTree);
        t=Lista_getFirst(semaforos);
        while(1){
            i = Lista_get(semaforos,t);
            if(i){
                
                Item it = Lista_get(semaforos, t);
                void* circ = getCircSemaf(it);

                xi = getXCirc(circ) - getRCirc(circ);
                xf = getXCirc(circ) + getRCirc(circ);
                yi = getYCirc(circ) - getRCirc(circ);
                yf = getYCirc(circ) + getRCirc(circ);

                if(xi >= x && yi >= y && xf <= x+w && yf <= y+h){
                    char * temp; temp = (char*) calloc(155, sizeof(char));
                    sprintf(temp, "Semaf. -  id: %s  -  x: %lf  -  y: %lf\n", getIdSemaf(it), getXCirc(circ), getYCirc(circ));
                    insert_Fila(info->respQRY, temp);
                }                    
                
                t = Lista_getNext(semaforos, t);
            }else{
            break;
            }
        }

    //imprimir resultados
    void* nt = createNotacao("Black", w, h, x, y, "");
    insert_Fila(info->notsQRY, nt);

}

/*Reporta quadras e quipamentos dentro do circulo*/
void reportCirc(char* text,Info* info){
        char* temp;
        temp = (char*) calloc (155, sizeof(char));
        strcpy(temp, text);
        insert_Fila(info->respQRY, temp);
        insert_Fila(info->respQRY, "\n");

        char *aux;
        double x, y, r;
        double xi, yi, xf, yf, ri;
        void* i;
        Posic t;

        aux = text; aux += 3;
        sscanf(aux, "%lf %lf %lf", &r, &x, &y);

        /*info->quadras*/

        Lista quadras = KDT_getAll(info->bd->QuadrasTree);
        t=Lista_getFirst(quadras);
        while(1){
            i = Lista_get(quadras,t);
            if(i){

                Item it = Lista_get(quadras, t);
                void* rc = getRecQuad(it);                    

                xi = getXRec(rc);
                xf = xi + getWRec(rc);
                yi = getYRec(rc);
                yf = yi + getHRec(rc);

                xi -= x;
                xf -= x;
                yi -= y;
                yf -= y;

                if(sqrt(xi*xi + yi*yi) <= r && sqrt(xf*xf + yf*yf) <= r
                    && sqrt(xi*xi + yf*yf) <= r && sqrt(xf*xf + yi*yi) <= r){
                    if(sqrt(xi*xi + yf*yf) <= r && sqrt(xf*xf + yi*yi) <= r){
                        char * temp; temp = (char*) calloc(155, sizeof(char));
                        sprintf(temp, "Quadra. -  id: %s  -  x: %lf  -  y: %lf\n", getCepQuad(it), getXRec(rc), getYCirc(rc));
                        insert_Fila(info->respQRY, temp);
                    }
                }

                t = Lista_getNext(quadras, t);
            }else{
            break;
            }
        }

        /*hidrantes*/

        Lista hidrantes = KDT_getAll(info->bd->HidrantesTree);
        t=Lista_getFirst(hidrantes);
        while(1){
            i = Lista_get(hidrantes,t);
            if(i){
                
                Item it = Lista_get(hidrantes, t);
                void* circ = getCircHidr(it);

                xi = getXCirc(circ);
                yi = getYCirc(circ);
                ri = getRCirc(circ);
                
                xi -= x;
                xf -= x;


                if(sqrt(xi*xi + yi*yi)+ri <= r){
                    char * temp; temp = (char*) calloc(155, sizeof(char));
                    sprintf(temp, "Hidr. -  id: %s  -  x: %lf  -  y: %lf\n", getIdHidr(it), getXCirc(circ), getYCirc(circ));
                    insert_Fila(info->respQRY, temp);
                }                   
                
                t = Lista_getNext(hidrantes, t);
            }else{
            break;
            }
        }

        /*info->radio-base*/

        Lista radios = KDT_getAll(info->bd->RadioBaseTree);
        t=Lista_getFirst(radios);
        while(1){
            i = Lista_get(radios,t);
            if(i){
                
                Item it = Lista_get(radios, t);
                void* circ = getCircRadioB(it);

                xi = getXCirc(circ);
                yi = getYCirc(circ);
                ri = getRCirc(circ);
                
                xi -= x;
                xf -= x;

                if(sqrt(xi*xi + yi*yi)+ri <= r){
                    char * temp; temp = (char*) calloc(155, sizeof(char));
                    sprintf(temp, "Radios. -  id: %s  -  x: %lf  -  y: %lf\n", getIdRadioB(it), getXCirc(circ), getYCirc(circ));
                    insert_Fila(info->respQRY, temp);
                }                   
                
                t = Lista_getNext(radios, t);
            }else{
            break;
            }
        }

        /*info->semaforo*/

        Lista semaforos = KDT_getAll(info->bd->SemaforosTree);
        t=Lista_getFirst(semaforos);
        while(1){
            i = Lista_get(semaforos,t);
            if(i){
                
                Item it = Lista_get(semaforos, t);
                void* circ = getCircSemaf(it);

                xi = getXCirc(circ);
                yi = getYCirc(circ);
                ri = getRCirc(circ);

                xi -= x;
                xf -= x;

                if(sqrt(xi*xi + yi*yi)+ri <= r){
                    char * temp; temp = (char*) calloc(155, sizeof(char));
                    sprintf(temp, "Semaf. -  id: %s  -  x: %lf  -  y: %lf\n", getIdSemaf(it), getXCirc(circ), getYCirc(circ));
                    insert_Fila(info->respQRY, temp);
                }                     
                
                t = Lista_getNext(semaforos, t);
            }else{
            break;
            }
        }

    //imprimir resultados
    void* nt = createNotacao("Black", r, 0, x, y, "");
    insert_Fila(info->notsQRY, nt);

}

/*Remove as quadras dentro do retangulo*/
void deleteQuadrasRec(char* text,Info* info){
        char* temp;
        temp = (char*) calloc (155, sizeof(char));
        strcpy(temp, text);
        insert_Fila(info->respQRY, temp);
        insert_Fila(info->respQRY, "\n");
        


        char *aux;
        double x, y , w, h;
        double xi, yi, xf, yf;
        void* i;
        Posic t;

        aux = text; aux += 3;
        sscanf(aux, "%lf %lf %lf %lf", &x, &y, &w, &h);


        /*info->quadras*/
        Lista quadras = KDT_getAll(info->bd->QuadrasTree);
        t=Lista_getFirst(quadras);
        printf("/n/n___  %d  ___\n\n",Lista_lenght(quadras));
        while(1){
            i = Lista_get(quadras,t);
            if(i){

                Item it = Lista_get(quadras, t);
                void* rc = getRecQuad(it);                    

                xi = getXRec(rc);
                xf = xi + getWRec(rc);
                yi = getYRec(rc);
                yf = yi + getHRec(rc);

                if(xi >= x && yi >= y && xf <= x+w && yf <= y+h){
                    char * temp1; temp1 = (char*) calloc(155, sizeof(char));
                    sprintf(temp1, "%s\n", getCepQuad(it));
                    insert_Fila(info->respQRY, temp1);

                    void* temp = Lista_getNext(quadras, t);
                    KDT_remove(info->bd->QuadrasTree, it);
                    remove_hashtable(info->bd->cepQuadraHash, it);
                    Lista_remove(quadras, t);
                    t = temp;  
                }else{              
                    t = Lista_getNext(quadras, t);
                }
            }else{
            break;
            }
        }


    //imprimir resultados
    void* nt = createNotacao("red", w, h, x, y, "");
    insert_Fila(info->notsQRY, nt);

}       

/*Remove equipamentos dentro do retangulo*/
void deleteUrbamEqRec(char* text,Info* info){
    char* temp;
        temp = (char*) calloc (155, sizeof(char));
        strcpy(temp, text);
        insert_Fila(info->respQRY, temp);
        insert_Fila(info->respQRY, "\n");


        char *aux, *cont, *auxcont;
        int hd = 0, sm = 0, rb = 0;
        double x, y , w, h;
        double xi, yi, xf, yf;
        void* i;
        Posic t;

        cont = (char*) calloc(155, sizeof(char));

        aux = text; aux += 4;
        sscanf(aux, "%s %lf %lf %lf %lf", cont, &x, &y, &w, &h);
        auxcont = cont;
        while(*cont){
            switch(*cont){
                case 'h':hd = 1;
                break;
                case 's':sm = 1;
                break;
                case 'r':rb = 1;
                break;
            }
            cont++;
        }
        free(auxcont);


        /*hidrantes*/
        Lista hidrantes = KDT_getAll(info->bd->HidrantesTree);
        Lista_lenght(hidrantes);
        t=Lista_getFirst(hidrantes);
        while(hd){
            i = Lista_get(hidrantes,t);
            if(i){
                
                Item it = Lista_get(hidrantes, t);
                void* circ = getCircHidr(it);

                xi = getXCirc(circ) - getRCirc(circ);
                xf = getXCirc(circ) + getRCirc(circ);
                yi = getYCirc(circ) - getRCirc(circ);
                yf = getYCirc(circ) + getRCirc(circ);

                if(xi >= x && yi >= y && xf <= x+w && yf <= y+h){
                    char * temp2; temp2 = (char*) calloc(155, sizeof(char));
                    sprintf(temp2, "Hidr. -  id: %s  -  x: %lf  -  y: %lf\n", getIdHidr(it), getXCirc(circ), getYCirc(circ));
                    insert_Fila(info->respQRY, temp2);
                    void* temp = Lista_getNext(hidrantes, t);
                    Lista_remove(hidrantes, t);
                    KDT_remove(info->bd->HidrantesTree, it);
                    remove_hashtable(info->bd->HidrantesHash, it);
                    t = temp;  
                }else{
                    t = Lista_getNext(hidrantes, t);
                }
            }else{
            break;
            }
        }

        /*info->radio-base*/

        Lista radios = KDT_getAll(info->bd->RadioBaseTree);
        t=Lista_getFirst(radios);
        while(rb){
            i = Lista_get(radios,t);
            if(i){
                
                Item it = Lista_get(radios, t);
                void* circ = getCircRadioB(it);

                xi = getXCirc(circ) - getRCirc(circ);
                xf = getXCirc(circ) + getRCirc(circ);
                yi = getYCirc(circ) - getRCirc(circ);
                yf = getYCirc(circ) + getRCirc(circ);

                if(xi >= x && yi >= y && xf <= x+w && yf <= y+h){
                    char * temp2; temp2 = (char*) calloc(155, sizeof(char));
                    sprintf(temp2, "Radios. -  id: %s  -  x: %lf  -  y: %lf\n", getIdRadioB(it), getXCirc(circ), getYCirc(circ));
                    insert_Fila(info->respQRY, temp2);
                    void* temp = Lista_getNext(radios, t);
                    Lista_remove(radios, t);
                    KDT_remove(info->bd->RadioBaseTree, it);
                    remove_hashtable(info->bd->RadioBaseHash, it);
                    t = temp;  
                }else{
                    t = Lista_getNext(radios, t);
                }
            }else{
            break;
            }
        }

        /*info->semaforo*/

        Lista semaforos = KDT_getAll(info->bd->SemaforosTree);
        t=Lista_getFirst(semaforos);
        while(sm){
            i = Lista_get(semaforos,t);
            if(i){
                
                Item it = Lista_get(semaforos, t);
                void* circ = getCircSemaf(it);

                xi = getXCirc(circ) - getRCirc(circ);
                xf = getXCirc(circ) + getRCirc(circ);
                yi = getYCirc(circ) - getRCirc(circ);
                yf = getYCirc(circ) + getRCirc(circ);

                if(xi >= x && yi >= y && xf <= x+w && yf <= y+h){
                    char * temp2; temp2 = (char*) calloc(155, sizeof(char));
                    sprintf(temp2, "Semaf. -  id: %s  -  x: %lf  -  y: %lf\n", getIdSemaf(it), getXCirc(circ), getYCirc(circ));
                    insert_Fila(info->respQRY, temp2);
                    void* temp = Lista_getNext(semaforos, t);
                    Lista_remove(semaforos, t);
                    KDT_remove(info->bd->SemaforosTree, it);
                    remove_hashtable(info->bd->SemaforosHash, it);
                    t = temp;  
                }else{
                    t = Lista_getNext(semaforos, t);
                }                
                
            }else{
            break;
            }
        }

    //imprimir resultados
    void* nt = createNotacao("Black", w, h, x, y, "");
    insert_Fila(info->notsQRY, nt);

}

/*Remove as quadras dentro do circulo*/
void deleteQuadrasCirc(char* text,Info* info){
        char* temp;
        temp = (char*) calloc (155, sizeof(char));
        strcpy(temp, text);
        insert_Fila(info->respQRY, temp);
        insert_Fila(info->respQRY, "\n");


        char *aux;
        double x, y , r;
        double xi, yi, xf, yf;
        void* i;
        Posic t;

        aux = text; aux += 3;
        sscanf(aux, "%lf %lf %lf", &r, &x, &y);

        Lista list;
        list = Lista_createLista();

        /*info->quadras*/

        Lista quadras = KDT_getAll(info->bd->QuadrasTree);
        t=Lista_getFirst(quadras);
        while(1){
            i = Lista_get(quadras,t);
            if(i){

                Item it = Lista_get(quadras, t);
                void* rc = getRecQuad(it);                    

                xi = getXRec(rc);
                xf = xi + getWRec(rc);
                yi = getYRec(rc);
                yf = yi + getHRec(rc);

                xi -= x;
                xf -= x;
                yi -= y;
                yf -= y;

                if(sqrt(xi*xi + yi*yi) <= r && sqrt(xf*xf + yf*yf) <= r
                    && sqrt(xi*xi + yf*yf) <= r && sqrt(xf*xf + yi*yi) <= r){
                    char * temp1; temp1 = (char*) calloc(155, sizeof(char));
                    sprintf(temp1, "%s\n", getCepQuad(it));
                    insert_Fila(info->respQRY, temp1);
                    void* temp = Lista_getNext(quadras, t);
                    Lista_remove(quadras, t);
                    KDT_remove(info->bd->QuadrasTree, it);
                    remove_hashtable(info->bd->cepQuadraHash, it);
                    t = temp;                    
                }else{
                    t = Lista_getNext(quadras, t);
                }                            
            }else{
            break;
            }
        }


    //imprimir resultados
    void* nt = createNotacao("red", r, 0, x, y, "");
    insert_Fila(info->notsQRY, nt);



}   
/*Remove os equipamentos dentro do circulo*/
void deleteUrbamEqCirc(char* text,Info* info){
        char* temp;
        temp = (char*) calloc (155, sizeof(char));
        strcpy(temp, text);
        insert_Fila(info->respQRY, temp);
        insert_Fila(info->respQRY, "\n");


        char *aux, *cont, *auxcont;
        int hd = 0, sm = 0, rb = 0;
        double x, y , r;
        double xi, yi, xf, yf, ri;
        void* i;
        Posic t;
        cont = (char*) calloc(155, sizeof(char));

        aux = text; aux += 4;
        sscanf(aux, "%s %lf %lf %lf", cont, &x, &y, &r);
        auxcont = cont;
        while(*cont){
            switch(*cont){
                case 'h':hd = 1;
                break;
                case 's':sm = 1;
                break;
                case 'r':rb = 1;
                break;
            }
            cont++;
        }
        free(auxcont);

        /*hidrantes*/

        Lista hidrantes = KDT_getAll(info->bd->HidrantesTree);
        t=Lista_getFirst(hidrantes);
        while(hd){
            i = Lista_get(hidrantes,t);
            if(i){
                
                Item it = Lista_get(hidrantes, t);
                void* circ = getCircHidr(it);

                xi = getXCirc(circ);
                yi = getYCirc(circ);
                ri = getRCirc(circ);

                xi -= x;
                yi -= y;

                if(sqrt(xi*xi + yi*yi)+ri <= r){
                    char * temp2; temp2 = (char*) calloc(155, sizeof(char));
                    sprintf(temp2, "Hidr. -  id: %s  -  x: %lf  -  y: %lf\n", getIdHidr(it), getXCirc(circ), getYCirc(circ));
                    insert_Fila(info->respQRY, temp2);
                    void* temp = Lista_getNext(hidrantes, t);
                    Lista_remove(hidrantes, t);
                    KDT_remove(info->bd->HidrantesTree, it);
                    remove_hashtable(info->bd->HidrantesHash, it);
                    t = temp;  
                }else{
                    t = Lista_getNext(hidrantes, t);
                }
                
            }else{
            break;
            }
        }

        /*info->radio-base*/

        Lista radios = KDT_getAll(info->bd->RadioBaseTree);
        t=Lista_getFirst(radios);
        while(rb){
            i = Lista_get(radios,t);
            if(i){
                
                Item it = Lista_get(radios, t);
                void* circ = getCircRadioB(it);

                xi = getXCirc(circ);
                yi = getYCirc(circ);
                ri = getRCirc(circ);

                xi -= x;
                yi -= y;

                if(sqrt(xi*xi + yi*yi)+ri <= r){
                    char * temp2; temp2 = (char*) calloc(155, sizeof(char));
                    sprintf(temp2, "Radios. -  id: %s  -  x: %lf  -  y: %lf\n", getIdRadioB(it), getXCirc(circ), getYCirc(circ));
                    insert_Fila(info->respQRY, temp2);
                    void* temp = Lista_getNext(radios, t);
                    Lista_remove(radios, t);
                    KDT_remove(info->bd->RadioBaseTree, it);
                    remove_hashtable(info->bd->RadioBaseHash, it);
                    t = temp;  
                }else{
                    t = Lista_getNext(radios, t);
                }
                
            }else{
            break;
            }
        }

        /*info->semaforo*/

        Lista semaforos = KDT_getAll(info->bd->SemaforosTree);
        t=Lista_getFirst(semaforos);
        while(sm){
            i = Lista_get(semaforos,t);
            if(i){
                
                Item it = Lista_get(semaforos, t);
                void* circ = getCircSemaf(it);

                xi = getXCirc(circ);
                yi = getYCirc(circ);
                ri = getRCirc(circ);

                xi -= x;
                yi -= y;

                if(sqrt(xi*xi + yi*yi)+ri <= r){
                    char * temp2; temp2 = (char*) calloc(155, sizeof(char));
                    sprintf(temp2, "Semaf. -  id: %s  -  x: %lf  -  y: %lf\n", getIdSemaf(it), getXCirc(circ), getYCirc(circ));
                    insert_Fila(info->respQRY, temp2);
                    void* temp = Lista_getNext(semaforos, t);
                    Lista_remove(semaforos, t);
                    KDT_remove(info->bd->SemaforosTree, it);
                    remove_hashtable(info->bd->SemaforosHash, it);
                    t = temp;  
                }else{
                    t = Lista_getNext(semaforos, t);
                }
                
            }else{
            break;
            }
        }

    //imprimir resultados
    void* nt = createNotacao("Black", r, 0, x, y, "");
    insert_Fila(info->notsQRY, nt);

}

/*Muda a cor do item relacionado ao id/cep passado*/
void colorChange(char* text,Info* info){
        char *aux, *ident, *strok, *fill;
        Posic t;
        void* i;

        aux = text; aux += 3;

        ident = (char*) calloc(155, sizeof(char));
        strok = (char*) calloc(155, sizeof(char));
        fill = (char*) calloc(155, sizeof(char));
        
        sscanf(aux, "%s %s %s", ident, strok, fill);

            /*info->quadras*/

        Lista quadras = KDT_getAll(info->bd->QuadrasTree);
        t=Lista_getFirst(quadras);
        while(1){
            i = Lista_get(quadras,t);
            if(i){

                Item it = Lista_get(quadras, t);
                if(!strcmp(getCepQuad(it), ident)){
                    setColorStrokeQuad(it, strok);
                    setColorFillQuad(it, fill);
                    free(ident);
                    free(strok);
                    free(fill);
                    return;
                }                                        
                t = Lista_getNext(quadras, t);
            }else{
            break;
            }
        }

        /*hidrantes*/

        Lista hidrantes = KDT_getAll(info->bd->HidrantesTree);
        t=Lista_getFirst(hidrantes);
        while(1){
            i = Lista_get(hidrantes,t);
            if(i){
                
                Item it = Lista_get(hidrantes, t);
                char *temp;                     
                temp = (char*) calloc(155, sizeof(char));
                sprintf(temp, "%s", getIdHidr(it));

                if(!strcmp(temp, ident)){
                    setColorStrokeHidr(it, strok);
                    setColorFillHidr(it, fill);
                    free(ident);
                    free(strok);
                    free(fill);
                    return;
                }                    
                
                t = Lista_getNext(hidrantes, t);
            }else{
            break;
            }
        }

        /*info->radio-base*/

        Lista radios = KDT_getAll(info->bd->RadioBaseTree);
        t=Lista_getFirst(radios);
        while(1){
            i = Lista_get(radios,t);
            if(i){
                
                Item it = Lista_get(radios, t);
                char *temp;                     
                temp = (char*) calloc(155, sizeof(char));
                sprintf(temp, "%s", getIdRadioB(it));

                if(!strcmp(temp, ident)){
                    setColorStrokeRB(it, strok);
                    setColorFillRB(it, fill);
                    free(ident);
                    free(strok);
                    free(fill);
                    return;
                }            
                
                t = Lista_getNext(radios, t);
            }else{
            break;
            }
        }

        /*info->semaforo*/

        Lista semaforos = KDT_getAll(info->bd->SemaforosTree);
        t=Lista_getFirst(semaforos);    
        while(1){
            i = Lista_get(semaforos,t);
            if(i){
                
                Item it = Lista_get(semaforos, t);
                char *temp;                     
                temp = (char*) calloc(155, sizeof(char));
                sprintf(temp, "%s", getIdSemaf(it));

                if(!strcmp(temp, ident)){
                    setColorStrokeSemaf(it, strok);
                    setColorFillSemaf(it, fill);
                    free(ident);
                    free(strok);
                    free(fill);
                    return;
                }                  
                
                t = Lista_getNext(semaforos, t);
            }else{
            break;
            }
        }
        free(ident);
        free(strok);
        free(fill);
}

/*informa as cordenadas e o ID do item passado, se for uma quadra, 
retorna as cordenadas e id's de todos os equipamentos presentes nela*/
void equipOnCepOrId(char* text,Info* info){
    char* temp;
    temp = (char*) calloc (155, sizeof(char));
    strcpy(temp, text);
    insert_Fila(info->respQRY, temp);
    insert_Fila(info->respQRY, "\n");


    char *aux, *ident;
    Posic t;
    void* i;

    aux = text; aux += 5;
    ident = (char*) calloc(155, sizeof(char));
    sscanf(aux, "%s", ident);


    /*hidrantes*/

        Lista hidrantes = KDT_getAll(info->bd->HidrantesTree);
        t=Lista_getFirst(hidrantes);
        while(1){
            i = Lista_get(hidrantes,t);
            if(i){
                
                Item it = Lista_get(hidrantes, t);
                char *temp;                     
                temp = (char*) calloc(155, sizeof(char));
                
                sprintf(temp, "%s", getIdHidr(it));

                if(!strcmp(temp, ident)){
                    sprintf(temp, "Hidr. -  id: %s  -  x: %lf  -  y: %lf\n", getIdHidr(it), getXCirc(getCircHidr(it)), getYCirc(getCircHidr(it)));
                    insert_Fila(info->respQRY, temp);
                    free(ident);
                    return;
                }                    
                
                t = Lista_getNext(hidrantes, t);
            }else{
            break;
            }
        }

        /*info->radio-base*/

        Lista radios = KDT_getAll(info->bd->RadioBaseTree);
        t=Lista_getFirst(radios);
        while(1){
            i = Lista_get(radios,t);
            if(i){
                
                Item it = Lista_get(radios, t);
                char *temp;                     
                temp = (char*) calloc(155, sizeof(char));
                sprintf(temp, "%s", getIdRadioB(it));

                if(!strcmp(temp, ident)){
                    sprintf(temp, "Radio-Base. -  id: %s  -  x: %lf  -  y: %lf\n", getIdRadioB(it), getXCirc(getCircRadioB(it)), getYCirc(getCircRadioB(it)));
                    insert_Fila(info->respQRY, temp);
                    free(ident);
                    return;
                }                
                
                t = Lista_getNext(radios, t);
            }else{
            break;
            }
        }

        /*info->semaforo*/

        Lista semaforos = KDT_getAll(info->bd->SemaforosTree);
        t=Lista_getFirst(semaforos);
        while(1){
            i = Lista_get(semaforos,t);
            if(i){
                
                Item it = Lista_get(semaforos, t);
                char *temp;                     
                temp = (char*) calloc(155, sizeof(char));
                sprintf(temp, "%s", getIdSemaf(it));

                if(!strcmp(temp, ident)){
                    sprintf(temp, "Semaforo. -  id: %s  -  x: %lf  -  y: %lf\n", getIdSemaf(it), getXCirc(getCircSemaf(it)), getYCirc(getCircSemaf(it)));
                    insert_Fila(info->respQRY, temp);
                    free(ident);
                    return;
                }                 
                
                t = Lista_getNext(semaforos, t);
            }else{
            break;
            }
        }


        //achar cep

        void* rt;
        rt = NULL;
        Lista quadras = KDT_getAll(info->bd->QuadrasTree);
        t=Lista_getFirst(quadras);
        while(1){
            i = Lista_get(quadras,t);
            if(i){

                Item it = Lista_get(quadras, t);
                if(!strcmp(getCepQuad(it), ident)){
                    rt = getRecQuad(it);
                    free(ident);
                    break;
                }                                        
                t = Lista_getNext(quadras, t);
            }else{
            break;
            }
        }

        if(rt == NULL){
            return;
        }
        double x, y, w, h;
        x = getXRec(rt);
        y = getYRec(rt);
        w = getWRec(rt);
        h = getHRec(rt);

        double xi, xf, yi, yf;

        t=Lista_getFirst(hidrantes);
        while(1){
            i = Lista_get(hidrantes,t);
            if(i){
                
                Item it = Lista_get(hidrantes, t);
                void* circ = getCircHidr(it);

                xi = getXCirc(circ) - getRCirc(circ);
                xf = getXCirc(circ) + getRCirc(circ);
                yi = getYCirc(circ) - getRCirc(circ);
                yf = getYCirc(circ) + getRCirc(circ);

                if(xi >= x && yi >= y && xf <= x+w && yf <= y+h){
                    char * temp; temp = (char*) calloc(155, sizeof(char));
                    sprintf(temp, "Hidr. -  id: %s  -  x: %lf  -  y: %lf\n", getIdHidr(it), getXCirc(circ), getYCirc(circ));
                    insert_Fila(info->respQRY, temp);
                }                    
                
                t = Lista_getNext(hidrantes, t);
            }else{
            break;
            }
        }

        /*info->radio-base*/


        t=Lista_getFirst(radios);
        while(1){
            i = Lista_get(radios,t);
            if(i){
                
                Item it = Lista_get(radios, t);
                void* circ = getCircRadioB(it);

                xi = getXCirc(circ) - getRCirc(circ);
                xf = getXCirc(circ) + getRCirc(circ);
                yi = getYCirc(circ) - getRCirc(circ);
                yf = getYCirc(circ) + getRCirc(circ);

                if(xi >= x && yi >= y && xf <= x+w && yf <= y+h){
                    char * temp; temp = (char*) calloc(155, sizeof(char));
                    sprintf(temp, "Radio-Base. -  id: %s  -  x: %lf  -  y: %lf\n", getIdRadioB(it), getXCirc(circ), getYCirc(circ));
                    insert_Fila(info->respQRY, temp);
                }                    
                
                t = Lista_getNext(radios, t);
            }else{
            break;
            }
        }

        /*info->semaforo*/


        t=Lista_getFirst(semaforos);
        while(1){
            i = Lista_get(semaforos,t);
            if(i){
                
                Item it = Lista_get(semaforos, t);
                void* circ = getCircSemaf(it);

                xi = getXCirc(circ) - getRCirc(circ);
                xf = getXCirc(circ) + getRCirc(circ);
                yi = getYCirc(circ) - getRCirc(circ);
                yf = getYCirc(circ) + getRCirc(circ);

                if(xi >= x && yi >= y && xf <= x+w && yf <= y+h){
                    char * temp; temp = (char*) calloc(155, sizeof(char));
                    sprintf(temp, "Semaforo. -  id: %s  -  x: %lf  -  y: %lf\n", getIdSemaf(it), getXCirc(circ), getYCirc(circ));
                    insert_Fila(info->respQRY, temp);
                }                    
                
                t = Lista_getNext(semaforos, t);
            }else{
            break;
            }
        }


}



/*encontra as radio-base mais proximas, e informa id's e distancia*/
void closestRBase(char* text,Info* info){
    Lista radios = KDT_getAll(info->bd->RadioBaseTree);
    insert_Fila(info->respQRY, "crb?\n");

    void *t, *i;
    void *it1, *it2, *itTemp;
    double minDist = -1;
    it1 = NULL, it2 = NULL;
    t=Lista_getFirst(radios);
    while(1){
        i = Lista_get(radios,t);
        if(i){
            itTemp = closestNeibord(info->bd->RadioBaseTree, i);
            double a;
            double b;
            a = getXCirc(getCircRadioB(i)) - getXCirc(getCircRadioB(itTemp));
            b = getYCirc(getCircRadioB(i)) - getYCirc(getCircRadioB(itTemp));
            a = a*a;
            b = b*b;
            double dist = sqrt( a + b);
            if(minDist < 0 || dist < minDist && i != itTemp){
                minDist = dist;
                it1 = i;
                it2 = itTemp;
            }
            t = Lista_getNext(radios, t);
        }else{
        break;
        }
    }

    
    
    char* temp;
    temp = (char*) calloc(155, sizeof(char));
    sprintf(temp, "id: %s e %s  -   Dist: %lf", getIdRadioB(it1), getIdRadioB(it2), minDist);
    insert_Fila(info->respQRY, temp);

    double xt, yt;
    void* nt;
    void* cr;
    //criar as duas anotações
    cr = getCircRadioB(it1);
    xt = getXCirc(cr);
    yt = getYCirc(cr);
    nt = createNotacao("BLACK", 15, 0, xt, yt, "");
    Lista_insert(info->notsQRY, nt);

    cr = getCircRadioB(it2);
    xt = getXCirc(cr);
    yt = getYCirc(cr);
    nt = createNotacao("BLACK", 15, 0, xt, yt, "");
    Lista_insert(info->notsQRY, nt);
}

void closeQRY(Info* info){
    int i;
    char* path, *aux, *aux2;
    FILE *arqSVG_QRY, *arqTXT;

    void *auxN, *auxF, *t, *temp; 

    //configurar path e abrir arquivo
    path = (char*) calloc (255, sizeof(char));
    sprintf(path, "%s/%s", info->o, info->f);
    // if(*path == '/') path++;
    aux = path;
    aux += strlen(path);
    while(*aux != '.')aux--;
    *aux = 0;
    aux = info->q;
    while(*aux){
        if(*aux == '/'){
            aux2 = aux+1;
        }
        aux++;
    }
    sprintf(path, "%s-%s", path, aux2);
    aux = path;
    aux += strlen(path);
    while(*aux != '.')aux--;
    strcpy(aux, ".svg");
    arqSVG_QRY = fopen(path, "w");

    //imprimir circulos e retangulos
    fprintf(arqSVG_QRY,"<svg xmlns=\"http://www.w3.org/2000/svg\" width = \"%lf\" height = \"%lf\">\n", info->conf->x, info->conf->y);

    t=Lista_getFirst(info->bd->Drawer);
    while(1){
        temp = Lista_get(info->bd->Drawer,t);
        if(temp){
            
            Item it = Lista_get(info->bd->Drawer, t);
            fprintf(arqSVG_QRY, "%s\n", createSvg(it));
            t = Lista_getNext(info->bd->Drawer, t);
        }else{
        break;
        }
    }

    //Imprimir notas GEO
    auxF = create_Fila();
    while(!empty_Fila(info->notsGeo)){
        auxN = (void*) remove_Fila(info->notsGeo);
        insert_Fila(auxF,(void*) auxN);
        fprintf(arqSVG_QRY, "%s\n", createNotacaoSvg(auxN));
    }
    free(info->notsGeo);
    info->notsGeo = auxF;

    //imprimir notas QRY
    auxF = create_Fila();
    while(!empty_Fila(info->notsQRY)){
        auxN = (void*) remove_Fila(info->notsQRY);
        insert_Fila(auxF,(void*) auxN);
        fprintf(arqSVG_QRY, "%s\n", createNotacaoSvg(auxN));
    }
    free(info->notsQRY);
    info->notsQRY = auxF;

    //imprimir quadras
    Lista quadras = KDT_getAll(info->bd->QuadrasTree);
    t=Lista_getFirst(quadras);
    while(1){
        temp = Lista_get(quadras,t);
        if(temp){
            
            Item it = Lista_get(quadras, t);
            fprintf(arqSVG_QRY, "%s\n", createQuadraSvg(it));
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
            fprintf(arqSVG_QRY, "%s\n", createSemaforoSvg(it));
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
            fprintf(arqSVG_QRY, "%s\n", createHidranteSvg(it));
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
            fprintf(arqSVG_QRY, "%s\n", createRadioBSvg(it));
            t = Lista_getNext(radios, t);
        }else{
        break;
        }
    }

    //imprimir carros
    Lista carros = KDT_getAll(info->bd->carroTree);
    t=Lista_getFirst(carros);
    while(1){
        temp = Lista_get(carros,t);
        if(temp){          
              
            Item it = Lista_get(carros, t);
            fprintf(arqSVG_QRY, "%s\n", createCarroSVG(it));
            t = Lista_getNext(carros, t);
        }else{
        break;
        }
    }

    fprintf(arqSVG_QRY,"</svg>");

    fclose(arqSVG_QRY);

    aux = path;
    aux += strlen(path);
    while(*aux != '.')aux--;
    strcpy(aux, ".txt");

    arqTXT = fopen(path, "w");


    while(!empty_Fila(info->respGEO)){
        aux = (char*) remove_Fila(info->respGEO);
        fprintf(arqTXT, "%s", aux);
    }


    while(!empty_Fila(info->respQRY)){
        aux = (char*) remove_Fila(info->respQRY);
        fprintf(arqTXT, "%s", aux);
    }
    freeFila(info->respQRY);
    fclose(arqTXT);
    free(path);

}

char* moradoresQuadra(char* cep, Info* info){
    void* ident = Pessoa_IdentEndereco(cep);
    Lista enderecos = getList_hashtable(info->bd->enderecoPessoa, ident);
    char *result;
    result = (char*) calloc(Lista_lenght(enderecos)*510, sizeof(char));
    strcpy(result, "");
    void* t=Lista_getFirst(enderecos);
    while(1){
        void* temp = Lista_get(enderecos,t);
        if(temp){
            void* pessoa = Pessoa_getPessoaEndereco(temp);
            if(pessoa!=NULL)
                strcat(result, Pessoa_relatorio(pessoa));
            t = Lista_getNext(enderecos, t);
        }else{
        break;
        }
    }
    return result;
}

void whoIsHere(char* text, Info* info){
    char* aux, *cep;
    aux = (char*) calloc(strlen(text)+2, sizeof(char));
    strcpy(aux, text);
    insert_Fila(info->respQRY, aux);
    insert_Fila(info->respQRY, "\n");
    aux = text;
    aux+=3;
    cep = (char*) calloc(1, sizeof(char));
    sscanf(aux, "%s", cep);
    char* result;
    result = moradoresQuadra(cep, info);
    insert_Fila(info->respQRY, result);
    insert_Fila(info->respQRY, "\n");
    free(cep);
}

void whoIsInThisArea(char* text, Info* info){
    char* temp;
    temp = (char*) calloc (155, sizeof(char));
    strcpy(temp, text);
    insert_Fila(info->respQRY, temp);
    insert_Fila(info->respQRY, "\n");
    char *aux;
    double x, y , w, h;
    double xi, yi, xf, yf;
    void* i;
    Posic t;

    aux = text; aux += 4;
    sscanf(aux, "%lf %lf %lf %lf", &x, &y, &w, &h);

    /*info->quadras*/
    Lista quadras = KDT_getAll(info->bd->QuadrasTree);
    t=Lista_getFirst(quadras);
    while(1){
        i = Lista_get(quadras,t);
        if(i){

            Item it = Lista_get(quadras, t);
            void* rc = getRecQuad(it);                    

            xi = getXRec(rc);
            xf = xi + getWRec(rc);
            yi = getYRec(rc);
            yf = yi + getHRec(rc);

            if(xi >= x && yi >= y && xf <= x+w && yf <= y+h){
                char* result;
                result = moradoresQuadra(getCepQuad(it), info);
                insert_Fila(info->respQRY, result);
            }                    
            
            t = Lista_getNext(quadras, t);
        }else{
        break;
        }
    }
}

void whoAreYou(char* text, Info* info){
    char* temp;
    temp = (char*) calloc (155, sizeof(char));
    strcpy(temp, text);
    insert_Fila(info->respQRY, temp);
    insert_Fila(info->respQRY, "\n");
    char *aux, *cpf;
    cpf = (char*) calloc(55, sizeof(char));
    aux = text; aux += 4;
    sscanf(aux, "%s", cpf);
    void* p = Pessoa_create(cpf, "", "", "", "");
    void* pessoa = get_hashtable(info->bd->PessoaCepHash, p);
    Pessoa_Free(p);
    if(pessoa == NULL){
        insert_Fila(info->respQRY, "Pessoa não encontrada\n");
        free(cpf);
        return;
    }
    double* cord = Pessoa_getCordGeo(pessoa, info);
    if(cord == NULL){
       char* result;
        result = (char*) calloc(255, sizeof(char));
        sprintf(result, "%s\n", Pessoa_relatorio(pessoa));
        insert_Fila(info->respQRY, result);
    }else{
        char* result;
        result = (char*) calloc(255, sizeof(char));
        sprintf(result, "%s (Cordenadas [%lf,%lf])\n", Pessoa_relatorio(pessoa), cord[0], cord[1]);
        insert_Fila(info->respQRY, result);
        void* nt = createNotacao("RED", 5, 0, cord[0], cord[1], cpf);
        insert_Fila(info->notsQRY, nt);
    }
    free(cpf);
}

void whoAreYouEstab(char* text, Info* info){
    char* temp;
    temp = (char*) calloc (155, sizeof(char));
    strcpy(temp, text);
    insert_Fila(info->respQRY, temp);
    insert_Fila(info->respQRY, "\n");
    char *aux, *cnpj;
    cnpj = (char*) calloc(55, sizeof(char));
    aux = text; aux += 4;
    sscanf(aux, "%s", cnpj);
    void* e = Estab_create(info, cnpj, NULL, "", "", "", "");
    void* estab = get_hashtable(info->bd->EstabHash, e);
    Estab_Free(e);
    if(estab == NULL){
        insert_Fila(info->respQRY, "Estabelecimento não encontrado\n");
        free(cnpj);
        return;
    }
    double* cord = Estab_getCordGeo(estab);
    if(cord == NULL){
       char* result;
        result = (char*) calloc(255, sizeof(char));
        sprintf(result, "%s\n", Estab_relatorio(estab));
        insert_Fila(info->respQRY, result);
    }else{
        char* result;
        result = (char*) calloc(255, sizeof(char));
        sprintf(result, "%s (Cordenadas [%lf,%lf])\n", Estab_relatorio(estab), cord[0], cord[1]);
        insert_Fila(info->respQRY, result);
        void* nt = createNotacao("PURPLE", 5, 0, cord[0], cord[1], cnpj);
        insert_Fila(info->notsQRY, nt);
    }
    free(cnpj);
}

/*Mãe, no céu tem Pão? e Morreu...*/
void bread(char* text, Info* info){
    char *aux, *cpf;
    aux = (char*) calloc (155, sizeof(char));
    strcpy(aux, text);
    insert_Fila(info->respQRY, aux);
    insert_Fila(info->respQRY, "\n");
    cpf = (char*) calloc(55, sizeof(char));
    aux = text; aux += 4;
    sscanf(aux, "%s", cpf);
    void* *p = Pessoa_create(cpf, "", "", "", "");
    void* pessoa = get_hashtable(info->bd->PessoaCepHash, p);
    Pessoa_Free(p);
    if(pessoa == NULL){
        insert_Fila(info->respQRY, "Esta pessoa não existe\n");
        free(cpf);
        return;
    }
    double* cord = Pessoa_getCordGeo(pessoa, info);
    if(cord == NULL){
       char* result;
        result = (char*) calloc(255, sizeof(char));
        sprintf(result, "%s\n", Pessoa_relatorio(pessoa));
        insert_Fila(info->respQRY, result);
    }else{
        char* result;
        result = (char*) calloc(255, sizeof(char));
        sprintf(result, "%s\n", Pessoa_relatorio(pessoa));
        insert_Fila(info->respQRY, result);
        void* nt = createNotacao("RED", 0, 1, cord[0], cord[1], cpf);
        insert_Fila(info->notsQRY, nt);
    }
    //remove
    remove_hashtable(info->bd->PessoaCepHash, pessoa);
    void* end = Pessoa_getEndereco(pessoa);
    if(end != NULL)
    remove_hashtable(info->bd->enderecoPessoa, end);
    free(cpf);
}


char* estabsQuadra(char* cep, Info* info, char* tipo){
    void* ident = Estab_IdentEndereco(cep);
    Lista enderecos = getList_hashtable(info->bd->enderecoEstab, ident);
    char *result;
    result = (char*) calloc(Lista_lenght(enderecos)*510, sizeof(char));
    strcpy(result, "");
    void* t=Lista_getFirst(enderecos);
    while(1){
        void* temp = Lista_get(enderecos,t);
        if(temp){
            void* estab = Estab_getEstabEndereco(temp);
            if(estab!=NULL && (tipo == NULL || strcmp(tipo, Estab_getTipoCod(estab)) == 0)){
                strcat(result, Estab_relatorio(estab));
                strcat(result, "\n");
            }
            t = Lista_getNext(enderecos, t);
        }else{
        break;
        }
    }
    return result;
}

void whatHaveHere(char* text, Info* info){
    char* aux, *cep;
    aux = (char*) calloc(strlen(text)+2, sizeof(char));
    strcpy(aux, text);
    insert_Fila(info->respQRY, aux);
    insert_Fila(info->respQRY, "\n");
    aux = text;
    aux+=5;
    cep = (char*) calloc(1, sizeof(char));
    sscanf(aux, "%s", cep);
    char* result;
    result = estabsQuadra(cep, info, NULL);
    insert_Fila(info->respQRY, result);
    free(cep);
}

void whatHaveInThisArea(char* text, Info* info){
    char* temp;
    temp = (char*) calloc (155, sizeof(char));
    strcpy(temp, text);
    insert_Fila(info->respQRY, temp);
    insert_Fila(info->respQRY, "\n");
    char *aux, *tipo;
    int ctrl;
    double x, y , w, h;
    double xi, yi, xf, yf;
    void* i;
    Posic t;
    tipo = (char*) calloc(55, sizeof(char));

    aux = text; aux += 5;
    sscanf(aux, "%s", tipo);
    if(strlen(aux) - strlen(tipo) > 5){
        ctrl = 0;
        sscanf(aux, "%s %lf %lf %lf %lf", tipo, &x, &y, &w, &h);
    }else{
        ctrl = 1;
    }

    /*info->quadras*/
    Lista quadras = KDT_getAll(info->bd->QuadrasTree);
    t=Lista_getFirst(quadras);
    while(1){
        i = Lista_get(quadras,t);
        if(i){

            Item it = Lista_get(quadras, t);
            void* rc = getRecQuad(it);                    

            xi = getXRec(rc);
            xf = xi + getWRec(rc);
            yi = getYRec(rc);
            yf = yi + getHRec(rc);

            if((ctrl == 1) || (xi >= x && yi >= y && xf <= x+w && yf <= y+h)){
                char* result;
                result = estabsQuadra(getCepQuad(it), info, tipo);
                insert_Fila(info->respQRY, result);
            }                    
            
            t = Lista_getNext(quadras, t);
        }else{
        break;
        }
    }
    free(tipo);
}

char* estabsQuadra_typeOrderPrint(Lista estabs){
        char *result;
        result = (char*) calloc(Lista_lenght(estabs)*510, sizeof(char));
        strcpy(result, "");
        while(Lista_lenght(estabs) > 0){
        void* t=Lista_getFirst(estabs);
        char* control;
        control = Estab_getTipoCod(Lista_get(estabs,t));
        strcat(result, Estab_Tipo(Lista_get(estabs,t)));
        strcat(result, ":\n");
        while(1){
            void* temp = Lista_get(estabs,t);
            if(temp){
                char * testAux = Estab_getTipoCod(temp);
                if(strcmp(control, testAux) == 0){
                    strcat(result, Estab_Name(temp));
                    strcat(result, "\n");
                    void* taux = Lista_getNext(estabs, t);
                    Lista_remove(estabs, t);
                    t = taux;
                    continue;
                }
                t = Lista_getNext(estabs, t);
            }else{
            break;
            }
        }
    }
    return result;
}

Lista estabsQuadra_typeOrder(char* cep, Info* info, char* tipo){
    void* ident = Estab_IdentEndereco(cep);
    Lista enderecos = getList_hashtable(info->bd->enderecoEstab, ident);
    Lista estabs = Lista_createLista();
    void* t=Lista_getFirst(enderecos);
    while(1){
        void* temp = Lista_get(enderecos,t);
        if(temp){
            void* estab = Estab_getEstabEndereco(temp);
            if(estab!=NULL && (tipo == NULL || strcmp(tipo, Estab_getTipoCod(estab)) == 0)){
                Lista_insert(estabs, estab);
            }
            t = Lista_getNext(enderecos, t);
        }else{
        break;
        }
    }
    freeLista(enderecos);
    return estabs;
}

void whatHaveHere_typeOrder(char* text, Info* info){
    char* aux, *cep;
    aux = (char*) calloc(strlen(text)+2, sizeof(char));
    strcpy(aux, text);
    insert_Fila(info->respQRY, aux);
    insert_Fila(info->respQRY, "\n");
    aux = text;
    aux+=6;
    cep = (char*) calloc(55, sizeof(char));
    sscanf(aux, "%s", cep);
    char* result;
    result = estabsQuadra_typeOrderPrint(estabsQuadra_typeOrder(cep, info, NULL));
    insert_Fila(info->respQRY, result);
    free(cep);
}

void whatHaveInThisArea_typeOrder(char* text, Info* info){
    char* temp;
    temp = (char*) calloc (155, sizeof(char));
    strcpy(temp, text);
    insert_Fila(info->respQRY, temp);
    insert_Fila(info->respQRY, "\n");
    char *aux;
    double x, y , w, h;
    double xi, yi, xf, yf;
    void* i;
    Posic t;

    aux = text; aux += 6;
    sscanf(aux, "%lf %lf %lf %lf",&x, &y, &w, &h);

    /*info->quadras*/
    Lista quadras = KDT_getAll(info->bd->QuadrasTree);
    t=Lista_getFirst(quadras);
    Lista estabs;
    estabs = Lista_createLista();
    while(1){
        i = Lista_get(quadras,t);
        if(i){

            Item it = Lista_get(quadras, t);
            void* rc = getRecQuad(it);                    

            xi = getXRec(rc);
            xf = xi + getWRec(rc);
            yi = getYRec(rc);
            yf = yi + getHRec(rc);
            if(xi >= x && yi >= y && xf <= x+w && yf <= y+h){
                Lista_insertLista(estabs, estabsQuadra_typeOrder(getCepQuad(it), info, NULL));   
            }   
            t = Lista_getNext(quadras, t);
        }else{
        break;
        }
    }
    char* result;
    result = estabsQuadra_typeOrderPrint(estabs);                 
    insert_Fila(info->respQRY, result);
}

void closestHidrant(char* text, Info* info){
    char* temp, *aux, *cep, *face;
    double num;
    void* nt;
    temp = (char*) calloc (155, sizeof(char));
    strcpy(temp, text);
    insert_Fila(info->respQRY, temp);
    insert_Fila(info->respQRY, "\n");
    aux = text; aux += 6;
    cep  = (char*) calloc(55, sizeof(char));
    face = (char*) calloc(55, sizeof(char));
    sscanf(aux, "%s %s %lf",cep, face, &num);

    double x,y;
    void* q = createQuadra(cep, "", "", 0, 0, 0, 0);
    void* qd = get_hashtable(info->bd->cepQuadraHash, q);
    freeQuad(q);
    x = getXRec(getRecQuad(qd));
    y = getYRec(getRecQuad(qd));
    if(strcmp(face, "N") == 0){
        x += num;
        y += getHRec(getRecQuad(qd));
    }
    if(strcmp(face, "S") == 0){
        x += num;
    }
    if(strcmp(face, "L") == 0){
        y += num;
    }
    if(strcmp(face, "O") == 0){
        y += num;
        x += getWRec(getRecQuad(qd));
    }
    nt = createNotacao("RED", 0, 0, x, y, "X");
    insert_Fila(info->notsQRY, nt);

    void* hidr = createHidrante("", "", "", x, y);
    void* hd = closestNeibord(info->bd->HidrantesTree, hidr);
    free(hidr);
    nt = createNotacao("RED", x*(-1), y*(-1), getXCirc(getCircHidr(hd))*(-1), getYCirc(getCircHidr(hd))*(-1), "");
    insert_Fila(info->notsQRY, nt);
    double dist = sqrt( abs(x - getXRec(getCircHidr(hd)))^2 + abs(y - getYRec(getCircHidr(hd)))^2);
    char* result;
    result = (char*) calloc(255, sizeof(char));
    sprintf(result, "%s, dist: %lf", reportHidrante(hd), dist);
    insert_Fila(info->respQRY, result);
    free(cep);
    free(face);
    // Linha nt = createNotacao("RED", x*(-1), y*(-1), x1*(-1), y1*(-1), "");

}

void closestHidrantFromRB(char* text, Info* info){
    char *temp, *aux, *idRB, *result;
    void* rb, *rbTemp;
    void* hd;
    void* nt;
    double dist, a, b;
    temp = (char*) calloc (155, sizeof(char));
    strcpy(temp, text);
    insert_Fila(info->respQRY, temp);
    insert_Fila(info->respQRY, "\n");
    aux = text; aux += 5;
    idRB  = (char*) calloc(55, sizeof(char));
    sscanf(aux, "%s",idRB);
    
    rbTemp = createRadioB(idRB, "", "", 0, 0);
    rb = get_hashtable(info->bd->RadioBaseHash, rbTemp);
    freeRadioB(rbTemp);
    if(rb == NULL){
        insert_Fila(info->respQRY, "RadioB não Encontrada");
        return;
    }

    hd = closestNeibord(info->bd->HidrantesTree, rb);

    nt = createNotacao("RED", getXCirc(getCircRadioB(rb))*(-1), getYCirc(getCircRadioB(rb))*(-1),getXCirc(getCircHidr(hd))*(-1), getYCirc(getCircHidr(hd))*(-1), "");
    a = getXCirc(getCircRadioB(rb)) - getXCirc(getCircHidr(hd));
    b = getYCirc(getCircRadioB(rb)) - getYCirc(getCircHidr(hd));
    dist = sqrt(a*a + b*b);
    result = (char*) calloc(255, sizeof(char));
    sprintf(result, "%s, %s - dist: %lf", reportRadioB(rb), reportHidrante(rb), dist);

    insert_Fila(info->notsQRY, nt);
    insert_Fila(info->respQRY, result);
    free(idRB);
}

void closeEstab(char* text, Info* info){
    char *aux, *cnpj;
    aux = (char*) calloc (155, sizeof(char));
    strcpy(aux, text);
    insert_Fila(info->respQRY, aux);
    insert_Fila(info->respQRY, "\n");
    cnpj = (char*) calloc(55, sizeof(char));
    aux = text; aux += 4;
    sscanf(aux, "%s", cnpj);
    void* Est = Estab_create(info, cnpj, NULL,  "", "", "", "");
    void* estab = get_hashtable(info->bd->EstabHash, Est);
    Estab_Free(Est); free(cnpj);
    if(estab == NULL){
        insert_Fila(info->respQRY, "Este Estabelecimento não existe\n");
        return;
    }
    char* result;
    result = (char*) calloc(255, sizeof(char));
    sprintf(result, "%s\n", Estab_relatorio(estab));
    insert_Fila(info->respQRY, result);
    
    //remove
    remove_hashtable(info->bd->EstabHash, estab);
    void* end = Estab_getEndereco(estab);
    if(end != NULL)
    remove_hashtable(info->bd->enderecoEstab, end);
}

void mudancaPessoa(char* text, Info* info){
    char *aux, *cpf, *cep, *face, *num, *comp;
    aux = (char*) calloc (155, sizeof(char));
    strcpy(aux, text);
    insert_Fila(info->respQRY, aux);
    insert_Fila(info->respQRY, "\n");
    cpf = (char*) calloc(55, sizeof(char));
    cep = (char*) calloc(55, sizeof(char));
    face= (char*) calloc(55, sizeof(char));
    num = (char*) calloc(55, sizeof(char));
    comp= (char*) calloc(55, sizeof(char));
    aux = text; aux += 4;
    sscanf(aux, "%s %s %s %s %s", cpf, cep, face, num, comp);

    void* temp = Pessoa_create(cpf, "", "", "", "");
    void* pessoa = get_hashtable(info->bd->PessoaCepHash, temp);
    Pessoa_Free(temp);
    if(pessoa == NULL){
        insert_Fila(info->respQRY, "Pessoa nao Encontrada\n");
        return;
    }

    char* result;
    result = (char*) calloc(255, sizeof(char));
    sprintf(result, "%s --> Novo Endereco: %s %s, nº %s - %s\n", Pessoa_relatorio(pessoa), cep, face, num, comp);
    insert_Fila(info->respQRY, result);

    double *cord_i;
    cord_i = Pessoa_getCordGeo(pessoa, info);
    
    void* contr = Pessoa_getEndereco(pessoa);
    void* end = Pessoa_SetEndereco(pessoa, cep, face, num, comp);
    if(contr == NULL)
        insert_hashtable(info->bd->enderecoPessoa, end);
    
    double *cord_j;
    cord_j = Pessoa_getCordGeo(pessoa, info);

    if(cord_i != NULL && cord_j != NULL){
        void* nt = createNotacao(info->conf->colorMud, cord_i[0]*(-1), cord_i[1]*(-1), cord_j[0]*(-1), cord_j[1]*(-1), "");
        insert_Fila(info->notsQRY, nt);
    }
    free(cep); free(face), free(num); free(comp);
}

void mudancaEstab(char* text, Info* info){
    char *aux, *cnpj, *cep, *face, *num;
    aux = (char*) calloc (155, sizeof(char));
    strcpy(aux, text);
    insert_Fila(info->respQRY, aux);
    insert_Fila(info->respQRY, "\n");
    cnpj = (char*) calloc(55, sizeof(char));
    cep = (char*) calloc(55, sizeof(char));
    face= (char*) calloc(55, sizeof(char));
    num = (char*) calloc(55, sizeof(char));
    aux = text; aux += 6;
    sscanf(aux, "%s %s %s %s", cnpj, cep, face, num);

    void* temp = Estab_create(info, cnpj, NULL,  "", "", "", "");
    void* estab = get_hashtable(info->bd->EstabHash, temp);
    Estab_Free(temp); free(cnpj);
    if(estab == NULL){
        insert_Fila(info->respQRY, "Estabelecimento nao Encontrado\n");
        return;
    }

    char* result;
    result = (char*) calloc(255, sizeof(char));
    sprintf(result, "%s --> Novo Endereco: %s %s, nº %s\n", Estab_relatorio(estab), cep, face, num);
    insert_Fila(info->respQRY, result);

    double *cord_i;
    cord_i = Estab_getCordGeo(estab);
    
    void* contr = Estab_getEndereco(estab);
    void* end = Estab_changeEndereco(info, estab, cep, face, num);
    if(contr == NULL)
        insert_hashtable(info->bd->enderecoEstab, end);
    
    double *cord_j;
    cord_j = Estab_getCordGeo(estab);

    if(cord_i != NULL && cord_j != NULL){
        void* nt = createNotacao(info->conf->colorMudec, cord_i[0]*(-1), cord_i[1]*(-1), cord_j[0]*(-1), cord_j[1]*(-1), "");
        insert_Fila(info->notsQRY, nt);
    }
    free(cep); free(face), free(num);
}

void desapropriar(char* text, Info* info){
    char *aux;
    double x, y, w, h;
    double xi, yi, xf, yf;
    void* i, *t, *ident;
    aux = (char*) calloc (155, sizeof(char));
    strcpy(aux, text);
    insert_Fila(info->respQRY, aux);
    insert_Fila(info->respQRY, "\n");
    aux = text; aux += 4;
    sscanf(aux, "%lf %lf %lf %lf", &x, &y, &w, &h);

    void* nt = createNotacao("BLUE", w, h, x, y, "");
    insert_Fila(info->notsQRY, nt);

    //apagar quadra e tudo que esta nela, estabelecimentos e desapropriar pessoas(não matar)
    //apaga quadras
    Lista quadras = KDT_getAll(info->bd->QuadrasTree);
    i=Lista_getFirst(quadras);
    while(1){
        void* cont = Lista_get(quadras,i);
        if(cont){

            Item it = Lista_get(quadras, i);
            void* rc = getRecQuad(it);                    

            xi = getXRec(rc);
            xf = xi + getWRec(rc);
            yi = getYRec(rc);
            yf = yi + getHRec(rc);
            freeRec(rc);
            if(xi >= x && yi >= y && xf <= x+w && yf <= y+h){
                Lista enderecos;
                //deleta estabelecimentos
                ident = Estab_IdentEndereco(getCepQuad(it));
                enderecos = getList_hashtable(info->bd->enderecoEstab, ident);

                t = Lista_getFirst(enderecos);
                while(1){
                    void* temp = Lista_get(enderecos, t);
                    if(temp){
                        void* estab = Estab_getEstabEndereco(temp);
                        char * temp1; temp1 = (char*) calloc(155, sizeof(char));
                        sprintf(temp1, "%s\n", Estab_relatorio(estab));
                        insert_Fila(info->respQRY, temp1);

                        void* temp = Lista_getNext(enderecos, t);
                        remove_hashtable(info->bd->EstabHash, estab);
                        Lista_remove(enderecos, t);
                        t = temp;
                        continue;
                    }else{
                        break;
                    }
                    t = Lista_getNext(enderecos, t);
                }


                //desapropria pessoas
                ident = Pessoa_IdentEndereco(getCepQuad(it));
                enderecos = getList_hashtable(info->bd->enderecoPessoa, ident);
                t = Lista_getFirst(enderecos);
                while(1){
                    void* temp = Lista_get(enderecos, t);
                    if(temp){
                        void* pess = Pessoa_getPessoaEndereco(temp);
                        char * temp1; temp1 = (char*) calloc(155, sizeof(char));
                        sprintf(temp1, "%s\n", Pessoa_relatorio(pess));
                        insert_Fila(info->respQRY, temp1);

                        void* temp = Lista_getNext(enderecos, t);
                        remove_hashtable(info->bd->PessoaCepHash, pess);
                        Lista_remove(enderecos, t);
                        t = temp;
                        continue;
                    }else{
                        break;
                    }
                    t = Lista_getNext(enderecos, t);
                }


                char * temp1; temp1 = (char*) calloc(155, sizeof(char));
                sprintf(temp1, "%s\n", getCepQuad(it));
                insert_Fila(info->respQRY, temp1);

                void* temp = Lista_getNext(quadras, i);
                KDT_remove(info->bd->QuadrasTree, it);
                remove_hashtable(info->bd->cepQuadraHash, it);
                Lista_remove(quadras, i);
                i = temp;
                continue;  
            }else{              
                i = Lista_getNext(quadras, i);
            }
        }else{
        break;
        }
    }
    freeLista(quadras);

    //apaga hidrantes
    Lista hidrantes = KDT_getAll(info->bd->HidrantesTree);
    t=Lista_getFirst(hidrantes);
    while(1){
        i = Lista_get(hidrantes,t);
        if(i){
            
            Item it = Lista_get(hidrantes, t);
            void* circ = getCircHidr(it);

            xi = getXCirc(circ) - getRCirc(circ);
            xf = getXCirc(circ) + getRCirc(circ);
            yi = getYCirc(circ) - getRCirc(circ);
            yf = getYCirc(circ) + getRCirc(circ);
            freeCirculo(circ);

            if(xi >= x && yi >= y && xf <= x+w && yf <= y+h){
                char * temp2; temp2 = (char*) calloc(155, sizeof(char));
                sprintf(temp2, "Hidr. -  id: %s  -  x: %lf  -  y: %lf\n", getIdHidr(it), getXCirc(circ), getYCirc(circ));
                insert_Fila(info->respQRY, temp2);
                void* temp = Lista_getNext(hidrantes, t);
                Lista_remove(hidrantes, t);
                KDT_remove(info->bd->HidrantesTree, it);
                remove_hashtable(info->bd->HidrantesHash, it);
                t = temp; 
            }else{
                t = Lista_getNext(hidrantes, t);
            }
        }else{
        break;
        }
    }
    freeLista(hidrantes);

    //apaga radioB
    Lista radios = KDT_getAll(info->bd->RadioBaseTree);
    t=Lista_getFirst(radios);
    while(1){
        i = Lista_get(radios,t);
        if(i){
            
            Item it = Lista_get(radios, t);
            void* circ = getCircRadioB(it);

            xi = getXCirc(circ) - getRCirc(circ);
            xf = getXCirc(circ) + getRCirc(circ);
            yi = getYCirc(circ) - getRCirc(circ);
            yf = getYCirc(circ) + getRCirc(circ);
            freeCirculo(circ);
            if(xi >= x && yi >= y && xf <= x+w && yf <= y+h){
                char * temp2; temp2 = (char*) calloc(155, sizeof(char));
                sprintf(temp2, "Radios. -  id: %s  -  x: %lf  -  y: %lf\n", getIdRadioB(it), getXCirc(circ), getYCirc(circ));
                insert_Fila(info->respQRY, temp2);
                void* temp = Lista_getNext(radios, t);
                Lista_remove(radios, t);
                KDT_remove(info->bd->RadioBaseTree, it);
                remove_hashtable(info->bd->RadioBaseHash, it);
                t = temp; 
            }else{
                t = Lista_getNext(radios, t);
            }
        }else{
        break;
        }
    }
    freeLista(radios);

    //apaga semaforos
    Lista semaforos = KDT_getAll(info->bd->SemaforosTree);
    t=Lista_getFirst(semaforos);
    while(1){
        i = Lista_get(semaforos,t);
        if(i){
            
            Item it = Lista_get(semaforos, t);
            void* circ = getCircSemaf(it);

            xi = getXCirc(circ) - getRCirc(circ);
            xf = getXCirc(circ) + getRCirc(circ);
            yi = getYCirc(circ) - getRCirc(circ);
            yf = getYCirc(circ) + getRCirc(circ);
            freeCirculo(circ);
            if(xi >= x && yi >= y && xf <= x+w && yf <= y+h){
                char * temp2; temp2 = (char*) calloc(155, sizeof(char));
                sprintf(temp2, "Semaf. -  id: %s  -  x: %lf  -  y: %lf\n", getIdSemaf(it), getXCirc(circ), getYCirc(circ));
                insert_Fila(info->respQRY, temp2);
                void* temp = Lista_getNext(semaforos, t);
                Lista_remove(semaforos, t);
                KDT_remove(info->bd->SemaforosTree, it);
                remove_hashtable(info->bd->SemaforosHash, it);
                t = temp;  
            }else{
                t = Lista_getNext(semaforos, t);
            }                
            
        }else{
        break;
        }
    }
    freeLista(semaforos);
}

void pessoaToReg(char* text, Info* info){
    char *aux, *id, *cpf;
    aux = (char*) calloc (155, sizeof(char));
    strcpy(aux, text);
    insert_Fila(info->respQRY, aux);
    aux = text; aux += 4;
    id = (char*) calloc(55, sizeof(char));
    cpf = (char*) calloc(55, sizeof(char));
    sscanf(aux, "%s %s", id, cpf);
    Pessoa pAux = Pessoa_create(cpf, "", "", "", "");
    Pessoa pes = get_hashtable(info->bd->PessoaCepHash, pAux);
    Pessoa_Free(pAux);
    if(pes == NULL){
        insert_Fila(info->respQRY, "Pessoa Não Encontrada\n");
        free(id); free(cpf);
        return;
    }
    double* cord;
    cord = Pessoa_getCordGeo(pes, info);
    if(cord == NULL){
        insert_Fila(info->respQRY, "Pessoa Não Possui Endereco\n");
        free(id); free(cpf);
        return;
    }
    regis auxReg = create_Reg(id, cord);
    regis regt = get_hashtable(info->bd->Reg, auxReg);
    if(regt == NULL){
        insert_hashtable(info->bd->Reg, auxReg);
    }else{
        setValueReg(regt, cord);
        free_Reg(auxReg);
    }

    char* result;
    result = (char*) calloc(110, sizeof(char));
    sprintf(result, "%s  <--  %s - (Cord: [%lf , %lf])\n", id, cpf, cord[0], cord[1]);
    insert_Fila(info->respQRY, result);
    free(id); free(cpf);
}

void enderecoToReg(char* text, Info* info){
    char *aux, *id, *cep, *face;
    double num;
    aux = (char*) calloc (155, sizeof(char));
    strcpy(aux, text);
    insert_Fila(info->respQRY, aux);
    aux = text; aux += 4;
    id = (char*) calloc(25, sizeof(char));
    cep = (char*) calloc(25, sizeof(char));
    face = (char*) calloc(5, sizeof(char));
    sscanf(aux, "%s %s %s %lf", id, cep, face, &num);
    double *cord = (double*) calloc(2, sizeof(double));
    
    quadra temp = createQuadra(cep, "", "", 0, 0, 0, 0);
    quadra quad = get_hashtable(info->bd->cepQuadraHash, temp);
    freeQuad(temp);
    
    cord[0] = getXRec(getRecQuad(quad));
    cord[1] = getYRec(getRecQuad(quad));

    if(strcmp(face, "N") == 0){
        //x += num
        cord[0] += num;
        //y += h
        cord[1] += getHRec(getRecQuad(quad));
    }
    if(strcmp(face, "S") == 0){
        //x += num
        cord[0] += num;
    }
    if(strcmp(face, "L") == 0){
        //y += num
        cord[1] += num;
    }
    if(strcmp(face, "O") == 0){
        //y += num
        cord[1] += num;
        //x += w
        cord[0] += getWRec(getRecQuad(quad));
    }

    regis auxR = create_Reg(id, cord);
    regis regt = get_hashtable(info->bd->Reg, auxR);
    if(regt == NULL){
        insert_hashtable(info->bd->Reg, auxR);
    }else{
        setValueReg(regt, cord);
        free_Reg(auxR);
    }

    char* result;
    result = (char*) calloc(155, sizeof(char));
    sprintf(result, "%s  <--  %s %s nº %lf - (Cord: [%lf , %lf])\n", id, cep, face, num, cord[0], cord[1]);
    insert_Fila(info->respQRY, result);
    free(id); free(cep); free(face);
}

void equipUrbanToReg(char* text, Info* info){
    char *aux, *id, *item;
    aux = (char*) calloc (155, sizeof(char));
    strcpy(aux, text);
    insert_Fila(info->respQRY, aux);
    aux = text; aux += 4;
    id = (char*) calloc(55, sizeof(char));
    item = (char*) calloc(55, sizeof(char));
    sscanf(aux, "%s %s", id, item);
    void* it, *temp;
    double *cord;
    it == NULL; temp == NULL; cord == NULL;

    if(it == NULL){
        temp = createHidrante(item, "", "", 0, 0);
        it = get_hashtable(info->bd->HidrantesHash, temp);
        if(it != NULL)
        cord = conrdenadaCentroCirc(getCircHidr(it));
    }
    if(it == NULL){
        temp = createSemaforo(item, "", "", 0, 0);
        it = get_hashtable(info->bd->SemaforosHash, temp);
        if(it != NULL)
        cord = conrdenadaCentroCirc(getCircSemaf(it));
    }
    if(it == NULL){
        temp = createRadioB(item, "", "", 0, 0);
        it = get_hashtable(info->bd->RadioBaseHash, temp);
        if(it != NULL)
        cord = conrdenadaCentroCirc(getCircRadioB(it));
    }
    if(it == NULL){
        insert_Fila(info->respQRY, "Item Não Encontrado!\n");
        free(id); free(item);
        return;
    }
    if(cord == NULL){
        insert_Fila(info->respQRY, "Cordenada Não Encontrado!\n");
        free(id); free(item);
        return;
    }
    
    regis auxR = create_Reg(id, cord);
    regis regt = get_hashtable(info->bd->Reg, auxR);
    if(regt == NULL){
        insert_hashtable(info->bd->Reg, auxR);
    }else{
        setValueReg(regt, cord);
        free_Reg(auxR);
    }

    char *result = (char*) calloc(155, sizeof(char));
    sprintf(result, "%s  <-- %s (Cord: [%lf , %lf])\n", id, item , cord[0], cord[1]);
    insert_Fila(info->respQRY, result);
    free(id); free(item);
}

void cordToReg(char* text, Info* info){
    char *aux, *id;
    double x, y;
    double* cord;
    cord = (double*) calloc(2, sizeof(double));
    aux = (char*) calloc (155, sizeof(char));
    strcpy(aux, text);
    insert_Fila(info->respQRY, aux);
    aux = text; aux += 4;
    id = (char*) calloc(55, sizeof(char));
    sscanf(aux, "%s %lf %lf", id, &x, &y);
    cord[0] = x;
    cord[1] = y;
    
    
    regis auxR = create_Reg(id, cord);
    regis regt = get_hashtable(info->bd->Reg, auxR);
    if(regt == NULL){
        insert_hashtable(info->bd->Reg, auxR);
    }else{
        setValueReg(regt, cord);
        free_Reg(auxR);
    }

    
    char *result = (char*) calloc(155, sizeof(char));
    sprintf(result, "%s  <-- (Cord: [%lf , %lf])\n", id, cord[0], cord[1]);
    insert_Fila(info->respQRY, result);
    free(id);
}

void theClosestEstab(char* text, Info* info){
    char *aux, *idA, *tipo, *idB;
    double x, y;
    double* cord;
    cord = (double*) calloc(2, sizeof(double));
    aux = (char*) calloc (155, sizeof(char));
    strcpy(aux, text);
    insert_Fila(info->respQRY, aux);
    aux = text; aux += 5;
    idA  = (char*) calloc(55, sizeof(char));
    tipo = (char*) calloc(55, sizeof(char));
    idB  = (char*) calloc(55, sizeof(char));
    sscanf(aux, "%s %s %s", idA, tipo, idB);
    Lista estabs = getAll_hashtable(info->bd->EstabHash);
    Tree estabskdt = KDT_create(Estab_compare, 2, Estab_Free);

    void *temp, *auxEstab;
    temp = Lista_getFirst(estabs);
    while(1){
        auxEstab = Lista_get(estabs, temp);
        if(auxEstab){
            char* tip;
            tip = Estab_getTipoCod(auxEstab);
            if(tip != NULL && !strcmp(tip, tipo)){
                KDT_insert(estabskdt, auxEstab);
            }
            temp = Lista_getNext(estabs, temp);
        }else{
            break;
        }
    }

    if(KDT_Size(estabskdt) == 0){
        char *result = (char*) calloc(155, sizeof(char));
        sprintf(result, "Nenhum Estabelecimento desse tipo encontrado\n");
        insert_Fila(info->respQRY, result);
        return;
    }

    void *reg, *regAux;
    regAux  = create_Reg(idB, NULL);
    reg = get_hashtable(info->bd->Reg, regAux);
    free_Reg(regAux);

    if(reg==NULL){
        insert_Fila(info->respQRY, "registrador nao encontrado\n");
        return;
    }
    double* cordB = (double*) getValue_Reg(reg);
    void* reference = createEstabCord(cordB[0], cordB[1]);
    void* closestEstab = closestNeibord(estabskdt, reference);
    Estab_Free(reference);
    cord = Estab_getCordGeo(closestEstab);
    
    regis auxR = create_Reg(idA, cord);
    regis regt = get_hashtable(info->bd->Reg, auxR);
    if(regt == NULL){
        insert_hashtable(info->bd->Reg, auxR);
    }else{
        setValueReg(regt, cord);
        free_Reg(auxR);
    }


    char *result = (char*) calloc(155, sizeof(char));
    if(cord == NULL){
        sprintf(result, "Error\n");    
    }else{
        sprintf(result, "%s  <-- (Cord: [%lf , %lf])\n", idA, cord[0], cord[1]);
    }
    insert_Fila(info->respQRY, result);
    free(idA);
}


/*Cria um Carro*/
void create_Carro(char* text, Info* info){
    char *aux, *placa;
    double x, y, w, h;
    aux = text; aux += 3;
    placa = (char*) calloc(55, sizeof(char));
    sscanf(aux, "%s %lf %lf %lf %lf", placa, &x, &y, &w, &h);

    carro car = createCarro(placa, x, y, w, h);
    free(placa);

    KDT_insert(info->bd->carroTree, car);
    insert_hashtable(info->bd->carroHash, car);

}

void remove_Carro(char* text, Info* info){
    char *aux, *placa;
    aux = (char*) calloc (155, sizeof(char));
    strcpy(aux, text);
    insert_Fila(info->respQRY, aux);    
    placa = (char*) calloc(55, sizeof(char));
    aux += 4;
    sscanf(aux, "%s", placa);

    carro car, auxCar;
    auxCar = createCarro(placa, 0, 0, 0, 0);
    car = get_hashtable(info->bd->carroHash, auxCar);
    freeCarro(auxCar);
    aux = (char*) calloc (155, sizeof(char));
    void* rec = getRecCarro(car);
    sprintf(aux, "Removido -> %s (%lf ,%lf)\n", placa, getXRec(rec), getYRec(rec));
    insert_Fila(info->respQRY, aux);
    freeRec(rec);    
    KDT_remove(info->bd->carroTree, car);
    remove_hashtable(info->bd->carroHash, car);
    //freeCarro(car);
    free(placa);
}

void detectColision(char* text, Info* info){
    char *aux, *sufixo;
    aux = (char*) calloc (155, sizeof(char));
    strcpy(aux, text);
    insert_Fila(info->respQRY, aux);    
    sufixo = (char*) calloc(55, sizeof(char));
    aux += 3;
    sscanf(aux, "%s", sufixo);

    GrafoD_unlock(info->bd->grafo);
    Fila acidentes = Lista_createLista();
    Notation nt;
    char *result;

    //while para carros{
    Lista cars = KDT_getAll(info->bd->carroTree);
    void* posic = Lista_getFirst(cars);
    while(1){
        void*item = Lista_get(cars, posic);
        if(item){

            //detecta se esse carro esta colidido
            void* closestCar = closestNeibord(info->bd->carroTree, item);
            Item ij = createItem(getRecCarro(item), 0);
            Item ik = createItem(getRecCarro(closestCar), 0);
            if(Item_overlap(ij, ik) != 1 || item == closestCar){
                freeRec(ij);
                freeRec(ik);
                posic = Lista_getNext(cars, posic);
                continue;
            }
            //cria um retangulo na area do acidente
            double x = Item_Xi(ij) < Item_Xi(ik) ? Item_Xi(ij) : Item_Xi(ik);
            double y = Item_Yi(ij) < Item_Yi(ik) ? Item_Yi(ij) : Item_Yi(ik);
            double w = Item_Xf(ij) > Item_Xf(ik) ? Item_Xf(ij) : Item_Xf(ik);
            double h = Item_Yf(ij) > Item_Yf(ik) ? Item_Yf(ij) : Item_Yf(ik);
            w -= x;
            h -= y;
            char *placaA, *placaB;
            placaA = getPlacaCarro(item);
            placaB = getPlacaCarro(closestCar);

            //imprime o relatorio do TXT
            result = (char*) calloc(strlen(placaA) + strlen(placaB) + 55, sizeof(char));
            sprintf(result, "Carros Colididos -> %s / %s\n", placaA, placaB);
            insert_Fila(info->respQRY, result);

            //imprime o relatorio do SVG
            result = (char*) calloc(255, sizeof(char));
            sprintf(result, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"RED\" stroke-width=\"5\"/>\n", x-5, y-5, w+10, h+10);
            insert_Fila(acidentes, result);
            
            //Bloqueia os vertices que estao nessa area
            GrafoD_blockVertices(info->bd->grafo, w, h, x, y);
            //Bloqueia as arestas que passam por essa area
            GrafoD_blockArestas(info->bd->grafo, w, h, x, y);
        }else{break;}
        posic = Lista_getNext(cars, posic);
    }
    //}

    //imprimir o arquivo-sufixo
    char *path, *aux2;
    FILE *arqSVG_QRY;
    void *t, *temp, *auxF, *auxN;

    //configurar path e abrir arquivo
    path = (char*) calloc (255, sizeof(char));
    sprintf(path, "%s/%s", info->o, info->f);
    // if(*path == '/') path++;
    aux = path;
    aux += strlen(path);
    while(*aux != '.')aux--;
    *aux = 0;
    aux = info->q;
    while(*aux){
        if(*aux == '/'){
            aux2 = aux+1;
        }
        aux++;
    }
    sprintf(path, "%s-%s", path, aux2);
    aux = path;
    aux += strlen(path);
    while(*aux != '.')aux--;
    *aux = 0;
    strcat(path, "-");
    strcat(path, sufixo);
    strcat(aux, ".svg");
    arqSVG_QRY = fopen(path, "w");

    fprintf(arqSVG_QRY,"<svg xmlns=\"http://www.w3.org/2000/svg\" width = \"%lf\" height = \"%lf\">\n", info->conf->x, info->conf->y);

    //imprimir circulos e retangulos
    t=Lista_getFirst(info->bd->Drawer);
    while(1){
        temp = Lista_get(info->bd->Drawer,t);
        if(temp){
            
            Item it = Lista_get(info->bd->Drawer, t);
            fprintf(arqSVG_QRY, "%s\n", createSvg(it));
            t = Lista_getNext(info->bd->Drawer, t);
        }else{
        break;
        }
    }

    //Imprimir notas GEO
    auxF = create_Fila();
    while(!empty_Fila(info->notsGeo)){
        auxN = (void*) remove_Fila(info->notsGeo);
        insert_Fila(auxF,(void*) auxN);
        fprintf(arqSVG_QRY, "%s\n", createNotacaoSvg(auxN));
    }
    free(info->notsGeo);
    info->notsGeo = auxF;

    //imprimir notas QRY
    auxF = create_Fila();
    while(!empty_Fila(info->notsQRY)){
        auxN = (void*) remove_Fila(info->notsQRY);
        insert_Fila(auxF,(void*) auxN);
        fprintf(arqSVG_QRY, "%s\n", createNotacaoSvg(auxN));
    }
    free(info->notsQRY);
    info->notsQRY = auxF;

    //imprimir notas Sufixo
    while(!empty_Fila(acidentes)){
        char* auxChar = (char*) remove_Fila(acidentes);
        fprintf(arqSVG_QRY, "%s\n", auxChar);
    }
    free(acidentes);

    //imprimir quadras
    Lista quadras = KDT_getAll(info->bd->QuadrasTree);
    t=Lista_getFirst(quadras);
    while(1){
        temp = Lista_get(quadras,t);
        if(temp){            
            Item it = Lista_get(quadras, t);
            fprintf(arqSVG_QRY, "%s\n", createQuadraSvg(it));
            t = Lista_getNext(quadras, t);
        }else{break;}
    }

    //imprimir semaforos
    Lista semaforos = KDT_getAll(info->bd->SemaforosTree);
    t=Lista_getFirst(semaforos);
    while(1){
        temp = Lista_get(semaforos,t);
        if(temp){
            Item it = Lista_get(semaforos, t);
            fprintf(arqSVG_QRY, "%s\n", createSemaforoSvg(it));
            t = Lista_getNext(semaforos, t);
        }else{break;}
    }

    //imprimir hidrantes
    Lista hidrantes = KDT_getAll(info->bd->HidrantesTree);
    t=Lista_getFirst(hidrantes);
    while(1){
        temp = Lista_get(hidrantes,t);
        if(temp){
            Item it = Lista_get(hidrantes, t);
            fprintf(arqSVG_QRY, "%s\n", createHidranteSvg(it));
            t = Lista_getNext(hidrantes, t);
        }else{break;}
    }

    //imprimir torres-base
    Lista radios = KDT_getAll(info->bd->RadioBaseTree);
    t=Lista_getFirst(radios);
    while(1){
        temp = Lista_get(radios,t);
        if(temp){
            Item it = Lista_get(radios, t);
            fprintf(arqSVG_QRY, "%s\n", createRadioBSvg(it));
            t = Lista_getNext(radios, t);
        }else{break;}
    }

    //imprimir carros
    Lista carros = KDT_getAll(info->bd->carroTree);
    t=Lista_getFirst(carros);
    while(1){
        temp = Lista_get(carros,t);
        if(temp){          
            Item it = Lista_get(carros, t);
            fprintf(arqSVG_QRY, "%s\n", createCarroSVG(it));
            t = Lista_getNext(carros, t);
        }else{break;}
    }

    fprintf(arqSVG_QRY,"</svg>");
    fclose(arqSVG_QRY);
    free(path);

}



//separar text em tokens
void simpleRout(char* text, Info*info){  
    char *aux, *saida, *sufixo, *tipo, *inic, *end, *cor, *path, *aux2;
    FILE *arqTXT, *arqSVG;
    aux = (char*) calloc (155, sizeof(char));
    strcpy(aux, text);
    insert_Fila(info->respQRY, aux);   
    aux += 3;
    saida   = (char*) calloc(55, sizeof(char));
    sufixo  = (char*) calloc(55, sizeof(char));
    tipo    = (char*) calloc(55, sizeof(char));
    inic    = (char*) calloc(55, sizeof(char));
    end     = (char*) calloc(55, sizeof(char));
    cor     = (char*) calloc(55, sizeof(char));
    sscanf(aux, "%s %s %s %s %s %s", saida, sufixo, tipo, inic, end, cor);
    if(strcmp(saida, "t") == 0){
        cor = end;
        end = inic;
        inic = tipo;
        tipo = sufixo;
    }

    double *inicio, *fim;
    void *auxReg, *temp;

    temp = create_Reg(inic, NULL);
    auxReg = get_hashtable(info->bd->Reg, temp);
    free_Reg(temp);
    if(auxReg == NULL){
        insert_Fila(info->respQRY, "Registrador Inicial não encontrado\n"); 
        return;
    } 
    inicio = getValue_Reg(auxReg);

    temp = create_Reg(end, NULL);
    auxReg = get_hashtable(info->bd->Reg, temp);
    free_Reg(temp);
    if(auxReg == NULL){
        insert_Fila(info->respQRY, "Registrador Final não encontrado\n"); 
        return;
    } 
    fim = getValue_Reg(auxReg);

    int mod;
    mod = strcmp(tipo, "D")==0? 0 : 1;

    void ***ar;
    if(info->bd->ar0 == NULL){
        info->bd->ar0 = GrafoD_arestaTable(info->bd->grafo, 0);
    }
    ar = info->bd->ar0;

    Lista rota = caminho(info->bd->grafo, inicio, fim, mod, ar);

    

    if(rota == NULL){
        insert_Fila(info->respQRY, "Rota não encontrada\n"); 
        return; //Comentar durante texte
    }
    Lista result;
    
    void *auxF, *auxN, *t;
    if(strcmp(saida, "t") == 0){      
        
        result = txtCaminho(rota);
        //imprimir resultado no txt

        t=Lista_getFirst(result);
        while(1){
            temp = Lista_get(result,t);
            if(temp){                
                Item it = Lista_get(result, t);
                insert_Fila(info->respQRY, it);
                auxN = Lista_getNext(result, t);
                Lista_remove(result, t);
                t = auxN;
            }else{
            break;
            }
        }

    }else{
        path = (char*) calloc (255, sizeof(char));
        sprintf(path, "%s/%s", info->o, info->f);
        // if(*path == '/') path++;
        aux = path;
        aux += strlen(path);
        while(*aux != '.')aux--;
        *aux = 0;
        aux = info->q;
        while(*aux){
            if(*aux == '/'){
                aux2 = aux+1;
            }
            aux++;
        }
        sprintf(path, "%s-%s", path, aux2);
        aux = path;
        aux += strlen(path);
        while(*aux != '.')aux--;
        strcpy(aux, "-");
        strcat(aux, sufixo);
        strcat(aux, ".svg");
        arqSVG = fopen(path, "w");

        result = svgCaminho(rota, cor, inicio, fim);
        //imprimir resultado no SVG


        fprintf(arqSVG,"<svg xmlns=\"http://www.w3.org/2000/svg\" width = \"%lf\" height = \"%lf\">\n", info->conf->x, info->conf->y);

        //Texte
        circulo circ;
        circ = createCirculo(0, "GREEN", "GREEN", 20, *inicio, *(inicio+1));
        fprintf(arqSVG, "%s\n", createCirculoSvg(circ));
        freeCirculo(circ);
        circ = createCirculo(0, "GREEN", "RED", 20, *fim, *(fim+1));
        fprintf(arqSVG, "%s\n", createCirculoSvg(circ));
        freeCirculo(circ);

        //imprimir circulos e retangulos
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

        //Imprimir notas GEO
        auxF = create_Fila();
        while(!empty_Fila(info->notsGeo)){
            auxN = (void*) remove_Fila(info->notsGeo);
            insert_Fila(auxF,(void*) auxN);
            fprintf(arqSVG, "%s\n", createNotacaoSvg(auxN));
        }
        free(info->notsGeo);
        info->notsGeo = auxF;

        //imprimir notas QRY
        auxF = create_Fila();
        while(!empty_Fila(info->notsQRY)){
            auxN = (void*) remove_Fila(info->notsQRY);
            insert_Fila(auxF,(void*) auxN);
            fprintf(arqSVG, "%s\n", createNotacaoSvg(auxN));
        }
        free(info->notsQRY);
        info->notsQRY = auxF;


        //imprimir quadras
        Lista quadras = KDT_getAll(info->bd->QuadrasTree);
        t=Lista_getFirst(quadras);
        while(1){
            temp = Lista_get(quadras,t);
            if(temp){            
                Item it = Lista_get(quadras, t);
                fprintf(arqSVG, "%s\n", createQuadraSvg(it));
                t = Lista_getNext(quadras, t);
            }else{break;}
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
            }else{break;}
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
            }else{break;}
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
            }else{break;}
        }

        //imprimir carros
        Lista carros = KDT_getAll(info->bd->carroTree);
        t=Lista_getFirst(carros);
        while(1){
            temp = Lista_get(carros,t);
            if(temp){          
                Item it = Lista_get(carros, t);
                fprintf(arqSVG, "%s\n", createCarroSVG(it));
                t = Lista_getNext(carros, t);
            }else{break;}
        }

        t=Lista_getFirst(result);
        while(1){
            temp = Lista_get(result,t);
            if(temp){                
                Item it = Lista_get(result, t);
                fprintf(arqSVG, "\n%s", (char*) it);
                auxN = Lista_getNext(result, t);
                Lista_remove(result, t);
                t = auxN;
            }else{
            break;
            }
        }
        // char *util = grafoToSvg(info->bd->grafo);
        // fprintf(arqSVG, "%s", util);//em texte

        fprintf(arqSVG,"</svg>");
        
    }

}

void multRout(char* text, Info*info){
    char *aux, *saida, *sufixo, *tipo, **cor, *path, *aux2, **regs;
    int n, i;
    FILE *arqTXT, *arqSVG;
    aux = (char*) calloc (155, sizeof(char));
    strcpy(aux, text);
    insert_Fila(info->respQRY, aux);   
    aux += 4;
    saida   = (char*) calloc(55, sizeof(char));
    sufixo  = (char*) calloc(55, sizeof(char));
    tipo    = (char*) calloc(55, sizeof(char));
    cor     = (char**) calloc(2, sizeof(char*));
    cor[0]  = (char*) calloc(55, sizeof(char));
    cor[1]  = (char*) calloc(55, sizeof(char));
    sscanf(aux, "%s", saida);

    if(strcmp(saida, "t") == 0){
        sscanf(aux, "%s %s %d", saida, tipo, &n);
        strcpy(sufixo, "");
    }else{
        sscanf(aux, "%s %s %s %d", saida, sufixo, tipo, &n);
    }

    aux += strlen(saida) + strlen(sufixo) + strlen(tipo) + 3;
    while(*aux != ' ') aux++;
    aux++;
    regs = (char**) calloc(n, sizeof(char*));

    for(i=0; i<n; i++){
        regs[i] = (char*) calloc(10, sizeof(char));
        sscanf(aux, "%s ", regs[i]);
        aux += strlen(regs[i]) + 1;
    }
    sscanf(aux, "%s %s", cor[0], cor[1]);
    Lista *rota = (Lista*) calloc(n-1, sizeof(Lista));

    int mod;
    mod = strcmp(tipo, "D")==0? 0 : 1;
    void *temp, *auxReg;
    double *inicio, *fim;
    int ctr = 0;
    double** paradas = (double**) calloc(n-1, sizeof(double*));

    void ***ar;
    if(info->bd->ar0 == NULL){
        info->bd->ar0 = GrafoD_arestaTable(info->bd->grafo, 0);
    }
    ar = info->bd->ar0;



    for(i=0; i < n - 1 ; i++){

        temp = create_Reg(regs[i], NULL);
        auxReg = get_hashtable(info->bd->Reg, temp);
        free_Reg(temp);
        if(auxReg == NULL){
            insert_Fila(info->respQRY, "Registrador não encontrado\n"); 
            return;
        } 
        inicio = getValue_Reg(auxReg);
        paradas[i] = inicio;

        temp = create_Reg(regs[i+1], NULL);
        auxReg = get_hashtable(info->bd->Reg, temp);
        free_Reg(temp);
        if(auxReg == NULL){
            insert_Fila(info->respQRY, "Registrador não encontrado\n"); 
            return;
        } 
        fim = getValue_Reg(auxReg);


        printf("Calculando rota de %s até %s\n", regs[i], regs[i+1]);
        rota[i] = caminho(info->bd->grafo, inicio, fim, mod, ar);
        printf("Rota de %s até %s concluida\n", regs[i], regs[i+1]);
        if(rota[i] != NULL){
            ctr = 1;
        }
    }
    if(ctr == 0){
        insert_Fila(info->respQRY, "Rota não encontrada\n"); 
        return; //Comentar durante texte
    }
    Lista result = Lista_createLista();
        
    void *auxF, *auxN, *t;
    if(strcmp(saida, "t") == 0){      
        
        for(i=0; i < n - 1; i++){
            Lista_insertLista(result, txtCaminho(rota[i]));
        }
        //imprimir resultado no txt
        

        t=Lista_getFirst(result);
        while(1){
            temp = Lista_get(result,t);
            if(temp){                
                Item it = Lista_get(result, t);
                insert_Fila(info->respQRY, it);
                auxN = Lista_getNext(result, t);
                Lista_remove(result, t);
                t = auxN;
            }else{
            break;
            }
        }


        fclose(arqTXT);

    }else{
        path = (char*) calloc (255, sizeof(char));
        sprintf(path, "%s/%s", info->o, info->f);
        // if(*path == '/') path++;
        aux = path;
        aux += strlen(path);
        while(*aux != '.')aux--;
        *aux = 0;
        aux = info->q;
        while(*aux){
            if(*aux == '/'){
                aux2 = aux+1;
            }
            aux++;
        }
        sprintf(path, "%s-%s", path, aux2);
        aux = path;
        aux += strlen(path);
        while(*aux != '.')aux--;
        strcpy(aux, "-");
        strcat(aux, sufixo);
        strcat(aux, ".svg");
        arqSVG = fopen(path, "w");       

        for(i=0; i < n - 1; i++){
            if(rota[i] != NULL)
                if(i == n-2){
                    Lista_insertLista(result, svgCaminho(rota[i], cor[i%2], paradas[i], fim));
                }else{
                    Lista_insertLista(result, svgCaminho(rota[i], cor[i%2], paradas[i], paradas[i+1]));
                }
                
        }
        //imprimir resultado no SVG


        fprintf(arqSVG,"<svg xmlns=\"http://www.w3.org/2000/svg\" width = \"%lf\" height = \"%lf\">\n", info->conf->x, info->conf->y);


        circulo circ;
        circ = createCirculo(0, "GREEN", "GREEN", 20, *paradas[0], *(paradas[0]+1));
        fprintf(arqSVG, "%s\n", createCirculoSvg(circ));
        freeCirculo(circ);

        for(i=1; i<n-1;i++){
            circ = createCirculo(0, "GREEN", "BLUE", 10, *paradas[i], *(paradas[i]+1));
            fprintf(arqSVG, "%s\n", createCirculoSvg(circ));
            freeCirculo(circ);    
        }

        circ = createCirculo(0, "GREEN", "RED", 20, *fim, *(fim+1));
        fprintf(arqSVG, "%s\n", createCirculoSvg(circ));
        freeCirculo(circ);

        //imprimir circulos e retangulos
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

        //Imprimir notas GEO
        auxF = create_Fila();
        while(!empty_Fila(info->notsGeo)){
            auxN = (void*) remove_Fila(info->notsGeo);
            insert_Fila(auxF,(void*) auxN);
            fprintf(arqSVG, "%s\n", createNotacaoSvg(auxN));
        }
        free(info->notsGeo);
        info->notsGeo = auxF;

        //imprimir notas QRY
        auxF = create_Fila();
        while(!empty_Fila(info->notsQRY)){
            auxN = (void*) remove_Fila(info->notsQRY);
            insert_Fila(auxF,(void*) auxN);
            fprintf(arqSVG, "%s\n", createNotacaoSvg(auxN));
        }
        free(info->notsQRY);
        info->notsQRY = auxF;


        //imprimir quadras
        Lista quadras = KDT_getAll(info->bd->QuadrasTree);
        t=Lista_getFirst(quadras);
        while(1){
            temp = Lista_get(quadras,t);
            if(temp){            
                Item it = Lista_get(quadras, t);
                fprintf(arqSVG, "%s\n", createQuadraSvg(it));
                t = Lista_getNext(quadras, t);
            }else{break;}
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
            }else{break;}
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
            }else{break;}
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
            }else{break;}
        }

        //imprimir carros
        Lista carros = KDT_getAll(info->bd->carroTree);
        t=Lista_getFirst(carros);
        while(1){
            temp = Lista_get(carros,t);
            if(temp){          
                Item it = Lista_get(carros, t);
                fprintf(arqSVG, "%s\n", createCarroSVG(it));
                t = Lista_getNext(carros, t);
            }else{break;}
        }

        t=Lista_getFirst(result);
        while(1){
            temp = Lista_get(result,t);
            if(temp){                
                Item it = Lista_get(result, t);
                fprintf(arqSVG, "\n%s", (char*) it);
                auxN = Lista_getNext(result, t);
                Lista_remove(result, t);
                t = auxN;
            }else{
            break;
            }
        }

        // char *util = grafoToSvg(info->bd->grafo);
        // fprintf(arqSVG, "%s", util);//em texte

        fprintf(arqSVG,"</svg>");
        
    }


}