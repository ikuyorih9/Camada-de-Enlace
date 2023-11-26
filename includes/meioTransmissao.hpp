#ifndef __MEIO_TRANSMISSAO_H__
#define __MEIO_TRANSMISSAO_H__

#define PORCENTAGEM_ERRO 0

class CamadaDeTransmissao{
    private:
        int * quadro;
        int tamanho;
    
    public:
        CamadaDeTransmissao(int * quadro, int tamanho);
        ~CamadaDeTransmissao();
        void meioDeTransmissao();
        int * retornaQuadro();
        int retornaTamanho();
};



#endif