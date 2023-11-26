#ifndef __CAMADA_ENLACE_H__
#define __CAMADA_ENLACE_H__

#define polinomioCRC 2187366107 //0x82608EDB IEE 802.3 polynomial standart.
#define COEF_CRC {1,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,1,1,0,1,1,0,1,1,0,1,1}
#define GRAU_COEF 31
//1000 0010 0110 0000 1000 1110 1101 1011 -> x31 + x25 + x22 + x21 + x15 + x11 + x10 + x9 + x7 + x6 + x4 + x3 + x1 + x0

using namespace std;

class CamadaEnlace{
    private:
        int * quadro;
        int tamanho;

        bool retornaSePar(int * quadro, int tamanho);
        //Transmissão.
        void controlaParidadeTransmissao(bool controlePar);
        void controlaCRCTransmissao();
        //Recepção.
        void controlaParidadeRecepcao(bool controlePar);
        void controlaCRCRecepcao();

    public:
        const static int controle = 2;
        CamadaEnlace(int * quadro, int tamanho);
        void CamadaEnlaceDadosTransmissora();
        void configuraCamadaEnlace(int * quadro, int tamanho);
        int * retornaQuadro();
        int retornaTamanho();

        //Transmissão.
        void controleErroTransmissao(int tipoControle);

        //Recepção.
        void controleErroRecepcao(int tipoControle);   
};

#endif