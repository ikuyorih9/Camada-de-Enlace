#include <iostream>
#include <ctime>
#include "../includes/meioTransmissao.hpp"
#include "../includes/camadaAplicacao.hpp"
#include "../includes/camadaEnlace.hpp"
#include "../includes/funcoes.hpp"
#include "../includes/log.hpp"

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
 * Destrutor da classe CamadaDeTransmissao.
*/
CamadaDeTransmissao::~CamadaDeTransmissao(){
    //Libera o quadro se houver memória alocada.
    if(this->quadro != NULL){
        delete [] this->quadro;
        this->quadro = NULL;
    }
    
    //Tamanho com valor inválido.
    this->tamanho = -1;
}

/**
 * Muda bits do quadro conforme uma porcentagem de erros.
*/
void CamadaDeTransmissao::meioDeTransmissao(){
    int porcentagemErros = PORCENTAGEM_ERRO;

    int * fluxoBrutoBytesPontoA = this->quadro; //Recebe o quadro original.
    int * fluxoBrutoBytesPontoB = new int[this->tamanho]; //Aloca espaço para um novo quadro, o fluxo B.

    //Para cada bit do quadro.
    for(int i = 0; i < tamanho; i++){
        int porcentagemAleatoria = rand()%100 + 1;

        //Se a porcentagem aleatória for maior que a porcentagem de erros definida.
        if(porcentagemAleatoria >= porcentagemErros)
            fluxoBrutoBytesPontoB[i] = fluxoBrutoBytesPontoA[i]; //Copia o bit do quadro pro fluxo B.
        else
            fluxoBrutoBytesPontoB[i] = !fluxoBrutoBytesPontoA[i]; //Copia o inverso do bit do quadro pro fluxo B.
    }

    this->quadro = fluxoBrutoBytesPontoB; //Salva o novo quadro como o fluxo B

    Log::logInicioCamada("APLICACAO COMUNICACAO", this->quadro, this->tamanho);

    //Chama camada de enlace receptora.
    CamadaEnlace * camadaEnlaceReceptora = new CamadaEnlace(&(this->quadro), this->tamanho); //Cria a camada de enlace receptora.
    camadaEnlaceReceptora->camadaEnlaceDadosReceptora(); //Chama a camada de enlace receptora.

    Log::logFimCamada("APLICACAO COMUNICACAO");
    delete camadaEnlaceReceptora; //Libera memória da camada de enlace receptora.    
    
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
