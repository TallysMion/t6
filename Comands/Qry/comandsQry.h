#ifndef COMANDS_QRY_H
#define COMANDS_QRY_H
#include "../../Config/config.h"

    /*Reporta quadras e equipamentos dentro do retanguo*/
    void reportRec(char* text,Info* info);
    
    /*Reporta quadras e quipamentos dentro do circulo*/
    void reportCirc(char* text,Info* info);

    /*Remove as quadras dentro do retangulo*/
    void deleteQuadrasRec(char* text,Info* info);        

    /*Remove equipamentos dentro do retangulo*/
    void deleteUrbamEqRec(char* text,Info* info);

    /*Remove as quadras dentro do circulo*/
    void deleteQuadrasCirc(char* text,Info* info);

    /*Remove os equipamentos dentro do circulo*/
    void deleteUrbamEqCirc(char* text,Info* info);

    /*Muda a cor do item relacionado ao id/cep passado*/
    void colorChange(char* text,Info* info);

    /*informa as cordenadas e o ID do item passado, se for uma quadra, 
    retorna as cordenadas e id's de todos os equipamentos presentes nela*/
    void equipOnCepOrId(char* text,Info* info);

    /*encontra as radio-base mais proximas, e informa id's e distancia*/
    void closestRBase(char* text,Info* info);

    /*Finaliza os Processos de QRY e imprime o arquivo de saida */
    void closeQRY(Info* info);

    /*Imprime um relatorio dos moradores da quadra <m? 'cep'> */
    void whoIsHere(char* text, Info* info);

    /*Imprime um m? de todos as quadras inteiramente nessa area*/
    void whoIsInThisArea(char* text, Info* info);

    /*Imprime um relatorio da pessoa, incluindo a cordenada geografica, e imprime uma marcação no mapa*/
    void whoAreYou(char* text, Info* info);

    /*Imprime um relatorio do Estabelecimento, incluindo a cordenada geografica, e imprime uma marcação no mapa*/
    void whoAreYouEstab(char* text,Info* info);

    /*Mãe, no céu tem Pão? e Morreu...*/
    void bread(char* text, Info* info);

    /*Imprime um relatorio dos estabelecimentos existentes nessa quadra*/
    void whatHaveHere(char* text, Info* info);

    /*Imprime um relatorio dos estabelecimentos de um determinado tipo em uma area*/
    void whatHaveInThisArea(char* text, Info* info);

    /*Imprime um relatorio dos estabelecimentos existentes nessa quadra, ordenando os tipos*/
    void whatHaveHere_typeOrder(char* text, Info* info);

    /*Imprime um relatorio dos estabelecimentos existentes nessa area, ordenando os tipos*/
    void whatHaveInThisArea_typeOrder(char* text, Info* info);

    /*Marca um X no local, e faz uma linha entre o X e o hidrante mais proximo dele, 
    faz um relatorio sobre o hidrante e a distancia entre ele e o X*/
    void closestHidrant(char* text, Info* info);

    /*Faz uma linha entre a RadioB e o hidrante mais proximo dela, 
    faz um relatorio sobre a RadioB e o hidrante, incluindo a distancia entre eles*/
    void closestHidrantFromRB(char* text, Info* info);

    /*Fecha um estabelecimento comercial, e deleta todas as informações*/
    void closeEstab(char* text, Info* info);

    /*Uma pessoa ta de mudança, faz um relatorio no txt, e imprime uma linha no svg*/
    void mudancaPessoa(char* text, Info* info);

    /*Uma pessoa ta de mudança, faz um relatorio no txt, e imprime uma linha no svg*/
    void mudancaEstab(char* text, Info* info);

    /*Desapropria uma região*/
    void desapropriar(char* text, Info* info);

    /*Inclui a cordenada geografica de uma pessoa(cpf) no registrador(r)*/
    void pessoaToReg(char* text, Info* info);

    /*Inclui a cordenada geografica de um endereco no registrador(r)*/
    void enderecoToReg(char* text, Info* info);

    /*Inclui a cordenada geografica do equipamento urbano no registrador(r)*/
    void equipUrbanToReg(char* text, Info* info);

    /*Inclui a cordenada geografica no registrador(r)*/
    void cordToReg(char* text, Info* info);

    /*Inlclui no regA, o estab de 'tipo' mais proximo do regB*/
    void theClosestEstab(char* text, Info* info);

    /*Cria um Carro*/
    void create_Carro(char* text, Info* info);

    /*Remove um carro*/
    void remove_Carro(char* text, Info* info);

    //Detecta colisões de carros
    void detectColision(char* text, Info* info);

    //Rota simples
    void simpleRout(char* text, Info*info);

    //Rota com paradas
    void multRout(char* text, Info*info);

#endif