#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Quadra/quadra.h"
#include "../Retangulo/retangulo.h"
#include "../Config/config.h"
#include "../HashTable/hashtable.h"

typedef struct{
    int tipo;
    char* cep;
    char* face;
    char* num;
    char* comp;
    void* pessoa;
} Endereco;

typedef struct{
    char* cpf;
    char* nome;
    char* sobrenome;
    char* sexo;
    char* nasc;
    Endereco* endereco;
} Pessoa;


//criar Estabelecimento
void* Pessoa_create(char* cpf, char* nome, char* sobrenome, char* sexo, char* nasc){
    Pessoa* pessoa;
    pessoa = (Pessoa*) calloc(1, sizeof(Pessoa));
    
    pessoa->cpf         = (char*) calloc(strlen(cpf)+2, sizeof(char));
    pessoa->nome        = (char*) calloc(strlen(nome)+2, sizeof(char));
    pessoa->sobrenome   = (char*) calloc(strlen(sobrenome)+2, sizeof(char));
    pessoa->sexo        = (char*) calloc(strlen(sexo)+2, sizeof(char));
    pessoa->nasc        = (char*) calloc(strlen(nasc)+2, sizeof(char));
    pessoa->endereco    = NULL;

    strcpy(pessoa->cpf, cpf);
    strcpy(pessoa->nome, nome);
    strcpy(pessoa->sobrenome, sobrenome);
    strcpy(pessoa->sexo, sexo);
    strcpy(pessoa->nasc, nasc);

    return (void*) pessoa;

}

//criar Morador
void* Pessoa_SetEndereco(void* pes, char* cep, char* face, char* num, char* comp){
    Pessoa* pessoa;
    pessoa = (Pessoa*) pes;
    if(pessoa->endereco == NULL){
        Endereco* end;
        end = (Endereco*) calloc(1, sizeof(Endereco));
        end->tipo = 1;
        end->cep = (char*) calloc(strlen(cep )+2, sizeof(char));
        end->face= (char*) calloc(strlen(face)+2, sizeof(char));
        end->num = (char*) calloc(strlen(num )+2, sizeof(char));
        end->comp= (char*) calloc(strlen(comp)+2, sizeof(char));
        end->pessoa = pessoa;
        strcpy(end->cep, cep);
        strcpy(end->face, face);
        strcpy(end->num, num);
        strcpy(end->comp, comp);
        pessoa->endereco = end;
        return (void*) end;
    }else{
        free(pessoa->endereco->cep);
        free(pessoa->endereco->face);
        free(pessoa->endereco->num);
        free(pessoa->endereco->comp);
        pessoa->endereco->cep = cep;
        pessoa->endereco->face= face;
        pessoa->endereco->num = num;
        pessoa->endereco->comp= comp;
        return (void*) pessoa->endereco;
    }
}

void* Pessoa_IdentEndereco(char* cep){
    Endereco* end;
    end = (Endereco*) calloc(1, sizeof(Endereco));
    end->tipo = 1;
    end->cep = cep;
    end->face= NULL;
    end->num = NULL;
    end->comp= NULL;
    end->pessoa = NULL;
}

void* Pessoa_getPessoaEndereco(void* endereco){
    Endereco * end;
    end = (Endereco*) endereco;
    if(end->tipo == 0) return NULL;
    return end->pessoa;
}

//Retorna o endereco
void* Pessoa_getEndereco(void* pes){
    Pessoa* pessoa;
    pessoa = (Pessoa*) pes;
    return (void*) pessoa->endereco;
}

//free - Limpa a memoria
void Pessoa_Free(void* pes){
    Pessoa* pessoa;
    pessoa = (Pessoa*) pes;
    free(pessoa->cpf);
    free(pessoa->nome);
    free(pessoa->sobrenome);
    free(pessoa->sexo);
    free(pessoa->nasc);
    if(pessoa->endereco != NULL){
        free(pessoa->endereco->cep);
        free(pessoa->endereco->face);
        free(pessoa->endereco->num);
        free(pessoa->endereco->comp);
        free(pessoa->endereco);
    }
    free(pessoa);
}

//compare - função de comparaçao de Pessoaelecimentos
int Pessoa_compare(void* pes1, void* pes2, int dimension){
    Pessoa *pesA, *pesB;
    pesA = (Pessoa*)pes1;
    pesB = (Pessoa*)pes2;
    return strcmp(pesA->cpf, pesB->cpf);
}

//hashCode - retorna o codigo do Pessoaelecimento
int Pessoa_HashCode(void* pes, int modulo){
    Pessoa *pessoa;
    pessoa = (Pessoa*) pes;
    int x = strlen(pessoa->cpf);
    int hash = 0;
    char *aux = pessoa->cpf;
    while(*aux != 0){
        hash += x*(*aux);
        aux++;
        x--;
    }
    return modulo < 0 ? hash : hash%modulo;
}

int Pessoa_HashCompare(void* pes, void* cpf){
    Pessoa *pessoa, *id;
    pessoa = (Pessoa*) pes;
    id = (Pessoa*) cpf;
    return strcmp(pessoa->cpf, id->cpf);
}


//hashCode - retorna o codigo do estabelecimento
int Pessoa_Ende_HashCode(void* endereco, int modulo){
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

int Pessoa_Ende_HashCompare(void* Endereco1, void* Endereco2){
    Endereco *est1, *est2;
    est1 = (Endereco*) Endereco1;
    est2 = (Endereco*) Endereco2;
    return strcmp(est1->cep, est2->cep);
}

char* Pessoa_relatorio(void* pessoa){
    Pessoa* pes;
    char* result;
    result = (char*) calloc(510, sizeof(char));
    pes = (Pessoa*) pessoa;
    if(pes->endereco == NULL){
        sprintf(result, "%s", pes->nome);
    }else{
        sprintf(result, "%s (%s), %s %s, nº %s - %s", pes->nome, pes->nasc, pes->endereco->cep, pes->endereco->face, pes->endereco->num, pes->endereco->comp);
    }
    return result;
}

double* Pessoa_getCordGeo(void* pessoa, Info* info){
    Pessoa* pes;
    double num;
    pes = (Pessoa*) pessoa;
    double* result;
    if(pes->endereco == NULL){
        return NULL;
    }
    quadra temp = createQuadra(pes->endereco->cep, "", "", 0, 0, 0, 0);
    quadra quad = get_hashtable(info->bd->cepQuadraHash, temp);
    freeQuad(temp);
    sscanf(pes->endereco->num, "%lf", &num);
    result = (double*) calloc(2, sizeof(double));
    result[0] = getXRec(getRecQuad(quad));
    result[1] = getYRec(getRecQuad(quad));

    if(strcmp(pes->endereco->face, "N") == 0){
        //x += num
        result[0] += num;
        //y += h
        result[1] += getHRec(getRecQuad(quad));
    }
    if(strcmp(pes->endereco->face, "S") == 0){
        //x += num
        result[0] += num;
    }
    if(strcmp(pes->endereco->face, "L") == 0){
        //y += num
        result[1] += num;
    }
    if(strcmp(pes->endereco->face, "O") == 0){
        //y += num
        result[1] += num;
        //x += w
        result[0] += getWRec(getRecQuad(quad));
    }
    return result;
}