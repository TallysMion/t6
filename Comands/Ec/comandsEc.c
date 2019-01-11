#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Config/config.h"
#include "../../Estabelecimento/estabelecimento.h"

/*comando 't' do EC*/
int newEstabType(char* text,Info *info){
    char *aux, *cod, *descrip;
    aux = text; aux += 2;
    cod = (char*) calloc(55, sizeof(char));
    descrip = (char*) calloc(255, sizeof(char));
    sscanf(aux, "%s %s", cod, descrip);
    type tipo = Estab_createType(cod, descrip);
    insert_hashtable(info->bd->EstabelecimentoType, tipo);
    free(cod);
    free(descrip);
    return 1;
}

/*comando 'e' do EC*/
int newEstab(char* text,Info *info){
    char *aux, *cnpj, *tipoCod, *cep, *face, *num, *nome;
    type tipo, tipotemp;
    cnpj = (char*) calloc(55, sizeof(char));
    tipoCod = (char*) calloc(55, sizeof(char));
    cep = (char*) calloc(55, sizeof(char));
    face = (char*) calloc(55, sizeof(char));
    num = (char*) calloc(55, sizeof(char));
    nome = (char*) calloc(55, sizeof(char));
    aux = text; aux += 2;

    sscanf(aux, "%s %s %s %s %s %s", cnpj, tipoCod, cep, face, num, nome);
    tipotemp = Estab_createType(tipoCod, "");
    tipo = get_hashtable(info->bd->EstabelecimentoType, tipotemp);
    free(tipotemp);
    Estab estab = Estab_create(info, cnpj, tipo, cep, face, num, nome);
    insert_hashtable(info->bd->EstabHash, estab);
    insert_hashtable(info->bd->enderecoEstab, Estab_getEndereco(estab));
    free(cnpj);
    free(tipoCod);
    free(cep);
    free(face);
    free(num);
    free(nome);
    return 1;
}
