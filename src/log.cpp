#include <iostream>
#include <cstring>
#include "../includes/log.hpp"
#include "../includes/funcoes.hpp"

#define ERRO_ALOCACAO "Erro ao alocar memoria."
#define ERRO_ARRAY_VAZIO "O array recebido pela funcao está vazio."

using namespace std;

/**
 * Imprime mensagem de erro de alocação de memória.
 * @param retorno valor do retorno da função.
 * @return 
*/
void Log::erroAlocacao(string nomeFuncao){
    cout << endl;
    cout << "\t\t(" << nomeFuncao << "): " << ERRO_ALOCACAO << endl;
}

void Log::erroArrayVazio(string nomeFuncao){
    cout << endl;
    cout << "\t\t(" << nomeFuncao << "): " << ERRO_ARRAY_VAZIO << endl;
}

void Log::erroQuadro(string texto){
    cout << endl;
    cout << "QUADRO COM ERRO: " << texto << endl;
}

void Log::logInicioCamada(string nome, string mensagem){
    cout << endl;
    cout << nome << ": " << mensagem << endl;
}

void Log::logInicioCamada(string nome, int * quadro, int tamanho){
    cout << endl;
    cout << nome << ": ";    
    imprimeArrayBits(quadro, tamanho);
}

void Log::sublogCamada(string texto, int * quadro, int tamanho){
    cout << "\t- " << texto << ": ";
    imprimeArrayBits(quadro, tamanho);
}

void Log::logFimCamada(string nome){
    cout << "*** Fim da "<< nome << " ***" << endl;
}