#include <iostream>
#include "../includes/camadaAplicacao.hpp"
#include "../includes/camadaEnlace.hpp"
#include "../includes/funcoes.hpp"

void camadaAplicacao(){
    string mensagem;
    cin >> mensagem;
    fflush(stdin);
    camadaAplicacaoTransmissora(mensagem);
}

void camadaAplicacaoTransmissora(string mensagem){
    int * quadro = stringParaBits(mensagem);
    int tamanho = mensagem.length()*8;
    imprimeArrayBits(quadro, tamanho);
    CamadaEnlace * camadaEnlace = new CamadaEnlace(quadro, tamanho);
    camadaEnlace->controleErro(2);
    
}