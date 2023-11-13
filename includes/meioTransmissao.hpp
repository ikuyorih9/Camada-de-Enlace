#ifndef __MEIO_TRANSMISSAO_H__
#define __MEIO_TRANSMISSAO_H__

class CamadaDeTransmissao{
    private:
        int * quadro;
        int tamanho;
    
    public:
        CamadaDeTransmissao(int * quadro, int tamanho);
        void meioDeTransmissao();
        int * retornaQuadro();
        int retornaTamanho();
};



#endif