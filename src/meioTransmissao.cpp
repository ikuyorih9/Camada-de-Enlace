#include <iostream>
#include <ctime>
#include "../includes/meioTransmissao.hpp"

/**
 * Construtor da classe CamadaDeTransmissao.
 * @param quadro array com os bits dos quadros.
 * @param tamanho tamanho do array.
*/
CamadaDeTransmissao::CamadaDeTransmissao(int * quadro, int tamanho){
    this->quadro = quadro;
    this->tamanho = tamanho;
}

/**
 * Muda bits do quadro conforme uma porcentagem de erros.
*/
void CamadaDeTransmissao::meioDeTransmissao(){
    int porcentagemErros = 0;

    int * fluxoBrutoBytesPontoA = this->quadro; //Recebe o quadro original.
    int * fluxoBrutoBytesPontoB = (int *) malloc(sizeof(int) * this->tamanho); //Aloca espaço para um novo quadro, o fluxo B.

    //Para cada bit do quadro.
    for(int i = 0; i < tamanho; i++){
        //Se a porcentagem aleatória for maior que a porcentagem de erros definida.
        if((rand()%100 + 1) >= porcentagemErros)
            fluxoBrutoBytesPontoB[i] = fluxoBrutoBytesPontoA[i]; //Copia o bit do quadro pro fluxo B.
        else
            fluxoBrutoBytesPontoB[i] = !fluxoBrutoBytesPontoA[i]; //Copia o inverso do bit do quadro pro fluxo B.
    }

    free(this->quadro);
    this->quadro = fluxoBrutoBytesPontoB; //Salva o novo quadro como o fluxo B

    //Chama camada de enlace receptora.
}

/**
 * Retorna o quadro da camada de enlace.
 * @return Array binário do quadro da camada de enlace.
*/
int * CamadaDeTransmissao::retornaQuadro(){
    return this->quadro;
}

/**
 * Retorna o tamanho do quadro da camada de enlace.
 * @return Tamanho do quadro da camada de enlace.
*/
int CamadaDeTransmissao::retornaTamanho(){
    return this->tamanho;
}
