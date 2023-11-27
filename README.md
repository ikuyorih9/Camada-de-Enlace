# Camada-de-Enlace
Projeto implementado como segundo trabalho da disciplina Redes de Computadores (SSC0641), ministrada pelo professor Rodolfo Ipolito Meneguette.

## Hierarquia das camadas.

<p align="center">
    <img width=500 src="img/Figura - hierarquia camadas.png">
</p>

### X.1. Aplicação transmissora.

### X.2. Camada de aplicação transmissora.

### X.3. Camada de enlace de dados transmissora.

A **camada de enlace de dados transmissora** é chamada pela camada de aplicação transmissora. Ela começa realizando o *controle de erro para transmmissão* do quadro, que consiste na codificação do quadro original em um novo com bits anexados ao seu fim. A quantidade e o valor dos bits anexados depende do tipo de controle, que pode ser por ``paridade`` ou ``CRC``.

#### X.3.1. **Codificação da transmissão por ``paridade``.**

O controle da transmissão por paridade consiste em *adicionar um único bit ao final do quadro*, funcionando como um booleano. 

O bit de paridade, anexado ao final do quadro, depende do tipo de codificação (par ou ímpar) e da quantidade de 1's. A tabela abaixo mostra que a relação entre esses dois parâmetros equivale a uma lógica XOR.

| Codificação | Quantidade de '1's | Bit de paridade |
|:-----------:|:------------------:|:---------------:|
|  ímpar (0)  |      ímpar (0)     |        0        |
|  ímpar (0)  |       par (1)      |        1        |
|   par (1)   |      ímpar (0)     |        1        |
|   par (1)   |       par (1)      |        0        |

##### Tabela 1: tabela-verdade do controle de paridade para transmissão.

Dessa forma, o algorítmo de codificação da transmissão por paridade é dado pelo código abaixo.

```
void controlaParidadeTransmissao(bool controlePar){
    ALOCA MEMÓRIA PARA O QUADRO CODIFICADO.

    int tamanho = this->tamanho;
    int * quadro = new int[tamanho + 1];
    memcpy(quadro, this->quadro, sizeof(int) * tamanho);

    REALIZA A LÓGICA XOR PARA O BIT DE PARIDADE.

    quadro[tamanho] = (int)(controlePar ^ retornaSePar(this->quadro, tamanho));

    ATUALIZA O QUADRO COM O QUADRO CODIFICADO.

    delete [] this->quadro; //Libera memória alocada para o último quadro.
    this->quadro = quadro;
    this->tamanho = tamanho + 1;
}
```
##### Código 1: função de controle de paridade na transmissão.

Observe que o booleano `controlePar` corresponde ao "Codificação" da tabela, enquanto a função `retornaSePar()` obtém a informação da paridade de 1's.

#### X.3.2. **Codificação da transmissão por ``CRC``.**

O controle da transmissão por CRC consiste em transformar o valor do quadro em um valor divisível por um **polinômio gerador**. Como o quadro é binário, o polinômio gerador é convertido em um número binário considerando os seus coeficientes.

O polinômio gerador utilizado é escolhido conforme o padrão IEE 802.3, ou seja

> x<sup>31</sup> + x<sup>25</sup> + x<sup>22</sup> + x<sup>21</sup> + x<sup>15</sup> + x<sup>11</sup> + x<sup>10</sup> + x<sup>9</sup> + x<sup>7</sup> + x<sup>6</sup> + x<sup>4</sup> + x<sup>3</sup> + x<sup>1</sup> + x<sup>0</sup>

que, em binário se torna o número de 32 bits:

> 1000 0010 0110 0000 1000 1110 1101 1011

Para transformar o quadro em um número divisível por 1000 0010 0110 0000 1000 1110 1101 1011, é preciso:

1. Anexar 31 bits 0 ao final do quadro;
2. Realizar a divisão binária de módulo 2 (XOR) entre o quadro e o número 1000 0010 0110 0000 1000 1110 1101 1011;
3. Subtrair o quadro pelo resto da divisão.

Assim, o algorítimo dessa codificação se dá por

```
void controlaCRCTransmissao(){
    int coeficientes [] = COEF_CRC;

    ALOCA MEMÓRIA PARA O QUADRO CODIFICADO.

    int tamanho = this->tamanho + GRAU_COEF;
    int * quadro = new int[tamanho];
    
    ANEXA 31 BITS ZERO À DIREITA DO QUADRO.

    for(i = 0; i < this->tamanho; i++){
        quadro[i] = this->quadro[i];
    }
    for(; i<tamanho; i++){
        quadro[i] = 0;
    }
    
    REALIZA A DIVISÃO DE MÓDULO 2 E SUBTRAI O RESTO DO QUADRO (XOR).

    int * resto = retornaRestoDivisao(quadro, tamanho, coeficientes, 32);
    for(int i = 0; i < tamanho; i++){
        quadro[i] ^= resto[i];
    }

    ATUALIZA O QUADRO.

    delete [] resto; //Libera a memória do resto obtido.
    delete [] this->quadro; //Libera a memória do quadro original.

    this->quadro = quadro; //Atualiza o quadro com o quadro codificado.
    this->tamanho = tamanho; //Atualiza o tamanho do quadro.
}
```
##### Código 2: função de controle CRC na transmissão.


Por fim, a a camada de enlace de dados de transmissão chama o **meio de comunicação**.
### X.4. Meio de comunicação.

### X.5. Camada de enlace de dados receptora.


### X.6. Camada de aplicação receptora.


### X.7. Aplicação receptora.