#ifndef __CAMADA_ENLACE_H__
#define __CAMADA_ENLACE_H__

using namespace std;

class CamadaEnlace{
    private:
        int * quadro;
        int tamanho;

        bool retornaSePar();
        void controlaParidade(bool controlePar);
    public:
        CamadaEnlace(int * quadro, int tamanho);
        void configuraCamadaEnlace(int * quadro, int tamanho);
        void controleErro(int tipoControle);
        
};

#endif