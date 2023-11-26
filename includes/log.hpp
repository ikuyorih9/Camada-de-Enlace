#ifndef __LOGS_H__
#define __LOGS_H__

using namespace std;

class Log{
    public:
        static void erroAlocacao(string nomeFuncao);
        static void erroArrayVazio(string nomeFuncao);
        static void erroQuadro(string texto);
        static void logInicioCamada(string nome, string mensagem);
        static void logInicioCamada(string nome, int * quadro, int tamanho);
        static void sublogCamada(string texto, int * quadro, int tamanho);
        static void logFimCamada(string nome);
};

#endif