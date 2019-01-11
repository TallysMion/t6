#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Config/config.h"
#include "../../Pessoa/pessoa.h"

/*Cria uma Pessoa*/
int createPessoa(char* text, Info* info){
    char *aux, *cpf, *nome, *sobrenome, *sexo, *nascimento;
    aux = text; aux += 2;
    cpf        = (char*) calloc(55, sizeof(char));
    nome       = (char*) calloc(55, sizeof(char));
    sobrenome  = (char*) calloc(55, sizeof(char));
    sexo       = (char*) calloc(55, sizeof(char));
    nascimento = (char*) calloc(55, sizeof(char));
    sscanf(aux, "%s %s %s %s %s", cpf, nome, sobrenome, sexo, nascimento);
    Pessoa ps = Pessoa_create(cpf, nome, sobrenome, sexo, nascimento);
    insert_hashtable(info->bd->PessoaCepHash, ps);   
    free(cpf);
    free(nome);
    free(sobrenome);
    free(sexo);
    free(nascimento);
    return 1;
}

/*Informa quem mora em um determinado endereco*/
int setEndereco(char* text, Info* info){
    char *aux, *pessoaCod, *cep, *face, *num, *comp;
    Pessoa pessoa, pessoatemp;
    pessoaCod   = (char*) calloc(55, sizeof(char));
    cep         = (char*) calloc(55, sizeof(char));
    face        = (char*) calloc(55, sizeof(char));
    num         = (char*) calloc(55, sizeof(char));
    comp        = (char*) calloc(55, sizeof(char));
    aux = text; aux += 2;
    sscanf(aux, "%s %s %s %s %s", pessoaCod, cep, face, num, comp);
    pessoatemp = Pessoa_create(pessoaCod, "", "", "", "");
    pessoa = get_hashtable(info->bd->PessoaCepHash, pessoatemp);
    Pessoa_Free(pessoatemp);
    Endereco end = Pessoa_SetEndereco(pessoa, cep, face, num, comp);
    insert_hashtable(info->bd->enderecoPessoa, end);
    free(pessoaCod);
    free(cep);
    free(face);
    free(num);
    free(comp);
    return 1;
}