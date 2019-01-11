#ifndef PESSOA_H
#define PESSOA_H

typedef void* Pessoa;
typedef void* Endereco;

//criar Estabelecimento
Pessoa Pessoa_create(char* cpf, char* nome, char* sobrenome, char* sexo, char* nasc);

//criar Morador
Endereco Pessoa_SetEndereco(Pessoa pes, char* cep, char* face, char* num, char* comp);

//Retorna o endereco
Endereco Pessoa_getEndereco(Pessoa pes);

//free - Limpa a memoria
void Pessoa_Free(Pessoa pes);

//compare - função de comparaçao de Pessoaelecimentos
int Pessoa_compare(Pessoa pes1, Pessoa pes2, int dimension);

//hashCode - retorna o codigo do Pessoaelecimento
int Pessoa_HashCode(Pessoa pes, int modulo);

//Comparador para hashtable
int Pessoa_HashCompare(void* pes, void* cpf);

//retorna a struct da pessoa que mora aqui, se não for um endereco de pessoa, retorna NULL
void* Pessoa_getPessoaEndereco(void* endereco);

int Pessoa_Ende_HashCode(void* endereco, int modulo);
int Pessoa_Ende_HashCompare(void* Endereco1, void* Endereco2);
void* Pessoa_IdentEndereco(char* cep);
char* Pessoa_relatorio(void* pessoa);
double* Pessoa_getCordGeo(void* pessoa, void* info);

#endif
