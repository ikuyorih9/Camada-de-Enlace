#include <iostream>
#include "../includes/camadaAplicacao.hpp"
#include "../includes/camadaEnlace.hpp"
#include "../includes/meioTransmissao.hpp"
#include "../includes/funcoes.hpp"
#include "../includes/log.hpp"

/**
 * Aplicação Transmissora. Recebe a mensagem do usuário.
*/
void aplicacaoTransmissora(){
    //Recebe a mensagem da entrada padrão.
    string mensagem;
    cin >> mensagem;
    fflush(stdin);

    Log::logInicioCamada("APLICACAO TRANSMISSORA", mensagem);

    //Chama a camada de aplicação transmissora.
    camadaAplicacaoTransmissora(mensagem);

    Log::logFimCamada("APLICACAO TRANSMISSORA");
}

/**
 * Camada de aplicação transmissora. Recebe uma mensagem e a enquadra.
 * @param mensagem mensagem recebida pelo usuário.
*/
void camadaAplicacaoTransmissora(string mensagem){
    int * quadro = stringParaBits(mensagem); //Obtém a mensagem de bytes para bits.
    int tamanho = mensagem.length()*8; //Obtém o tamanho do quadro.

    Log::logInicioCamada("CAMADA DE APLICACAO TRANSMISSORA", quadro, tamanho);

    //Envia informações para a próxima camada: a camada de enlace transmissora.
    CamadaEnlace * camadaEnlaceTransmissora = new CamadaEnlace(&quadro, tamanho); //Cria uma camada de enlace com o quadro e o tamanho.
    camadaEnlaceTransmissora->camadaEnlaceDadosTransmissora();

    Log::logFimCamada("CAMADA DE APLICACAO TRANSMISSORA");
    delete camadaEnlaceTransmissora;
}

/**
 * Camada de aplicação receptora. Recebe o quadro das camadas inferiores e o transforma em uma mensagem para o usuário.
 * @param quadro array binário com os bits da mensagem.
 * @param tamanho tamanho do array binário.
*/
void camadaAplicacaoReceptora(int * quadro, int tamanho){
    Log::logInicioCamada("CAMADA DE APLICACAO RECEPTORA", quadro, tamanho);

    string mensagem = bitsParaString(quadro, tamanho);

    aplicacaoReceptora(mensagem);

    Log::logFimCamada("CAMADA DE APLICACAO RECEPTORA");
}

/**
 * Aplicação receptora. Envia mensagem ao usuário.
 * @param mensagem mensagem recebida pela camada inferior.
*/
void aplicacaoReceptora(string mensagem){
    Log::logInicioCamada("APLICACAO RECEPTORA", mensagem);
    Log::logFimCamada("APLICACAO RECEPTORA");
}