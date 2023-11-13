#include <iostream>
#include "../includes/camadaAplicacao.hpp"
#include "../includes/camadaEnlace.hpp"
#include "../includes/meioTransmissao.hpp"
#include "../includes/funcoes.hpp"

void camadaAplicacao(){
    string mensagem;
    cin >> mensagem;
    fflush(stdin);
    camadaAplicacaoTransmissora(mensagem);
}

void camadaAplicacaoTransmissora(string mensagem){
    int * quadro = stringParaBits(mensagem); //Salva a mensagem em binário no quadro.
    int tamanho = mensagem.length()*8; //Salva o tamanho do quadro.
    
    imprimeArrayBits(quadro, tamanho);

    //Envia informações para a próxima camada: a camada de enlace transmissora.
    CamadaEnlace * camadaEnlace = new CamadaEnlace(quadro, tamanho); //Cria uma camada de enlace com o quadro e o tamanho.
    camadaEnlace->CamadaEnlaceDadosTransmissora();
}