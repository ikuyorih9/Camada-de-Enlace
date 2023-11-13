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
 * Função que executa a camada de enlace transmissora, realizando os métodos de controle de erro e chamando a camada de comunicação.
*/
void CamadaEnlace::CamadaEnlaceDadosTransmissora(){
    //Realiza o controle de erro.
    controleErro(2); //O controle de erro escolhido foi o CRC.

    //Obtém o quadro e o tamanho localmente para facilitar a leitura.
    int * quadro = this->quadro;
    int tamanho = this->tamanho;

    //Envia dados para a camada de comunicação.
    CamadaDeTransmissao * camadaTransmissao = new CamadaDeTransmissao(quadro, tamanho); //Cria a camada de comunicação.
    camadaTransmissao->meioDeTransmissao();
}

/**
 * Retorna se o quadro tem um número par de bits 1.
 * @return TRUE se par, FALSE se ímpar.
*/
bool CamadaEnlace::retornaSePar(int * quadro, int tamanho){
    if(quadro == NULL)
        return false;

    bool par = false;
    
    //Conta a paridade do quadro.
    for(int i = 0; i < tamanho; i++){
        if(quadro[i])
            par = !par;
    }
    return par;
}

/**
 * Realiza o controle CRC (Cyclic Redudancy Check), dividindo o quadro e subtraindo o resto.
*/
void CamadaEnlace::controlaCRC(){
    int coeficientes [] = COEF_CRC;
    int * quadro = this->quadro;
    int tamanho = this->tamanho;

    int * resto = retornaRestoDivisao(quadro, tamanho, coeficientes, 32);
    imprimeArrayBits(resto, tamanho);
    for(int i = 0; i < tamanho; i++){
        quadro[i] ^= resto[i];
    }
}

/**
 * Adiciona o bit de paridade ao fim do quadro. O controle pode considerar o número par ou ímpar de bits '1' no quadro, dependendo do parâmetro.
 * @param controlePar variável booleana que faz o controle par (true) ou o controle ímpar (false).
*/
void CamadaEnlace::controlaParidadeTransmissao(bool controlePar){
    int tamanho = this->tamanho;

    int * novoQuadro = (int*) malloc(sizeof(int) * (tamanho + 1)); //Aloca memória para o novo quadro, com espaço para um bit a mais.
    memcpy(novoQuadro, this->quadro, sizeof(int) * tamanho); //Copia o quadro sem paridade para o quadro com paridade.

    if(controlePar)
        novoQuadro[tamanho] = (int) retornaSePar(this->quadro, tamanho); //Põe o bit de paridade (par) ao fim da mensagem.
    else
        novoQuadro[tamanho] = (int) !retornaSePar(this->quadro, tamanho); //Põe o bit de paridade (ímpar) ao fim da mensagem.

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
 * Retorna o quadro da camada de enlace.
 * @return Array binário do quadro da camada de enlace.
*/
int * CamadaEnlace::retornaQuadro(){
    return this->quadro;
}

/**
 * Retorna o tamanho do quadro da camada de enlace.
 * @return Tamanho do quadro da camada de enlace.
*/
int CamadaEnlace::retornaTamanho(){
    return this->tamanho;
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
void CamadaEnlace::controleErroTransmissao(int tipoControle){
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

/*---------------------------------
    CAMADA DE ENLACE RECEPTORA
----------------------------------*/

void CamadaEnlace::controleErroRecepcao(int tipoControle){
    switch (tipoControle){
        case 0:
            controlaParidadeRecepcao(true);
            break;
        case 1:
            controlaParidadeRecepcao(false);
            break;
        case 2:
            controlaCRC();
            break;
    }
}

/**
 * Recupera o quadro original através do controle de erro de paridade.
 * @param controlePar booleano que indica a paridade par ou ímpar.
*/
void CamadaEnlace::controlaParidadeRecepcao(bool controlePar){
    int tamanho = this->tamanho;

    int * novoQuadro = (int*) malloc(sizeof(int) * (tamanho - 1)); //Aloca memória para o novo quadro, sem o último bit de paridade.
    memcpy(novoQuadro, this->quadro, sizeof(int) * (tamanho - 1)); //Copia o quadro com paridade para o quadro com paridade.

    bool paridade = retornaSePar(novoQuadro, tamanho-1);
    if(this->quadro[tamanho - 1] != paridade)
        //ERRO

    free(this->quadro);
    this->quadro = novoQuadro;
    this->tamanho = tamanho - 1;
}