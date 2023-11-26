#ifndef __FUNCOES_H__
#define __FUNCOES_H__

using namespace std;

int * stringParaBits(string mensagem);
string bitsParaString(int * bits, int tamanho);
void imprimeArrayBits(int * bits, int tam);
int retornaTamanhoUtilBits(int * bits, int tamanhoBits);
void divisaoBinaria(int * dividendo, int * divisor, int tamDividendo, int tamDivisor);
int * retornaRestoDivisao(int * dividendo, int tamDividendo, int * divisor, int tamDivisor);
bool arrayBinarioEstaZerado(int * array, int tamanho);

#endif