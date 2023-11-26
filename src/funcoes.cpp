#include <iostream>
#include <cstring>
#include <cstdlib>
#include <malloc.h>
#include <cmath>
#include "../includes/funcoes.hpp"
#include "../includes/log.hpp"

using namespace std;

/**
 * Transforma uma string em um array de bits.
 * @param mensagem string para transformar em bits.
 * @return (int) array com os bits da mensagem.
*/
int * stringParaBits(string mensagem){
    int * bits = new (nothrow) int[mensagem.size()*8];
    if(bits == NULL){
        Log::erroAlocacao("stringParaBits");
        return NULL;
    }

    int * teste = bits;
    for(auto &c: mensagem){
        for(int i = 7; i >=0; i--){
            int mascara = pow(2,i);
            int bit = (c & mascara)/mascara;
            *teste = bit;
            teste++;
        }  
    }
    
    return bits;
}

/**
 * Converte um array de bits em string.
 * @param bits array de bits para converter.
 * @param tamanho tamanho do array de bits.
 * @return Retorna o array de bits em string.
 * @note O tamanho precisa ser um múltiplo de 8 para que seja possível a conversão para bytes.
*/
string bitsParaString(int * bits, int tamanho){
    if(bits == NULL){
        Log::erroArrayVazio("bitsParaString");
        return "";
    }
    
    int tamanhoMensagem = tamanho/8;
    char mensagem[tamanhoMensagem + 1];
    for(int i = 0; i < tamanhoMensagem; i++){
        int b = 0;
        for(int j = i*8; j < i*8 + 8; j++){
            b <<= 1;
            b += bits[j];
        }
        mensagem[i] = (char)b;
        mensagem[i+1] = '\0';
    }

    return (string) mensagem;

}

/**
 * Imprime o array de bits para debug.
 * @param bits o array de bits a se imprimir.
 * @param tam o tamanho do array de bits.
*/
void imprimeArrayBits(int * bits, int tam){
    if(bits == NULL){
        Log::erroArrayVazio("imprimeArrayBits");
        return;
    }
        
    for(int i = 0; i < tam; i++)
        cout << bits[i];
    cout << endl;
}

/**
 * Retorna o tamanho útil de uma sequência de bits com vários 0s à direita.
 * @param bits array com a sequência de bits.
 * @param tamanhoBits o tamanho real da sequência.
 * @return tamanho útil da sequência, sem os zeros à direita.
*/
int retornaTamanhoUtilBits(int * bits, int tamanhoBits){
    if(bits == NULL)
        return -1;

    int tam = 1;
    bool contaTamanho = false;
    for(int i = 0; i < tamanhoBits; i++){
        if(!contaTamanho){
            if(bits[i] == 1)
                contaTamanho = true;
        }
        else
            tam++;
    }
    return tam;
}


/**
 * Função recursiva que realiza uma iteração da divisão binária.
 * @param dividendo um array que será o dividendo da divisão.
 * @param divisor um array que será o divisor da divisão.
 * @param tamDividendo tamanho do dividendo.
 * @param tamDivisor tamanho do divisor.
*/
void divisaoBinaria(int * dividendo, int * divisor, int tamDividendo, int tamDivisor){
    //Verifica se pode-se dividir: o tamanho do dividendo deve ser maior ou igual ao divisor.
    int tamUtilDividendo = retornaTamanhoUtilBits(dividendo, tamDividendo);
    int tamUtilDivisor = retornaTamanhoUtilBits(divisor, tamDivisor);
    
    if(tamUtilDividendo < tamUtilDivisor)
        return;

    //Procura o índice do HSB.
    int inicio;
    for(inicio = 0; inicio < tamDividendo; inicio++){
        if(dividendo[inicio] == 1)
            break;
    }

    //Se o HSB do dividendo for 1, o subtrai com o divisor.
    if(dividendo[inicio] == 1){
        for(int i = inicio, j = 0; j < tamDivisor; i++, j++){
            //cout << "\t\t\t\tXOR: " << dividendo[i] << "^" << divisor[j];
            dividendo[i] = dividendo[i]^divisor[j];
            //cout << " = " << dividendo[i] << endl;
        }
    }

    divisaoBinaria(dividendo, divisor, tamDividendo, tamDivisor);
}

/**
 * Realiza a divisão binária e retorna o resto da divisão.
 * @param dividendo array de bits que representa o dividendo.
 * @param tamDividendo tamanho do array do dividendo.
 * @param divisor array de bits que representa o divisor.
 * @param tamDivisor tamanho do array do divisor.
 * @return Array de inteiros com o resto da divisão.
 * 
 * @note o array (int *) retornado é alocado dinamicamente, é preciso desalocá-lo.
*/
int * retornaRestoDivisao(int * dividendo, int tamDividendo, int * divisor, int tamDivisor){
    //Aloca dinamicamente o resto e verifica se foi alocado corretamente.
    int * resto = new (nothrow) int[tamDividendo];
    if(resto == NULL){
        Log::erroAlocacao("retornaRestoDivisao");
        return NULL;
    }

    for(int i = 0; i < tamDividendo; i++){
        resto[i] = dividendo[i];
    }

    divisaoBinaria(resto, divisor, tamDividendo, tamDivisor); //Realiza, recursivamente, a divisão binária.

    return resto;
}

/**
 * Verifica se o array de números binários está zerado.
 * @param array array de números binários.
 * @param tamanho tamanho do array.
 * @return Retorna TRUE se está zerado e FALSE se não está.
 * @note Caso o array não esteja alocado, o retorno é FALSE.
*/
bool arrayBinarioEstaZerado(int * array, int tamanho){
    if(array == NULL){
        Log::erroArrayVazio("arrayBinarioEstaZerado");
        return false;
    }

    for(int i = 0; i < tamanho; i++){
        if(array[i] == 1)
            return false;
    }

    return true;
}