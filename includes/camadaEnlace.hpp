#ifndef __CAMADA_ENLACE_H__
#define __CAMADA_ENLACE_H__

#define polinomioCRC 2187366107 //0x82608EDB IEE 802.3 polynomial standart.
#define COEF_CRC {1,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,1,1,0,1,1,0,1,1,0,1,1}
//1000 0010 0110 0000 1000 1110 1101 1011 - x31 + x25 + x22 + x21 + x15 + x11 + x10 + x9 + x7 + x6 + x4 + x3 + x1 + x0

using namespace std;

class CamadaEnlace{
    private:
        int * quadro;
        int tamanho;

        bool retornaSePar();
        void controlaParidade(bool controlePar);
        void controlaCRC();
    public:
        CamadaEnlace(int * quadro, int tamanho);
        void configuraCamadaEnlace(int * quadro, int tamanho);
        void controleErro(int tipoControle);
        
};

#endif