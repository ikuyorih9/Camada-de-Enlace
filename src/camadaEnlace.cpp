#include <iostream>
#include <cstring>
#include "../includes/camadaEnlace.hpp"
#include "../includes/meioTransmissao.hpp"
#include "../includes/camadaAplicacao.hpp"
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
    controleErroTransmissao(controle); //O controle de erro escolhido foi o de paridade par.

    //Obtém o quadro e o tamanho localmente para facilitar a leitura.
    int * quadro = this->quadro;
    int tamanho = this->tamanho;

    
    printf("ENLACE TRANSMISSORA - QUADRO:");
    imprimeArrayBits(quadro, tamanho);

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

    bool par = true;
    
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
void CamadaEnlace::controlaCRCTransmissao(){
    int coeficientes [] = COEF_CRC;

    int tamanho = this->tamanho + GRAU_COEF;
    int * quadro = (int*) malloc(sizeof(int) * tamanho);
    
    int i;
    for(i = 0; i < this->tamanho; i++){
        quadro[i] = this->quadro[i];
    }
    for(; i<tamanho; i++){
        quadro[i] = 0;
    }

    cout << "\tNovo quadro CRC transmissao: ";
    imprimeArrayBits(quadro, tamanho);
    

    int * resto = retornaRestoDivisao(quadro, tamanho, coeficientes, 32);

    for(int i = 0; i < tamanho; i++){
        quadro[i] ^= resto[i];
    }
    cout << "Controle CRC Transmissao: ";
    imprimeArrayBits(quadro, tamanho);

    free(resto);
    free(this->quadro);
    this->quadro = quadro;
    this->tamanho = tamanho;
}

/**
 * Adiciona o bit de paridade ao fim do quadro. O controle pode considerar o número par ou ímpar de bits '1' no quadro, dependendo do parâmetro.
 * @param controlePar variável booleana que faz o controle par (true) ou o controle ímpar (false).
*/
void CamadaEnlace::controlaParidadeTransmissao(bool controlePar){
    int tamanho = this->tamanho;

    int * novoQuadro = (int*) malloc(sizeof(int) * (tamanho + 1)); //Aloca memória para o novo quadro, com espaço para um bit a mais.
    memcpy(novoQuadro, this->quadro, sizeof(int) * tamanho); //Copia o quadro sem paridade para o quadro com paridade.

    //Se o quadro tiver um número par de '1's, ele deve ter o último bit 0 na paridade par e 1 na paridade ímpar. Vice-versa.
    if(controlePar)
        novoQuadro[tamanho] = (int) !retornaSePar(this->quadro, tamanho); //Põe o bit de paridade (par) ao fim da mensagem.
    else
        novoQuadro[tamanho] = (int) retornaSePar(this->quadro, tamanho); //Põe o bit de paridade (ímpar) ao fim da mensagem.

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
            controlaParidadeTransmissao(true);
            break;
        case 1:
            controlaParidadeTransmissao(false);
            break;
        case 2:
            controlaCRCTransmissao();
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
            controlaCRCRecepcao();
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

    printf("ENLACE RECEPTORA - QUADRO: ");
    imprimeArrayBits(novoQuadro, tamanho-1);

    bool paridade = retornaSePar(novoQuadro, tamanho-1); //Retorna se a quantidade de 1's é par (true) ou ímpar (false).

    bool bitParidade = (bool) this->quadro[tamanho - 1]; //Obtém o último bit do quadro, indicador de paridade.

    //controlePar   paridade  bitParidade   Erro
    //0(ímpar)      0(ímpar)  0(ímpar)      0             
    //0(ímpar)      0(ímpar)  1(par)        1
    //0(ímpar)      1(par)    0(ímpar)      1
    //0(ímpar)      1(par)    1(par)        0 
    //1(par)        0(ímpar)  0(par)        1             
    //1(par)        0(ímpar)  1(ímpar)      0
    //1(par)        1(par)    0(par)        0
    //1(par)        1(par)    1(ímpar)      1  

    bool erroQuadro = (bool)(controlePar ^ paridade ^ bitParidade);

    cout << "controlePar: " << controlePar << endl;
    cout << "paridade do quadro: " << paridade << endl;
    cout << "bit de paridade: " << (bool)this->quadro[tamanho-1] << endl;

    if(erroQuadro){
        cout << "Erro na mensagem!" << endl;
        exit(-1);
    }

    free(this->quadro);
    this->quadro = novoQuadro;
    this->tamanho = tamanho - 1;
}

void CamadaEnlace::controlaCRCRecepcao(){
    int coeficientes [] = COEF_CRC;

    int * resto = retornaRestoDivisao(this->quadro, this->tamanho, coeficientes, 32);
    cout << "\tResto CRC recepcao: ";
    imprimeArrayBits(resto, this->tamanho);
    if(!arrayBinarioEstaZerado(resto, this->tamanho)){
        cout << "ERRO NO ARRAY CRC!" << endl;
        exit(-1);
    }

    free(resto);

    int tamanho = this->tamanho - GRAU_COEF;
    int * quadro = (int*) malloc(sizeof(int) * tamanho);
    memcpy(quadro, this->quadro, sizeof(int) * tamanho);

    cout << "\tNovo quadro CRC recepcao ";
    imprimeArrayBits(quadro,tamanho);

    free(this->quadro);
    this->quadro = quadro;
    this->tamanho = tamanho;

    camadaAplicacaoReceptora(this->quadro, this->tamanho);
}