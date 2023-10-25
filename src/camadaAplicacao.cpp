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


    cout << "QUADRO (" << tamanho << "): \n \t";
    for(int i = 0; i < tamanho; i++)
        cout << quadro[i];
    cout << endl;
    

    CamadaEnlace * camadaEnlace = new CamadaEnlace(quadro, tamanho);
    camadaEnlace->controleErro(0);
    
}