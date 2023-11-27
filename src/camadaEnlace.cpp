#include <iostream>
#include <cstring>
#include "../includes/camadaEnlace.hpp"
#include "../includes/meioTransmissao.hpp"
#include "../includes/camadaAplicacao.hpp"
#include "../includes/funcoes.hpp"
#include "../includes/log.hpp"

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
 * Destrutor da classe CamadaEnlace.
*/
CamadaEnlace::~CamadaEnlace(){
    //Libera o quadro se houver memória alocada.
    if(this->quadro != NULL){
        delete []this->quadro;
        this->quadro = NULL;
    }
    
    //Tamanho com valor inválido.
    this->tamanho = -1;
}

/**
 * Retorna se o quadro tem um número par de bits 1.
 * @return TRUE se par, FALSE se ímpar.
*/
bool CamadaEnlace::retornaSePar(int * quadro, int tamanho){
    //Se o quadro enviado não está alocado, retorna FALSE.
    if(quadro == NULL){
        Log::erroArrayVazio("retornaSePar");
        return false;
    }

    bool par = true;
    
    //Conta a paridade do quadro.
    for(int i = 0; i < tamanho; i++){
        if(quadro[i])
            par = !par;
    }
    return par;
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

/*------------------------------------
    CAMADA DE ENLACE TRANSMISSORA
------------------------------------*/

/**
 * Camada de enlace transmissora. Chama a função do controle de erro para transmissão e chama a próxima camada.
*/
void CamadaEnlace::camadaEnlaceDadosTransmissora(){
    Log::logInicioCamada("CAMADA DE ENLACE TRANSMISSORA", this->quadro, this->tamanho);

    //Realiza o controle de erro.
    controleErroTransmissao(controle);

    //Obtém o quadro e o tamanho.
    int * quadro = this->quadro;
    int tamanho = this->tamanho;

    //Envia dados para a camada de comunicação.
    CamadaDeTransmissao * camadaTransmissao = new CamadaDeTransmissao(quadro, tamanho); //Cria a camada de comunicação.
    camadaTransmissao->meioDeTransmissao(); //Chama a camada de comunicação.

    Log::logFimCamada("CAMADA DE ENLACE TRANSMISSORA");
    delete camadaTransmissao;
    
}

/**
 * Cria artifícios para o controle de erro no quadro.
 * @param tipoControle escolhe o tipo de controle de erro. Se for 0, controla com a paridade par; se 1, controla com a paridade ímpar; se 2, controla com CRC.
*/
void CamadaEnlace::controleErroTransmissao(int tipoControle){
    cout << "\t- Controle de erro: ";
    switch (tipoControle){
        case 0:
            cout << "paridade par" << endl;
            controlaParidadeTransmissao(true);
            break;
        case 1:
            cout << "paridade impar" << endl;
            controlaParidadeTransmissao(false);
            break;
        case 2:
            cout << "CRC" << endl;
            controlaCRCTransmissao();
            break;
    }
}

/**
 * Realiza o controle CRC (Cyclic Redudancy Check), dividindo o quadro e subtraindo o resto.
*/
void CamadaEnlace::controlaCRCTransmissao(){
    int coeficientes [] = COEF_CRC; //Obtém os coeficientes do polinomio gerador, segundo IEE 802.3.

    //Obtém o tamanho e o quadro codificado pelo método CRC.
    int tamanho = this->tamanho + GRAU_COEF;
    int * quadro = new int[tamanho];
    
    //Cria o novo quadro, anexando 'tamanho' zeros à direita do quadro original.
    int i;
    for(i = 0; i < this->tamanho; i++){
        quadro[i] = this->quadro[i];
    }
    for(; i<tamanho; i++){
        quadro[i] = 0;
    }

    Log::sublogCamada("Anexo de zeros CRC transmissao", quadro, tamanho);
    
    //Obtém o resto da divisão binário do novo quadro pelo polinomio gerador.
    int * resto = retornaRestoDivisao(quadro, tamanho, coeficientes, 32);

    //Realiza a subtração de módulo 2 entre o novo quadro e o resto.
    for(int i = 0; i < tamanho; i++){
        quadro[i] ^= resto[i];
    }

    Log::sublogCamada("Novo quadro CRC transmissao", quadro, tamanho);

    delete [] resto; //Libera a memória do resto obtido.
    delete [] this->quadro; //Libera a memória do quadro original.

    this->quadro = quadro; //Atualiza o quadro com o quadro codificado.
    this->tamanho = tamanho; //Atualiza o tamanho do quadro.
}

/**
 * Adiciona o bit de paridade ao fim do quadro. O controle pode considerar o número par ou ímpar de bits '1' no quadro, dependendo do parâmetro.
 * @param controlePar variável booleana que faz o controle par (true) ou o controle ímpar (false).
*/
void CamadaEnlace::controlaParidadeTransmissao(bool controlePar){
    int tamanho = this->tamanho;

    int * quadro = new int[tamanho + 1]; //Aloca memória para o novo quadro, com espaço para um bit a mais.
    memcpy(quadro, this->quadro, sizeof(int) * tamanho); //Copia o quadro sem paridade para o quadro com paridade.

    //Se o quadro tiver um número par de '1's, ele deve ter o último bit 0 na paridade par e 1 na paridade ímpar. Vice-versa.
    quadro[tamanho] = (int)(controlePar ^ retornaSePar(this->quadro, tamanho));

    delete [] this->quadro; //Libera memória alocada para o último quadro.

    //Atualiza os atributos do objeto.
    this->quadro = quadro;
    this->tamanho = tamanho + 1;

    Log::sublogCamada("Novo quadro", this->quadro, this->tamanho);

}

/*---------------------------------
    CAMADA DE ENLACE RECEPTORA
----------------------------------*/

void CamadaEnlace::camadaEnlaceDadosReceptora(){
    Log::logInicioCamada("CAMADA DE ENLACE RECEPTORA", this->quadro, this->tamanho);

    //Realiza o controle de erro.
    controleErroRecepcao(controle);

    //Obtém o quadro e o tamanho.
    int * quadro = this->quadro;
    int tamanho = this->tamanho;

    //Chama a próxima camada.
    camadaAplicacaoReceptora(this->quadro, this->tamanho);

    Log::logFimCamada("CAMADA DE ENLACE RECEPTORA");
}

/**
 * Controle de erro da camada de enlace receptora. Obtém o quadro codificado através do controle de erro da transmissão e verifica se ocorreu um erro no processo.
 * @param tipoControle escolhe o tipo de controle de erro. Se for 0, controla com a paridade par; se 1, controla com a paridade ímpar; se 2, controla com CRC.
*/
void CamadaEnlace::controleErroRecepcao(int tipoControle){
    cout << "\t- Controle de erro: ";
    switch (tipoControle){
        case 0:
            cout << "paridade par" << endl;
            controlaParidadeRecepcao(true);
            break;
        case 1:
            cout << "paridade impar" << endl;
            controlaParidadeRecepcao(false);
            break;
        case 2:
            cout << "CRC" << endl;
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

    int * quadro = new int[tamanho-1]; //Aloca memória para o quadro original, sem o último bit de paridade.
    memcpy(quadro, this->quadro, sizeof(int) * (tamanho - 1)); //Copia o quadro com paridade para o quadro com paridade.

    bool paridade = retornaSePar(quadro, tamanho-1); //Retorna se a quantidade de 1's é par (true) ou ímpar (false).

    bool bitParidade = (bool) this->quadro[tamanho - 1]; //Obtém o último bit do quadro, indicador de paridade.

    //Verifica se o quadro está com erro.
    bool erroQuadro = (bool)(controlePar ^ paridade ^ bitParidade);
    if(erroQuadro){
        Log::erroQuadro("BIT DE PARIDADE INCORRETO.");
        exit(-1);
    }

    delete [] this->quadro;
    this->quadro = quadro;
    this->tamanho = tamanho - 1;
}

/**
 * Recupera o quadro original através do controle de erro CRC.
*/
void CamadaEnlace::controlaCRCRecepcao(){
    int coeficientes [] = COEF_CRC; //Obtém os coeficientes do polinomio gerador, segundo IEE 802.3.

    //Obtém o resto da divisão binária de módulo 2 do quadro pelo polinômio gerador.
    int * resto = retornaRestoDivisao(this->quadro, this->tamanho, coeficientes, 32);
    
    Log::sublogCamada("Resto CRC recepcao", resto, this->tamanho);
    
    //Verifica o ERRO caso o resto não seja zero.
    if(!arrayBinarioEstaZerado(resto, this->tamanho)){
        Log::erroQuadro("RESTO DA DIVISAO NAO FOI ZERO.");
        exit(-1);
    }

    delete [] resto; //Libera memória alocada para o resto da divisão.

    //Obtém o tamanho e o quadro decodificado.
    int tamanho = this->tamanho - GRAU_COEF;
    int * quadro = new (nothrow) int[tamanho];
    memcpy(quadro, this->quadro, sizeof(int) * tamanho);

    Log::sublogCamada("Quadro original CRC recepcao", quadro, tamanho);

    delete [] this->quadro; //Libera o quadro salvo.

    this->quadro = quadro; //Atualiza o quadro da camada com o quadro decodificado.
    this->tamanho = tamanho; //Atualiza o tamanho do quadro.
}