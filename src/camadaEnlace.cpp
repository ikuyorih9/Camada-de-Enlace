#include <iostream>
#include <cstring>
#include "../includes/camadaEnlace.hpp"
#include "../includes/funcoes.hpp"


/**
 * Construtor da classe CamadaEnlace.
 * @param quadro array com os bits dos quadros.
 * @param tamanho tamanho do array.
*/
CamadaEnlace::CamadaEnlace(int * quadro, int tamanho){
    this->quadro = quadro;
    this->tamanho = tamanho;
}

/**
 * Retorna se o quadro tem um número par de bits 1.
 * @return TRUE se par, FALSE se ímpar.
*/
bool CamadaEnlace::retornaSePar(){
    if(quadro == NULL)
        return false;

    bool par = false;

    int * quadro = this->quadro;
    int tamanho = this->tamanho;
    
    //Conta a paridade do quadro.
    for(int i = 0; i < tamanho; i++){
        if(quadro[i])
            par = !par;
    }
    return par;
}

void CamadaEnlace::controlaCRC(){
    int coeficientes [] = COEF_CRC;
    int * quadro = this->quadro;
    int tamanho = this->tamanho;

    int * resto = retornaRestoDivisao(quadro, tamanho, coeficientes, 32);
    imprimeArrayBits(resto, tamanho);
    for(int i = 0; i < tamanho; i++){
        quadro[i] ^= resto[i];
    }
    imprimeArrayBits(quadro, tamanho);
    
}

/**
 * Adiciona o bit de paridade ao fim do quadro. O controle pode considerar o número par ou ímpar de bits '1' no quadro, dependendo do parâmetro.
 * @param controlePar variável booleana que faz o controle par (true) ou o controle ímpar (false).
*/
void CamadaEnlace::controlaParidade(bool controlePar){
    int tamanho = this->tamanho;

    int * novoQuadro = (int*) malloc(sizeof(int) * (tamanho + 1)); //Aloca memória para o novo quadro, com espaço para um bit a mais.
    memcpy(novoQuadro, this->quadro, sizeof(int) * tamanho); //Copia o quadro sem paridade para o quadro com paridade.

    if(controlePar)
        novoQuadro[tamanho] = (int) retornaSePar(); //Põe o bit de paridade (par) ao fim da mensagem.
    else
        novoQuadro[tamanho] = (int) !retornaSePar(); //Põe o bit de paridade (ímpar) ao fim da mensagem.

    free(this->quadro); //Libera memória alocada para o último quadro.

    //Atualiza os atributos do objeto.
    this->quadro = novoQuadro;
    this->tamanho = tamanho + 1;

    cout << "NOVO QUADRO (" << tamanho + 1 << "): \n \t";
    for(int i = 0; i < tamanho+1; i++)
        cout << novoQuadro[i];
    cout << endl;

}

/**
 * Configura os valores privados da camada de enlace.
 * @param quadro array de bits que guardam o quadro.
 * @param tamanho tamanho do array de bits que guardam o quadro.
 * 
*/
void CamadaEnlace::configuraCamadaEnlace(int * quadro, int tamanho){
    this->quadro = quadro;
    this->tamanho = tamanho;
}

/**
 * Cria artifícios para o controle de erro no quadro.
 * @param tipoControle escolhe o tipo de controle de erro. Se for 0, controla com a paridade par; se 1, controla com a paridade ímpar; se 2, controla com CRC.
*/
void CamadaEnlace::controleErro(int tipoControle){
    switch (tipoControle){
    case 0:
        controlaParidade(true);
        break;
    case 1:
        controlaParidade(false);
        break;
    case 2:
        controlaCRC();
        break;
    }
}
