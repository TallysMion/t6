#ifndef ESTABELECIMENTO
#define ESTABELECIMENTO

typedef void* type;
typedef void* Estab;

//Cria um estabelecimento fantasma
Estab* createEstabCord(double x,double y);

//criar Estabelecimento
Estab Estab_create(void* info, char* cnpj, type tipo, char* cep, char* face, char* num, char* nome);

//criar Tipo de Estabelecimento
type Estab_createType(char* cod, char* Info);

//Mudança - Retorna Linha em SVG da mudança
void* Estab_changeEndereco(void* info, Estab estab,  char* cep, char* face, char* num);

//retorna o endereco do estabelecimento
void* Estab_getEndereco(void* estab);

//free - Limpa a memoria
void Estab_Free(Estab estab);

//compare - função de comparaçao de estabelecimentos
int Estab_compare(Estab estab1, Estab estab2, int dimension);

//hashCode - retorna o codigo do estabelecimento
int Estab_HashCode(Estab estab, int modulo);

//Comparador para hash
int Estab_HashCompare(void* estab, void* cnpj);

//Comparador para enderecos
int Endereco_compare(void* end1, void* end2, int dimension);

int Estab_Type_HashCode(void*  tip,int modulo);

int Estab_Type_HashCompare(void* tip, void* cod);

//retorna a struct da pessoa que mora aqui, se não for um endereco de pessoa, retorna NULL
void* Estab_getEstabEndereco(void* endereco);

int Estab_Ende_HashCode(void* endereco, int modulo);

int Estab_Ende_HashCompare(void* Endereco1, void* Endereco2);

double* Estab_getCordGeo(void* estab);

char* Estab_relatorio(void* estab);

void* Estab_IdentEndereco(char* cep);

char* Estab_getTipoCod(void* estab);

char* Estab_Tipo(Estab* estab);

char* Estab_Name(Estab* estab);

#endif
