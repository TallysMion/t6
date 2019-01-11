#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Quadra/quadra.h"
#include "../Retangulo/retangulo.h"
#include "../Config/config.h"
#include "../HashTable/hashtable.h"


typedef struct{
    char* cod;
    char* info;
} type;

typedef struct{
    int tipo;
    char* cep;
    char* face;
    char* num;
    char* comp;
    void* estab;
} Endereco;

typedef struct{
    char* cnpj;
    type* tipo;
    Endereco* ende;
    char* nome;
    double* cord;
} Estab;


double* calcCord(void* estab, Info* info){
    Estab* est;
    double num;
    est = (Estab*) estab;
    double* result;
    if(est->ende == NULL){
        return NULL;
    }
    quadra temp = createQuadra(est->ende->cep, "", "", 0, 0, 0, 0);
    quadra quad = get_hashtable(info->bd->cepQuadraHash, temp);
    sscanf(est->ende->num, "%lf", &num);
    result = (double*) calloc(2, sizeof(double));
    result[0] = getXRec(getRecQuad(quad));
    result[1] = getYRec(getRecQuad(quad));

    if(strcmp(est->ende->face, "N") == 0){
        //x += num
        result[0] += num;
        //y += h
        result[1] += getHRec(getRecQuad(quad));
    }
    if(strcmp(est->ende->face, "S") == 0){
        //x += num
        result[0] += num;
    }
    if(strcmp(est->ende->face, "L") == 0){
        //y += num
        result[1] += num;
    }
    if(strcmp(est->ende->face, "O") == 0){
        //y += num
        result[1] += num;
        //x += w
        result[0] += getWRec(getRecQuad(quad));
    }
    return result;
}

//Cria um estab so com as cordenadas
Estab* createEstabCord(double x,double y){
    Estab* result;
    result = (Estab*) calloc(1, sizeof(Estab));

    result->cnpj    = (char*) calloc(10 , sizeof(char*));
    strcpy(result->cnpj, "");
    result->cord = (double*) calloc(2, sizeof(double));
    result->cord[0] = x;
    result->cord[1] = y;

    return (void*) result;
}

//criar Estabelecimento
Estab* Estab_create(Info* info, char* cnpj, void* tip, char* cep, char* face, char* num, char* nome){
    Estab* result;
    result = (Estab*) calloc(1, sizeof(Estab));

    Endereco* end;
    end = (Endereco*) calloc(1, sizeof(Endereco));

    end->tipo    = 0;
    end->cep     = (char*) calloc(strlen(cep)+2  , sizeof(char*));
    end->face    = (char*) calloc(strlen(face)+2 , sizeof(char*));
    end->num     = (char*) calloc(strlen(num)+2  , sizeof(char*));
    end->comp    = NULL;
    
    type* tipo;
    tipo = (type*) tip;

    result->cnpj    = (char*) calloc(strlen(cnpj)+2 , sizeof(char*));
    result->nome    = (char*) calloc(strlen(nome)+2 , sizeof(char*));

    strcpy(result->cnpj, cnpj);
    strcpy(end->cep, cep);
    strcpy(end->face, face);
    strcpy(end->num, num);
    strcpy(result->nome, nome);
    result->tipo = tipo;
    result->ende = end;
    result->ende->estab = result;
    if(result->tipo != NULL)
        result->cord = calcCord(result, info);

    return (void*) result;

}

//Retornar o Endereco
void* Estab_getEndereco(void* estab){
    Estab* est;
    est = (Estab*) estab;
    return (void*) est->ende;
}

//criar Tipo de Estabelecimento
type* Estab_createType(char* cod, char* info){
    type* tipo;
    tipo = (type*) calloc(1, sizeof(type));
    tipo->cod = (char*) calloc(strlen(cod)+2, sizeof(char));
    tipo->info =(char*) calloc(strlen(info)+2, sizeof(char));
    strcpy(tipo->cod,cod);
    strcpy(tipo->info,info);
    return (void*) tipo;
}

//Mudança - Retorna Linha em SVG da mudança
void* Estab_changeEndereco(Info* info, void* estab,  char* cep, char* face, char* num){
    Estab* est;
    est = (Estab*) estab;
    free(est->ende->cep);
    free(est->ende->face);
    free(est->ende->num);

    est->ende->cep    = (char*) calloc(strlen(cep)+2 , sizeof(char*));
    est->ende->face    = (char*) calloc(strlen(face)+2 , sizeof(char*));
    est->ende->num     = (char*) calloc(strlen(num)+2  , sizeof(char*));

    strcpy(est->ende->cep, cep);
    strcpy(est->ende->face, face);
    strcpy(est->ende->num, num);

    free(est->cord);
    est->cord = calcCord(estab, info);

    return (void*) est->ende;
}

//free - Limpa a memoria
void Estab_Free(void* estab){
    Estab* est;
    est = (Estab*) estab;
    free(est->nome);
    free(est->cnpj);
    if(est->ende != NULL){
    free(est->ende->cep);
    free(est->ende->face);
    free(est->ende->num);
    free(est->ende);
    }
    free(est);
}

//compare - função de comparaçao de estabelecimentos
int Estab_compare(void* estab1, void* estab2, int dimension){
    Estab* estA;
    Estab* estB;    
    estA = (Estab*) estab1;
    estB = (Estab*) estab2;
    dimension = dimension%2;
    double *cordA;
    double *cordB;
    if(strcmp(estA->cnpj, estB->cnpj) == 0) return 0;
    if (dimension == 0){
        return estA->cord[0] - estB->cord[0];
    }else{
        return estA->cord[1] - estB->cord[1];
    }
}

//hashCode - retorna o codigo do estabelecimento
int Estab_HashCode(void* estab, int modulo){
    Estab *est;
    est = (Estab*) estab;
    int x = strlen(est->cnpj);
    int hash = 0;
    char *aux = est->cnpj;
    while(*aux != 0){
        hash += x*(*aux);
        aux++;
        x--;
    }
    return modulo < 0 ? hash : hash%modulo;
}

int Estab_HashCompare(void* estab, void* cnpj){
    Estab *est, *est2;
    est = (Estab*) estab;
    est2 = (Estab*) cnpj;
    return strcmp(est->cnpj, est2->cnpj);
}

int Endereco_compare(void* end1, void* end2, int dimension){
    Endereco* endr1;
    Endereco* endr2;    
    endr1 = (Endereco*) end1;
    endr2 = (Endereco*) end2;
    return strcmp(endr1->cep, endr2->cep);
}


//hashCode - retorna o codigo do estabelecimento
int Estab_Type_HashCode(void*  tip,int modulo){
    type *tp;
    tp = (type*) tip;
    int x = strlen(tp->cod);
    int hash = 0;
    char *aux = tp->cod;
    while(*aux != 0){
        hash += x*(*aux);
        aux++;
        x--;
    }
    return modulo < 0 ? hash : hash%modulo;
}

int Estab_Type_HashCompare(void* tip, void* cod){
    type *tp, *id;
    tp = (type*) tip;
    id = (type*) cod;
    return strcmp(tp->cod, id->cod);
}

void* Estab_getEstabEndereco(void* endereco){
    Endereco * end;
    end = (Endereco*) endereco;
    if(end->tipo == 1) return NULL;
    return end->estab;
}

//hashCode - retorna o codigo do estabelecimento
int Estab_Ende_HashCode(void* endereco, int modulo){
    Endereco *end;
    end = (Endereco*) endereco;
    int x = strlen(end->cep);
    int hash = 0;
    char *aux = end->cep;
    while(*aux != 0){
        hash += x*(*aux);
        aux++;
        x--;
    }
    return modulo < 0 ? hash : hash%modulo;
}

int Estab_Ende_HashCompare(void* Endereco1, void* Endereco2){
    Endereco *est1, *est2;
    est1 = (Endereco*) Endereco1;
    est2 = (Endereco*) Endereco2;
    return strcmp(est1->cep, est2->cep);
}

double* Estab_getCordGeo(void* estab, Info* info){
    Estab* est;
    est = (Estab*) estab;
    if(est == NULL)
    return NULL;
    return  est->cord;
}

char* Estab_relatorio(void* estab){
    Estab* est;
    est = (Estab*) estab;
    char* result;
    result = (char*) calloc(510, sizeof(char));
    if(est->ende == NULL){
        sprintf(result, "%s - %s", est->nome, est->tipo->info);
    }else{
        sprintf(result, "%s - %s, %s %s, nº %s", est->nome, est->tipo->info, est->ende->cep, est->ende->face, est->ende->num);
    }
    return result;
}

void* Estab_IdentEndereco(char* cep){
    Endereco* end;
    end = (Endereco*) calloc(1, sizeof(Endereco));
    end->tipo = 0;
    end->cep = cep;
    end->face= NULL;
    end->num = NULL;
    end->comp= NULL;
    end->estab = NULL;
}

char* Estab_getTipoCod(void* estab){
    Estab* est;
    est = (Estab*) estab;
    if(est->tipo == NULL){
        return NULL;
    }
    if(est->cord == NULL){
        return NULL;
    }
    return est->tipo->cod;
}

char* Estab_Tipo(void* estab){
    Estab* est;
    est = (Estab*) estab;
    return est->tipo->info;
}

char* Estab_Name(void* estab){
    Estab* est;
    est = (Estab*) estab;
    return est->nome;
}