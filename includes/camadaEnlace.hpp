#ifndef __CAMADA_ENLACE_H__
#define __CAMADA_ENLACE_H__

#define polinomioCRC 2187366107 //0x82608EDB IEE 802.3 polynomial standart.
#define COEF_CRC {1,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,1,1,0,1,1,0,1,1,0,1,1,1}
#define GRAU_COEF 32
//100000100110000010001110110110111 -> x32 + x26 + x23 + x22 + x16 + x12 + x11 + x10 + x8 + x7 + x5 + x4 + x2 + x1 + x0

#define CONTROLE_PAR 0
#define CONTROLE_IMPAR 1
#define CONTROLE_CRC 2

using namespace std;

class CamadaEnlace{
    private:
        int **ptr_quadro;
        int * quadro;
        int tamanho;

        bool retornaSePar(int *quadro, int tamanho);
        //Transmissão.
        void controlaParidadeTransmissao(bool controlePar);
        void controlaCRCTransmissao();
        //Recepção.
        void controlaParidadeRecepcao(bool controlePar);
        void controlaCRCRecepcao();

    public:
        const static int controle = CONTROLE_CRC;

        CamadaEnlace(int **ptr_quadro, int tamanho);
        ~CamadaEnlace();
        
        void configuraCamadaEnlace(int * quadro, int tamanho);
        int * retornaQuadro();
        int retornaTamanho();

        //Transmissão.
        void camadaEnlaceDadosTransmissora();
        void controleErroTransmissao(int tipoControle);

        //Recepção.
        void camadaEnlaceDadosReceptora();
        void controleErroRecepcao(int tipoControle);   
};

#endif