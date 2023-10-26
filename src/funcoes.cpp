#include <iostream>
#include <cstring>
#include <cstdlib>
#include <malloc.h>
#include <cmath>
#include "../includes/funcoes.hpp"

/**
 * Transforma uma string em um array de bits.
 * @param mensagem string para transformar em bits.
 * @return (int) array com os bits da mensagem.
*/
int * stringParaBits(string mensagem){
    int * bits = (int*) malloc(sizeof(int) * mensagem.size()*8);

    if(bits == NULL)
        return NULL;

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

long int bitsParaInt(int * bits, int tam){
    if(bits == NULL)
        return -1;
    
    long int valor = 0;
    for(int i = tam-1; i >=0; i--){
        valor += bits[i] * pow(2,i);
    }
    return valor;
}

/**
 * Imprime o array de bits para debug.
 * @param bits o array de bits a se imprimir.
 * @param tam o tamanho do array de bits.
*/
void imprimeArrayBits(int * bits, int tam){
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

    //Procura o índice do LSB.
    int inicio;
    for(inicio = 0; inicio < tamDividendo; inicio++){
        if(dividendo[inicio] == 1)
            break;
    }

    //Se o LSB do dividendo for 1, o subtrai com o divisor.
    if(dividendo[inicio] == 1){
        for(int i = inicio, j = 0; j < tamDivisor; i++, j++){
            dividendo[i] = dividendo[i]^divisor[j];
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
    int * resto = (int*) malloc(sizeof(int) * tamDividendo);
    if(resto == NULL)
        return NULL;

    for(int i = 0; i < tamDividendo; i++){
        resto[i] = dividendo[i];
    }

    divisaoBinaria(resto, divisor, tamDividendo, tamDivisor); //Realiza, recursivamente, a divisão binária.

    return resto;
}