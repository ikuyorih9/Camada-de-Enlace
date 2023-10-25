#include <iostream>
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